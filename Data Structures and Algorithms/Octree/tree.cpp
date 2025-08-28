#include "tree.hpp"
#include <sstream>
#include <cmath>
#include <algorithm>
#include <limits>

bool AABB::contains(const Vec3& p) const {
    return std::abs(p.x - center.x) <= half_size &&
           std::abs(p.y - center.y) <= half_size &&
           std::abs(p.z - center.z) <= half_size;
}

bool AABB::intersects(const AABB& other) const {
    return std::abs(center.x - other.center.x) <= (half_size + other.half_size) &&
           std::abs(center.y - other.center.y) <= (half_size + other.half_size) &&
           std::abs(center.z - other.center.z) <= (half_size + other.half_size);
}

node::node(const Vec3& center, float half_size, int depth)
    : boundary_{center, half_size}, depth_{depth}, is_leaf_(true) {}

octree::octree(const Vec3& min, const Vec3& max, int max_depth, int max_objects)
    : max_depth_(max_depth), max_objects_(max_objects) {
    Vec3 center = {
        (min.x + max.x) / 2,
        (min.y + max.y) / 2,
        (min.z + max.z) / 2
    };
    
    float half_size = std::max({max.x - min.x, max.y - min.y, max.z - min.z}) / 2;
    root_ = std::make_unique<node>(center, half_size, 0);
}

void octree::insert_object(const Object& obj, node* n) {
    if (!n) { 
        n = root_.get();
    }
    if (!n->boundary_.contains(obj.position)) {
        return;
    }
    if (n->is_leaf_ && (n->objects_.size() < max_objects_ || n->depth_ >= max_depth_)) {
        n->objects_.push_back(obj);
        return;
    }
    if (n->is_leaf_) {
        subdivide(n);
    }

    for (auto& child : n->children_) {
        insert_object(obj, child.get());
    }
}

void octree::batch_insert(const std::vector<Object>& objs) {
    for (const auto& obj : objs) 
        insert_object(obj);
}

void octree::subdivide(node* n) {
    float hs = n->boundary_.half_size / 2.0f;
    const Vec3& c = n->boundary_.center;

    int d = n->depth_ + 1;
    for (int i = 0; i < 8; ++i) {
        Vec3 offset = {
            hs * ((i & 1) ? 1 : -1),
            hs * ((i & 2) ? 1 : -1),
            hs * ((i & 4) ? 1 : -1)
        };
        
        Vec3 new_center = {
            c.x + offset.x,
            c.y + offset.y,
            c.z + offset.z
        };
        
        n->children_[i] = std::make_unique<node>(new_center, hs, d);
    }

    for (const auto& obj : n->objects_) {
        for (auto& child : n->children_) {
            if (child->boundary_.contains(obj.position)) {
                child->objects_.push_back(obj);
                break;
            }
        }
    }

    n->objects_.clear();
    n->is_leaf_ = false;
}

void octree::query_range(const AABB& range, std::vector<Object>& result, node* n) const {
    if (!n) {
        n = root_.get();
    }
    if (!n->boundary_.intersects(range)) {
        return;
    }

    if (n->is_leaf_) {
        for (const auto& obj : n->objects_) {
            if (range.contains(obj.position)) result.push_back(obj);
        }
    } 
    else {
        for (const auto& child : n->children_) {
            query_range(range, result, child.get());
        }
    }
}

bool octree::is_in_bounds(const Vec3& point, node* n) const {
    if (!n) {
        n = root_.get();
    }
    
    return n->boundary_.contains(point);
}

void octree::clear() {
    root_.reset();
}

int octree::get_depth(node* n) const {
    if (!n) {
        n = root_.get();
    }
    if (n->is_leaf_) {
        return n->depth_;
    }
    int max_child_depth = n->depth_;
    for (const auto& child : n->children_) {
        max_child_depth = std::max(max_child_depth, get_depth(child.get()));
    }
    
    return max_child_depth;
}

void octree::traverse(const std::function<void(node*)>& callback, node* n) const {
    if (!n) {
        n = root_.get();
    }
    
    callback(n);
    if (!n->is_leaf_) {
        for (const auto& child : n->children_) {
            traverse(callback, child.get());
        }
    }
}

void octree::get_all_objects(std::vector<Object>& result, node* n) const {
    if (!n) {
        n = root_.get();
    }
    if (n->is_leaf_) {
        result.insert(result.end(), n->objects_.begin(), n->objects_.end());
    } 
    else {
        for (const auto& child : n->children_) {
            get_all_objects(result, child.get());
        }
    }
}

void octree::remove_object(const Object& obj, node* n) {
    if (!n) {
        n = root_.get();
    }
    if (!n->boundary_.contains(obj.position)) {
        return;
    }
    
    if (n->is_leaf_) {
        auto& objs = n->objects_;
        objs.erase(std::remove(objs.begin(), objs.end(), obj), objs.end());
    } 
    else {
        for (auto& child : n->children_) {
            remove_object(obj, child.get());
        }
    }
}

void octree::update_object(const Object& obj, const Vec3& new_pos, node* n) {
    remove_object(obj, n);
    Object updated = obj;
    updated.position = new_pos;
    insert_object(updated, n);
}

void octree::merge(node* n) {
    if (!n) n = root_.get();
    if (n->is_leaf_) return;
    bool can_merge = true;
    int total = 0;
    for (const auto& child : n->children_) {
        if (!child->is_leaf_) {
            can_merge = false;
            break;
        }
    
        total += child->objects_.size();
    }
    
    if (can_merge && total <= max_objects_) {
        for (auto& child : n->children_) {
            n->objects_.insert(n->objects_.end(), child->objects_.begin(), child->objects_.end());
            child.reset();
        }
    
        n->is_leaf_ = true;
    } 
    else {
        for (auto& child : n->children_) {
            merge(child.get());
        }
    }
}

void octree::balance() {
    merge();
}

void octree::find_collisions(node* n, std::vector<std::pair<Object, Object>>& collisions) const {
    if (!n) {
        n = root_.get();
    }
    if (n->is_leaf_) {
        const auto& objs = n->objects_;
        for (size_t i = 0; i < objs.size(); ++i) {
            for (size_t j = i + 1; j < objs.size(); ++j) {
                if (objs[i].position == objs[j].position)
                    collisions.emplace_back(objs[i], objs[j]);
            }
        }
    } 
    else {
        for (const auto& child : n->children_) {
            find_collisions(child.get(), collisions);
        }
    }
}

std::string octree::serialize(node* n) const {
    if (!n) {
        n = root_.get();
    }
    
    std::stringstream ss;
    ss << n->depth_ << "," << (n->is_leaf_ ? 1 : 0) << ","
       << n->boundary_.center.x << "," << n->boundary_.center.y << "," << n->boundary_.center.z << ","
       << n->boundary_.half_size << "," << n->objects_.size();
    for (const auto& obj : n->objects_) {
        ss << "," << obj.position.x << "," << obj.position.y << "," << obj.position.z << "," << obj.id;
    }
    
    if (!n->is_leaf_) {
        for (const auto& child : n->children_) {
            ss << ";" << serialize(child.get());
        }
    }
    
    return ss.str();
}

void octree::deserialize(const std::string& data) {
    std::stringstream ss(data);
    std::vector<std::string> nodes;
    std::string node_data;
    while (std::getline(ss, node_data, ';')) {
        nodes.push_back(node_data);
    }

    root_.reset();
    if (nodes.empty()) {
        return;
    }

    auto parse_node = [](const std::string& node_str) -> std::unique_ptr<node> {
        std::stringstream ns(node_str);
        std::string item;
        std::vector<std::string> items;
        while (std::getline(ns, item, ',')) {
            items.push_back(item);
        }
        
        if (items.size() < 7) {
            return nullptr;
        }

        int depth = std::stoi(items[0]);
        bool is_leaf = std::stoi(items[1]) == 1;
        Vec3 center = {std::stof(items[2]), std::stof(items[3]), std::stof(items[4])};
        float half_size = std::stof(items[5]);
        int num_objects = std::stoi(items[6]);

        auto n = std::make_unique<node>(center, half_size, depth);
        n->is_leaf_ = is_leaf;

        for (int i = 0; i < num_objects; ++i) {
            if (items.size() < 7 + 4 * (i + 1)) break;
            Object obj;
            obj.position = {std::stof(items[7 + 4 * i]), std::stof(items[8 + 4 * i]), std::stof(items[9 + 4 * i])};
            obj.id = std::stoi(items[10 + 4 * i]);
            n->objects_.push_back(obj);
        }
        
        return n;
    };

    root_ = parse_node(nodes[0]);
    if (!root_) {
        return;
    }

    std::queue<node*> node_queue;
    node_queue.push(root_.get());
    size_t node_index = 1;

    while (!node_queue.empty() && node_index < nodes.size()) {
        node* current = node_queue.front();
        node_queue.pop();
        if (current->is_leaf_) continue;

        for (int i = 0; i < 8 && node_index < nodes.size(); ++i) {
            current->children_[i] = parse_node(nodes[node_index++]);
            if (current->children_[i]) {
                node_queue.push(current->children_[i].get());
            }
        }
    }
}

void octree::query_point(const Vec3& point, std::vector<Object>& result, node* n) const {
    if (!n) {
        n = root_.get();
    }
    if (!n->boundary_.contains(point)) {
        return;
    }

    if (n->is_leaf_) {
        for (const auto& obj : n->objects_) {
            if (obj.position == point) result.push_back(obj);
        }
    } 
    else {
        for (const auto& child : n->children_) {
            query_point(point, result, child.get());
        }
    }
}

void octree::query_ray(const Vec3& origin, const Vec3& direction, std::vector<Object>& result, node* n) const {
    if (!n) n = root_.get();

    // simple ray-AABB intersection test
    float t_min = 0.0f, t_max = std::numeric_limits<float>::max();
    const Vec3& min = {n->boundary_.center.x - n->boundary_.half_size,
                       n->boundary_.center.y - n->boundary_.half_size,
                       n->boundary_.center.z - n->boundary_.half_size};
    const Vec3& max = {n->boundary_.center.x + n->boundary_.half_size,
                       n->boundary_.center.y + n->boundary_.half_size,
                       n->boundary_.center.z + n->boundary_.half_size};

    for (int i = 0; i < 3; ++i) {
        float origin_i = (&origin.x)[i];
        float direction_i = (&direction.x)[i];
        float min_i = (&min.x)[i];
        float max_i = (&max.x)[i];

        if (std::abs(direction_i) < 1e-6) {
            if (origin_i < min_i || origin_i > max_i) {
                return;
            }
        } 
        else {
            float t1 = (min_i - origin_i) / direction_i;
            float t2 = (max_i - origin_i) / direction_i;
            if (t1 > t2) std::swap(t1, t2);
            t_min = std::max(t_min, t1);
            t_max = std::min(t_max, t2);
            if (t_min > t_max) {
                return;
            }
        }
    }

    if (n->is_leaf_) {
        for (const auto& obj : n->objects_) {
            // check if object position lies close to the ray (simplified one)
            Vec3 to_obj = {obj.position.x - origin.x, obj.position.y - origin.y, obj.position.z - origin.z};
            float t = (to_obj.x * direction.x + to_obj.y * direction.y + to_obj.z * direction.z) /
                      (direction.x * direction.x + direction.y * direction.y + direction.z * direction.z);
            if (t >= t_min && t <= t_max) {
                Vec3 point = {origin.x + t * direction.x, origin.y + t * direction.y, origin.z + t * direction.z};
                if (std::abs(point.x - obj.position.x) < 1e-3 &&
                    std::abs(point.y - obj.position.y) < 1e-3 &&
                    std::abs(point.z - obj.position.z) < 1e-3) {
                    result.push_back(obj);
                }
            }
        }
    } 
    else {
        for (const auto& child : n->children_) {
            query_ray(origin, direction, result, child.get());
        }
    }
}

void octree::query_knn(const Vec3& point, int k, std::vector<Object>& result, node* n) const {
    if (!n) {
        n = root_.get();
    }
    if (!n->boundary_.contains(point) && !n->is_leaf_) {
        for (const auto& child : n->children_) {
            if (child->boundary_.intersects(AABB{point, 1e-3f})) {
                query_knn(point, k, result, child.get());
            }
        }
    
        return;
    }

    struct Entry {
        Object obj;
        float distance;
        bool operator<(const Entry& other) const { return distance > other.distance; }
    };
    
    static std::priority_queue<Entry> pq;

    if (n->is_leaf_) {
        for (const auto& obj : n->objects_) {
            float dx = obj.position.x - point.x;
            float dy = obj.position.y - point.y;
            float dz = obj.position.z - point.z;
            float distance = std::sqrt(dx * dx + dy * dy + dz * dz);
            pq.push({obj, distance});
            if (pq.size() > static_cast<size_t>(k)) {
                pq.pop();
            }
        }
    } 
    else {
        for (const auto& child : n->children_) {
            query_knn(point, k, result, child.get());
        }
    }

    if (n == root_.get()) {
        result.clear();
        while (!pq.empty()) {
            result.push_back(pq.top().obj);
            pq.pop();
        }
       
        std::reverse(result.begin(), result.end());
    }
}