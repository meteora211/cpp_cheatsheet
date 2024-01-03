#include <iostream>
#include <string>

// PROBLEM: how to define a static variable inside class
// class MyClass {
//   static std::string msg{"OK"};
// };

// ref: https://zhuanlan.zhihu.com/p/394975612

// method 1
struct MyClass1 {
  static std::string msg;
};

std::string MyClass1::msg {"OK"};

// method 2
struct MyClass2 {
  static std::string getMsg() {
    static std::string msg {"OK"};
    return msg;
  }
};


int main() {
  std::cout << MyClass1::msg << std::endl;
  std::cout << MyClass2::getMsg() << std::endl;
}
