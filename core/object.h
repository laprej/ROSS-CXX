// Stolen from http://cppcodereviewers.com/covariant-return-types-and-smart-pointers/
//          or https://github.com/CppCodeReviewers/Covariant-Return-Types-and-Smart-Pointers

#ifndef Object_h
#define Object_h

// BOOST_POOL_NO_MT turns off multithreading
#define BOOST_POOL_NO_MT
#include <boost/pool/pool_alloc.hpp>
#include <memory>

namespace object
{
    template<typename T>
    std::unique_ptr<T> clone(const T& object)
    {
        using base_type = typename T::base_type;
        static_assert(std::is_base_of<base_type, T>::value, "T object has to derived from T::base_type");
        auto ptr = static_cast<const base_type&>(object).clone();
        return std::unique_ptr<T>(static_cast<T*>(ptr));
    }

    template<typename T>
    auto clone(T* object) -> decltype(clone(*object))
    {
        return clone(*object);
    }

    template<typename T>
    struct cloneable
    {
        using base_type = T;

        virtual ~cloneable() = default;

        virtual T* clone() const = 0;

        template <typename X>
        friend std::unique_ptr<X> object::clone(const X&);
    };
}

template <typename T>
class SP_wrapper
{
    bool newly_cloned = {true};
    std::shared_ptr<T> ptr;

public:
    void set(const T& x)
    {
        if (newly_cloned) {
            newly_cloned = false;
            ptr = std::allocate_shared<T>(boost::fast_pool_allocator<T>(), x);
        }
        else {
            *ptr = x;
        }
    }
    T* get() const
    {
        return ptr.get();
    }
    std::shared_ptr<T>& getSP() { return ptr; }

    SP_wrapper() = default;
    SP_wrapper(const SP_wrapper &x) : newly_cloned(true), ptr(x.ptr) { }
};

#endif /* Object_h */
