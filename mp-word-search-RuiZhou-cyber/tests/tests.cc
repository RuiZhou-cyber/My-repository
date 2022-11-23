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
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"
using namespace std;
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

bool AreEqual(const WordLocation& a, const WordLocation& b) {
  if (a.word == "" && b.word == "") {
    return true;
  }
  if (a.word == b.word && a.char_positions.size() == b.char_positions.size()) {
    for (int i = 0; i < int(a.char_positions.size()); ++i) {
      if (a.char_positions.at(i).character !=
              b.char_positions.at(i).character ||
          a.char_positions.at(i).row != b.char_positions.at(i).row ||
          a.char_positions.at(i).col != b.char_positions.at(i).col) {
        return false;
      }
    }
  }
  return true;
}

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("checkhorizontal", "horizontal") {
  SECTION("h") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 'a', 'l', 'o', 'm'},
                                          {'a', 'e', 't', 'a', 'u'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    vector<CharPositions> c = {
        {'h', 1, 0}, {'e', 1, 1}, {'l', 1, 2}, {'l', 1, 3}, {'o', 1, 4}};
    WordLocation answer = {"hello", c};
    REQUIRE(AreEqual(wss.FindWord("hello"), answer));
    REQUIRE(wss.FindWord("hello").char_positions[2].row == 1);
    REQUIRE(wss.FindWord("hello").char_positions[2].col == 2);
    REQUIRE(wss.FindWord("hello", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("hello", CheckDirection::kVertical).word.empty());
  }
}

TEST_CASE("checkvertical", "vertical") {
  SECTION("v") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 'a', 'l', 'o', 'm'},
                                          {'a', 'e', 't', 'a', 'u'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    vector<CharPositions> c = {
        {'u', 0, 4}, {'o', 1, 4}, {'m', 2, 4}, {'u', 3, 4}};
    WordLocation answer = {"uomu", c};
    REQUIRE(AreEqual(wss.FindWord("uomu"), answer));
    REQUIRE(AreEqual(wss.FindWord("uomu", CheckDirection::kVertical), answer));
    REQUIRE(wss.FindWord("uomu", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("uomu", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("uomu", CheckDirection::kLeftDiag).word.empty());
  }
}

TEST_CASE("checkleftdiag", "leftdiag") {
  SECTION("ld") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 'a', 'l', 'o', 'm'},
                                          {'a', 'e', 't', 'a', 'u'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    vector<CharPositions> c = {
        {'l', 1, 3}, {'l', 2, 2}, {'e', 3, 1}, {'t', 4, 0}};
    WordLocation answer = {"llet", c};
    REQUIRE(AreEqual(wss.FindWord("llet"), answer));
    REQUIRE(wss.FindWord("llet", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("llet", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("llet", CheckDirection::kVertical).word.empty());
  }
}

TEST_CASE("checkrightdiag", "rightdiag") {
  SECTION("rd") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 'a', 'l', 'o', 'm'},
                                          {'a', 'e', 't', 'a', 'u'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    vector<CharPositions> c = {
        {'d', 0, 0}, {'e', 1, 1}, {'l', 2, 2}, {'a', 3, 3}, {'u', 4, 4}};
    WordLocation answer = {"delau", c};
    REQUIRE(AreEqual(wss.FindWord("delau"), answer));
    REQUIRE(
        AreEqual(wss.FindWord("delau", CheckDirection::kRightDiag), answer));
    REQUIRE(wss.FindWord("delau", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("delau", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("delau", CheckDirection::kVertical).word.empty());
  }
}

TEST_CASE("out of bounds", "out") {
  SECTION("horizontal") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 'a', 'l', 'o', 'm'},
                                          {'a', 'e', 't', 'a', 'u'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation answer = {};
    REQUIRE(AreEqual(wss.FindWord("ssssss"), answer));
    REQUIRE(
        AreEqual(wss.FindWord("ssssss", CheckDirection::kHorizontal), answer));
    REQUIRE(wss.FindWord("ssssss", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("ssssss", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("ssssss", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("ssssss", CheckDirection::kVertical).word.empty());
  }

  SECTION("vertical") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 'a', 'l', 'o', 'm'},
                                          {'a', 'e', 't', 'a', 'u'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation answer = {};
    REQUIRE(AreEqual(wss.FindWord("ssssss"), answer));
    REQUIRE(
        AreEqual(wss.FindWord("ssssss", CheckDirection::kVertical), answer));
    REQUIRE(wss.FindWord("ssssss", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("ssssss", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("ssssss", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("ssssss", CheckDirection::kVertical).word.empty());
  }

  SECTION("rd") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 'a', 'l', 'o', 'm'},
                                          {'a', 'e', 't', 'a', 'u'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation answer = {};
    REQUIRE(AreEqual(wss.FindWord("ssssss"), answer));
    REQUIRE(
        AreEqual(wss.FindWord("ssssss", CheckDirection::kRightDiag), answer));
  }

  SECTION("ld") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 'a', 'l', 'o', 'm'},
                                          {'a', 'e', 't', 'a', 'u'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation answer = {};
    REQUIRE(AreEqual(wss.FindWord("ssssss"), answer));
    REQUIRE(
        AreEqual(wss.FindWord("ssssss", CheckDirection::kLeftDiag), answer));
  }
}

TEST_CASE("cannot find", "cf") {
  SECTION("horizontal") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 'a', 'l', 'o', 'm'},
                                          {'a', 'e', 't', 'a', 'u'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation answer = {};
    REQUIRE(AreEqual(wss.FindWord("hallm"), answer));
    REQUIRE(
        AreEqual(wss.FindWord("hallm", CheckDirection::kHorizontal), answer));
    REQUIRE(wss.FindWord("hallm", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("hallm", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("hallm", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("hallm", CheckDirection::kVertical).word.empty());
  }

  SECTION("vertical") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 'a', 'l', 'o', 'm'},
                                          {'a', 'e', 't', 'a', 'u'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation answer = {};
    REQUIRE(AreEqual(wss.FindWord("ctt"), answer));
    REQUIRE(AreEqual(wss.FindWord("ctt", CheckDirection::kVertical), answer));
    REQUIRE(wss.FindWord("ctt", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("ctt", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("ctt", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("ctt", CheckDirection::kVertical).word.empty());
  }

  SECTION("rd") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 'a', 'l', 'o', 'm'},
                                          {'a', 'e', 't', 'a', 'u'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation answer = {};
    REQUIRE(AreEqual(wss.FindWord("het"), answer));
    REQUIRE(AreEqual(wss.FindWord("het", CheckDirection::kRightDiag), answer));
    REQUIRE(wss.FindWord("het", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("het", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("het", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("het", CheckDirection::kVertical).word.empty());
  }

  SECTION("ld") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 'a', 'l', 'o', 'm'},
                                          {'a', 'e', 't', 'a', 'u'},
                                          {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver wss(puzzle);
    WordLocation answer = {};
    REQUIRE(AreEqual(wss.FindWord("ulltt"), answer));
    REQUIRE(AreEqual(wss.FindWord("ulltt", CheckDirection::kLeftDiag), answer));
    REQUIRE(wss.FindWord("ulltt", CheckDirection::kRightDiag).word.empty());
    REQUIRE(wss.FindWord("ulltt", CheckDirection::kHorizontal).word.empty());
    REQUIRE(wss.FindWord("ulltt", CheckDirection::kLeftDiag).word.empty());
    REQUIRE(wss.FindWord("ulltt", CheckDirection::kVertical).word.empty());
  }
}

TEST_CASE("one word", "out") {
  SECTION("allfind") {
    std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                          {'h', 'e', 'l', 'l', 'o'},
                                          {'c', 'a', 'l', 'o', 'm'},
                                          {'a', 'e', 't', 'a', 'u'},
                                          {'t', 'e', 't', 'o', 'z'}};
    WordSearchSolver wss(puzzle);
    vector<CharPositions> c = {{'z', 4, 4}};
    WordLocation answer = {"z", c};
    REQUIRE(AreEqual(wss.FindWord("z"), answer));
    REQUIRE(AreEqual(wss.FindWord("z", CheckDirection::kHorizontal), answer));
    REQUIRE(AreEqual(wss.FindWord("z", CheckDirection::kVertical), answer));
    REQUIRE(AreEqual(wss.FindWord("z", CheckDirection::kLeftDiag), answer));
    REQUIRE(AreEqual(wss.FindWord("z", CheckDirection::kRightDiag), answer));
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////