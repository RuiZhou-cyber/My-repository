#include "db.hpp"

using namespace std;
void Database::CreateTable(const std::string& table_name) {
  tables_.insert({table_name, new DbTable});
}

void Database::DropTable(const std::string& table_name) {
  if (tables_.contains(table_name)) {
    delete tables_.at(table_name);
    tables_.at(table_name) = nullptr;
    tables_.erase(table_name);
    return;
  }
  throw invalid_argument("this table does not exist.");
}

DbTable& Database::GetTable(const std::string& table_name) {
  if (tables_.contains(table_name)) {
    return *tables_.at(table_name);
  }
  throw invalid_argument("this table does not exist.");
}

// copy constructor
Database::Database(const Database& rhs) {
  for (auto const& [key, val] : rhs.tables_) {
    auto* put_in = new DbTable(*val);
    tables_.insert({key, put_in});
  }
}

// override assignment
Database& Database::operator=(const Database& rhs) {
  if (this == &rhs) return *this;
  for (auto const& [key, val] : tables_) {
    delete tables_.at(key);
    tables_.at(key) = nullptr;
  }
  tables_.clear();
  for (auto const& [key, val] : rhs.tables_) {
    auto* put_in = new DbTable(*val);
    tables_.insert({key, put_in});
  }
  return *this;
}

// destructor
Database::~Database() {
  vector<string> key;
  for (auto it = tables_.begin(); it != tables_.end(); ++it) {
    key.push_back(it->first);
  }
  for (int i = 0; i < int(key.size()); ++i) {
    if (tables_.contains(key.at(i))) {
      delete tables_.at(key.at(i));
      tables_.at(key.at(i)) = nullptr;
      tables_.erase(key.at(i));
    }
  }
}
