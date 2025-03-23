#ifndef OPTIONAL_HPP
#define OPTIONAL_HPP

#include <type_traits>
#include <stdexcept>
#include <utility>

namespace hw {

class nullopt_t {
public:
    constexpr nullopt_t() noexcept = default;
};

inline constexpr nullopt_t nullopt;

template <typename T>
class Optional {
public:
    using value_type = T;

    constexpr Optional() noexcept;
    constexpr Optional(nullopt_t) noexcept;
    
    template <typename U = T, typename = std::enable_if_t<std::is_constructible_v<T, U>>>
    constexpr Optional(U&& val);
    
    Optional(const Optional& rhs);
    Optional(Optional&& rhs) noexcept(std::is_nothrow_move_constructible_v<T>);
    
    Optional& operator=(const Optional& rhs);
    Optional& operator=(Optional&& rhs) noexcept(std::is_nothrow_move_assignable_v<T>);
    
    ~Optional();
    
    constexpr bool has_value() const noexcept;
    // constexpr explicit operator bool() const noexcept; ??
    constexpr operator bool() const noexcept;
    
    value_type& operator*();
    const value_type& operator*() const;
    
    value_type* operator->();
    const value_type* operator->() const;
    
    template <typename U>
    value_type value_or(U&& default_value) const&;
    
    template <typename U>
    value_type value_or(U&& default_value) &&;
    
    Optional& emplace(T&& value);
    
    template <typename Func>
    Optional<std::remove_reference_t<std::invoke_result_t<Func, const T&>>> map(Func&& func) const&;
    
    template <typename Func>
    Optional<std::remove_reference_t<std::invoke_result_t<Func, T&&>>> map(Func&& func) &&;
    
    template <typename Func>
    Optional<std::remove_reference_t<std::invoke_result_t<Func, const T&>>> and_then(Func&& func) const&;
    
    template <typename Func>
    Optional<std::remove_reference_t<std::invoke_result_t<Func, T&&>>> and_then(Func&& func) &&;
    
    friend bool operator==(const Optional& lhs, const Optional& rhs);
    friend bool operator!=(const Optional& lhs, const Optional& rhs);
    friend bool operator==(const Optional& lhs, nullopt_t);
    friend bool operator!=(const Optional& lhs, nullopt_t);

private:
    union Storage {
        alignas(value_type) value_type value;
        Storage() noexcept {}
        ~Storage() {}
    };

    Storage storage;
    bool engaged = false;

    void destroy() noexcept(std::is_nothrow_destructible_v<value_type>);
};

template <typename T, typename... Args>
constexpr Optional<T> make_optional(Args&&... args);

} // namespace hw

#endif // OPTIONAL_HPP
