#include <memory>
#include <iostream>
#include <string>
#include <map>

using namespace std;

struct PrintHelper {
  PrintHelper() {
    cout << "print: " << this << " ctor call" << endl;
  }
  PrintHelper(const PrintHelper&) {
    ++cp_ctor_count;
    cout << "print: " << this << " copy call " << cp_ctor_count << endl;
  }
  PrintHelper(PrintHelper&&) {
    ++mv_ctor_count;
    cout << "print: " << this << " move call " << mv_ctor_count << endl;
  }
  PrintHelper& operator=(const PrintHelper&) {
    ++cp_asig_count;
    cout << "print: " << this << " copy assign call " << cp_asig_count << endl;
    return *this;
  }
  PrintHelper& operator=(PrintHelper&&) {
    ++mv_asig_count;
    cout << "print: " << this << " move assign call" << mv_asig_count << endl;
    return *this;
  }
  ~PrintHelper() {
    cout << "print: " << this << " dtor call" << endl;
  }
  void print_address() {
    cout << this << endl;
  }
  static int cp_ctor_count;
  static int mv_ctor_count;
  static int cp_asig_count;
  static int mv_asig_count;
};
int PrintHelper::cp_ctor_count=0;
int PrintHelper::mv_ctor_count=0;
int PrintHelper::cp_asig_count=0;
int PrintHelper::mv_asig_count=0;

unique_ptr<PrintHelper> create() {
  auto ptr = make_unique<PrintHelper>();
  return ptr;
}
int main() {
  // Create unique ptr
  // unique_ptr as return
  auto a = create();
}
