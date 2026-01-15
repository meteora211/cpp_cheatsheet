#include <iostream>
#include <vector>
#include <tuple>
#include <variant>
using namespace std;

// **************************************************************
//                    dynamic
// **************************************************************
class ShapeDynamic {
public:
  virtual ~ShapeDynamic() = default;
  virtual void draw() = 0;
};

class CircleDynamic : public ShapeDynamic {
public:
  void draw() override {
    std::cout << "circle dynamic draw" << std::endl;
  }
};
class RectDynamic : public ShapeDynamic {
public:
  void draw() override {
    std::cout << "circle dynamic draw" << std::endl;
  }
};

void draw_dynamic(ShapeDynamic* shape) {
  shape->draw();
}

// **************************************************************
//                    CRTP classic 
// **************************************************************
template <typename Derived>
class ShapeCRTP {
public:
  void draw() const {
    static_cast<const Derived*>(this)->draw_impl();
  }
};

class CircleCRTP : public ShapeCRTP<CircleCRTP> {
public:
  void draw_impl() const {
    std::cout << "circle crtp draw" << std::endl;
  }
};

class RectCRTP : public ShapeCRTP<RectCRTP> {
public:
  void draw_impl() const {
    std::cout << "rect crtp draw" << std::endl;
  }
};

template<typename T>
void draw_crtp(ShapeCRTP<T>& s) {
  std::cout << " ----- ShapeCRTP ----- " << std::endl;
  s.draw();
  std::cout << " ----- ShapeCRTP ----- " << std::endl;
}

// **************************************************************
//                    CRTP Deducing this
// **************************************************************
class ShapeCRTPDeduce {
public:
  void draw(this const auto& self) {
    self.draw_impl();
  }
};

class CircleCRTPDeduce : public ShapeCRTPDeduce {
public:
  void draw_impl() const {
    std::cout << "circle crtp deduced draw" << std::endl;
  }
};

class RectCRTPDeduce : public ShapeCRTPDeduce {
public:
  void draw_impl() const {
    std::cout << "rect crtp deduced draw" << std::endl;
  }
};

// Can not declare argument with base class. CRTP is static polymorphism
// void draw(const ShapeCRTPDeduce& s)
template <typename T>
void draw_deduce(const T& s) {
  std::cout << " ----- ShapeCRTPDeduce ----- " << std::endl;
  s.draw();
  std::cout << " ----- ShapeCRTPDeduce ----- " << std::endl;
}

// **************************************************************
//                    Variant
// **************************************************************
class CircleVar {
public:
  void draw() {
    std::cout << "circle variant draw" << std::endl;
  }
};

class RectVar {
public:
  void draw() {
    std::cout << "rect variant draw" << std::endl;
  }
};

using ShapeVar = std::variant<CircleVar, RectVar>;

void draw_var(ShapeVar& shape) {
  auto visitor = [](auto& s){
    s.draw();
  };
  std::visit(visitor, shape);
}

// **************************************************************
//                    Tuple
// **************************************************************
class CircleTup {
public:
  void draw() {
    std::cout << "circle tuple draw" << std::endl;
  }
};

class RectTup {
public:
  void draw() {
    std::cout << "rect tuple draw" << std::endl;
  }
};

using ShapeTup = std::tuple<CircleTup, RectTup>;

void draw_tup(ShapeTup& shape) {
  auto visitor = [](auto& s){
    s.draw();
  };
  auto tup_apply = [=]<typename ...T>(T&... args) {
    (visitor(args),...);
  };
  std::apply(tup_apply, shape);
}

// **************************************************************
//                    Concept
// **************************************************************
template<typename T>
concept CShape = requires (T shape) {
  shape.draw();
};

template<CShape... TS>
struct ShapeCon {
  ShapeCon(auto s) : shape(s) {}
  void set_shape(auto s) {
    shape = s;
  }
  void draw() {
    std::visit([](auto& s){s.draw();}, shape);
  }
  std::variant <TS...> shape{};
};

struct Circle {
  Circle() = default;
  explicit Circle(int r): r{r} {}
  void draw() {
    std::cout << "circle draw" << r << std::endl;
  }
  int r{0};
};

struct Rect {
  Rect() = default;
  explicit Rect(int r): r{r} {}
  void draw() {
    std::cout << "rect draw" << r << std::endl;
  }
  int r{0};
};

template <CShape... TS>
struct ShapeConVec {
  template <typename T>
  void push(T&& elem) {
    std::get<vector<T>>(shape_vec).push_back(std::forward<T>(elem));
  }
  void draw() {
    std::apply(
      [](auto&... vec){
        ([&vec](){
          for (auto& v:vec) {v.draw();}
        }(),...);
      }
      ,shape_vec);
  }
  std::tuple<std::vector<TS>...> shape_vec;
};

void draw_con(auto& shape_con) {
  shape_con.draw();
}

int main() {
  std::cout << "\n--------------------------------" << std::endl;
  CircleDynamic c0{};
  RectDynamic r0{};
  draw_dynamic(&c0);
  draw_dynamic(&r0);
  std::cout << "--------------------------------\n" << std::endl;

  std::cout << "\n--------------------------------" << std::endl;
  CircleCRTP c1; c1.draw();
  RectCRTP r1; r1.draw();
  draw_crtp(c1); draw_crtp(r1);
  std::cout << "--------------------------------\n" << std::endl;

  std::cout << "\n--------------------------------" << std::endl;
  CircleCRTPDeduce c2; c2.draw();
  RectCRTPDeduce r2; r2.draw();
  draw_deduce(c2); draw_deduce(r2);
  std::cout << "--------------------------------\n" << std::endl;

  std::cout << "\n--------------------------------" << std::endl;
  ShapeVar c3{CircleVar{}};
  ShapeVar r3{RectVar{}};
  draw_var(c3); draw_var(r3);
  std::cout << "--------------------------------\n" << std::endl;

  std::cout << "\n--------------------------------" << std::endl;
  ShapeTup s0{CircleTup{}, RectTup{}};
  draw_tup(s0);
  std::cout << "--------------------------------\n" << std::endl;

  std::cout << "\n--------------------------------" << std::endl;
  ShapeCon<Circle, Rect> s1{Circle{}};
  s1.draw();
  draw_con(s1);
  s1.set_shape(Rect{});
  s1.draw();
  draw_con(s1);

  ShapeConVec<Circle, Rect> s2;
  s2.push(Circle{0});
  s2.push(Circle{1});
  s2.push(Rect{2});
  s2.push(Rect{3});
  s2.draw();
  std::cout << "--------------------------------\n" << std::endl;

}
