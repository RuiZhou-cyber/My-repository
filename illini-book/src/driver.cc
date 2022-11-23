#include <iostream>

#include "illini_book.hpp"
using namespace std;

int main() {
  /// home/vagrant/src/mp-illini-book-RuiZhou-cyber/example/relations.csv
  IlliniBook a = IlliniBook(
      "/home/vagrant/src/mp-illini-book-RuiZhou-cyber/example/persons.csv",
      "/home/vagrant/src/mp-illini-book-RuiZhou-cyber/example/relations.csv");
  cout << a.CountGroups("173");
  return 0;
}
