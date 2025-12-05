#pragma once
#include <iostream>
#include <memory>

class Circle {
public:
  Circle(float r): r_(r) {}
  float r_;
};
class Square {
public:
  Square(float d): d_(d) {}
  float d_;
};

namespace impl {
  inline void draw(const Circle& c) { std::cout << "circle draw: " << c.r_ << std::endl; }
  inline void serialize(const Circle& c) { std::cout << "circle serialize: " << c.r_ << std::endl; }

  inline void draw(const Square& s) { std::cout << "square draw: " << s.d_ << std::endl; }
  inline void serialize(const Square& s) { std::cout << "square serialize: " << s.d_ << std::endl; }
}

class Shape {
private:
  class ShapeConcept {
  public:
    virtual ~ShapeConcept() = default;
    virtual void draw() const = 0;
    virtual void serialize() const = 0;
    virtual std::unique_ptr<ShapeConcept> clone() = 0;
  };

  template<typename T>
  class ShapeModel : public ShapeConcept {
  public:
    // XXX: T&& is still rvalue reference since it's class template not function template.
    // which means following format cause an issue due to binding a rvalue to lvalue;
    // explicit ShapeModel(T&& x): x_{std::forward<T>(x)} {}
    
    explicit ShapeModel(const T& x): x_{x} {}

    void draw() const override {
      impl::draw(x_);
    }
    void serialize () const override {
      impl::serialize(x_);
    }
    std::unique_ptr<ShapeConcept> clone() override {
      return std::make_unique<ShapeModel<T>>(*this);
    }

  private:
    T x_;
  };
  
  friend void draw(const Shape& s) {
    s.pimpl->draw();
  }
  friend void serialize(const Shape& s) {
    s.pimpl->serialize();
  }

  std::unique_ptr<ShapeConcept> pimpl;

public:
  template<typename T>
  Shape(const T& x) : pimpl { std::make_unique<ShapeModel<T>>(x) } {}
  // Shape(const T& x) : pimpl {new ShapeModel<T>(x)} {}

  Shape(const Shape& s) {
    pimpl = s.pimpl->clone();
  }
  Shape& operator=(const Shape& s) {
    pimpl = s.pimpl->clone();
    return *this;
  }
  Shape(Shape&&) = default;
  Shape& operator=(Shape&&) = default;
};

