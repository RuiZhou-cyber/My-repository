#include <fstream>
#include <iostream>

#include "functions.hpp"
#include "utilities.hpp"

// /home/vagrant/src/mp-dna-forensics-RuiZhou-cyber/data.dat
// AGACGGGTTACCATGACTATTATTATTATTATTATTATTATACGTACGTACGTATGAGATGAGATGAGATGAGATGAGATGCCTCGACTTCGATCGCAATGAATGCCAATAGACAAAA

using namespace std;
int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1;
  }
  string dna_sequence = argv[2];
  string filename = argv[1];
  vector<vector<string>> file_trans;
  ifstream ifs{filename};
  for (string line; getline(ifs, line); line = "") {
    vector<string> row = utilities::GetSubstrs(line, ',');
    file_trans.push_back(row);
  }

  vector<int> max_cons_dna;
  for (int i = 1; i < (int)file_trans.at(0).size(); ++i) {
    int maxsequence = Maxnumber(file_trans.at(0).at(i), dna_sequence);
    max_cons_dna.push_back(maxsequence);
  }

  vector<string> answer = Findmatch(file_trans, max_cons_dna);

  if (answer.size() == 1) {
    std::cout << answer.at(0) << std::endl;
  } else {
    std::cout << "No match" << std::endl;
  }

  return 0;
}