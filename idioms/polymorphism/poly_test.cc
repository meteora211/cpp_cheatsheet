#include <iostream>
#include <vector>
using namespace std;

class ShapeDynamic {
public:
  virtual ~ShapeDynamic() = default;
  virtual void draw() = 0;
};

class CircleDynamic : ShapeDynamic {
public:
  void draw() override {
    std::cout << "circle dynamic draw" << std::endl;
  }
};

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
void draw(ShapeCRTP<T>& s) {
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
void draw(const T& s) {
  std::cout << " ----- ShapeCRTPDeduce ----- " << std::endl;
  s.draw();
  std::cout << " ----- ShapeCRTPDeduce ----- " << std::endl;
}

int main() {

  // vector<ShapeCRTP> v_crtp{CircleCRTP(), RectCRTP()};
  // draw(v_crtp);
  CircleCRTP c1; c1.draw();
  RectCRTP r1; r1.draw();
  draw(c1); draw(r1);

  CircleCRTPDeduce c2; c2.draw();
  RectCRTPDeduce r2; r2.draw();
  draw(c2); draw(r2);
}
