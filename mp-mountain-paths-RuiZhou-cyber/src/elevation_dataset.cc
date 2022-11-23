#include "elevation_dataset.hpp"

#include <stdexcept>
using namespace std;

ElevationDataset::ElevationDataset(const std::string& filename,
                                   size_t width,
                                   size_t height):
    width_(width), height_(height) {
  ifstream ifs(filename);
  if (!ifs.is_open()) {
    throw runtime_error("file not open.");
  }

  int value = 0;
  for (size_t i = 0; i < height_; ++i) {
    vector<int> thing;
    for (size_t j = 0; j < width_; ++j) {
      ifs >> value;
      if (ifs.fail()) {
        throw runtime_error("too few or in valid input.");
      }
      thing.push_back(value);
    }
    data_.push_back(thing);
  }

  ifs >> value;
  if (!ifs.fail()) {
    throw runtime_error("too much data.");
  }

  max_ele_ = data_.at(0).at(0);
  min_ele_ = data_.at(0).at(0);
  for (size_t i = 0; i < height_; ++i) {
    for (size_t j = 0; j < width_; ++j) {
      if (data_.at(i).at(j) > max_ele_) {
        max_ele_ = data_.at(i).at(j);
      }
      if (data_.at(i).at(j) < min_ele_) {
        min_ele_ = data_.at(i).at(j);
      }
    }
  }
}

int ElevationDataset::DatumAt(size_t row, size_t col) const {
  if (0 > row || row > height_ - 1 || col < 0 || col > width_ - 1) {
    throw runtime_error("not valid row and col.");
  }
  return data_.at(row).at(col);
}

const std::vector<std::vector<int>>& ElevationDataset::GetData() const {
  return data_;
}
