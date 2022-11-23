#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>  // for size_t
#include <vector>

#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"
using namespace std;
class PathImage {
public:
  PathImage(const GrayscaleImage& image, const ElevationDataset& dataset);
  size_t Width() const { return width_; }
  size_t Height() const { return height_; }
  unsigned int MaxColorValue() const { return kMaxColorValue; }
  const std::vector<Path>& Paths() const { return paths_; }
  const std::vector<std::vector<Color>>& GetPathImage() const {
    return path_image_;
  }
  void ToPpm(const std::string& name) const;
  int Findnext(const ElevationDataset& dataset,
               int row,
               const int& next_col,
               const size_t& height_of_image);
  void Findgreen(const std::vector<Path>& paths,
                 std::vector<std::vector<Color>>& image);

private:
  std::vector<Path> paths_;
  size_t width_ = 0;
  size_t height_ = 0;
  std::vector<std::vector<Color>> path_image_;
  static const int kMaxColorValue = 255;
  static const int kRed1 = 252;
  static const int kRed2 = 25;
  static const int kRed3 = 63;
  static const int kGreen1 = 31;
  static const int kGreen2 = 253;
  static const int kGreen3 = 13;
};

#endif