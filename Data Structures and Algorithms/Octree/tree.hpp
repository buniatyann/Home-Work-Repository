#ifndef OCTREE_HPP
#define OCTREE_HPP

#include <vector>
#include <memory>
#include <array>
#include <functional>
#include <string>
#include <queue>

struct Vec3 {
    float x, y, z;

    bool operator==(const Vec3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }
};

struct Object {
    Vec3 position;
    int id;

    bool operator==(const Object& other) const {
        return id == other.id;
    }
};

struct AABB {
    Vec3 center;
    float half_size;

    bool contains(const Vec3& p) const;
    bool intersects(const AABB& other) const;
}; // axis-aligned bounding box

class node {
public:
    node(const Vec3& center, float half_size, int depth);
    int depth_;

private:
    AABB boundary_;
    std::vector<Object> objects_;
    std::array<std::unique_ptr<node>, 8> children_;
    bool is_leaf_;

    friend class octree;
};

class octree {
public:
    octree(const Vec3& min, const Vec3& max, int max_depth, int max_objects);
    void insert_object(const Object& obj, node* n = nullptr);
    void batch_insert(const std::vector<Object>& objs);
    void query_range(const AABB& range, std::vector<Object>& result, node* n = nullptr) const;
    bool is_in_bounds(const Vec3& point, node* n = nullptr) const;
    void clear();
    int get_depth(node* n = nullptr) const;
    void traverse(const std::function<void(node*)>& callback, node* n = nullptr) const;
    void get_all_objects(std::vector<Object>& result, node* n = nullptr) const;
    void remove_object(const Object& obj, node* n = nullptr);
    void update_object(const Object& obj, const Vec3& new_pos, node* n = nullptr);
    void merge(node* n = nullptr);
    void balance();
    void find_collisions(node* n = nullptr, std::vector<std::pair<Object, Object>>& collisions = {}) const;
    std::string serialize(node* n = nullptr) const;
    void deserialize(const std::string& data);
    void query_point(const Vec3& point, std::vector<Object>& result, node* n = nullptr) const;
    void query_ray(const Vec3& origin, const Vec3& direction, std::vector<Object>& result, node* n = nullptr) const;
    void query_knn(const Vec3& point, int k, std::vector<Object>& result, node* n = nullptr) const;

private:
    std::unique_ptr<node> root_;
    int max_depth_;
    int max_objects_;

    void subdivide(node* n);
};

#endif // OCTREE_HPP