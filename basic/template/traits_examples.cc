#include <type_traits>

template<typename T>
struct array_size;

template<typename T, std::size_t N>
struct array_size<T[N]> {
  static constexpr std::size_t len = N;
  using value_type = T;
};

int main() {
  static_assert(array_size<int[5]>::len == 5);
  static_assert(std::is_same_v<array_size<int[5]>::value_type, int>);
}
