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
}
