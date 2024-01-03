#include <iostream>
#include <string>

// PROBLEM: how to define a static variable inside class
// class MyClass {
//   static std::string msg{"OK"};
// };

// ref: https://zhuanlan.zhihu.com/p/394975612

// method 1: define static outside
struct MyClass1 {
  static std::string msg;
};

std::string MyClass1::msg {"1.OK"};

// method 2: static local variable
struct MyClass2 {
  static std::string getMsg() {
    static std::string msg {"2.OK"};
    return msg;
  }
};

// method 3: variable template (since c++14)
template<typename T = std::string> T VTmsg{"VT.OK"};

// C++17: inline static
struct MyClass3 {
  inline static std::string msg{"3.OK"};
};

int main() {
  std::cout << MyClass1::msg << std::endl;
  std::cout << MyClass2::getMsg() << std::endl;
  std::cout << VTmsg<> << std::endl;
  std::cout << MyClass3::msg << std::endl;
}
