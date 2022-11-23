#include <cassert>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"
#include "path_image.hpp"

using namespace std;
int main(int argc, char* argv[]) {
  // /home/vagrant/src/mp-mountain-paths-RuiZhou-cyber/example-data/ex_input_data/prompt_5w_2h.dat
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " [input_file] " << std::endl;
    return 1;
  }
  ElevationDataset d(argv[1], 5, 2);
  GrayscaleImage gi(d);
  gi.ToPpm(
      "/home/vagrant/src/mp-mountain-paths-RuiZhou-cyber/example-data/"
      "answer.dat");
}