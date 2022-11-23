#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP
#include <iostream>
#include <vector>

#include "utilities.hpp"
using namespace std;

int Maxnumber(const string& str, const string& dna_sequence);
vector<string> Findmatch(vector<vector<string>> file_trans,
                         vector<int> max_cons_dna);

#endif