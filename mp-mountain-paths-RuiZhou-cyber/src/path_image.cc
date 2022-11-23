#include "path_image.hpp"

using namespace std;

int PathImage::Findnext(const ElevationDataset& dataset,
                        int row,
                        const int& next_col,
                        const size_t& height_of_image) {
  int curr_row = row;
  int curr_data = dataset.GetData().at(curr_row).at(next_col - 1);
  int mid =
      dataset.GetData().at(curr_row).at(next_col);  // current node right data
  int min_ele_difference =
      abs(mid - curr_data);  // the elevation difference between current
                             // node and right node
  if (row != int(height_of_image - 1)) {
    int down =
        dataset.GetData().at(row + 1).at(next_col);  // right down node data
    int ele_difference_down =
        abs(down - curr_data);  // the elevation difference between current
                                // node and right down data
    if (ele_difference_down < min_ele_difference) {
      curr_row = row + 1;
      min_ele_difference = ele_difference_down;
    }
  }
  if (row != 0) {
    int up = dataset.GetData().at(row - 1).at(next_col);  // right up node data
    int ele_difference_up =
        abs(up - curr_data);  // the elevation difference between current
                              // node and right up data
    if (ele_difference_up < min_ele_difference) {
      curr_row = row - 1;
      min_ele_difference = ele_difference_up;
    }
  }
  return curr_row;
}

void PathImage::Findgreen(const std::vector<Path>& paths,
                          std::vector<std::vector<Color>>& image) {
  int least_index = 0;
  size_t least_ele = paths.at(0).EleChange();
  for (int i = 0; i < int(paths.size()); ++i) {
    if (paths.at(i).EleChange() < least_ele) {
      least_ele = paths.at(i).EleChange();
      least_index = i;
    }
  }
  Color green(kGreen1, kGreen2, kGreen3);
  for (size_t j = 0; j < paths.at(least_index).Length(); ++j) {
    size_t row = paths.at(least_index).GetPath().at(j);
    size_t col = j;
    image.at(row).at(col) = green;
  }
}

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset) {
  height_ = image.Height();
  width_ = image.Width();
  path_image_ = image.GetImage();
  for (size_t i = 0; i < height_; ++i) {
    Path a(width_, i);
    int curr_row = int(i);
    Color red(kRed1, kRed2, kRed3);
    path_image_.at(i).at(0) = red;
    for (int j = 1; j < int(width_); ++j) {
      int curr_data = dataset.GetData().at(curr_row).at(j - 1);
      int min_row = Findnext(dataset, curr_row, j, height_);
      int min_ele_difference =
          abs(dataset.GetData().at(min_row).at(j) - curr_data);
      a.IncEleChange(min_ele_difference);
      a.SetLoc(j, min_row);
      path_image_.at(min_row).at(j) = red;
      curr_row = min_row;
    }
    paths_.push_back(a);
  }
  Findgreen(paths_, path_image_);
}

void PathImage::ToPpm(const std::string& name) const {
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
      Color curr_color = path_image_.at(i).at(j);
      curr_line += to_string(curr_color.Red()) + " " +
                   to_string(curr_color.Green()) + " " +
                   to_string(curr_color.Blue()) + " ";
    }
    curr_line = curr_line.substr(0, curr_line.length() - 1);
    ifs << curr_line << endl;
  }
}