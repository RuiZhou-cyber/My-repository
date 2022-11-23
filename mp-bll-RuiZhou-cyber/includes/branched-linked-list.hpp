#ifndef BRANCHED_LINKED_LIST_HPP
#define BRANCHED_LINKED_LIST_HPP

#include <cstddef>
#include <stdexcept>
#include <string>

#include "node.hpp"

class BLL {
public:
  BLL() = default;          // done
  BLL(const BLL& to_copy);  // done
  ~BLL();                   // done

  BLL& operator=(const BLL& rhs);    // done
  Node* PushBack(char dat);          // done
  char GetAt(size_t idx) const;      // done
  void SetAt(size_t idx, char dat);  // done
  void Join(size_t idx, BLL* list);  // done
  std::string ToString() const;
  size_t Size() const;                                // done
  Node* Findloc(Node* startpoint, size_t idx) const;  // done

private:
  Node* head_ = nullptr;
  bool IsBLLAcyclic() const;               // done
  Node* Findnext(const Node* from) const;  // done
  void Clear(Node* n);                     // done
  void Clear();                            // done
};

#endif
