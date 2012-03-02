#ifndef _LIST_BASE_H_
#define _LIST_BASE_H_

#define LIST_DEFAULT_SIZE 512

#include <iostream>

template<typename Elem>
class list_base {
 public:
  list_base() {}
  ~list_base() {}

  int size() = 0;
  bool is_empty() = 0;
  bool append(const Elem &) = 0;
  bool remove_last(Elem&) = 0;
};

#endif //_LIST_BASE_H_

