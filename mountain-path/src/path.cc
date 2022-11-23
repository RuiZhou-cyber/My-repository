#include "path.hpp"

#include <stdexcept>

using namespace std;
Path::Path(size_t length, size_t starting_row):
    length_(length), starting_row_(starting_row) {
  if (length_ <= 0) {
    throw runtime_error("length not right.");
  }
  path_.push_back(starting_row);
  for (size_t i = 1; i < length_; ++i) {
    path_.push_back(0);
  }
}

void Path::IncEleChange(unsigned int value) {
  if (value > 0) {
    ele_change_ += value;
  }
}

void Path::SetLoc(size_t col, size_t row) { path_.at(col) = row; }