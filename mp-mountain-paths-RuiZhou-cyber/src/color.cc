#include "color.hpp"

#include <stdexcept>
using namespace std;

bool Color::ValidColor(int a) const { return a >= 0 && a <= kMaxColorValue; }

Color::Color() {
  red_ = 0;
  green_ = 0;
  blue_ = 0;
}

Color::Color(int r, int g, int b) {
  if (ValidColor(r) && ValidColor(g) && ValidColor(b)) {
    red_ = r;
    green_ = g;
    blue_ = b;
  } else {
    throw std::runtime_error("invalid color");
  }
}

// do not modify
bool operator==(const Color& rhs, const Color& lhs) {
  return (rhs.Red() == lhs.Red() && rhs.Green() == lhs.Green() &&
          rhs.Blue() == lhs.Blue());
}