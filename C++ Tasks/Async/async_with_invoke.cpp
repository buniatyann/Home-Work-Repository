#include <future>
#include <functional>
#include <thread>
#include <utility>
#include <type_traits>

template <typename Func, typename... Args>
auto async(Func&& f, Args&&... args) -> std::future<std::invoke_result_t<Func, Args...>> {
    using return_type = std::invoke_result_t<Func, Args...>;

    auto prom = std::make_shared<std::promise<return_type>>();
    std::future<return_type> fut = prom->get_future();

    std::thread([prom, func = std::forward<Func>(f), ... args_copy = std::forward<Args>(args)]() mutable {
        try {
            if constexpr (std::is_void_v<return_type>) {
                std::invoke(std::move(func), std::move(args_copy)...);
                prom->set_value();
            } 
            else {
                prom->set_value(std::invoke(std::move(func), std::move(args_copy)...));
            }
        } catch (...) {
            prom->set_exception(std::current_exception());
        }
    }).detach();

    return fut;
}