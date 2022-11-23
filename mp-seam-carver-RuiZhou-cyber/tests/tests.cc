// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include <catch/catch.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "image_ppm.hpp"
#include "pixel.hpp"
#include "seam_carver.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("True == True", "") { REQUIRE(true == true); }

TEST_CASE("get_energy") {
  ImagePPM a(
      "/home/vagrant/src/mp-seam-carver-RuiZhou-cyber/images/image1.ppm");
  SeamCarver b(a);
  REQUIRE(b.GetEnergy(0, 0) == 0);
  REQUIRE(b.GetEnergy(0, 1) == 10);
  REQUIRE(b.GetEnergy(0, 2) == 30);
  REQUIRE(b.GetEnergy(0, 3) == 10);
  REQUIRE(b.GetEnergy(0, 4) == 16);

  REQUIRE(b.GetEnergy(1, 0) == 10);
  REQUIRE(b.GetEnergy(1, 1) == 28);
  REQUIRE(b.GetEnergy(1, 2) == 2);
  REQUIRE(b.GetEnergy(1, 3) == 28);
  REQUIRE(b.GetEnergy(1, 4) == 4);

  REQUIRE(b.GetEnergy(2, 0) == 30);
  REQUIRE(b.GetEnergy(2, 1) == 2);
  REQUIRE(b.GetEnergy(2, 2) == 4);
  REQUIRE(b.GetEnergy(2, 3) == 6);
  REQUIRE(b.GetEnergy(2, 4) == 0);

  REQUIRE(b.GetEnergy(3, 0) == 10);
  REQUIRE(b.GetEnergy(3, 1) == 28);
  REQUIRE(b.GetEnergy(3, 2) == 6);
  REQUIRE(b.GetEnergy(3, 3) == 12);
  REQUIRE(b.GetEnergy(3, 4) == 0);

  REQUIRE(b.GetEnergy(4, 0) == 16);
  REQUIRE(b.GetEnergy(4, 1) == 4);
  REQUIRE(b.GetEnergy(4, 2) == 0);
  REQUIRE(b.GetEnergy(4, 3) == 0);
  REQUIRE(b.GetEnergy(4, 4) == 0);
}

TEST_CASE("cal vertical value matrix") {
  ImagePPM a(
      "/home/vagrant/src/mp-seam-carver-RuiZhou-cyber/images/image1.ppm");
  SeamCarver b(a);
  int** value_matrix = b.Calvaluematrixvertical();
  REQUIRE(value_matrix[0][0] == 18);
  REQUIRE(value_matrix[0][1] == 18);
  REQUIRE(value_matrix[0][2] == 38);
  REQUIRE(value_matrix[0][3] == 14);
  REQUIRE(value_matrix[0][4] == 20);

  REQUIRE(value_matrix[1][0] == 18);
  REQUIRE(value_matrix[1][1] == 36);
  REQUIRE(value_matrix[1][2] == 8);
  REQUIRE(value_matrix[1][3] == 28);
  REQUIRE(value_matrix[1][4] == 4);

  REQUIRE(value_matrix[2][0] == 44);
  REQUIRE(value_matrix[2][1] == 8);
  REQUIRE(value_matrix[2][2] == 10);
  REQUIRE(value_matrix[2][3] == 6);
  REQUIRE(value_matrix[2][4] == 0);

  REQUIRE(value_matrix[3][0] == 14);
  REQUIRE(value_matrix[3][1] == 28);
  REQUIRE(value_matrix[3][2] == 6);
  REQUIRE(value_matrix[3][3] == 12);
  REQUIRE(value_matrix[3][4] == 0);

  REQUIRE(value_matrix[4][0] == 16);
  REQUIRE(value_matrix[4][1] == 4);
  REQUIRE(value_matrix[4][2] == 0);
  REQUIRE(value_matrix[4][3] == 0);
  REQUIRE(value_matrix[4][4] == 0);

  for (int i = 0; i < b.GetHeight(); i++) {
    delete[] value_matrix[i];
  }

  delete[] value_matrix;
}

TEST_CASE("cal horizontal value matrix") {
  ImagePPM a(
      "/home/vagrant/src/mp-seam-carver-RuiZhou-cyber/images/image1.ppm");
  SeamCarver b(a);
  int** value_matrix = b.Calvaluematrixhorizontal();
  REQUIRE(value_matrix[0][0] == 18);
  REQUIRE(value_matrix[0][1] == 18);
  REQUIRE(value_matrix[0][2] == 44);
  REQUIRE(value_matrix[0][3] == 14);
  REQUIRE(value_matrix[0][4] == 16);

  REQUIRE(value_matrix[1][0] == 18);
  REQUIRE(value_matrix[1][1] == 36);
  REQUIRE(value_matrix[1][2] == 8);
  REQUIRE(value_matrix[1][3] == 28);
  REQUIRE(value_matrix[1][4] == 4);

  REQUIRE(value_matrix[2][0] == 38);
  REQUIRE(value_matrix[2][1] == 8);
  REQUIRE(value_matrix[2][2] == 10);
  REQUIRE(value_matrix[2][3] == 6);
  REQUIRE(value_matrix[2][4] == 0);

  REQUIRE(value_matrix[3][0] == 14);
  REQUIRE(value_matrix[3][1] == 28);
  REQUIRE(value_matrix[3][2] == 6);
  REQUIRE(value_matrix[3][3] == 12);
  REQUIRE(value_matrix[3][4] == 0);

  REQUIRE(value_matrix[4][0] == 20);
  REQUIRE(value_matrix[4][1] == 4);
  REQUIRE(value_matrix[4][2] == 0);
  REQUIRE(value_matrix[4][3] == 0);
  REQUIRE(value_matrix[4][4] == 0);

  for (int i = 0; i < b.GetHeight(); i++) {
    delete[] value_matrix[i];
  }

  delete[] value_matrix;
}

TEST_CASE("get energy after verticle") {
  ImagePPM a(
      "/home/vagrant/src/mp-seam-carver-RuiZhou-cyber/images/image1.ppm");
  SeamCarver b(a);
  b.RemoveVerticalSeam();
  REQUIRE(b.GetEnergy(0, 0) == 0);
  REQUIRE(b.GetEnergy(0, 1) == 10);
  REQUIRE(b.GetEnergy(0, 2) == 14);
  REQUIRE(b.GetEnergy(0, 3) == 10);

  REQUIRE(b.GetEnergy(1, 0) == 6);
  REQUIRE(b.GetEnergy(1, 1) == 28);
  REQUIRE(b.GetEnergy(1, 2) == 2);
  REQUIRE(b.GetEnergy(1, 3) == 20);

  REQUIRE(b.GetEnergy(2, 0) == 18);
  REQUIRE(b.GetEnergy(2, 1) == 2);
  REQUIRE(b.GetEnergy(2, 2) == 4);
  REQUIRE(b.GetEnergy(2, 3) == 6);

  REQUIRE(b.GetEnergy(3, 0) == 10);
  REQUIRE(b.GetEnergy(3, 1) == 28);
  REQUIRE(b.GetEnergy(3, 2) == 6);
  REQUIRE(b.GetEnergy(3, 3) == 20);

  REQUIRE(b.GetEnergy(4, 0) == 16);
  REQUIRE(b.GetEnergy(4, 1) == 4);
  REQUIRE(b.GetEnergy(4, 2) == 0);
  REQUIRE(b.GetEnergy(4, 3) == 16);
}

TEST_CASE("get verticle after verticle") {
  ImagePPM a(
      "/home/vagrant/src/mp-seam-carver-RuiZhou-cyber/images/image1.ppm");
  SeamCarver b(a);
  b.RemoveVerticalSeam();
  int** value_matrix = b.Calvaluematrixvertical();
  REQUIRE(value_matrix[0][0] == 14);
  REQUIRE(value_matrix[0][1] == 20);
  REQUIRE(value_matrix[0][2] == 24);
  REQUIRE(value_matrix[0][3] == 20);

  REQUIRE(value_matrix[1][0] == 14);
  REQUIRE(value_matrix[1][1] == 36);
  REQUIRE(value_matrix[1][2] == 10);
  REQUIRE(value_matrix[1][3] == 30);

  REQUIRE(value_matrix[2][0] == 32);
  REQUIRE(value_matrix[2][1] == 8);
  REQUIRE(value_matrix[2][2] == 10);
  REQUIRE(value_matrix[2][3] == 12);

  REQUIRE(value_matrix[3][0] == 14);
  REQUIRE(value_matrix[3][1] == 28);
  REQUIRE(value_matrix[3][2] == 6);
  REQUIRE(value_matrix[3][3] == 20);

  REQUIRE(value_matrix[4][0] == 16);
  REQUIRE(value_matrix[4][1] == 4);
  REQUIRE(value_matrix[4][2] == 0);
  REQUIRE(value_matrix[4][3] == 16);

  for (int i = 0; i < b.GetHeight(); i++) {
    delete[] value_matrix[i];
  }

  delete[] value_matrix;
}

TEST_CASE("get seams after h.") {
  ImagePPM a(
      "/home/vagrant/src/mp-seam-carver-RuiZhou-cyber/images/"
      "original_small_file.ppm");
  SeamCarver b(a);
  b.RemoveHorizontalSeam();
  int** value_matrix = b.Calvaluematrixvertical();
  REQUIRE(value_matrix[0][0] == 150);
  REQUIRE(value_matrix[0][1] == 525);
  REQUIRE(value_matrix[0][2] == 150);
  REQUIRE(value_matrix[0][3] == 525);

  REQUIRE(value_matrix[1][0] == 75);
  REQUIRE(value_matrix[1][1] == 450);
  REQUIRE(value_matrix[1][2] == 75);
  REQUIRE(value_matrix[1][3] == 450);

  for (int i = 0; i < b.GetHeight(); i++) {
    delete[] value_matrix[i];
  }

  delete[] value_matrix;
}

TEST_CASE("get seams after h.2") {
  ImagePPM a(
      "/home/vagrant/src/mp-seam-carver-RuiZhou-cyber/images/"
      "original_small_file.ppm");
  SeamCarver b(a);
  b.RemoveHorizontalSeam();
  int** value_matrix = b.Calvaluematrixhorizontal();
  REQUIRE(value_matrix[0][0] == 1050);
  REQUIRE(value_matrix[0][1] == 975);
  REQUIRE(value_matrix[0][2] == 525);
  REQUIRE(value_matrix[0][3] == 450);

  REQUIRE(value_matrix[1][0] == 1050);
  REQUIRE(value_matrix[1][1] == 975);
  REQUIRE(value_matrix[1][2] == 525);
  REQUIRE(value_matrix[1][3] == 450);

  for (int i = 0; i < b.GetHeight(); i++) {
    delete[] value_matrix[i];
  }

  delete[] value_matrix;
}

/////////////////////////////////////////////////////////////////////////////////////////////