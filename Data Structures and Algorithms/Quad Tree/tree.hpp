#ifndef QUAD_TREE_HPP
#define QUAD_TREE_HPP

#include <vector>
#include <memory>
#include <queue>
#include <string>
#include <optional>

// Forward declarations
class point;
class rectangle;
class quad_tree;

// Point-like interface
struct has_position {
    static double get_x(const point& obj);
    static double get_y(const point& obj);
};

// Rectangle structure
class rectangle {
public:
    rectangle(double x, double y, double half_width, double half_height);
    
    bool contains(double px, double py) const;
    bool contains(const point& p) const;
    bool intersects(const rectangle& other) const;
    double get_x() const;
    double get_y() const;
    double get_half_width() const;
    double get_half_height() const;
    bool is_valid() const;
    std::string serialize() const;
    static std::optional<rectangle> deserialize(const std::string& data);

private:
    double x_;
    double y_;
    double half_width_;
    double half_height_;
};

// Point structure
class point {
public:
    point(double x, double y, int id = 0);

    double get_x() const;
    double get_y() const;
    int get_id() const;
    std::string serialize() const;
    static std::optional<point> deserialize(const std::string& data);

private:
    double x_;
    double y_;
    int id_;
};

// QuadTree iterator
class quad_tree_iterator {
public:
    quad_tree_iterator(const quad_tree* tree);
    bool has_next() const;
    point next();

private:
    const quad_tree* root_;
    std::queue<const quad_tree*> nodes_;
    size_t current_point_index_;
    std::vector<point> current_points_;
};

// QuadTree class
class quad_tree {
public:
    quad_tree(const rectangle& boundary);
    ~quad_tree();

    bool insert(const point& point);
    bool insert_batch(const std::vector<point>& points);
    bool remove(const point& point);
    void query(const rectangle& range, std::vector<point>& found) const;
    size_t count_in_range(const rectangle& range) const;
    std::optional<point> find_nearest(double x, double y, double max_distance = std::numeric_limits<double>::max()) const;
    void clear();
    size_t size() const;
    bool empty() const;
    void get_all_points(std::vector<point>& points) const;
    int get_depth() const;
    bool is_valid() const;
    std::string serialize() const;
    static std::optional<quad_tree> deserialize(const std::string& data);
    
    // Iterator support
    quad_tree_iterator begin() const;
    quad_tree_iterator end() const;

private:
    static const int CAPACITY = 4;

    // Declare quad_tree_iterator as a friend to access private members
    friend class quad_tree_iterator;

    void subdivide();
    void count_nodes(size_t& count) const;
    bool remove_from_subtrees(const point& point, const rectangle& range);
    void find_nearest_helper(double x, double y, double max_distance, 
                           std::optional<point>& best_point, double& best_distance) const;

    rectangle boundary_;
    std::vector<point> points_;
    bool divided_;
    std::unique_ptr<quad_tree> northeast_;
    std::unique_ptr<quad_tree> northwest_;
    std::unique_ptr<quad_tree> southeast_;
    std::unique_ptr<quad_tree> southwest_;
};

#endif // QUAD_TREE_HPP