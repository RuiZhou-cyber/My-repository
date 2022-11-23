// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Michael R. Nowak                Environment : ubuntu:latest               //
//  Date ......: 2022/02/07                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "board.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////
constexpr int kBoardWidth = 7;
constexpr int kBoardHeight = 6;

bool AreEqual(DiskType solution[][kBoardWidth],
              DiskType student[][kBoardWidth]) {
  for (int i = 0; i < kBoardHeight; ++i) {
    for (int j = 0; j < kBoardWidth; ++j) {
      if (solution[i][j] != student[i][j]) return false;
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("Board initialization", "[board_init]") {
  // SECTION("Can use sections") {}
  // clang-format off
  DiskType solution[kBoardHeight][kBoardWidth] = { 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty}, 
    {DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty, DiskType::kEmpty} 
  };
  // clang-format on
  Board student;  // NOLINT
  InitBoard(student);
  REQUIRE(AreEqual(solution, student.board));
}

TEST_CASE("Board drop disk", "[board_drop]") {
  // SECTION("Can use sections") {}
  // clang-format on
  Board student;  // NOLINT
  SECTION("drop one") {
    InitBoard(student);
    DropDiskToBoard(student, DiskType::kPlayer1, 0);
    REQUIRE(student.board[0][0] == DiskType::kPlayer1);
  }
  SECTION("drop two") {
    InitBoard(student);
    DropDiskToBoard(student, DiskType::kPlayer1, 0);
    DropDiskToBoard(student, DiskType::kPlayer2, 0);
    REQUIRE(student.board[0][0] == DiskType::kPlayer1);
    REQUIRE(student.board[1][0] == DiskType::kPlayer2);
  }
  SECTION("drop three") {
    InitBoard(student);
    DropDiskToBoard(student, DiskType::kPlayer1, 0);
    DropDiskToBoard(student, DiskType::kPlayer2, 0);
    DropDiskToBoard(student, DiskType::kPlayer1, 0);
    REQUIRE(student.board[0][0] == DiskType::kPlayer1);
    REQUIRE(student.board[1][0] == DiskType::kPlayer2);
    REQUIRE(student.board[2][0] == DiskType::kPlayer1);
  }
  SECTION("drop four") {
    InitBoard(student);
    DropDiskToBoard(student, DiskType::kPlayer2, 0);
    DropDiskToBoard(student, DiskType::kPlayer1, 0);
    DropDiskToBoard(student, DiskType::kPlayer1, 0);
    DropDiskToBoard(student, DiskType::kPlayer2, 0);
    REQUIRE(student.board[0][0] == DiskType::kPlayer2);
    REQUIRE(student.board[1][0] == DiskType::kPlayer1);
    REQUIRE(student.board[2][0] == DiskType::kPlayer1);
    REQUIRE(student.board[3][0] == DiskType::kPlayer2);
  }
}

TEST_CASE("Board drop disk invalid", "[invalid drop]") {
  // SECTION("Can use sections") {}
  // clang-format on
  Board student;  // NOLINT
  SECTION("should say col is full") {
    InitBoard(student);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer2, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer2, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 2),
                      std::runtime_error);
  }
  SECTION("should say col out of bound") {
    InitBoard(student);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 7),
                      std::runtime_error);
  }

  SECTION("should say col out of bound2") {
    InitBoard(student);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, -1),
                      std::runtime_error);
  }
  SECTION("should say col out of bound3") {
    InitBoard(student);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, 768),
                      std::runtime_error);
  }
  SECTION("should say col out of bound4") {
    InitBoard(student);
    REQUIRE_THROWS_AS(DropDiskToBoard(student, DiskType::kPlayer1, -300),
                      std::runtime_error);
  }
}

TEST_CASE("check win") {
  // SECTION("Can use sections") {}
  // clang-format on
  Board student;  // NOLINT
  SECTION("check if vertical win") {
    InitBoard(student);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer2, 2);
    DropDiskToBoard(student, DiskType::kPlayer2, 3);
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));

    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(!CheckForWinner(student, DiskType::kPlayer2));
  }
  SECTION("check if horizontal win") {
    InitBoard(student);
    DropDiskToBoard(student, DiskType::kPlayer2, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer2, 2);
    DropDiskToBoard(student, DiskType::kPlayer2, 3);
    DropDiskToBoard(student, DiskType::kPlayer2, 4);
    DropDiskToBoard(student, DiskType::kPlayer2, 1);
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));

    REQUIRE(CheckForWinner(student, DiskType::kPlayer2));
    REQUIRE(!CheckForWinner(student, DiskType::kPlayer1));
  }
  SECTION("check if leftdiag win") {
    InitBoard(student);
    DropDiskToBoard(student, DiskType::kPlayer1, 1);
    DropDiskToBoard(student, DiskType::kPlayer2, 1);
    DropDiskToBoard(student, DiskType::kPlayer1, 1);
    DropDiskToBoard(student, DiskType::kPlayer1, 1);
    DropDiskToBoard(student, DiskType::kPlayer2, 2);
    DropDiskToBoard(student, DiskType::kPlayer2, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer2, 3);
    DropDiskToBoard(student, DiskType::kPlayer1, 3);
    DropDiskToBoard(student, DiskType::kPlayer1, 4);
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));

    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(!CheckForWinner(student, DiskType::kPlayer2));
  }
  SECTION("check if rightdiag win") {
    InitBoard(student);
    DropDiskToBoard(student, DiskType::kPlayer1, 0);
    DropDiskToBoard(student, DiskType::kPlayer2, 1);
    DropDiskToBoard(student, DiskType::kPlayer1, 1);
    DropDiskToBoard(student, DiskType::kPlayer2, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 3);
    DropDiskToBoard(student, DiskType::kPlayer2, 3);
    DropDiskToBoard(student, DiskType::kPlayer2, 3);
    DropDiskToBoard(student, DiskType::kPlayer1, 3);
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));

    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(!CheckForWinner(student, DiskType::kPlayer2));
  }
  SECTION("check all win") {
    InitBoard(student);
    DropDiskToBoard(student, DiskType::kPlayer1, 1);
    DropDiskToBoard(student, DiskType::kPlayer1, 1);
    DropDiskToBoard(student, DiskType::kPlayer1, 1);
    DropDiskToBoard(student, DiskType::kPlayer1, 1);

    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);

    DropDiskToBoard(student, DiskType::kPlayer1, 3);
    DropDiskToBoard(student, DiskType::kPlayer1, 3);
    DropDiskToBoard(student, DiskType::kPlayer1, 3);
    DropDiskToBoard(student, DiskType::kPlayer1, 3);

    DropDiskToBoard(student, DiskType::kPlayer1, 4);
    DropDiskToBoard(student, DiskType::kPlayer1, 4);
    DropDiskToBoard(student, DiskType::kPlayer1, 4);
    DropDiskToBoard(student, DiskType::kPlayer1, 4);
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE(SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));

    REQUIRE(CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(!CheckForWinner(student, DiskType::kPlayer2));
  }

  SECTION("check not win1") {
    InitBoard(student);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));

    REQUIRE(!CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(!CheckForWinner(student, DiskType::kPlayer2));
  }

  SECTION("check not win2") {
    InitBoard(student);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 3);
    DropDiskToBoard(student, DiskType::kPlayer1, 3);
    DropDiskToBoard(student, DiskType::kPlayer1, 4);

    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));

    REQUIRE(!CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(!CheckForWinner(student, DiskType::kPlayer2));
  }

  SECTION("check not win3") {
    InitBoard(student);
    DropDiskToBoard(student, DiskType::kPlayer1, 2);
    DropDiskToBoard(student, DiskType::kPlayer1, 3);
    DropDiskToBoard(student, DiskType::kPlayer1, 4);

    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kVertical));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kHorizontal));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kLeftDiag));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer1, WinningDirection::kRightDiag));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kVertical));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kHorizontal));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kLeftDiag));
    REQUIRE(!SearchForWinner(
        student, DiskType::kPlayer2, WinningDirection::kRightDiag));

    REQUIRE(!CheckForWinner(student, DiskType::kPlayer1));
    REQUIRE(!CheckForWinner(student, DiskType::kPlayer2));
  }
}

TEST_CASE("check out of bounds") {
  // SECTION("Can use sections") {}
  // clang-format on
  Board student;  // NOLINT
  SECTION("row and col out of bounds") {
    InitBoard(student);
    REQUIRE(!BoardLocationInBounds(-1, -1));
    REQUIRE(!BoardLocationInBounds(-99, -200));
    REQUIRE(!BoardLocationInBounds(99, -200));
    REQUIRE(!BoardLocationInBounds(300, -87));
  }
  SECTION("row out of bounds") {
    InitBoard(student);
    REQUIRE(!BoardLocationInBounds(6, 3));
  }
  SECTION("col out of bounds") {
    InitBoard(student);
    REQUIRE(!BoardLocationInBounds(3, 7));
  }
  SECTION("col and row in bounds") {
    InitBoard(student);
    REQUIRE(BoardLocationInBounds(0, 0));
    REQUIRE(BoardLocationInBounds(5, 6));
    REQUIRE(BoardLocationInBounds(2, 4));
    REQUIRE(BoardLocationInBounds(4, 3));
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////