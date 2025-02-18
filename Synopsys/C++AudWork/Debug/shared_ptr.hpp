#ifndef SHARED_POINTER_H
#define SHARED_POINTER_H
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <type_traits>
#include <memory>
#include <cassert>

// Reference Counting policies
struct single_threaded_t {};
struct multi_threaded_t {};

// alignof(T)

namespace helper {
    template <typename T>
    struct control_block_base {
        using storage_type = typename std::aligned_storage<sizeof(T), alignof(T)>::type; // uninitialized storage for a type T with the correct alignment requirements.
        /// The storage buffer to create the type `T`
        storage_type value_buf;
        
        /// Create a control object in derived implementation.
        template <typename Allocator, typename Deletor, typename RefCntPolicy>
        static control_block_base* create(Allocator&& allocator, Deletor&& deletor);
        
        /*
            Calls destructor of the embedded object.
        */
        virtual ~control_block_base() // virtual for inheritance
        {
            (reinterpret_cast<T*>(&value_buf))->~T();
        }
        /*
            // Old code:
            // (previously the implementation was here)
        */
        void new_function() {
            std::cout << "New function implementation." << std::endl;
        }
        /*
            Get the actual mutable pointer type of the object residing
            in the storage area.
        */
        T* get_type_ptr() {
            return reinterpret_cast<T*>(&value_buf);
        }
        
        /*
            Get the actual const pointer type of the object residing
            in the storage area.
        */
        const T* get_const_type_ptr() {
            return const_cast<const T*>(reinterpret_cast<T*>(&value_buf));
        }
        
        //
        virtual void add_ref()   = 0;
        //
        virtual size_t get_ref() const = 0;
        //
        virtual size_t dec_ref() = 0;
        //
        virtual void destruct() noexcept = 0;
    
    };
    
    /*
        The control block object where the 
        allocated object resides along with
        its reference count.
    */
    template <typename T, typename Allocator, typename Deletor, typename RefCntPolicy>
      // The ref count policy to be used.
      // Single threaded or Multi Threaded 
    struct control_block;
    
    /*
        for Single Thread.
    */
    template <typename T, typename Allocator, typename Deletor>
    struct control_block<T, Allocator, Deletor, single_threaded_t>: control_block_base<T>
    {
        //=
        using allocator_type = typename std::allocator_traits<std::decay_t<Allocator>>::template rebind_alloc<control_block>; // ?
      
        /// Reference counter for single threaded applications
        size_t ref_cnt_ = 0;
        
        /*
            Constructor.
        */
        control_block(Allocator&& allocator, Deletor&& deletor): control_block_base<T>(), 
            alloc_(std::forward<Allocator>(allocator)), deletor_(std::forward<Deletor>(deletor))
        {}
        
        /*
            Increments the ref count.
        */
        void add_ref() override
        {
            ref_cnt_++;
        }
        
        /*
            Return the current ref count for the object.
        */
        size_t get_ref() const override
        {
            return ref_cnt_;
        }
    
        /**
         * Decrements the ref count.
         */
        size_t dec_ref() override
        {
            assert (ref_cnt_ > 0);
            return (--ref_cnt_);
        }
        
        //
        void destruct() noexcept override
        {
            this->~control_block_base<T>();
            alloc_.deallocate(this, 1);
        }
        
        //
        ~control_block() {}
        
        allocator_type alloc_;
        Deletor deletor_;
    };
    
    /*
         
        rebind_alloc -?
        std::allocator_traits -?
    */
    // std::decay_t - Used to remove references, const-ness, and convert arrays/functions to pointers
    // It transforms the type by removing reference and const qualifiers and turning arrays/functions into pointers
    
    // std::rebind_alloc - Used to rebind an allocator to another type
    // It allows us to use an allocator for one type (e.g., T) to allocate memory for another type (e.g., control_block).
    // The rebind mechanism is useful when we want to change the type of memory being allocated by an allocator.
    
    //std::forward - Used to forward arguments while preserving their value category (lvalue or rvalue)
    // This is used in perfect forwarding to maintain whether an argument was passed as an lvalue or rvalue.
    // It ensures that the argument is forwarded in the correct form (either as an rvalue or lvalue).    

    // std::allocator_traits - Used to interact with allocators in a standardized and type-safe manner.
    // It provides utility functions for allocating, constructing, deallocating, and managing objects with an allocator.

    /*
        Construct the control block.
    */
    template <typename T>
    template <typename Allocator, typename Deletor, typename RCP>
    control_block_base<T>*
    control_block_base<T>::create(Allocator&& allocator, Deletor&& deletor)
    {
        using DerSelf = typename helper::control_block<T, std::decay_t<Allocator>, std::decay_t<Deletor>, RCP>;
        typename std::allocator_traits<std::decay_t<Allocator>>::template rebind_alloc<DerSelf> rb_alloc;
        
        auto address = static_cast<DerSelf*>(rb_alloc.allocate(1));
        auto ctrl_blk = new (address) DerSelf{std::forward<Allocator>(allocator), std::forward<Deletor>(deletor)};
        
        return static_cast<control_block_base<T>*>(ctrl_blk);
    }
    
    
    /*
        Construct the object in its aligned storage area.
    */
    template <typename T, typename... Args>
    void construct_wrapped_type(control_block_base<T>* cb, Args&&... args) // ?
    {
        // new (&cb->value_buf) T{std::forward<Args>(args)...};
        // cb->add_ref();
        new (&cb->value_buf) T{std::forward<Args>(args)...};
        cb->add_ref();
    }
    
} // namespace helper
    
    
/*
    Shared Pointer.
*/
template <typename T, typename RefCntPolicy=single_threaded_t>
class shared_ptr
{
public:
    /*
        Constructor for default constructible.
    */
    template <typename Allocator=std::allocator<T>,typename Deletor=std::default_delete<T>>
    explicit shared_ptr(): shared_ptr(Allocator{}, Deletor{})
    {
        // ?
        // ctrl_blk_ = helper::control_block_base<T>::template create<Allocator, Deletor, RefCntPolicy>(
        //     std::forward<Allocator>(valloc),
        //     std::forward<Deletor>(Deletor)
        // );
        ctrl_blk_ = helper::control_block_base<T>::template create<Allocator, Deletor, RefCntPolicy>(
            std::forward<Allocator>(valloc),         // Forward the allocator
            std::forward<Deletor>(deletor)          // Forward the actual deletor
        );


        // Construct the object and increment ref count
        helper::construct_wrapped_type(ctrl_blk_);
    }

    /*
        Forwarding constructor.
        Create a shared pointer from the Args.
    */
    template <typename... Args, typename Allocator=std::allocator<T>,
              typename Deletor=std::default_delete<T>, 
              typename Cond = std::enable_if_t<std::is_constructible<T, Args...>::value ||
                                               std::is_convertible<T, Args...>::value>
            >
    explicit shared_ptr(Args&&... args): shared_ptr(Allocator{}, Deletor{}, std::forward<Args>(args)...)
    {
    }

    //
    template <typename Allocator=std::allocator<T>,
                typename Deletor=std::default_delete<T>>
    explicit shared_ptr(Allocator&& alloc, Deletor&& deletor);

    //
    template <typename... Args, typename Allocator=std::allocator<T>, typename Deletor=std::default_delete<T>,
              typename Cond = std::enable_if_t<std::is_constructible<T, Args...>::value ||
              std::is_convertible<T, Args...>::value>>
    explicit shared_ptr(Allocator&& alloc, Deletor&& deletor, Args&&... args);
    

    /*
        Regular copy constructor.
    */
    shared_ptr(const shared_ptr& other): ctrl_blk_(other.ctrl_blk_)
    {
        ctrl_blk_->add_ref();
    }

    /*
        Move copy constructor.
    */
    shared_ptr(shared_ptr&& other): ctrl_blk_(other.ctrl_blk_) noexcept
    {
        other.ctrl_blk_ = nullptr;
    }

    /*
        Move assignment.
        Destroy current control block / decrease ref count.

        NOTE: Self assignment not supported.
    */
    shared_ptr& operator=(shared_ptr&& rhs) noexcept {
        if (this != &rhs) {
            if (ctrl_blk_ && ctrl_blk_->dec_ref() == 0) {
                ctrl_blk_->destruct();
            }
            ctrl_blk_ = rhs.ctrl_blk_;
            rhs.ctrl_blk_ = nullptr;
        }

        return *this;
    }

    
    shared_ptr& operator=(const shared_ptr& rhs)
    {
        if(this == &rhs){
            return *this;
        }

        assert (rhs.ctrl_blk_ != ctrl_blk_);
        this->~shared_ptr();
        ctrl_blk_ = rhs.ctrl_blk_;
        ctrl_blk_->add_ref();
        return *this;
    }

    /*
        Destructor.
    */
    ~shared_ptr();

// Pointer like semantics
public: 
    T* get() noexcept
    {
        return ctrl_blk_->get_type_ptr();
    }
    //
    const T* get() const noexcept
    {
        return ctrl_blk_->get_const_type_ptr();
    }

    //
    T* operator->() noexcept
    {
        return ctrl_blk_->get_type_ptr();
    }

    //
    const T* operator->() const noexcept
    {
        return ctrl_blk_->get_const_type_ptr();
    }

    //
    T& operator*() noexcept
    {
        return *(ctrl_blk_->get_type_ptr());
    }

    //
    const T& operator*() const noexcept
    {
        return *(ctrl_blk_->get_const_type_ptr());
    }

// Reference cout APIs
public: 
    //
    size_t strong_ref_count() const noexcept
    {
        return ctrl_blk_->get_ref();
    }

private:
    /// The control block where the pointed type actually lives
    helper::control_block_base<T>* ctrl_blk_ = nullptr;
};

    //-----------------------------------------------------------------

template <typename T, typename RCP>
template <typename Allocator, typename Deletor>
shared_ptr<T, RCP>::shared_ptr(Allocator&& alloc, Deletor&& deletor)
{
    ctrl_blk_ = helper::control_block_base<T>::template create<Allocator, Deletor, RCP>(
                                std::forward<Allocator>(alloc),
                                std::forward<Deletor>(deletor));

    // Construct the object and increment ref count
    helper::construct_wrapped_type(ctrl_blk_);
}


template <typename T, typename RCP>
template <typename... Args, typename Allocator, typename Deletor, typename Cond>
shared_ptr<T, RCP>::shared_ptr(Allocator&& alloc, Deletor&& deletor, Args&&... args)
{
    ctrl_blk_ = helper::control_block_base<T>::template create<Allocator, Deletor, RCP>(
                                std::forward<Allocator>(alloc),
                                std::forward<Deletor>(deletor));

    // Construct the object and increment ref count
    helper::construct_wrapped_type(ctrl_blk_, std::forward<Args>(args)...);
}


template <typename T, typename RCP>
shared_ptr<T, RCP>::~shared_ptr()
{
    // moved from? not in control any more
    if (!ctrl_blk_) return;

    auto ref_cnt = ctrl_blk_->dec_ref();
    if (ref_cnt == 0){
        ctrl_blk_->destruct();
    }
}



#endif // SHARED_POINTER_H