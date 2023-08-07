#pragma once
#include <memory>

template <class T>
class UniquePtr{
  T* ptr_;
 public:
  explicit UniquePtr(T* ptr = nullptr) {
    ptr_ = ptr;
  }

  UniquePtr(const UniquePtr&) = delete;
  UniquePtr& operator=(const UniquePtr&) = delete;

  ~UniquePtr() {
    delete ptr_;
  }

  UniquePtr(UniquePtr&& other) noexcept {
    ptr_ = std::move(other.ptr_);
    other.ptr_ = nullptr;
  }

  UniquePtr& operator=(UniquePtr&& other) noexcept {  // NOLINT
    if (this != &other) {
      delete ptr_;
      ptr_ = std::move(other.ptr_);
      other.ptr_ = nullptr;
    }
    return *this;
  }

  const T* Release() {
    auto new_ptr = ptr_;
    ptr_ = nullptr;
    return new_ptr;
  }

  void Reset(T* ptr = nullptr) {
    delete ptr_;
    ptr_ = ptr;
  }

  void Swap(UniquePtr& other) {
    auto temp = ptr_;
    ptr_ = other.ptr_;
    other.ptr_ = temp;
  }

  T* Get() const{
    return ptr_;
  }

  T& operator*() const{
    return *ptr_;
  }

  T* operator->() const{
    return ptr_;
  }

  explicit operator bool() const {
    return (ptr_ != nullptr);
  }
};