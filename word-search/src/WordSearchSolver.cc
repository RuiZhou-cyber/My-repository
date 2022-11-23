#include "WordSearchSolver.hpp"

#include <iostream>
using namespace std;

bool WordSearchSolver::LocationInBounds(size_t row, size_t col) const {
  return ((row < puzzle_height_) && (col < puzzle_width_));
}

WordSearchSolver::WordSearchSolver(
    const std::vector<std::vector<char>>& puzzle) {
  puzzle_height_ = puzzle.size();
  for (int i = 0; i < int(puzzle.size()); ++i) {
    vector<char> a;
    for (int j = 0; j < int(puzzle.at(i).size()); ++j) {
      a.push_back(puzzle.at(i).at(j));
      puzzle_width_ = puzzle.at(i).size();
    }
    puzzle_.push_back(a);
  }
}

// check horizontally
WordLocation WordSearchSolver::CheckHorizontal(const string& word) const {
  if (word.length() < 0 || word.length() > puzzle_width_) {
    return WordLocation{};
  }
  vector<CharPositions> char_positions;
  for (size_t i = 0; i < puzzle_height_; ++i) {
    for (size_t j = 0; j <= puzzle_width_ - word.length(); ++j) {
      string word_to_check;
      for (size_t k = 0; k < word.length(); ++k) {
        word_to_check += puzzle_.at(i).at(j + k);
      }
      if (word_to_check == word) {
        for (size_t l = 0; l < word.length(); ++l) {
          CharPositions a = {puzzle_.at(i).at(j + l), i, j + l};
          char_positions.push_back(a);
        }
        WordLocation answer = {word, char_positions};
        return answer;
      }
    }
  }
  return WordLocation{};
}

// check vertically
WordLocation WordSearchSolver::CheckVertical(const string& word) const {
  if (word.length() < 0 || word.length() > puzzle_height_) {
    return WordLocation{};
  }
  vector<CharPositions> char_positions;
  for (size_t i = 0; i < puzzle_width_; ++i) {
    for (size_t j = 0; j <= puzzle_height_ - word.length(); ++j) {
      string word_to_check;
      for (size_t k = 0; k < word.length(); ++k) {
        word_to_check += puzzle_.at(j + k).at(i);
      }
      if (word_to_check == word) {
        for (size_t l = 0; l < word.length(); ++l) {
          CharPositions a = {puzzle_.at(j + l).at(i), j + l, i};
          char_positions.push_back(a);
        }
        WordLocation answer = {word, char_positions};
        return answer;
      }
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::CheckLeftDiag(const string& word) const {
  if (!LocationInBounds(word.length() - 1, word.length() - 1)) {
    return WordLocation{};
  }
  vector<CharPositions> char_positions;
  for (size_t i = 0; i <= puzzle_height_ - word.length(); ++i) {
    for (size_t j = word.length() - 1; j < puzzle_width_; ++j) {
      string word_to_check;
      for (size_t k = 0; k < word.length(); ++k) {
        word_to_check += puzzle_.at(i + k).at(j - k);
      }
      if (word_to_check == word) {
        for (size_t l = 0; l < word.length(); ++l) {
          CharPositions a = {puzzle_.at(i + l).at(j - l), i + l, j - l};
          char_positions.push_back(a);
        }
        WordLocation answer = {word, char_positions};
        return answer;
      }
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::CheckRightDiag(const string& word) const {
  if (!LocationInBounds(word.length() - 1, word.length() - 1)) {
    return WordLocation{};
  }
  vector<CharPositions> char_positions;
  for (size_t i = 0; i <= puzzle_height_ - word.length(); ++i) {
    for (size_t j = 0; j <= puzzle_width_ - word.length(); ++j) {
      string word_to_check;
      for (size_t k = 0; k < word.length(); ++k) {
        word_to_check += puzzle_.at(i + k).at(j + k);
      }
      if (word_to_check == word) {
        for (size_t l = 0; l < word.length(); ++l) {
          CharPositions a = {puzzle_.at(i + l).at(j + l), i + l, j + l};
          char_positions.push_back(a);
        }
        WordLocation answer = {word, char_positions};
        return answer;
      }
    }
  }
  return WordLocation{};
}

WordLocation WordSearchSolver::FindWord(const std::string& word,
                                        CheckDirection direction) {
  if (direction == CheckDirection::kHorizontal) {
    return CheckHorizontal(word);
  }
  if (direction == CheckDirection::kVertical) {
    return CheckVertical(word);
  }
  if (direction == CheckDirection::kLeftDiag) {
    return CheckLeftDiag(word);
  }
  return CheckRightDiag(word);
}

WordLocation WordSearchSolver::FindWord(const std::string& word) {
  if (FindWord(word, CheckDirection::kHorizontal).word == word) {
    return FindWord(word, CheckDirection::kHorizontal);
  }
  if (FindWord(word, CheckDirection::kVertical).word == word) {
    return FindWord(word, CheckDirection::kVertical);
  }
  if (FindWord(word, CheckDirection::kLeftDiag).word == word) {
    return FindWord(word, CheckDirection::kLeftDiag);
  }
  if (FindWord(word, CheckDirection::kRightDiag).word == word) {
    return FindWord(word, CheckDirection::kRightDiag);
  }
  return WordLocation{};
}
