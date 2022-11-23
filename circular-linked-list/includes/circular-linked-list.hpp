#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  void InsertInOrder(const T& data);
  void AscOrder(const T& data);
  void DesOrder(const T& data);
  void Reverse();

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  if (head_ == nullptr) return;
  Node<T>* iter = head_;
  while (iter != tail_) {
    Node<T>* next = iter->next;
    delete iter;
    iter = next;
  }
  delete iter;
  head_ = tail_ = nullptr;
}

template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) {
  if (source.head_ == nullptr) {
    head_ = tail_ = nullptr, node_order_ = source.node_order_;
    return;
  }
  head_ = new Node<T>(source.head_->data);
  Node<T>* iter = source.head_;
  Node<T>* thing = head_;
  while (iter->next != source.head_) {
    thing->next = new Node<T>(iter->next->data);
    iter = iter->next;
    thing = thing->next;
  }
  thing->next = head_;
  tail_ = thing;
  node_order_ = source.node_order_;
  iter = thing = nullptr;
}

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(
    const CircularLinkedList<T>& source) {
  if (this == &source) return *this;
  this->~CircularLinkedList();
  if (source.head_ == nullptr) {
    head_ = tail_ = nullptr, node_order_ = source.node_order_;
    return *this;
  }
  head_ = new Node<T>(source.head_->data);
  Node<T>* iter = source.head_;
  Node<T>* thing = head_;
  while (iter->next != source.head_) {
    thing->next = new Node<T>(iter->next->data);
    iter = iter->next;
    thing = thing->next;
  }
  thing->next = head_;
  tail_ = thing;
  node_order_ = source.node_order_;
  iter = thing = nullptr;
  return *this;
}

template <typename T>
void CircularLinkedList<T>::AscOrder(const T& data) {
  if (head_ == nullptr) {
    head_ = new Node<T>(data), tail_ = head_, tail_->next = head_;
    return;
  }
  if (data <= head_->data) {
    Node<T>* tmp = new Node(data);
    tmp->next = head_;
    head_ = tmp;
    tail_->next = head_;
  } else {
    Node<T>* curr = head_;
    Node<T>* tmp = new Node(data);
    while (curr->next != head_ && curr->next->data < data) {
      curr = curr->next;
    }
    tmp->next = curr->next;
    curr->next = tmp;
    if (tmp->next == head_) {
      tail_ = tmp;
      tail_->next = head_;
    }
  }
}

template <typename T>
void CircularLinkedList<T>::DesOrder(const T& data) {
  if (head_ == nullptr) {
    head_ = new Node<T>(data), tail_ = head_, tail_->next = head_;
    return;
  }
  if (data >= head_->data) {
    Node<T>* tmp = new Node(data);
    tmp->next = head_;
    head_ = tmp;
    tail_->next = head_;
  } else {
    Node<T>* curr = head_;
    Node<T>* tmp = new Node(data);
    while (curr->next != head_ && curr->next->data > data) {
      curr = curr->next;
    }
    tmp->next = curr->next;
    curr->next = tmp;
    if (tmp->next == head_) {
      tail_ = tmp;
      tail_->next = head_;
    }
  }
}

template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  if (node_order_ == Order::kASC) {
    AscOrder(data);
  } else {
    DesOrder(data);
  }
}

template <typename T>
void CircularLinkedList<T>::Reverse() {
  if (head_ == tail_ || head_ == nullptr) {
    if (node_order_ == Order::kASC) {
      node_order_ = Order::kDESC;
    } else {
      node_order_ = Order::kASC;
    }
    return;
  }
  Node<T>* curr = head_;
  Node<T>* prev = nullptr;
  Node<T>* next = curr->next;
  while (curr != tail_) {
    prev = curr;
    curr = next;
    next = curr->next;
    curr->next = prev;
  }
  next->next = tail_;
  tail_ = next;
  head_ = curr;
  if (node_order_ == Order::kASC) {
    node_order_ = Order::kDESC;
  } else {
    node_order_ = Order::kASC;
  }
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);

  return os;
}

#endif