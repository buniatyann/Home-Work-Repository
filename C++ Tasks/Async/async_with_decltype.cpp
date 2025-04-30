#include <future>
#include <utility>
#include <thread>
#include <functional>
#include <type_traits>

template <typename Func, typename... Args>
auto async(Func&& f, Args&&... args) -> std::future<decltype(f(args...))> {
    using return_type = typename decltype(f(args...));

    auto prom = std::make_shared(std::promise<return_type>()); // this?
    // auto prom = std::promise<return_type>(); or this?
    std::future<return_type> fut = prom->get_future();
    
    std::thread([prom, f = std::forward<Func>(f)](auto&&... args) mutable{
        try{
            if constexpr(is_void_v<return_type>){
                f(std::forward<decltype(args)>(args)...);
                prom.set_value();
            }
            else{
                prom.set_value(f(std::forward<decltype(args)>(args)...));
            }
        } catch(...){
            prom.set_exception(std::current_exception());
        }, 
        std::forward<Args>(args)...}).detach();

    return fut;
}