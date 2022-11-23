#include "db_table.hpp"

// const unsigned int kRowGrowthRate = 2;
//   for (int i = 0; i < int(row_col_capacity_); ++i) {
//     if (col_descs_.at(i).second == DataType::kString) {
//       delete static_cast<string*>(rows_.at(row_id)[i]);
//    } else if (col_descs_.at(i).second == DataType::kDouble) {
//        delete static_cast<double*>(rows_.at(row_id)[i]);
//     } else {
//       delete static_cast<int*>(rows_.at(row_id)[i]);
//     }
//   }

using namespace std;
void DbTable::HelpResize(unsigned int new_size) {
  for (unsigned int row_id = 0; row_id < next_unique_id_; ++row_id) {
    void** tmp = new void*[new_size];
    for (unsigned int i = 0; i < row_col_capacity_; ++i) {
      tmp[i] = rows_.at(row_id)[i];
      rows_.at(row_id)[i] = nullptr;
    }
    delete[] rows_.at(row_id);
    rows_.at(row_id) = tmp;
  }
  row_col_capacity_ *= 2;
}

void DbTable::AddColumn(const std::pair<std::string, DataType>& col_desc) {
  if (col_descs_.size() == row_col_capacity_) {
    HelpResize(row_col_capacity_ * 2);
  }
  col_descs_.push_back(col_desc);
  for (unsigned int row_id = 0; row_id < next_unique_id_; ++row_id) {
    if (col_desc.second == DataType::kString) {
      rows_.at(row_id)[col_descs_.size() - 1] =
          static_cast<void*>(new std::string(""));
    } else if (col_desc.second == DataType::kDouble) {
      rows_.at(row_id)[col_descs_.size() - 1] =
          static_cast<void*>(new double(0.0));
    } else {
      rows_.at(row_id)[col_descs_.size() - 1] =
          static_cast<void*>(new double(0));
    }
  }
}

void DbTable::DeleteColumnByIdx(unsigned int col_idx) {
  if (col_idx < 0 || col_idx >= col_descs_.size()) {
    throw out_of_range("Input column index not valid.");
  }
  if (col_descs_.size() == 1 && !rows_.empty()) {
    throw runtime_error(
        "Any table with at least one row must have at least one column.");
  }
  for (unsigned int row_id = 0; row_id < next_unique_id_; ++row_id) {
    // delete this col of this row
    if (col_descs_.at(col_idx).second == DataType::kString) {
      delete static_cast<string*>(rows_.at(row_id)[col_idx]);
    } else if (col_descs_.at(col_idx).second == DataType::kDouble) {
      delete static_cast<double*>(rows_.at(row_id)[col_idx]);
    } else {
      delete static_cast<int*>(rows_.at(row_id)[col_idx]);
    }
    for (unsigned int i = col_idx; i < col_descs_.size(); ++i) {
      if (i == col_descs_.size() - 1) {
        rows_.at(row_id)[i] = nullptr;
      } else {
        rows_.at(row_id)[i] = rows_.at(row_id)[i + 1];
      }
    }
  }
  col_descs_.erase(col_descs_.begin() + col_idx);
}

void DbTable::AddRow(const std::initializer_list<std::string>& col_data) {
  if (col_data.size() != col_descs_.size()) {
    throw invalid_argument("input data does not have valid number of data.");
  }
  void** new_row = new void*[row_col_capacity_];
  int index = 0;
  for (const string& str : col_data) {
    if (col_descs_.at(index).second == DataType::kString) {
      new_row[index] = static_cast<void*>(new string(str));
    } else if (col_descs_.at(index).second == DataType::kDouble) {
      new_row[index] = static_cast<void*>(new double(stod(str)));
    } else {
      new_row[index] = static_cast<void*>(new int(stoi(str)));
    }
    ++index;
  }
  rows_.insert({next_unique_id_, new_row});
  next_unique_id_ += 1;
}

void DbTable::DeleteRowById(unsigned int id) {
  if (id < 0 || id >= next_unique_id_) {
    throw runtime_error("Row with this id does not exist.");
  }
  for (unsigned int i = 0; i < col_descs_.size(); ++i) {
    if (col_descs_.at(i).second == DataType::kString) {
      delete static_cast<string*>(rows_.at(id)[i]);
    } else if (col_descs_.at(i).second == DataType::kDouble) {
      delete static_cast<double*>(rows_.at(id)[i]);
    } else {
      delete static_cast<int*>(rows_.at(id)[i]);
    }
  }
  delete[] rows_.at(id);
  rows_.erase(id);
}

DbTable::DbTable(const DbTable& rhs):
    next_unique_id_(rhs.next_unique_id_),
    row_col_capacity_(rhs.row_col_capacity_),
    col_descs_(rhs.col_descs_) {
  if (rhs.rows_.empty() && rhs.col_descs_.empty()) return;
  for (unsigned int row_id = 0; row_id < next_unique_id_; ++row_id) {
    void** new_row = new void*[row_col_capacity_];
    rows_.insert({row_id, new_row});
  }
  for (unsigned int row_id = 0; row_id < next_unique_id_; ++row_id) {
    for (unsigned int i = 0; i < col_descs_.size(); ++i) {
      if (col_descs_.at(i).second == DataType::kString) {
        string to_put_in =
            *(static_cast<std::string*>(rhs.rows_.at(row_id)[i]));
        rows_.at(row_id)[i] = static_cast<void*>(new string(to_put_in));
      } else if (col_descs_.at(i).second == DataType::kDouble) {
        double to_put_in = *(static_cast<double*>(rhs.rows_.at(row_id)[i]));
        rows_.at(row_id)[i] = static_cast<void*>(new double(to_put_in));
      } else {
        int to_put_in = *(static_cast<int*>(rhs.rows_.at(row_id)[i]));
        rows_.at(row_id)[i] = static_cast<void*>(new int(to_put_in));
      }
    }
  }
}

DbTable& DbTable::operator=(const DbTable& rhs) {
  if (this == &rhs) return *this;
  for (unsigned int row_id = 0; row_id < next_unique_id_; ++row_id) {
    if (rows_.contains(row_id)) DeleteRowById(row_id);
  }
  next_unique_id_ = rhs.next_unique_id_;
  row_col_capacity_ = rhs.row_col_capacity_;
  col_descs_ = rhs.col_descs_;
  if (rhs.rows_.empty() && rhs.col_descs_.empty()) return *this;
  for (unsigned int row_id = 0; row_id < next_unique_id_; ++row_id) {
    void** new_row = new void*[row_col_capacity_];
    rows_.insert({row_id, new_row});
  }
  for (unsigned int row_id = 0; row_id < next_unique_id_; ++row_id) {
    for (unsigned int i = 0; i < col_descs_.size(); ++i) {
      if (col_descs_.at(i).second == DataType::kString) {
        string to_put_in =
            *(static_cast<std::string*>(rhs.rows_.at(row_id)[i]));
        rows_.at(row_id)[i] = static_cast<void*>(new string(to_put_in));
      } else if (col_descs_.at(i).second == DataType::kDouble) {
        double to_put_in = *(static_cast<double*>(rhs.rows_.at(row_id)[i]));
        rows_.at(row_id)[i] = static_cast<void*>(new double(to_put_in));
      } else {
        int to_put_in = *(static_cast<int*>(rhs.rows_.at(row_id)[i]));
        rows_.at(row_id)[i] = static_cast<void*>(new int(to_put_in));
      }
    }
  }
  return *this;
}

DbTable::~DbTable() {
  for (unsigned int row_id = 0; row_id < next_unique_id_; ++row_id) {
    if (rows_.contains(row_id)) {
      for (unsigned int i = 0; i < col_descs_.size(); ++i) {
        if (col_descs_.at(i).second == DataType::kString) {
          delete static_cast<string*>(rows_.at(row_id)[i]);
        } else if (col_descs_.at(i).second == DataType::kDouble) {
          delete static_cast<double*>(rows_.at(row_id)[i]);
        } else {
          delete static_cast<int*>(rows_.at(row_id)[i]);
        }
      }
      delete[] rows_.at(row_id);
      rows_.erase(row_id);
    }
  }
}

std::ostream& operator<<(std::ostream& os, const DbTable& table) {
  string first_line;
  for (const pair<string, DataType>& a : table.col_descs_) {
    if (a.second == DataType::kString) {
      first_line += a.first + "(" + "std::string" + ")" + "," + " ";
    } else if (a.second == DataType::kDouble) {
      first_line += a.first + "(" + "double" + ")" + "," + " ";
    } else if (a.second == DataType::kInt) {
      first_line += a.first + "(" + "int" + ")" + "," + " ";
    }
  }
  os << first_line.substr(0, first_line.length() - 2) << endl;

  for (unsigned int row_id = 0; row_id < table.next_unique_id_; ++row_id) {
    for (unsigned int i = 0; i < table.col_descs_.size(); ++i) {
      if (table.col_descs_.at(i).second == DataType::kString) {
        string to_put_in =
            *(static_cast<std::string*>(table.rows_.at(row_id)[i]));
        os << to_put_in;
      } else if (table.col_descs_.at(i).second == DataType::kDouble) {
        double to_put_in = *(static_cast<double*>(table.rows_.at(row_id)[i]));
        os << to_put_in;
      } else if (table.col_descs_.at(i).second == DataType::kInt) {
        int to_put_in = *(static_cast<int*>(table.rows_.at(row_id)[i]));
        os << to_put_in;
      }
      if (i != table.col_descs_.size() - 1) {
        os << ","
           << " ";
      } else if (i == table.col_descs_.size() - 1 &&
                 row_id != table.next_unique_id_ - 1) {
        os << "\n";
      }
    }
  }
  return os;
}
