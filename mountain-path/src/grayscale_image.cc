#include "grayscale_image.hpp"

#include <cmath>
#include <stdexcept>

using namespace std;
GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset) {
  // size_t width_;
  // size_t height_;
  // std::vector<std::vector<Color>> image_;
  width_ = dataset.Width();
  height_ = dataset.Height();
  int min = dataset.MinEle();
  int max = dataset.MaxEle();
  for (size_t i = 0; i < height_; ++i) {
    std::vector<Color> image;
    for (size_t j = 0; j < width_; ++j) {
      int curr = dataset.GetData().at(i).at(j);
      if (max == min) {
        Color a(0, 0, 0);
        image.push_back(a);
      } else {
        double shade_of_gray =
            round(double((curr - min)) / (max - min) * kMaxColorValue);
        int to_in = int(shade_of_gray);
        Color b(to_in, to_in, to_in);
        image.push_back(b);
      }
    }
    image_.push_back(image);
  }
}

GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height) {
  ElevationDataset dataset(filename, width, height);
  width_ = dataset.Width();
  height_ = dataset.Height();
  int min = dataset.MinEle();
  int max = dataset.MaxEle();
  for (size_t i = 0; i < height_; ++i) {
    std::vector<Color> image;
    for (size_t j = 0; j < width_; ++j) {
      int curr = dataset.GetData().at(i).at(j);
      if (max == min) {
        Color a(0, 0, 0);
        image.push_back(a);
      } else {
        double shade_of_gray =
            round(double((curr - min)) / (max - min) * kMaxColorValue);
        int to_in = int(shade_of_gray);
        Color b(to_in, to_in, to_in);
        image.push_back(b);
      }
    }
    image_.push_back(image);
  }
}

const Color& GrayscaleImage::ColorAt(int row, int col) const {
  if (0 > row || row > int(height_ - 1) || col < 0 || col > int(width_ - 1)) {
    throw runtime_error("not valid row and col.");
  }
  return image_.at(row).at(col);
}

void GrayscaleImage::ToPpm(const std::string& name) const {
  std::ofstream ifs{name};
  if (!ifs.is_open()) {
    throw runtime_error("file cannot open");
  }
  ifs << "P3"
      << "\n"
      << width_ << " " << height_ << "\n"
      << "255" << std::endl;

  for (size_t i = 0; i < height_; ++i) {
    string curr_line;
    for (size_t j = 0; j < width_; ++j) {
      Color curr_color = image_.at(i).at(j);
      curr_line += to_string(curr_color.Red()) + " " +
                   to_string(curr_color.Green()) + " " +
                   to_string(curr_color.Blue()) + " ";
    }
    curr_line = curr_line.substr(0, curr_line.length() - 1);
    ifs << curr_line << endl;
  }
}