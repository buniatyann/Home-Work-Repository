#ifndef POLYGON_TPP
#define POLYGON_TPP

template <typename T, std::size_t N>
Polygon<T, N>::Polygon() = default;

template <typename T, std::size_t N>
Polygon<T, N>::Polygon(const Polygon& other)
    : data_(other.data_), box_(other.box_), boxDirty_(other.boxDirty_) {
}

template <typename T, std::size_t N>
Polygon<T, N>& Polygon<T, N>::operator=(const Polygon& other) {
    if (this != &other) {
        data_ = other.data_;
        box_ = other.box_;
        boxDirty_ = other.boxDirty_;
    }

    return *this;
}

template <typename T, std::size_t N>
Polygon<T, N>::Polygon(Polygon&& other) noexcept
    : data_(std::move(other.data_)),
    box_(std::move(other.box_)),
    boxDirty_(other.boxDirty_) {
}

template <typename T, std::size_t N>
Polygon<T, N>& Polygon<T, N>::operator=(Polygon&& other) noexcept {
    if (this != &other) {
        data_ = std::move(other.data_);
        box_ = std::move(other.box_);
        boxDirty_ = other.boxDirty_;
    }

    return *this;
}

template <typename T, std::size_t N>
Polygon<T, N>::~Polygon() = default;

template <typename T, std::size_t N>
BoundingBox<T, N> Polygon<T, N>::boundingBox() const {
    if (boxDirty_) {
        BoundingBox<T> b;
        for (const auto& p : data_) b.expand(p);
        box_ = b;
        boxDirty_ = false;
    }

    return box_;
}

template <typename T, std::size_t N>
typename Polygon<T, N>::Point& Polygon<T, N>::operator[](std::size_t ind) {
    //assert(ind < data_.size());
    boxDirty_ = true;
    return data_.at(ind);
}

template <typename T, std::size_t N>
const typename Polygon<T, N>::Point& Polygon<T, N>::operator[](std::size_t ind) const {
    //assert(ind < data_.size());
    return data_.at(ind);
}

template <typename T, std::size_t N>
bool Polygon<T, N>::empty() const {
    return data_.empty();
}

template <typename T, std::size_t N>
std::size_t Polygon<T, N>::size() const {
    return data_.size();
}

template <typename T, std::size_t N>
bool Polygon<T, N>::isConvex() const {
    return false;
}

template <typename T, std::size_t N>
bool Polygon<T, N>::contains(const Point& p) const {
    return false;
}

template <typename T, std::size_t N>
auto Polygon<T, N>::area() const {
    return T{};
}

template <typename T, std::size_t N>
auto Polygon<T, N>::perimeter() const {
    return T{};
}

template <typename T, std::size_t N>
bool Polygon<T, N>::isClockwise() const {
    return false;
}

template <typename T, std::size_t N>
void Polygon<T, N>::makeCounterClockwise() {}

template <typename T, std::size_t N>
bool Polygon<T, N>::isSimple() const {
    return false;
}

template <typename T, std::size_t N>
std::vector<typename Polygon<T, N>::Segment> Polygon<T, N>::edges() const {
    std::vector<Segment> vec;
    std::size_t n = data_.size();
    if (n < 2) {
        return vec;
    }

    for (std::size_t i = 0; i < n; ++i) {
        vec.emplace_back(data_[i], data_[(i + 1) % n]);
    }

    return vec;
}

template <typename T, std::size_t N>
std::vector<typename Polygon<T, N>::Point> Polygon<T, N>::vertices() const {
    return data_;
}

template <typename T, std::size_t N>
void Polygon<T, N>::push_back(const Point& p) {
    data_.push_back(p);
    boxDirty_ = true;
}

template <typename T, std::size_t N>
void Polygon<T, N>::insert(const Point& p, std::size_t index) {
    assert(index <= data_.size());
    data_.insert(data_.begin() + index, p);
    boxDirty_ = true;
}

#endif // POLYGON_TPP