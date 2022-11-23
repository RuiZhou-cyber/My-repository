#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();
  int Findremoveidx(const char* pattern);  // should be ok now.
  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);
  int Getsizeofcharstring(const char* pattern);  // should be ok now.
  void Removemid(int idx, int size);             // should be ok now.
  void Removefront(int size);                    // should be ok now.
  void Insertmid(int idx, DNAstrand& to_splice_in);

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

#endif