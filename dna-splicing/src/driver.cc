#include <iostream>

#include "dna_strand.hpp"
using namespace std;

int main() {
  DNAstrand a = DNAstrand("456788");
  DNAstrand b = DNAstrand("abcdefg");
  a.SpliceIn("456788", b);
  a.PrintDNA(a);
}