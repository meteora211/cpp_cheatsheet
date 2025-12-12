#include <string>
#include <iostream>

class TestClass {
public:
  TestClass() {
    std::cout << "default init." << std::endl;
  }
  TestClass(std::string str) : str(str) {
    std::cout << "init " << str << std::endl;
  }
  TestClass(const TestClass& rhs) {
    str = rhs.str;
    std::cout << "copy init " << str << std::endl;
  }
  TestClass& operator=(const TestClass& rhs) {
    str = rhs.str;
    std::cout << "copy assign " << str << std::endl;
    return *this;
  }
  void print() {
    std::cout << "\nprint " << str << "\n" << std::endl;
  }
private:
  std::string str;
};

struct Point {
  int x;
  int y;
};

void f(TestClass t) {
  t.print();
}

int main() {
  TestClass t1{"t1"}; // value init
  TestClass t2("t2"); // direct init
  // NOTE: empty parentheses interpreted as a function declaration
  // TestClass t3(); 
  TestClass t3;       // default init
  TestClass t4{};     // default init
  TestClass t5 = TestClass();     // value init. it requires copy ctor without copy elision
  TestClass t6 = t1;     // copy init
  TestClass t7 = TestClass("t7");     // copy init
  t7 = t1; // copy assign

  f(t1);
  // NOTE: explicit on ctor will forbidden implicit cast
  f(std::string("t8"));

  [[maybe_unused]] Point p1 {1, 2}; // aggregate init
  [[maybe_unused]] Point p2 {.x=1, .y = 2}; // designated init
}
