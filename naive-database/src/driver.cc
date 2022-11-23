#include <iostream>

#include "db.hpp"
#include "db_table.hpp"

using namespace std;
int main() {
  DbTable a = DbTable();
  pair<string, DataType> col1 = {"Name", DataType::kString};
  pair<string, DataType> col2 = {"UIN", DataType::kInt};
  pair<string, DataType> col3 = {"Nick", DataType::kString};
  pair<string, DataType> col4 = {"Codenum", DataType::kDouble};
  pair<string, DataType> col5 = {"Partner", DataType::kString};
  a.AddColumn(col1);
  a.AddColumn(col2);
  a.AddColumn(col3);
  a.AddColumn(col4);
  a.AddColumn(col5);

  a.AddRow({"John", "122", "JN", "2.0", "me"});
  a.AddRow({"Mike", "123", "MK", "2.3", "you"});
  a.AddRow({"Nathan", "124", "NTH", "2.4", "he"});
  a.AddRow({"Catty", "125", "CTT", "2.5", "she"});
  a.AddRow({"Roy", "126", "RY", "2.6", "it"});

  DbTable b = DbTable(a);
  DbTable c = DbTable();
  c = b;

  Database data = Database();
  data.CreateTable("thing");
  data.CreateTable("otherthing");
  data.GetTable("thing") = b;
  cout << a << endl;

  data.~Database();
}