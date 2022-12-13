#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>

namespace s21 {

/* *****  ***** */

template <typename T> class ListNode {

public:
    ListNode(T value) : value_(value) { }   
    ListNode() = default;
    ~ListNode() = default;
    
    void print() {
        std::cout << value_ << " " << std::endl;
    }

private:
    T value_;
    ListNode *next_;
    ListNode *prev_;
};

/* *****  ***** */
template <typename T>
class ListIterator {
public:
private:
    // ListNode *head_;
    // ListNode *tail_;

    // ListIterator *head_iter_;
    // ListIterator *tail_iter_;
};

/* *****  ***** */

template <typename T> class List {

public:
public:
  List();
  ~List();

  // friend class ListNode<T>;
  // friend class ListIterator;

  int test() const { return 3; }

private:
};

/* *****  ***** */

} // namespace s21

#endif /* ifndef LIST_HPP */
