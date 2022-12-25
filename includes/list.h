#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <ostream>
#include <stdexcept>

namespace s21 {

// -------------------------------------------------------

template <typename T> class List {
  class Node {
    friend class Iterator;
    friend class List<T>;

  public:
    Node(T value) : value_(value), next_(nullptr), prev_(nullptr) {}
    Node() : value_(0), next_(nullptr), prev_(nullptr) {}
    // Node() = default;
    ~Node() = default;


  private:
    T value_;
    Node *next_;
    Node *prev_;
  };

  /* *****  ***** */

  class Iterator {
    // friend class Node<T>;
    friend class List<T>;

  public:
    Iterator() : node_(nullptr) {}
    Iterator(Node *node) : node_(node) {}
    Iterator(Iterator const &other) : node_(other.node_) {}
    Iterator &operator=(Iterator const &other) {
      node_ = other.node_;
      return *this;
    }

    bool operator==(Iterator const &other) const {
      return (node_ == other.node_);
    }

    bool operator!=(Iterator const &other) const { return !(other == *this); }

    Iterator &operator++() {
      if (node_ == nullptr)
        throw std::out_of_range("[ERROR] incremented an empty iterator");
      if (node_->next_ == nullptr)
        throw std::out_of_range("[ERROR] tried to increment too far past the end");

      node_ = node_->next_;
      return *this;
    }

    Iterator &operator--() {
      if (node_ == nullptr)
        throw std::out_of_range("[ERROR] decremented an empty iterator");
      if (node_->prev_ == nullptr)
        throw std::out_of_range("[ERROR] tried to decrement past the beginning");

      node_ = node_->prev_;
    }

    T &operator*() const {
      if (node_ == 0)
        throw std::out_of_range("[ERROR] tried to dereference an empty iterator");
      return node_->value_;
    }

  private:
    Node *node_;
  };

  /* *****  ***** */

public:
  List() { AllocateMemory(); }

  List(T value) {
    AllocateMemory();
    push_front(value);
  }

  ~List() {
    auto tmp_node = head_;

    for (auto begin = head_; begin != tail_;) {
      begin = begin->next_;
      delete tmp_node;
      tmp_node = begin;
    }

    delete tmp_node;
  }


  friend std::ostream &operator<<(std::ostream &os, List const &lst) {
      for (auto &i : lst) {
          os << i << std::endl;
      }
    return (os);
  }

  void push_front(T value);
  void push_back(T value);
  bool empty() { return (head_ == tail_); }
  unsigned size() const;
  void resize(unsigned num);
  void resize(unsigned from, unsigned to);
  void AllocateMemory();

  /* *****  ***** */

  inline Iterator begin() const { return head_iter_; }
  inline Iterator end() const { return tail_iter_; }

private:
  Node *head_;
  Node *tail_;

  Iterator head_iter_;
  Iterator tail_iter_;
};

/*************************************************/
/* ********         REALIZATION         ******** */
/*************************************************/

template <typename T> void List<T>::push_front(T value) {
  auto tmp_node = new Node(value);

  if (tail_ == nullptr)
      std::cout << "tail nullptr" << std::endl;

  if (head_ == nullptr)
      std::cout << "head nullptr" << std::endl;
  tmp_node->prev_ = nullptr;
  tmp_node->next_ = head_;
  head_->prev_ = tmp_node;
  head_ = tmp_node;
  head_iter_ = Iterator(head_);
}

// -------------------------------------------------------

template <typename T> void List<T>::push_back(T value) {
  auto tmp_node = new Node(value);

  // TODO: fix add back and allocate  fix
  tmp_node->next_ = nullptr;
  tmp_node->prev_ = tail_;
  tail_->next_ = tmp_node;
  tail_ = tmp_node;
  tail_iter_ = Iterator(tail_);
}

// -------------------------------------------------------

template <typename T> unsigned List<T>::size() const {
  unsigned n_variables = 0;
  for (auto *begin = head_; begin != tail_; begin = begin->next_) {
    ++n_variables;
  }
  return (n_variables);
}

// -------------------------------------------------------

template <typename T> void List<T>::resize(unsigned num) { (void)(num); }

// -------------------------------------------------------

template <typename T> void List<T>::resize(unsigned from, unsigned to) {
  (void)(from);
  (void)(to);
}

// -------------------------------------------------------

template <typename T> void List<T>::AllocateMemory() {
  head_ = new Node;
  tail_ = head_;

  tail_->next_ = nullptr;
  tail_->prev_ = nullptr;

  head_iter_ = Iterator(head_);
  tail_iter_ = Iterator(tail_);
}

} // namespace s21

// -------------------------------------------------------

#endif /* ifndef LIST_HPP */
