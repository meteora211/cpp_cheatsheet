#include <iostream>

class test_class {
public:
  test_class(int x, int y) : x(x), y(y) {
    std::cout << "test ctor called" << std::endl;
  }
  ~test_class() {
    std::cout << "test dtor called" << std::endl;
  }
  void print() {
    std::cout << "x: " << x << " y: " << y << std::endl;
  }
private:
  int x, y;
};

template<typename T>
class simple_shared_ptr {
public:
  simple_shared_ptr(T* ptr = nullptr) : _ptr(ptr), _refcount(_ptr? new unsigned int(1) : nullptr) {}
  simple_shared_ptr(const simple_shared_ptr& rhs) : _ptr(rhs._ptr) , _refcount(rhs._refcount) {
    if (_refcount) {
      ++(*_refcount);
    }
  }
  simple_shared_ptr(simple_shared_ptr&& rhs) : _ptr(rhs._ptr), _refcount(rhs._refcount) {
    rhs._refcount = nullptr;
  }
  simple_shared_ptr& operator=(const simple_shared_ptr& other) {
    if (this != &other) {
      release();
      _ptr = other.ptr;
      _refcount = other._refcount;
      ++(*_refcount);
    }
    return *this;
  }
  simple_shared_ptr& operator=(const simple_shared_ptr&& other) {
    if (this != &other) {
      release();
      _ptr = other.ptr;
      _refcount = other._refcount;
      other._refcount = nullptr;
    }
    return *this;
  }

  T* operator->() {
    return _ptr;
  }
  T& operator*() {
    return *_ptr;
  }
  T* get() {
    return _ptr;
  }
  unsigned int ref_count() {
    return _refcount ? *_refcount : 0;
  }

  ~simple_shared_ptr() {
    release();
  }

  void release() {
    if (_refcount) {
      --(*_refcount);
      if (*_refcount == 0) {
        delete _ptr;
        delete _refcount;
      }
    }
  }

private:
  T* _ptr;
  mutable unsigned int* _refcount;
};

int main() {
  auto t1 = simple_shared_ptr<test_class>(new test_class(1,2));
  t1->print();
  auto t2 = simple_shared_ptr<test_class>(simple_shared_ptr<test_class>(new test_class(2,3)));
  t2->print();
  std::cout << "ref_count: t1: " << t1.ref_count() << " t2: " << t2.ref_count() << std::endl;
  auto t3 = t1;
  auto t4 = std::move(t2);
  std::cout << "ref_count: t1: " << t1.ref_count() << " t2: " << t2.ref_count() << std::endl;
  std::cout << "ref_count: t3: " << t3.ref_count() << " t4: " << t4.ref_count() << std::endl;
}
