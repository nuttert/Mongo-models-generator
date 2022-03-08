#pragma once

#include <stdexcept>

namespace utils {

template <typename T>
class Single : public T {
    static T* instance_;

public:
    template <typename... Args>
    explicit Single(Args&&... args) : T(std::forward<Args>(args)...) {
        if (instance_)
            throw std::runtime_error("Second instance created");
        instance_ = this;
    }
    ~Single() { instance_ = nullptr; }
    static T* instance() { return instance_; }
};

template <typename T>
T* Single<T>::instance_ = nullptr;

}  // namespace utils
