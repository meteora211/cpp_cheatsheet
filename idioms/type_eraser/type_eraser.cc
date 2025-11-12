#include <vector>
#include "type_eraser.h"


void draw_all_shapes(const std::vector<Shape>& shapes) {
  for (const auto& shape : shapes) {
    draw(shape);
  }
}

int main() {
  std::vector<Shape> shapes;
  shapes.emplace_back(Circle{3});
  shapes.emplace_back(Square{4});
  draw_all_shapes(shapes);
}
