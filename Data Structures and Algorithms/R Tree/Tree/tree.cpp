#include "tree.hpp"

rect::rect() : xmin(0), ymin(0), xmax(0), ymax(0) {}
rect::rect(double x1, double y1, double x2, double y2)
    : xmin(std::min(x1, x2)),
      ymin(std::min(y1, y2)),
      xmax(std::max(x1, x2)),
      ymax(std::max(y1, y2)) {}

double rect::area() const {
    double w = std::max(0.0, xmax - xmin);
    double h = std::max(0.0, ymax - ymin);
    
    return w * h;
}

bool rect::contains(const rect &r) const {
    return xmin <= r.xmin && ymin <= r.ymin && xmax >= r.xmax && ymax >= r.ymax;
}

bool rect::intersects(const rect &r) const {
    return !(r.xmin > xmax || r.xmax < xmin || r.ymin > ymax || r.ymax < ymin);
}

rect rect::combine(const rect &a, const rect &b) {
    return rect(std::min(a.xmin, b.xmin),
                std::min(a.ymin, b.ymin),
                std::max(a.xmax, b.xmax),
                std::max(a.ymax, b.ymax));
}

double rect::enlargement_needed(const rect &r) const {
    rect comb = combine(*this, r);
    return comb.area() - this->area();
}

double rect::min_dist_point(const std::pair<double,double>& p) const {
    double dx = 0.0;
    if (p.first < xmin) {
        dx = xmin - p.first;
    }
    else if (p.first > xmax) {
        dx = p.first - xmax;
    }
    
    double dy = 0.0;
    if (p.second < ymin) {
        dy = ymin - p.second;
    }
    else if (p.second > ymax) {
        dy = p.second - ymax;
    }
    
    return std::sqrt(dx*dx + dy*dy);
}

template<typename ValueType>
RTree<ValueType>::RTree(int max_entries)
    : max_entries_(max_entries),
      min_entries_(std::max(2, (int)std::ceil(max_entries * 0.4))) {
    nodes_.reserve(1024);
    root_ = new_node(true);
}

template<typename ValueType>
void RTree<ValueType>::insert(const rect &r, const ValueType &v) {
    int leaf = choose_leaf(root_, r);
    nodes_[leaf].entries.emplace_back(r, v);
    if ((int)nodes_[leaf].entries.size() > max_entries_) {
        split_node(leaf);
    }
    
    adjust_tree(leaf);
}

template<typename ValueType>
void RTree<ValueType>::bulk_load(const std::vector<std::pair<rect, ValueType>>& items) {
    clear_internal();
    if (items.empty()) {
        return;
    }

    std::vector<std::pair<rect, ValueType>> arr = items;

    std::sort(arr.begin(), arr.end(), [](auto const& a, auto const& b){
        double ax = (a.first.xmin + a.first.xmax) * 0.5;
        double bx = (b.first.xmin + b.first.xmax) * 0.5;
        
        return ax < bx;
    });

    int n = (int)arr.size();
    int leaf_count = (n + max_entries_ - 1) / max_entries_;
    int s = std::max(1, (int)std::ceil(std::sqrt((double)leaf_count)));
    int per_strip = (n + s - 1) / s;

    std::vector<int> leaf_nodes;
    leaf_nodes.reserve(leaf_count);

    for (int strip = 0; strip < s; ++strip) {
        int start = strip * per_strip;
        if (start >= n) {
            break;
        }

        int end = std::min(n, start + per_strip);
        std::sort(arr.begin() + start, arr.begin() + end, [](auto const& a, auto const& b){
            double ay = (a.first.ymin + a.first.ymax) * 0.5;
            double by = (b.first.ymin + b.first.ymax) * 0.5;
            
            return ay < by;
        });

        for (int i = start; i < end; i += max_entries_) {
            int j = std::min(end, i + max_entries_);
            int idx = new_node(true);
            for (int k = i; k < j; ++k) {
                nodes_[idx].entries.emplace_back(arr[k].first, arr[k].second);
            }
            
            leaf_nodes.push_back(idx);
        }
    }

    std::vector<int> cur = leaf_nodes;
    while (cur.size() > 1) {
        std::vector<int> next;
        for (size_t i = 0; i < cur.size(); i += max_entries_) {
            size_t j = std::min(cur.size(), i + max_entries_);
            int idx = new_node(false);
            for (size_t k = i; k < j; ++k) {
                rect m = node_mbr((int)cur[k]);
                nodes_[idx].entries.emplace_back(m, (int)cur[k]);
                nodes_[cur[k]].parent = idx;
            }
            
            next.push_back(idx);
        }
        
        cur.swap(next);
    }

    if (!cur.empty()) {
        root_ = cur[0];
        nodes_[root_].parent = -1;
    }
    else {
        root_ = new_node(true);
    }
}

template<typename ValueType>
bool RTree<ValueType>::remove(const rect &r, const ValueType &v) {
    int leaf = find_leaf(root_, r, v);
    if (leaf == -1) {
        return false;
    }

    auto &ents = nodes_[leaf].entries;
    auto it = std::find_if(ents.begin(), ents.end(), [&](const entry &e){
        return e.child == -1 && e.val == v
               && e.mbr.xmin == r.xmin && e.mbr.ymin == r.ymin
               && e.mbr.xmax == r.xmax && e.mbr.ymax == r.ymax;
    });
    if (it == ents.end()) {
        return false;
    }
    
    ents.erase(it);
    condense_tree(leaf);
    if (nodes_[root_].entries.empty()) {
        if (!nodes_[root_].leaf && !nodes_[root_].entries.empty()) {
            root_ = nodes_[root_].entries[0].child;
            nodes_[root_].parent = -1;
        } 
        else {
            clear_internal();
        }
    }

    return true;
}

template<typename ValueType>
std::vector<ValueType> RTree<ValueType>::range_search(const rect &query) const {
    std::vector<ValueType> out;
    if (nodes_.empty()) {
        return out;
    }
    
    std::stack<int> st;
    st.push(root_);
    while (!st.empty()) {
        int idx = st.top(); st.pop();
        const node &nd = nodes_[idx];
        for (const entry &e : nd.entries) {
            if (!e.mbr.intersects(query)) {
                continue;
            }
            
            if (nd.leaf) {
                out.push_back(e.val);
            }
            else {
                st.push(e.child);
            }
        }
    }

    return out;
}

template<typename ValueType>
std::vector<ValueType> RTree<ValueType>::knn(const std::pair<double,double>& p, int k) const {
    struct item { 
        int idx;
        double dist; 
    };
    struct cmp { 
        bool operator()(item const& a, item const& b) const { 
            return a.dist > b.dist; 
        } 
    };

    std::priority_queue<item, std::vector<item>, cmp> pq;
    std::vector<ValueType> result;
    if (nodes_.empty()) {
        return result;
    }
    
    pq.push({root_, 0.0});
    while (!pq.empty() && (int)result.size() < k) {
        item it = pq.top(); pq.pop();
        const node &nd = nodes_[it.idx];
        if (nd.leaf) {
            std::vector<std::pair<double,ValueType>> local;
            local.reserve(nd.entries.size());
            for (const entry &e : nd.entries) {
                double d = e.mbr.min_dist_point(p);
                local.emplace_back(d, e.val);
            }

            std::sort(local.begin(), local.end(), [](auto const& a, auto const& b){ return a.first < b.first; });
            for (auto const& pr : local) {
                if ((int)result.size() >= k) {
                    break;
                }
                
                result.push_back(pr.second);
            }
        } 
        else {
            for (const entry &e : nd.entries) {
                double d = e.mbr.min_dist_point(p);
                pq.push({e.child, d});
            }
        }
    }

    return result;
}

template<typename ValueType>
std::vector<ValueType> RTree<ValueType>::point_search(const rect &r) const {
    std::vector<ValueType> out;
    if (nodes_.empty()) {
        return out;
    }
    
    std::stack<int> st;
    st.push(root_);
    while (!st.empty()) {
        int idx = st.top(); st.pop();
        const node &nd = nodes_[idx];
        for (const entry &e : nd.entries) {
            if (nd.leaf) {
                if (e.child == -1 && e.mbr.xmin==r.xmin && e.mbr.ymin==r.ymin && e.mbr.xmax==r.xmax && e.mbr.ymax==r.ymax) {
                    out.push_back(e.val);
                }
            } 
            else {
                if (e.mbr.intersects(r)) {
                    st.push(e.child);
                }
            }
        }
    }

    return out;
}

template<typename ValueType>
void RTree<ValueType>::print_tree() const {
    std::cout << "RTree dump (root=" << root_ << "):\n";
    print_node(root_, 0);
}

template<typename ValueType>
void RTree<ValueType>::clear() {
    clear_internal();
    root_ = new_node(true);
}

template<typename ValueType>
RTree<ValueType>::entry::entry() : mbr(), val(), child(-1) {}
template<typename ValueType>
RTree<ValueType>::entry::entry(const rect &r, const ValueType &v) : mbr(r), val(v), child(-1) {}
template<typename ValueType>
RTree<ValueType>::entry::entry(const rect &r, int child_idx) : mbr(r), val(), child(child_idx) {}

template<typename ValueType>
RTree<ValueType>::node::node(bool leaf_) : leaf(leaf_), parent(-1) {}

template<typename ValueType>
int RTree<ValueType>::new_node(bool leaf) {
    nodes_.emplace_back(leaf);
    nodes_.back().parent = -1;
   
    return static_cast<int>(nodes_.size()) - 1;
}

template<typename ValueType>
void RTree<ValueType>::clear_internal() {
    nodes_.clear();
    root_ = -1;
}

template<typename ValueType>
rect RTree<ValueType>::node_mbr(int node_idx) const {
    const node &nd = nodes_[node_idx];
    if (nd.entries.empty()) {
        return rect();
    }
    
    rect r = nd.entries[0].mbr;
    for (size_t i = 1; i < nd.entries.size(); ++i) {
        r = rect::combine(r, nd.entries[i].mbr);
    }
    
    return r;
}

template<typename ValueType>
int RTree<ValueType>::choose_leaf(int node_idx, const rect &r) {
    node &nd = nodes_[node_idx];
    if (nd.leaf) {
        return node_idx;
    }

    double best_enl = std::numeric_limits<double>::infinity();
    double best_area = std::numeric_limits<double>::infinity();
    int best_child = -1;

    for (const entry &e : nd.entries) {
        double enl = e.mbr.enlargement_needed(r);
        double area = e.mbr.area();
        if (enl < best_enl || (enl == best_enl && area < best_area)) {
            best_enl = enl;
            best_area = area;
            best_child = e.child;
        }
    }

    return choose_leaf(best_child, r);
}

template<typename ValueType>
void RTree<ValueType>::adjust_tree(int node_idx) {
    while (node_idx != -1) {
        int parent = nodes_[node_idx].parent;
        if (parent == -1) {
            break;
        }
        
        for (entry &e : nodes_[parent].entries) {
            if (e.child == node_idx) {
                e.mbr = node_mbr(node_idx);
                break;
            }
        }
        
        if ((int)nodes_[parent].entries.size() > max_entries_) {
            split_node(parent);
        }
        
        node_idx = parent;
    }
    
    if ((int)nodes_[root_].entries.size() > max_entries_) {
        split_node(root_);
    }
}

template<typename ValueType>
void RTree<ValueType>::split_node(int node_idx) {
    node &nd = nodes_[node_idx];
    int N = static_cast<int>(nd.entries.size());
    if (N <= 2) {
        return;
    }

    int seed1 = 0, seed2 = 1;
    double worst = -1.0;
    for (int i = 0; i < N; ++i) {
        for (int j = i + 1; j < N; ++j) {
            rect comb = rect::combine(nd.entries[i].mbr, nd.entries[j].mbr);
            double d = comb.area() - nd.entries[i].mbr.area() - nd.entries[j].mbr.area();
            if (d > worst) {
                worst = d;
                seed1 = i;
                seed2 = j;
            }
        }
    }

    int new_idx = new_node(nd.leaf);
    nodes_[new_idx].parent = nd.parent;
    std::vector<bool> assigned(N, false);
    std::vector<entry> group_a;
    std::vector<entry> group_b;
    group_a.push_back(nd.entries[seed1]); 
    assigned[seed1] = true;
    if (seed2 != seed1) { 
        group_b.push_back(nd.entries[seed2]); 
        assigned[seed2] = true; 
    }

    while (true) {
        int remaining = 0;
        for (int t = 0; t < N; ++t) if (!assigned[t]) ++remaining;
        if (remaining == 0) {
            break;
        }
        if (static_cast<int>(group_a.size()) + remaining == min_entries_) {
            for (int t = 0; t < N; ++t) {
                if (!assigned[t]) { 
                    group_a.push_back(nd.entries[t]);
                    assigned[t] = true;
                }
            }

            break;
        }
        if (static_cast<int>(group_b.size()) + remaining == min_entries_) {
            for (int t = 0; t < N; ++t) {
                if (!assigned[t]) { 
                    group_b.push_back(nd.entries[t]); 
                    assigned[t] = true; 
                }
            }
            
            break;
        }

        rect mbr_a = group_a[0].mbr; 
        for (size_t ii = 1; ii < group_a.size(); ++ii) {
            mbr_a = rect::combine(mbr_a, group_a[ii].mbr);
        }
        
        rect mbr_b = group_b[0].mbr; 
        for (size_t ii = 1; ii < group_b.size(); ++ii) {
            mbr_b = rect::combine(mbr_b, group_b[ii].mbr);
        }

        double best_diff = -std::numeric_limits<double>::infinity();
        int best_idx = -1;
        bool assign_to_a = false;

        for (int i = 0; i < N; ++i) if (!assigned[i]) {
            double enl_a = rect::combine(mbr_a, nd.entries[i].mbr).area() - mbr_a.area();
            double enl_b = rect::combine(mbr_b, nd.entries[i].mbr).area() - mbr_b.area();
            double diff = std::fabs(enl_a - enl_b);
            if (diff > best_diff) {
                best_diff = diff;
                best_idx = i;
                assign_to_a = (enl_a < enl_b) || (enl_a == enl_b && mbr_a.area() < mbr_b.area());
            }
        }

        if (best_idx == -1) {
            break;
        }

        if (assign_to_a) { 
            group_a.push_back(nd.entries[best_idx]);
            assigned[best_idx] = true; 
        }
        else { 
            group_b.push_back(nd.entries[best_idx]);
            assigned[best_idx] = true; 
        }
    }

    nd.entries = std::move(group_a);
    nodes_[new_idx].entries = std::move(group_b);

    if (!nd.leaf) {
        for (auto &e : nodes_[new_idx].entries) {
            nodes_[e.child].parent = new_idx;
        }
        
        for (auto &e : nd.entries) {
            nodes_[e.child].parent = node_idx;
        }
    }

    if (nd.parent == -1) {
        int new_root = new_node(false);
        nodes_[new_root].entries.emplace_back(node_mbr(node_idx), node_idx);
        nodes_[new_root].entries.emplace_back(node_mbr(new_idx), new_idx);
        nodes_[node_idx].parent = new_root;
        nodes_[new_idx].parent = new_root;
        root_ = new_root;
    } 
    else {
        int p = nd.parent;
        nodes_[p].entries.emplace_back(node_mbr(new_idx), new_idx);
        nodes_[new_idx].parent = p;
        for (auto &e : nodes_[p].entries) {
            if (e.child == node_idx) { 
                e.mbr = node_mbr(node_idx);
                break; 
            }
        }

        if (static_cast<int>(nodes_[p].entries.size()) > max_entries_) {
            split_node(p);
        }
    }
}

template<typename ValueType>
int RTree<ValueType>::find_leaf(int start, const rect &r, const ValueType &v) const {
    std::stack<int> st;
    st.push(start);
    while (!st.empty()) {
        int idx = st.top(); st.pop();
        const node &nd = nodes_[idx];
        if (nd.leaf) {
            for (const entry &e : nd.entries) {
                if (e.child == -1 && e.val == v
                    && e.mbr.xmin==r.xmin && e.mbr.ymin==r.ymin
                    && e.mbr.xmax==r.xmax && e.mbr.ymax==r.ymax) {
                    return idx;
                }
            }
        } 
        else {
            for (const entry &e : nd.entries) {
                if (e.mbr.intersects(r)) st.push(e.child);
            }
        }
    }
    
    return -1;
}

template<typename ValueType>
void RTree<ValueType>::condense_tree(int leaf_idx) {
    std::vector<int> eliminated;
    int n = leaf_idx;
    while (n != -1) {
        node &nd = nodes_[n];
        int p = nd.parent;
        if (static_cast<int>(nd.entries.size()) < min_entries_ && n != root_) {
            if (p != -1) {
                auto &pe = nodes_[p].entries;
                pe.erase(std::remove_if(pe.begin(), pe.end(), [&](const entry &e){ return e.child == n; }), pe.end());
                eliminated.push_back(n);
            }
        } 
        else {
            if (p != -1) {
                for (entry &e : nodes_[p].entries) {
                    if (e.child == n) { 
                        e.mbr = node_mbr(n);
                        break;
                    }
                }
            }
        }

        n = nodes_[n].parent;
    }

    for (int idx : eliminated) {
        node &nd = nodes_[idx];
        if (nd.leaf) {
            for (const entry &e : nd.entries)  {
                insert(e.mbr, e.val);
            }
        } 
        else {
            for (const entry &e : nd.entries) {
                collect_and_reinsert(e.child);
            }
        }

        nodes_[idx].entries.clear();
    }
}

template<typename ValueType>
void RTree<ValueType>::collect_and_reinsert(int node_idx) {
    node &nd = nodes_[node_idx];
    if (nd.leaf) {
        for (const entry &e : nd.entries) {
            insert(e.mbr, e.val);
        }
    } 
    else {
        for (const entry &e : nd.entries) {
            collect_and_reinsert(e.child);
        }
    }
}

template<typename ValueType>
void RTree<ValueType>::print_node(int idx, int depth) const {
    const node &n = nodes_[idx];
    std::cout << std::string(depth*2, ' ') << "Node["<<idx<<"] leaf="<<n.leaf<<" parent="<<n.parent<<" entries="<<n.entries.size()<<"\n";
    for (const entry &e : n.entries) {
        std::cout << std::string(depth*2, ' ') << "  rect=("<<e.mbr.xmin<<","<<e.mbr.ymin<<")-("<<e.mbr.xmax<<","<<e.mbr.ymax<<")";
        if (n.leaf) {
            std::cout << " val=" << e.val << "\n";
        }
        else {
            std::cout << " child=" << e.child << "\n";
        }
    }

    if (!n.leaf) {
        for (const entry &e : n.entries) {
            print_node(e.child, depth+1);
        }
    }
}