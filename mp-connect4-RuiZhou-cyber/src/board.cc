#include "board.hpp"

// you might need additional includes
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

using namespace std;

/**************************************************************************/
/* your function definitions                                              */
/**************************************************************************/

void InitBoard(Board& b) {
  for (int i = 0; i < Board::kBoardHeight; ++i) {
    for (int j = 0; j < Board::kBoardWidth; ++j) {
      b.board[i][j] = DiskType::kEmpty;
    }
  }
}

bool BoardLocationInBounds(int row, int col) {
  return 0 <= row && row < Board::kBoardHeight && 0 <= col &&
         col < Board::kBoardWidth;
}

void DropDiskToBoard(Board& b, DiskType disk, int col) {
  if (!BoardLocationInBounds(0, col)) throw runtime_error("col out of bound.");
  for (int i = 0; i < Board::kBoardHeight; ++i) {
    if (b.board[i][col] == DiskType::kEmpty) {
      b.board[i][col] = disk;
      return;
    }
  }
  throw runtime_error("the col is full.");
}
// check if type of the four disk are the same.
bool CheckType(DiskType disktocheck,
               DiskType disk1,
               DiskType disk2,
               DiskType disk3,
               DiskType disk4) {
  return disk1 == disktocheck && disk2 == disktocheck && disk3 == disktocheck &&
         disk4 == disktocheck;
}
// check horizontally
bool CheckHorizontal(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardHeight; ++i) {
    for (int j = 0; j < Board::kBoardWidth - 3; ++j) {
      if (CheckType(disk,
                    b.board[i][j],
                    b.board[i][j + 1],
                    b.board[i][j + 2],
                    b.board[i][j + 3])) {
        return true;
      }
    }
  }
  return false;
}

// check vertically
bool CheckVertical(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardWidth; ++i) {
    for (int j = 0; j < Board::kBoardHeight - 3; ++j) {
      if (CheckType(disk,
                    b.board[j][i],
                    b.board[j + 1][i],
                    b.board[j + 2][i],
                    b.board[j + 3][i])) {
        return true;
      }
    }
  }
  return false;
}

// check left diag
bool CheckLeftDiag(Board& b, DiskType disk) {
  for (int i = 3; i < Board::kBoardWidth; ++i) {
    for (int j = 3; j < Board::kBoardHeight; ++j) {
      if (CheckType(disk,
                    b.board[j][i - 3],
                    b.board[j - 1][i - 2],
                    b.board[j - 2][i - 1],
                    b.board[j - 3][i])) {
        return true;
      }
    }
  }
  return false;
}

// check right diag
bool CheckRightDiag(Board& b, DiskType disk) {
  for (int i = 0; i < Board::kBoardWidth - 3; ++i) {
    for (int j = 0; j < Board::kBoardHeight - 3; ++j) {
      if (CheckType(disk,
                    b.board[j][i],
                    b.board[j + 1][i + 1],
                    b.board[j + 2][i + 2],
                    b.board[j + 3][i + 3])) {
        return true;
      }
    }
  }
  return false;
}

// search winner in a specific direction
bool SearchForWinner(Board& b, DiskType disk, WinningDirection to_check) {
  if (to_check == WinningDirection::kHorizontal) {
    return CheckHorizontal(b, disk);
  }
  if (to_check == WinningDirection::kVertical) {
    return CheckVertical(b, disk);
  }
  if (to_check == WinningDirection::kLeftDiag) {
    return CheckLeftDiag(b, disk);
  }
  return CheckRightDiag(b, disk);
}

// check if someone is a winner
bool CheckForWinner(Board& b, DiskType disk) {
  return SearchForWinner(b, disk, WinningDirection::kHorizontal) ||
         SearchForWinner(b, disk, WinningDirection::kVertical) ||
         SearchForWinner(b, disk, WinningDirection::kLeftDiag) ||
         SearchForWinner(b, disk, WinningDirection::kRightDiag);
}

/**************************************************************************/
/* provided to you                                                        */
/**************************************************************************/
std::string BoardToStr(const Board& b) {
  constexpr int kTotalWidth = Board::kBoardWidth * 11 - Board::kBoardHeight - 1;
  std::stringstream ss;
  ss << std::endl;
  for (int row = Board::kBoardHeight; row > 0; --row) {
    ss << " |";
    for (int col = 0; col < Board::kBoardWidth; ++col) {
      std::string value_here;
      value_here.push_back(static_cast<char>(b.board[row - 1][col]));
      ss << ' ' << CenterStr(value_here, Board::kBoardWidth + 1) << '|';
    }
    ss << std::endl;
    ss << " |" << std::setw(kTotalWidth) << std::setfill('-') << '|'
       << std::endl;
  }
  ss << " |";
  for (int col = 0; col < Board::kBoardWidth; ++col) {
    ss << ' ' << CenterStr(std::to_string(col), Board::kBoardWidth + 1) << '|';
  }
  return ss.str();
}

std::string CenterStr(const std::string& str, int col_width) {
  // quick and easy (but error-prone) implementation
  auto padl = (col_width - str.length()) / 2;
  auto padr = (col_width - str.length()) - padl;
  std::string strf = std::string(padl, ' ') + str + std::string(padr, ' ');
  return strf;
}