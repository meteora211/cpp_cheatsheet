#include <iostream>
#include <string>
#include <type_traits>
#include <complex>

// ref: (non)static data members initialization:
// https://www.cppstories.com/2015/02/non-static-data-members-initialization/

struct Data {
  std::string name;
  double value;
};

struct MoreData : Data {
  bool done;
};

template<typename T>
struct D : std::string, std::complex<T> {
  std::string data;
};

int main() {
  MoreData y1{{"y1", 1.0}, true};
  MoreData y2{"y2", 2.0, true};
  MoreData y3{}; // {{"", 0.0}, false}
  MoreData y4{{"y4"}}; // {{"y4", 0.0}, false}
  MoreData y5; // data member not initailized

  static_assert(std::is_aggregate_v<MoreData>);

  D<float> s{{"hello"}, {4.5, 6.7}, "world"};
  D<float> t{"hello", {4.5, 6.7}, "world"};
  static_assert(std::is_aggregate_v<decltype(s)>);
  std::cout << s.data << std::endl;
  std::cout << static_cast<std::string>(s) << std::endl;
  std::cout << static_cast<std::complex<float>>(t) << std::endl;
}
