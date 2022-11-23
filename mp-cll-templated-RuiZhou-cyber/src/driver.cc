#include <iostream>

#include "circular-linked-list.hpp"
using namespace std;
int main() {
  CircularLinkedList<int> a;
  a.InsertInOrder(0);
  a.InsertInOrder(1);
  a.InsertInOrder(1);
  a.InsertInOrder(8);
  a.InsertInOrder(4);
  a.InsertInOrder(3);
  a.InsertInOrder(0);
  a.InsertInOrder(3);
  a.Reverse();
  CircularLinkedList<int> b(a);
  b.Reverse();
  cout << b << endl;
  CircularLinkedList<int> c;
  c.InsertInOrder(0);
  c.InsertInOrder(2);
  c.InsertInOrder(4);
  c.InsertInOrder(7);
  c.InsertInOrder(9);
  c.InsertInOrder(2);
  c.InsertInOrder(0);
  c.InsertInOrder(1);
  b.operator=(c);
  cout << c << endl;
  cout << b << endl;
}
