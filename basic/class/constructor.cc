#include <iostream>

using namespace std;

class Printer {
public:
  Printer() {
    cout << this << " ctor called" << std::endl;
  }
#ifdef CTOR
  Printer(const Printer& rhs) {
    cout << this << " copy ctor called" << std::endl;
  }
  Printer(Printer&& rhs) {
    cout << this << " move ctor called" << std::endl;
  }
#else
  Printer(const Printer& rhs) = delete;
  Printer(Printer&& rhs) = delete;
#endif
};

void foo(Printer p) {
}

Printer bar() {
  return Printer{};
}

int main() {
#ifdef CTOR
  cout << "---------------" << endl;
  Printer tmp = Printer();
  foo(tmp);
#endif
  cout << "---------------" << endl;
  foo(Printer());
  cout << "---------------" << endl;
  Printer p = bar();
  cout << "---------------" << endl;
  foo(bar());
}
