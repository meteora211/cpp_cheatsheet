#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

template <typename CB> class CountCall {
public:
  CountCall(CB cb) : callback{cb} {}

  template <typename... Args> decltype(auto) operator()(Args &&...args) {
    ++calls;
    // TODO: unpack and print args
    return callback(std::forward<Args>(args)...);
  }

  long count() const { return calls; }

private:
  CB callback;
  long calls = 0;
};

int main() {
  {
    // basic CTAD
    std::vector v1{42};     // vector<int>
    std::vector v2{v1};     // vector<int>
    std::vector v3{v1, v1}; // vector<vector<int>>
  }
  {
    // lambda as template arg
    std::vector vv{1, 3, 2, 5, 4, 7, 6, 9, 8};
    CountCall sc([](int x, int y) { return x > y; });
    std::sort(vv.begin(), vv.end(), std::ref(sc));
    std::cout << "sorted with " << sc.count() << " calls\n";
  }
}
