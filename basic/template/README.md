
## TypeTraits

前置特性

- enum hack
- 偏特化

### 是什么

A type trait is a simple template struct that contains a member constant, which in turn holds the answer to the question the type trait asks or the transformation it performs. 

ref: https://www.internalpointers.com/post/quick-primer-type-traits-modern-cpp

### 怎么做

考虑一般意义上的简单typetraits, 对于一个以下定义的class：
```
template <typename T>
class TypeTraits;
```

template`T`就是模板类在做typetrait时的实际输入，而输出会被定义为一个type保存在类内部。而偏特化的内部类定义充当了处理输入输出的函数。

- 输入： type `T`
- 输出： 类内定义的type `value`
- 函数： 偏特化的模板类

在考虑实现之前，先看下`TypeTraits`的使用方法, 可以通过一下代码判断输入的template `T` 是否为一个指针，代码在编译期返回一个bool值：
```
TypeTraits<int*>::is_pointer
```

据此，可以写出一下代码保存`is_pointer`, 这里用到了enum hack来做类内成员变量的初始化，如果编译器支持当然也可以使用`static`类内初始化。

```
template <typename T>
class TypeTraits{
  enum {is_pointer = some_value};
  /* static const bool is_pointer = some_value; */
};
```

对于`is_pointer`来说，当输入`T` 是指针时，应该返回true，否则为false。 可以考虑偏特化来实现这一功能，依据的原理是类模板/函数模板在匹配时，如果有一个模板比其他模板更特例化，则选择此模板。

借此可以定义一个模板类`PointerTraits`以及特例化版本。对于`PointerTraits<T>`的实例化，当`T`为指针类型时，将会选择更加特例化的`PointerTraits<U*>`。

```
template <typename U>
struct PointerTraits {};
template <typename U>
struct PointerTraits<U*> {};
```

再次使用enum hack，可以写出简单的TypeTraits用于判断给定模板`T` 是否为指针类型：

```
class NullType {};

template <typename T>
class TypeTraits {
public:
  template <typename U>
  struct PointerTraits {
    enum { value = false };
    typedef NullType PointeeType;
  };
  template <typename U>
  struct PointerTraits<U*> {
    enum { value = true };
    typedef U PointeeType;
  };

  enum {is_pointer = PointerTraits<T>::value};
  typedef typename PointerTraits<T>::PointeeType PointeeType;
};

```
