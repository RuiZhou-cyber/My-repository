#include "functions.hpp"

#include <cctype>
#include <iostream>

using namespace std;

std::map<std::string, std::string> vowels_groups = {{"ai", "eye"},
                                                    {"ae", "eye"},
                                                    {"ao", "ow"},
                                                    {"au", "ow"},
                                                    {"ei", "ay"},
                                                    {"eu", "eh-oo"},
                                                    {"iu", "ew"},
                                                    {"oi", "oy"},
                                                    {"ou", "ow"},
                                                    {"ui", "ooey"}};
std::map<char, std::string> vowels_pronoun = {
    {'a', "ah"}, {'e', "eh"}, {'i', "ee"}, {'o', "oh"}, {'u', "oo"}};
std::string validstring = "aeioupkhlmnw";
std::string consonants = "pkhlmnw";
std::string vowels = "aeiou";
std::string special_char = "ie";

std::string GivePronoun(std::string word) {
  std::string answer;
  std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) {
    return std::tolower(c);
  });
  for (int i = 0; i < int(word.length()); ++i) {
    if (word[i] != ' ' && word[i] != '\'') {
      if (validstring.find(word[i]) == string::npos) {
        return word +
               " contains a character not a part of the Hawaiian language.";
        break;
      }
      if (consonants.find(word[i]) != string::npos) {
        if (word[i] == 'w' && special_char.find(word[i - 1]) != string::npos) {
          answer += "v";
        } else {
          answer.push_back(word[i]);
        }
      }
      if (vowels.find(word[i]) != string::npos) {
        std::string split_string = word.substr(i, 2);
        if (vowels_groups.contains(split_string)) {
          answer += vowels_groups.at(split_string);
          ++i;
        } else {
          answer += vowels_pronoun.at(split_string[0]);
        }
        if (word[i + 1] != ' ' && word[i + 1] != '\'' &&
            i != int(word.length()) - 1) {
          answer.push_back('-');
        }
      }
    } else {
      answer += word[i];
      continue;
    }
  }
  return answer;
}
