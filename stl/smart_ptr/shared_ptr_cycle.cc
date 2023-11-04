#include <memory>
#include <iostream>

using namespace std;

struct B;
struct A {
  A(shared_ptr<B> ptr);
  ~A(){
    std::cout << "A dtor" << std::endl;
  }
  shared_ptr<B> ptr;
};

struct B {
  B(shared_ptr<A> ptr): ptr(ptr) {
    std::cout << "B ctor" << std::endl;
  }
  ~B(){
    std::cout << "B dtor" << std::endl;
  }
  shared_ptr<A> ptr;
};

A::A(shared_ptr<B> ptr) : ptr(ptr) {
  std::cout << "A ctor" << std::endl;
}

int main() {
  auto a = make_shared<A>(nullptr);
  auto b = make_shared<B>(nullptr);
  a->ptr = b;
  b->ptr = a;
}
