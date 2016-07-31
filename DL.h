#ifndef DL_H_
#define DL_H_

#include <dlfcn.h>

#include <iostream>
#include <stdexcept>
#include <utility>

class DL
{
private:
  template<class T>
  using CreateFunction = T* (*)();
  template<class T>
  using DestroyFunction = void (*)(T*);

public:
  explicit DL(const std::string& path) : handle_(nullptr)
  {
    handle_ = dlopen(path.c_str(), RTLD_LAZY);
    std::cout << "Dl ctor\n";
    if (handle_ == nullptr) {
      throw std::runtime_error(dlerror());
    }
  }

  DL(const DL&) = delete;
  DL& operator=(const DL&) = delete;

  DL(DL&& that) : handle_(nullptr)
  {
    std::cout << "Dl move ctor\n";
    swap(*this, that);
  }

  DL& operator=(DL&& that)
  {
    std::cout << "Dl move assignment\n";
    swap(*this, that);
    return *this;
  }

  ~DL() noexcept
  {
    std::cout << "Dl dtor\n";
    if (handle_) {
      dlclose(handle_);
    }
  }

  friend void swap(DL& left, DL& right) noexcept
  {
    using std::swap;
    swap(left.handle_, right.handle_);
  }

  template<class T>
  std::unique_ptr<T,DestroyFunction<T>> create(
    const std::string& createName = T::createFunctionName(),
    const std::string& destroyName = T::destroyFunctionName()) const
  {
    if (handle_ == nullptr) {
      throw std::runtime_error("DL object does not own a valid handle.");
    }
    const auto destroy = reinterpret_cast<DestroyFunction<T>>(dlsym(handle_, destroyName.c_str()));
    if (destroy == nullptr) {
      throw std::runtime_error(dlerror());
    }
    const auto create = reinterpret_cast<CreateFunction<T>>(dlsym(handle_, createName.c_str()));
    if (create == nullptr) {
      throw std::runtime_error(dlerror());
    }
    return std::unique_ptr<T, decltype(destroy)>(create(), destroy);
  }

private:
  void* handle_;
};


#endif
