#include "illini_book.hpp"

using namespace std;
// Your code here!
IlliniBook::IlliniBook(const std::string& people_fpath,
                       const std::string& relations_fpath) {
  ifstream person{people_fpath};
  ifstream relation{relations_fpath};

  for (string line; getline(person, line); line = "") {
    graph_.insert(pair<int, list<pair<int, string>>>(
        stoi(line), list<pair<int, string>>()));
    allvertices_.push_back(stoi(line));
  }

  for (string line; getline(relation, line); line = "") {
    vector<string> eachline = utilities::Split(line, ',');
    pair<int, string> thing = make_pair(stoi(eachline.at(1)), eachline.at(2));
    pair<int, string> another_thing =
        make_pair(stoi(eachline.at(0)), eachline.at(2));
    graph_.find(stoi(eachline.at(0)))->second.push_back(thing);
    graph_.find(stoi(eachline.at(1)))->second.push_back(another_thing);
    allrelation_.insert(eachline.at(2));
  }
}

bool IlliniBook::AreRelated(int uin_1, int uin_2) const {
  queue<int> path({uin_1});
  set<int> visited;
  while (!path.empty()) {
    unsigned long size = path.size();
    for (unsigned long i = 0; i < size; ++i) {
      int curr = path.front();
      if (curr == uin_2) return true;
      list<pair<int, string>> this_relation = graph_.find(curr)->second;
      for (auto const& i : this_relation) {
        if (visited.count(i.first) != 1) {
          path.push(i.first);
          visited.insert(i.first);
        }
      }
      path.pop();
    }
  }
  return false;
}

bool IlliniBook::AreRelated(int uin_1,
                            int uin_2,
                            const std::string& relationship) const {
  if (allrelation_.count(relationship) != 1) return false;
  queue<int> path({uin_1});
  set<int> visited;
  while (!path.empty()) {
    unsigned long size = path.size();
    for (unsigned long i = 0; i < size; ++i) {
      int curr = path.front();
      if (curr == uin_2) return true;
      list<pair<int, string>> this_relation = graph_.find(curr)->second;
      for (auto const& i : this_relation) {
        if (visited.count(i.first) != 1 && i.second == relationship) {
          path.push(i.first);
          visited.insert(i.first);
        }
      }
      path.pop();
    }
  }
  return false;
}

int IlliniBook::GetRelated(int uin_1, int uin_2) const {
  int answer = 0;
  queue<int> path({uin_1});
  set<int> visited({uin_1});
  while (!path.empty()) {
    unsigned long size = path.size();
    for (unsigned long i = 0; i < size; ++i) {
      int curr = path.front();
      if (curr == uin_2) return answer;
      list<pair<int, string>> this_relation = graph_.find(curr)->second;
      for (auto const& i : this_relation) {
        if (visited.count(i.first) != 1) {
          path.push(i.first);
          visited.insert(i.first);
        }
      }
      path.pop();
    }
    ++answer;
  }
  return -1;
}

int IlliniBook::GetRelated(int uin_1,
                           int uin_2,
                           const std::string& relationship) const {
  if (allrelation_.count(relationship) != 1) return -1;
  int answer = 0;
  queue<int> path({uin_1});
  set<int> visited({uin_1});
  while (!path.empty()) {
    unsigned long size = path.size();
    for (unsigned long i = 0; i < size; ++i) {
      int curr = path.front();
      if (curr == uin_2) return answer;
      list<pair<int, string>> this_relation = graph_.find(curr)->second;
      for (auto const& i : this_relation) {
        if (visited.count(i.first) != 1 && i.second == relationship) {
          path.push(i.first);
          visited.insert(i.first);
        }
      }
      path.pop();
    }
    ++answer;
  }
  return -1;
}

vector<int> IlliniBook::Getanswer(queue<int>& thing) const {
  vector<int> answer;
  while (!thing.empty()) {
    answer.push_back(thing.front());
    thing.pop();
  }
  return answer;
}

std::vector<int> IlliniBook::GetSteps(int uin, int n) const {
  int level = 0;
  queue<int> path({uin});
  set<int> visited({uin});
  while (!path.empty()) {
    if (level == n) break;
    unsigned long size = path.size();
    for (unsigned long i = 0; i < size; ++i) {
      int curr = path.front();
      list<pair<int, string>> this_relation = graph_.find(curr)->second;
      for (auto const& i : this_relation) {
        if (visited.count(i.first) != 1) {
          path.push(i.first);
          visited.insert(i.first);
        }
      }
      path.pop();
    }
    ++level;
  }
  return Getanswer(path);
}

size_t IlliniBook::CountGroups() const {
  unsigned int answer = 0;  // final answer
  set<int> visited;         // the set of visited vertices.
  for (unsigned long i = 0; i < allvertices_.size();
       ++i) {                            // for loop go over all the vertices.
    int curr_node = allvertices_.at(i);  // current vertice visit.
    if (visited.count(curr_node) == 1)
      continue;                             // if visited before, continue.
    ++answer;                               // add one to answer
    queue<int> thiscomponent({curr_node});  // create a queue for the component
                                            // containing current node.
    while (!thiscomponent.empty()) {
      unsigned long size = thiscomponent.size();
      for (unsigned long i = 0; i < size; ++i) {
        int curr = thiscomponent.front();
        list<pair<int, string>> li =
            graph_.find(curr)->second;  // get the neihbours for current node.
        for (auto const& i : li) {
          if (visited.count(i.first) != 1) {
            thiscomponent.push(i.first);
            visited.insert(i.first);
          }
        }
        thiscomponent.pop();
      }
    }
  }
  return answer;
}

size_t IlliniBook::CountGroups(const std::string& relationship) const {
  unsigned int answer = 0;  // final answer
  set<int> visited;         // the set of visited vertices.
  for (unsigned long i = 0; i < allvertices_.size();
       ++i) {                            // for loop go over all the vertices.
    int curr_node = allvertices_.at(i);  // current vertice visit.
    if (visited.count(curr_node) == 1)
      continue;                             // if visited before, continue.
    ++answer;                               // add one to answer
    queue<int> thiscomponent({curr_node});  // create a queue for the component
                                            // containing current node.
    while (!thiscomponent.empty()) {
      unsigned long size = thiscomponent.size();
      for (unsigned long i = 0; i < size; ++i) {
        int curr = thiscomponent.front();
        list<pair<int, string>> li =
            graph_.find(curr)->second;  // get the neihbours for current node.
        for (auto const& i : li) {
          if (visited.count(i.first) != 1 && i.second == relationship) {
            thiscomponent.push(i.first);
            visited.insert(i.first);
          }
        }
        thiscomponent.pop();
      }
    }
  }
  return answer;
}

bool IlliniBook::Checkinall(
    const std::vector<std::string>& relationships) const {
  for (unsigned long i = 0; i < relationships.size(); ++i) {
    if (allrelation_.count(relationships.at(i)) != 1) return false;
  }
  return true;
}

set<string> IlliniBook::GetDesiredrelation(
    const std::vector<std::string>& relationships) const {
  set<string> answer;
  for (unsigned long i = 0; i < relationships.size(); ++i) {
    answer.insert(relationships.at(i));
  }
  return answer;
}

size_t IlliniBook::CountGroups(
    const std::vector<std::string>& relationships) const {
  set<string> wantone = GetDesiredrelation(relationships);
  unsigned int answer = 0;  // final answer
  set<int> visited;         // the set of visited vertices.
  for (unsigned long i = 0; i < allvertices_.size();
       ++i) {                            // for loop go over all the vertices.
    int curr_node = allvertices_.at(i);  // current vertice visit.
    if (visited.count(curr_node) == 1)
      continue;                             // if visited before, continue.
    ++answer;                               // add one to answer
    queue<int> thiscomponent({curr_node});  // create a queue for the component
                                            // containing current node.
    while (!thiscomponent.empty()) {
      unsigned long size = thiscomponent.size();
      for (unsigned long i = 0; i < size; ++i) {
        int curr = thiscomponent.front();
        list<pair<int, string>> li =
            graph_.find(curr)->second;  // get the neihbours for current node.
        for (auto const& i : li) {
          if (visited.count(i.first) != 1 && wantone.count(i.second) == 1) {
            thiscomponent.push(i.first);
            visited.insert(i.first);
          }
        }
        thiscomponent.pop();
      }
    }
  }
  return answer;
}
