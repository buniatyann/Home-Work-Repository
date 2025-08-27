#include "tree.hpp"
#include <sstream>
#include <cmath>
#include <algorithm>
#include <limits>

// has_position implementations
double has_position::get_x(const point& obj) {
    return obj.get_x();
}

double has_position::get_y(const point& obj) {
    return obj.get_y();
}

// rectangle implementations
rectangle::rectangle(double x, double y, double half_width, double half_height)
    : x_(x), y_(y), half_width_(half_width), half_height_(half_height) {}

bool rectangle::contains(double px, double py) const {
    return (px >= x_ - half_width_ && px <= x_ + half_width_ &&
            py >= y_ - half_height_ && py <= y_ + half_height_);
}

bool rectangle::contains(const point& p) const {
    return contains(has_position::get_x(p), has_position::get_y(p));
}

bool rectangle::intersects(const rectangle& other) const {
    return !(other.x_ - other.half_width_ > x_ + half_width_ ||
             other.x_ + other.half_width_ < x_ - half_width_ ||
             other.y_ - other.half_height_ > y_ + half_height_ ||
             other.y_ + other.half_height_ < y_ - half_height_);
}

double rectangle::get_x() const { return x_; }
double rectangle::get_y() const { return y_; }
double rectangle::get_half_width() const { return half_width_; }
double rectangle::get_half_height() const { return half_height_; }

bool rectangle::is_valid() const {
    return half_width_ >= 0 && half_height_ >= 0 &&
           !std::isnan(x_) && !std::isnan(y_) &&
           !std::isinf(x_) && !std::isinf(y_);
}

std::string rectangle::serialize() const {
    std::stringstream ss;
    ss << x_ << "," << y_ << "," << half_width_ << "," << half_height_;
    return ss.str();
}

std::optional<rectangle> rectangle::deserialize(const std::string& data) {
    std::stringstream ss(data);
    double x, y, half_width, half_height;
    char comma;
    if (ss >> x >> comma >> y >> comma >> half_width >> comma >> half_height && comma == ',') {
        rectangle rect(x, y, half_width, half_height);
        if (rect.is_valid()) {
            return rect;
        }
    }
    return std::nullopt;
}

// point implementations
point::point(double x, double y, int id)
    : x_(x), y_(y), id_(id) {}

double point::get_x() const { return x_; }
double point::get_y() const { return y_; }
int point::get_id() const { return id_; }

std::string point::serialize() const {
    std::stringstream ss;
    ss << x_ << "," << y_ << "," << id_;
    return ss.str();
}

std::optional<point> point::deserialize(const std::string& data) {
    std::stringstream ss(data);
    double x, y;
    int id;
    char comma;
    if (ss >> x >> comma >> y >> comma >> id && comma == ',') {
        return point(x, y, id);
    }
   
    return std::nullopt;
}

// quad_tree_iterator implementations
quad_tree_iterator::quad_tree_iterator(const quad_tree* tree)
    : root_(tree), current_point_index_(0) {
    if (tree) {
        nodes_.push(tree);
        current_points_ = tree->points_;
    }
}

bool quad_tree_iterator::has_next() const {
    return !nodes_.empty() || current_point_index_ < current_points_.size();
}

point quad_tree_iterator::next() {
    while (current_point_index_ >= current_points_.size() && !nodes_.empty()) {
        const quad_tree* current = nodes_.front();
        nodes_.pop();
        
        if (current->divided_) {
            if (current->northeast_) nodes_.push(current->northeast_.get());
            if (current->northwest_) nodes_.push(current->northwest_.get());
            if (current->southeast_) nodes_.push(current->southeast_.get());
            if (current->southwest_) nodes_.push(current->southwest_.get());
        }
        
        current_point_index_ = 0;
        current_points_ = current->points_;
    }
    
    if (current_point_index_ < current_points_.size()) {
        return current_points_[current_point_index_++];
    }
    
    return point(0, 0, 0); // Should not reach here if has_next() is used properly
}

// quad_tree implementations
quad_tree::quad_tree(const rectangle& boundary)
    : boundary_(boundary), divided_(false) {}

quad_tree::~quad_tree() {
    clear();
}

bool quad_tree::insert(const point& point) {
    if (!boundary_.contains(point)) return false;

    if (points_.size() < CAPACITY && !divided_) {
        points_.push_back(point);
        return true;
    }

    if (!divided_) subdivide();

    return (northeast_->insert(point) ||
            northwest_->insert(point) ||
            southeast_->insert(point) ||
            southwest_->insert(point));
}

bool quad_tree::insert_batch(const std::vector<point>& points) {
    bool all_inserted = true;
    for (const auto& p : points) {
        if (!insert(p)) {
            all_inserted = false;
        }
    }
   
    return all_inserted;
}

bool quad_tree::remove(const point& point) {
    if (!boundary_.contains(point)) return false;

    if (!divided_) {
        auto it = std::find_if(points_.begin(), points_.end(),
            [&point](const point& p) {
                return std::abs(has_position::get_x(p) - has_position::get_x(point)) < 1e-10 &&
                       std::abs(has_position::get_y(p) - has_position::get_y(point)) < 1e-10 &&
                       p.get_id() == point.get_id();
            });
        
        if (it != points_.end()) {
            points_.erase(it);
            return true;
        }
        
        return false;
    }

    return remove_from_subtrees(point, boundary_);
}

bool quad_tree::remove_from_subtrees(const point& point, const rectangle& range) {
    if (!divided_) return false;

    bool removed = false;
    if (northeast_->boundary_.contains(point)) removed |= northeast_->remove(point);
    if (northwest_->boundary_.contains(point)) removed |= northwest_->remove(point);
    if (southeast_->boundary_.contains(point)) removed |= southeast_->remove(point);
    if (southwest_->boundary_.contains(point)) removed |= southwest_->remove(point);
    
    return removed;
}

void quad_tree::query(const rectangle& range, std::vector<point>& found) const {
    if (!boundary_.intersects(range)) return;

    for (const point& p : points_) {
        if (range.contains(p)) {
            found.push_back(p);
        }
    }

    if (divided_) {
        northeast_->query(range, found);
        northwest_->query(range, found);
        southeast_->query(range, found);
        southwest_->query(range, found);
    }
}

size_t quad_tree::count_in_range(const rectangle& range) const {
    if (!boundary_.intersects(range)) return 0;

    size_t count = 0;
    for (const point& p : points_) {
        if (range.contains(p)) {
            count++;
        }
    }

    if (divided_) {
        count += northeast_->count_in_range(range);
        count += northwest_->count_in_range(range);
        count += southeast_->count_in_range(range);
        count += southwest_->count_in_range(range);
    }
   
    return count;
}

std::optional<point> quad_tree::find_nearest(double x, double y, double max_distance) const {
    std::optional<point> best_point;
    double best_distance = max_distance;
    find_nearest_helper(x, y, max_distance, best_point, best_distance);
   
    return best_point;
}

void quad_tree::find_nearest_helper(double x, double y, double max_distance,
                                   std::optional<point>& best_point, double& best_distance) const {
    for (const point& p : points_) {
        double dx = has_position::get_x(p) - x;
        double dy = has_position::get_y(p) - y;
        double distance = std::sqrt(dx * dx + dy * dy);
        if (distance < best_distance) {
            best_distance = distance;
            best_point = p;
        }
    }

    if (divided_) {
        // Process subtrees in order of proximity
        std::vector<quad_tree*> subtrees = {northeast_.get(), northwest_.get(), 
                                          southeast_.get(), southwest_.get()};
        std::sort(subtrees.begin(), subtrees.end(),
            [x, y](const quad_tree* a, const quad_tree* b) {
                double dx_a = a->boundary_.get_x() - x;
                double dy_a = a->boundary_.get_y() - y;
                double dx_b = b->boundary_.get_x() - x;
                double dy_b = b->boundary_.get_y() - y;
                return (dx_a * dx_a + dy_a * dy_a) < (dx_b * dx_b + dy_b * dy_b);
            });

        for (const auto* subtree : subtrees) {
            double dx = subtree->boundary_.get_x() - x;
            double dy = subtree->boundary_.get_y() - y;
            double min_distance = std::sqrt(dx * dx + dy * dy) - 
                               std::sqrt(subtree->boundary_.get_half_width() * 
                                       subtree->boundary_.get_half_width() + 
                                       subtree->boundary_.get_half_height() * 
                                       subtree->boundary_.get_half_height());
            
            if (min_distance < best_distance) {
                subtree->find_nearest_helper(x, y, max_distance, best_point, best_distance);
            }
        }
    }
}

void quad_tree::clear() {
    points_.clear();
    if (divided_) {
        northeast_.reset();
        northwest_.reset();
        southeast_.reset();
        southwest_.reset();
        divided_ = false;
    }
}

size_t quad_tree::size() const {
    size_t count = points_.size();
    if (divided_) {
        count += northeast_->size();
        count += northwest_->size();
        count += southeast_->size();
        count += southwest_->size();
    }
    
    return count;
}

bool quad_tree::empty() const {
    return size() == 0;
}

void quad_tree::get_all_points(std::vector<point>& points) const {
    points.insert(points.end(), points_.begin(), points_.end());
    if (divided_) {
        northeast_->get_all_points(points);
        northwest_->get_all_points(points);
        southeast_->get_all_points(points);
        southwest_->get_all_points(points);
    }
}

int quad_tree::get_depth() const {
    if (!divided_) return 1;
    int ne_depth = northeast_->get_depth();
    int nw_depth = northwest_->get_depth();
    int se_depth = southeast_->get_depth();
    int sw_depth = southwest_->get_depth();
   
    return 1 + std::max({ne_depth, nw_depth, se_depth, sw_depth});
}

bool quad_tree::is_valid() const {
    if (!boundary_.is_valid()) return false;
    if (divided_) {
        return northeast_ && northwest_ && southeast_ && southwest_ &&
               northeast_->is_valid() && northwest_->is_valid() &&
               southeast_->is_valid() && southwest_->is_valid();
    }
    
    return true;
}

std::string quad_tree::serialize() const {
    std::stringstream ss;
    ss << boundary_.serialize() << "|";
    ss << points_.size() << "|";
    for (const auto& p : points_) {
        ss << p.serialize() << ";";
    }
    
    if (divided_) {
        ss << "1|";
        ss << northeast_->serialize() << "|";
        ss << northwest_->serialize() << "|";
        ss << southeast_->serialize() << "|";
        ss << southwest_->serialize();
    } 
    else {
        ss << "0";
    }
    
    return ss.str();
}

std::optional<quad_tree> quad_tree::deserialize(const std::string& data) {
    std::stringstream ss(data);
    std::string segment;
    
    // Read boundary
    std::getline(ss, segment, '|');
    auto boundary_opt = rectangle::deserialize(segment);
    if (!boundary_opt) return std::nullopt;
    
    quad_tree tree(*boundary_opt);
    
    // Read points count
    std::getline(ss, segment, '|');
    size_t point_count;
    try {
        point_count = std::stoul(segment);
    } catch (...) {
        return std::nullopt;
    }
    
    // Read points
    std::getline(ss, segment, '|');
    std::stringstream points_ss(segment);
    std::string point_data;
    for (size_t i = 0; i < point_count && std::getline(points_ss, point_data, ';'); ++i) {
        auto point_opt = point::deserialize(point_data);
        if (point_opt) {
            tree.points_.push_back(*point_opt);
        } 
        else {
            return std::nullopt;
        }
    }
    
    // Read divided flag and subtrees
    std::getline(ss, segment, '|');
    if (segment == "1") {
        tree.subdivide();
        
        // Read subtrees
        std::getline(ss, segment, '|');
        auto ne_opt = quad_tree::deserialize(segment);
        if (!ne_opt) return std::nullopt;
        tree.northeast_ = std::make_unique<quad_tree>(*ne_opt);
        
        std::getline(ss, segment, '|');
        auto nw_opt = quad_tree::deserialize(segment);
        if (!nw_opt) return std::nullopt;
        tree.northwest_ = std::make_unique<quad_tree>(*nw_opt);
        
        std::getline(ss, segment, '|');
        auto se_opt = quad_tree::deserialize(segment);
        if (!se_opt) return std::nullopt;
        tree.southeast_ = std::make_unique<quad_tree>(*se_opt);
        
        std::getline(ss, segment);
        auto sw_opt = quad_tree::deserialize(segment);
        if (!sw_opt) return std::nullopt;
        tree.southwest_ = std::make_unique<quad_tree>(*sw_opt);
        
        tree.divided_ = true;
    }
    
    return tree;
}

void quad_tree::subdivide() {
    double x = boundary_.get_x();
    double y = boundary_.get_y();
    double hw = boundary_.get_half_width() / 2.0;
    double hh = boundary_.get_half_height() / 2.0;

    northeast_ = std::make_unique<quad_tree>(rectangle(x + hw, y - hh, hw, hh));
    northwest_ = std::make_unique<quad_tree>(rectangle(x - hw, y - hh, hw, hh));
    southeast_ = std::make_unique<quad_tree>(rectangle(x + hw, y + hh, hw, hh));
    southwest_ = std::make_unique<quad_tree>(rectangle(x - hw, y + hh, hw, hh));

    divided_ = true;
}

void quad_tree::count_nodes(size_t& count) const {
    count++;
    if (divided_) {
        northeast_->count_nodes(count);
        northwest_->count_nodes(count);
        southeast_->count_nodes(count);
        southwest_->count_nodes(count);
    }
}

quad_tree_iterator quad_tree::begin() const {
    return quad_tree_iterator(this);
}

quad_tree_iterator quad_tree::end() const {
    return quad_tree_iterator(nullptr);
}