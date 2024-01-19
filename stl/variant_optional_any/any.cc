#include <any>
#include <string>
#include <iostream>
#include <vector>
#include <complex>


// variant -> have one type/value among the variant
// optional -> nullopt or type/value
// any -> could be any type/value

int main() {
  {
    // general
    std::any a; // a: empty
    std::any b = 4.3; // b: double 4.3
    a = 42; // a: int 42
    b = std::string("hi"); // b: string hi
    // use const string& to avoid copy
    std::cout << std::any_cast<int>(a) << std::any_cast<const std::string&>(b) << std::endl;
    // std::cout << std::any_cast<std::string>(a) << std::endl; // runtime exception
    // any_cast accept variable address as input, will return nullptr when failed.
    if (auto p = std::any_cast<std::string>(&a); !p) {
      std::cout << "cast a to string failed." << std::endl;
    }

    // reset value
    a.reset();
    if (!a.has_value()) {
      std::cout << "after reset(), has_value() return false." << std::endl;
    }

    a = "hello";
    if (a.type() == typeid(const char*)) { // true
      std::cout << "a = \"hello\" -> a.type() == const char*" << std::endl;
    }

    std::vector<std::any> v {42, std::string{"hello"}};
    for (const auto& elem : v) {
      if (auto p = std::any_cast<const std::string>(&elem)) {
        std::cout << "string " << *p << std::endl;
      } else if (auto p = std::any_cast<int>(&elem)) {
        std::cout << "int " << *p << std::endl;
      }
    }
  }

  {
    // construct
    std::any a1 = 42; // int 42
    std::any a2 {std::in_place_type<long>, 42}; // long 42
    std::any a3 = "hello"; // const char* "hello"
    std::any a4 {std::in_place_type<std::string>, "hello"}; // string "hello"
    std::any a5 {std::complex{4.0, 5.0}};
    std::any a6 {std::in_place_type<std::complex<double>>, 4, 5};
    auto a7 = std::make_any<float>(3);
    auto a8 = std::make_any<std::complex<double>>(3, 4);
  }
  {
    // modify
    std::any a;
    a = 42; // int 42
    a = "hello"; // const char*
    a.emplace<std::string>("hello");
    a.emplace<std::complex<double>>(4.4, 5.5);
  }
  {
    // move
    std::string s("hello");
    std::any a;
    a = std::move(s);
    s = std::move(std::any_cast<std::string&>(a));
  }
}
