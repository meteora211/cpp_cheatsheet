#include <type_traits>
#include <concepts>

// NOTE: SFINAE 是指模板替换失败时，并不会报错。但是这个特性能够应用到模板元编程中。

// helper classes
class Null {};
template <typename T> struct dump;

// ENUM HACK: old fasion before c++11
template <typename T> struct enum_is_pointer {
  enum { value = false };
  typedef Null type;
};

template <typename T> struct enum_is_pointer<T *> {
  enum { value = true };
  typedef T *type;
};

// static intialization: old fasion in c++11
template <typename T> struct static_is_pointer {
  const static bool value = false;
  typedef Null type;
};
template <typename T> struct static_is_pointer<T *> {
  const static bool value = true;
  typedef T *type;
};

// constexpr: best practise
template <typename T> struct constexpr_is_pointer {
  static constexpr bool value = false;
  typedef Null type;
};
template <typename T> struct constexpr_is_pointer<T *> {
  static constexpr bool value = true;
  typedef T *type;
};

// ENABLE_IF
template <typename T, class Enable = void> struct enable_if_is_pointer {
  static constexpr bool value = false;
  typedef Null type;
};
template <typename T>
struct enable_if_is_pointer<T, typename std::enable_if<std::is_pointer_v<T>>::type> {
  static constexpr bool value = true;
  typedef T type;
};

// if constexpr
template<typename T>
constexpr bool if_constexpr_is_pointer() {
  if constexpr (std::is_pointer_v<T>) {
    return true;
  }
  return false;
}

// VOID_T
template<typename T, class Enable = void>
struct void_t_is_pointer {
  static constexpr bool value = false;
  typedef Null type;
};
template<typename T>
struct void_t_is_pointer<T, std::void_t<decltype(*std::declval<T>())>> {
  static constexpr bool value = true;
  typedef T type;
};

// concepts && requires
template<typename T>
struct require_pointer {
  static constexpr bool value = false;
  typedef Null type;
};
template<typename T>
requires std::is_pointer_v<T>
struct require_pointer<T> {
  static constexpr bool value = true;
  typedef T type;
};

int main() {
  static_assert(enum_is_pointer<int>::value == false);
  static_assert(enum_is_pointer<int *>::value == true);
  static_assert(std::is_same_v<enum_is_pointer<int>::type, Null>);
  static_assert(std::is_same_v<enum_is_pointer<int *>::type, int *>);

  static_assert(static_is_pointer<int>::value == false);
  static_assert(static_is_pointer<int *>::value == true);
  static_assert(std::is_same_v<static_is_pointer<int>::type, Null>);
  static_assert(std::is_same_v<static_is_pointer<int *>::type, int *>);

  static_assert(constexpr_is_pointer<int>::value == false);
  static_assert(constexpr_is_pointer<int *>::value == true);
  static_assert(std::is_same_v<constexpr_is_pointer<int>::type, Null>);
  static_assert(std::is_same_v<constexpr_is_pointer<int *>::type, int *>);

  static_assert(enable_if_is_pointer<int>::value == false);
  static_assert(enable_if_is_pointer<int *>::value == true);
  static_assert(std::is_same_v<enable_if_is_pointer<int>::type, Null>);
  static_assert(std::is_same_v<enable_if_is_pointer<int *>::type, int *>);

  static_assert(if_constexpr_is_pointer<int>() == false);
  static_assert(if_constexpr_is_pointer<int *>() == true);

  // dump<decltype(*std::declval<int*>())>();
  static_assert(void_t_is_pointer<int>::value == false);
  static_assert(void_t_is_pointer<int *>::value == true);
  static_assert(std::is_same_v<void_t_is_pointer<int>::type, Null>);
  static_assert(std::is_same_v<void_t_is_pointer<int *>::type, int *>);

  static_assert(require_pointer<int>::value == false);
  static_assert(require_pointer<int*>::value == true);
  static_assert(std::is_same_v<require_pointer<int>::type, Null>);
  static_assert(std::is_same_v<require_pointer<int *>::type, int *>);
}
