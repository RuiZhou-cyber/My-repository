#include "functions.hpp"
using namespace std;

int Maxnumber(const string& str, const string& dna_sequence) {
  int max = 0;
  int cap = (int)str.size();
  for (int i = 0; i < (int)dna_sequence.size(); ++i) {
    if (dna_sequence.substr(i, cap) == str) {
      int j = 0;
      int count = 0;
      while (dna_sequence.substr(i + j, cap) == str) {
        count += 1;
        j += cap;
      }
      if (count > max) {
        max = count;
      }
    }
  }
  return max;
}

vector<string> Findmatch(vector<vector<string>> file_trans,
                         vector<int> max_cons_dna) {
  vector<string> answer;
  for (int i = 1; i < (int)file_trans.size(); ++i) {
    int matches = 0;
    for (int j = 1; j < (int)file_trans.at(i).size(); ++j) {
      if (std::stoi(file_trans.at(i).at(j)) == max_cons_dna.at(j - 1)) {
        matches += 1;
      }
    }
    if (matches == ((int)file_trans.at(0).size() - 1)) {
      answer.push_back(file_trans.at(i).at(0));
    }
  }
  return answer;
}