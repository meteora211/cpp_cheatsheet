#include <type_traits>

// NOTE: SFINAE 是指模板替换失败时，并不会报错。但是这个特性能够应用到模板元编程中。

// helper classes
class Null {};
// ENUM HACK: old fasion before c++11
template<typename T>
struct enum_is_pointer {
  enum {value = false};
  typedef Null type;
};

template<typename T>
struct enum_is_pointer<T*> {
  enum {value = true};
  typedef T* type;
};

// static intialization: old fasion in c++11
template<typename T>
struct static_is_pointer {
  const static bool value = false;
  typedef Null type;
};
template<typename T>
struct static_is_pointer<T*> {
  const static bool value = true;
  typedef T* type;
};

// constexpr: best practise
template<typename T>
struct constexpr_is_pointer {
  static constexpr bool value = false;
  typedef Null type;
};
template<typename T>
struct constexpr_is_pointer<T*> {
  static constexpr bool value = true;
  typedef T* type;
};

// ENABLE_IF

// VOID_T

// if constexpr

int main() {
  static_assert(enum_is_pointer<int>::value == false);
  static_assert(enum_is_pointer<int*>::value == true);
  static_assert(std::is_same_v<enum_is_pointer<int>::type, Null>);
  static_assert(std::is_same_v<enum_is_pointer<int*>::type, int*>);

  static_assert(static_is_pointer<int>::value == false);
  static_assert(static_is_pointer<int*>::value == true);
  static_assert(std::is_same_v<static_is_pointer<int>::type, Null>);
  static_assert(std::is_same_v<static_is_pointer<int*>::type, int*>);

  static_assert(constexpr_is_pointer<int>::value == false);
  static_assert(constexpr_is_pointer<int*>::value == true);
  static_assert(std::is_same_v<constexpr_is_pointer<int>::type, Null>);
  static_assert(std::is_same_v<constexpr_is_pointer<int*>::type, int*>);
}
