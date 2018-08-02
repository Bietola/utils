#pragma once

#include <memory>

namespace utl {

template <class Base>
class clonable_interface {
    private:
        virtual Base* clone_impl() const noexcept = 0;

    public:
        auto clone() const noexcept { return std::unique_ptr<Base>(clone_impl()); }
};

template <class Base, class Derived>
class clonable : public Base {
    private:
        clonable* clone_impl() const noexcept override {
            return new Derived(*this);
        }

    public:
        using Base::Base;

        auto clone() const noexcept {
            return std::unique_ptr<Derived>(static_cast<Derived*>(clone_impl()));
        }
};

}
