#include "dna_strand.hpp"

#include <stdexcept>

using namespace std;

DNAstrand::~DNAstrand() {
  while (head_ != nullptr) {
    Node* next = head_->next;
    delete head_;
    head_ = next;
  }
}

int DNAstrand::Getsizeofcharstring(const char* pattern) {
  int index = 0;
  while (pattern[index] != '\0') {
    ++index;
  }
  return index;
}

int DNAstrand::Findremoveidx(const char* pattern) {
  int answer = -1;
  int index = 0;
  Node* curr = head_;
  int size = Getsizeofcharstring(pattern);
  while (curr != nullptr) {
    if (curr->data == pattern[0]) {
      Node* start = curr;
      int count = 0;
      for (int i = 0; i < size; ++i) {
        if (start == nullptr) break;
        if (start->data == pattern[i] && start != nullptr) {
          ++count;
        }
        start = start->next;
      }
      if (count == size) {
        answer = index;
      }
    }
    curr = curr->next;
    ++index;
  }
  return answer;
}

void DNAstrand::Removefront(int size) {
  if (head_ == nullptr) return;
  int count = 0;
  while (head_ != nullptr && count != size) {
    Node* next = head_->next;
    delete head_;
    head_ = next;
    ++count;
  }
  if (head_ == nullptr) {
    tail_ = nullptr;
  }
}

void DNAstrand::Removemid(int idx, int size) {
  if (head_ == nullptr) return;
  Node* where = head_;
  int thing = 0;
  while (thing != idx - 1) {
    where = where->next;
    ++thing;
  }
  int count = 0;
  while (where->next != nullptr && count != size) {
    Node* next = where->next->next;
    delete where->next;
    where->next = next;
    ++count;
  }
  if (where->next == nullptr) {
    tail_ = where;
  }
}

void DNAstrand::Insertmid(int idx, DNAstrand& to_splice_in) {
  Node* where = head_;
  int count = 0;
  while (count != idx - 1) {
    where = where->next;
    ++count;
  }
  to_splice_in.tail_->next = where->next;
  where->next = to_splice_in.head_;
  if (to_splice_in.tail_->next == nullptr) {
    tail_ = to_splice_in.tail_;
  }
}

void DNAstrand::SpliceIn(const char* pattern, DNAstrand& to_splice_in) {
  int idx_to_remove = Findremoveidx(pattern);
  int size_of_pattern = Getsizeofcharstring(pattern);
  if (idx_to_remove == -1)
    throw runtime_error("cannot find the desired sequence.");
  if (to_splice_in.head_ == nullptr || Getsizeofcharstring(pattern) == 0 ||
      &to_splice_in == this)
    return;
  if (idx_to_remove == 0) {
    Removefront(size_of_pattern);
    if (head_ == nullptr) {
      head_ = to_splice_in.head_;
      tail_ = to_splice_in.tail_;
    } else {
      to_splice_in.tail_->next = head_;
      head_ = to_splice_in.head_;
    }
  } else {
    Removemid(idx_to_remove, size_of_pattern);
    if (head_ == nullptr) {
      head_ = to_splice_in.head_;
      tail_ = to_splice_in.tail_;
    } else {
      Insertmid(idx_to_remove, to_splice_in);
    }
  }
  to_splice_in.head_ = to_splice_in.tail_ = nullptr;
}
