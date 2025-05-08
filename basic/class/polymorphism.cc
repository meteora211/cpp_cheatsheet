#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Base {
public:
  Base() = default;
  virtual ~Base() = default;

  virtual void print() {
    cout << "Base class" << endl;
  }
};

class Derived : public Base {
public:
  Derived() = default;
  ~Derived() = default;

  virtual void print() {
    cout << "Derived class" << endl;
  }
};

int main() {
  // Static
  vector<Base> printers;
  for (int i = 0; i < 3; ++i) {
    printers.emplace_back(Base());
  }
  for (int i = 0; i < 3; ++i) {
    printers.emplace_back(Derived());
  }
  for (auto& p : printers) {
    p.print();
  }

  // Dynamic
  vector<unique_ptr<Base>> p_printers;
  for (int i = 0; i < 3; ++i) {
    p_printers.emplace_back(make_unique<Base>());
  }
  for (int i = 0; i < 3; ++i) {
    p_printers.emplace_back(make_unique<Derived>());
  }
  for (auto& p : p_printers) {
    p->print();
  }
}
