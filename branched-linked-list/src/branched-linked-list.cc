#include "branched-linked-list.hpp"

using namespace std;
BLL::BLL(const BLL& to_copy) {
  if (to_copy.head_ == nullptr) {
    head_ = nullptr;
    return;
  }
  head_ = new Node(to_copy.head_->data_);
  Node* curr = head_;
  Node* iter = to_copy.head_;
  while (iter != nullptr) {
    if (iter->next_node_ != nullptr) {
      curr->next_node_ = new Node(iter->next_node_->data_);
    }
    if (iter->next_bll_ != nullptr) {
      curr->next_bll_ = new BLL(*iter->next_bll_);
    }
    curr = curr->next_node_;
    iter = iter->next_node_;
  }
}

BLL::~BLL() {
  while (head_ != nullptr) {
    Node* next = head_->next_node_;
    delete head_->next_bll_;
    delete head_;
    head_ = next;
  }
  head_ = nullptr;
}

BLL& BLL::operator=(const BLL& rhs) {
  if (&rhs == this) return *this;
  this->~BLL();
  if (rhs.head_ == nullptr) {
    head_ = nullptr;
    return *this;
  }
  head_ = new Node(rhs.head_->data_);
  Node* curr = head_;
  Node* iter = rhs.head_;
  while (iter != nullptr) {
    if (iter->next_node_ != nullptr) {
      curr->next_node_ = new Node(iter->next_node_->data_);
    }
    if (iter->next_bll_ != nullptr) {
      curr->next_bll_ = new BLL(*iter->next_bll_);
    }
    curr = curr->next_node_;
    iter = iter->next_node_;
  }
  return *this;
}

Node* BLL::PushBack(char dat) {
  if (head_ == nullptr) {
    head_ = new Node(dat);
    return head_;
  }
  Node* next = head_;
  while (next->next_node_ != nullptr) {
    next = next->next_node_;
  }
  next->next_node_ = new Node(dat);
  return next->next_node_;
}

size_t BLL::Size() const {
  if (head_ == nullptr) return 0;
  size_t count = 0;
  Node* curr = head_;
  while (curr != nullptr) {
    ++count;
    if (curr->next_bll_ != nullptr) {
      count += curr->next_bll_->Size();
    }
    curr = curr->next_node_;
  }
  curr = nullptr;
  return count;
}

Node* BLL::Findloc(Node* startpoint, size_t idx) const {
  size_t where = 0;
  Node* curr = startpoint;
  while (where != idx) {
    if (curr->next_bll_ != nullptr) {
      if (curr->next_bll_->Size() >= idx - where) {
        return Findloc(curr->next_bll_->head_, idx - where - 1);
      }
      where += curr->next_bll_->Size();
    }
    curr = curr->next_node_;
    ++where;
  }
  return curr;
}

char BLL::GetAt(size_t idx) const {
  if (idx < 0 || idx >= this->Size()) throw runtime_error("idx not valid.");

  return Findloc(head_, idx)->data_;
}

void BLL::SetAt(size_t idx, char dat) {
  if (idx < 0 || idx >= this->Size()) throw runtime_error("idx not valid.");

  Findloc(head_, idx)->data_ = dat;
}

bool BLL::IsBLLAcyclic() const {
  if (head_ == nullptr) return true;
  Node* fast = Findnext(head_);
  Node* slow = head_;
  while (fast != nullptr && slow != nullptr) {
    if (fast == slow) return false;
    if (Findnext(fast) == nullptr)
      fast = nullptr;
    else
      fast = Findnext(Findnext(fast));
    slow = Findnext(slow);
  }
  return true;
}

Node* BLL::Findnext(const Node* from) const {
  if (from->next_bll_ != nullptr) return from->next_bll_->head_;
  if (from->next_node_ != nullptr) return from->next_node_;
  return nullptr;
}

void BLL::Join(size_t idx, BLL* list) {
  if (idx < 0 || idx >= this->Size()) throw runtime_error("idx not valid.");

  if (Findloc(head_, idx)->next_bll_ != nullptr)
    throw runtime_error("already exist.");

  Findloc(head_, idx)->next_bll_ = list;

  if (!IsBLLAcyclic()) {
    Findloc(head_, idx)->next_bll_ = nullptr;
    throw runtime_error("cause a cycle");
  }
}

std::string BLL::ToString() const {
  if (head_ == nullptr) return "";
  string answer;
  Node* curr = head_;
  while (curr != nullptr) {
    answer.push_back(curr->data_);
    if (curr->next_bll_ != nullptr) {
      answer += curr->next_bll_->ToString();
    }
    curr = curr->next_node_;
  }
  return answer;
}
