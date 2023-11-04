## 模板定义与实例化
## 函数模板
### 模板类型参数 type parameter
### 非类型模板参数 nontype parameter
### 模板编译
函数模板和类模板的定义放在头文件中。
## 类模板
与函数模板不同，类模板必须在模板名后的尖括号中提供额外的信息。(C++17之后可以忽略CTAD)
### 类模板和友元
当一个类包含一个友元声明时，类与友元各自是否是模板并无关联。如果一个类模板包含一个非模板友元，则友元可以访问所有类模板实例。如果友元自身是模板，则类可以给所有友元模板实例授予访问权限，也可以只授权给特定实例。
- 一对一友元关系

为了引用模板的一个特定实例，必须首先声明模板自身。模板声明包括模板参数列表。

- 通用和特定的模板友元关系

为了让模板的所有实例成为友元，友元声明中必须使用与类模板本身不同的模板参数。

```cpp
// forward declaration necessary to befriend a specific instantiation of a template
template <typename T> class Pal;

class C
{ // C is an ordinary, nontemplate class
    friend class Pal<C>;    // Pal instantiated with class C is a friend to C
    // all instances of Pal2 are friends to C;
    // no forward declaration required when we befriend all instantiations
    template <typename T> friend class Pal2;
};

template <typename T>
class C2
{ // C2 is itself a class template
    // each instantiation of C2 has the same instance of Pal as a friend
    friend class Pal<T>;    // a template declaration for Pal must be in scope
    // all instances of Pal2 are friends of each instance of C2, prior declaration needed
    template <typename X> friend class Pal2;
    // Pal3 is a nontemplate class that is a friend of every instance of C2
    friend class Pal3;      // prior declaration for Pal3 not needed
};
```

类模板可以声明static成员。

```

template <typename T>
class Foo
{
public:
    static std::size_t count() { return ctr; }

private:
    static std::size_t ctr;
};

// instantiates static members Foo<string>::ctr and Foo<string>::count
Foo<string> fs;
// all three objects share the same Foo<int>::ctr and Foo<int>::count members
Foo<int> fi, fi2, fi3;
```
类模板的每个实例都有一个独有的static对象，而每个static成员必须有且只有一个定义。因此与定义模板的成员函数类似，static成员也应该定义成模板。

### 模板成员函数与虚函数
类成员函数不能即是模板函数又是虚函数:
```cpp
class A {
  template<typename T>
  virtual void print(T x);
};
```

但是模板类是可以有虚函数:
```
template<typename T>
class B {
  virtual void print(T x);
};
```

这里的区别在于，虚函数需要在编译过程中产生虚表和虚指针，编译器对虚表的实现是一个固定大小的。这里两种情况分别是：
- class A: 在编译`A`编译单元时，编译器无法判断`print`是否会在其他编译单元中实例化，虚表大小无法判断。
- class B: 在编译每个实例化的`class B`时, `print`函数不会影响虚表的大小。
