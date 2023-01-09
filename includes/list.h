/* ************************************************************************** */
/* Copyright 2023 *********************************************************** */
/*                                              ############       ####       */
/*                                              ############       ####       */
/*          *.h                                             ####       ####   */
/*                                                          ####       ####   */
/*   By: probiuss@student.21-school.ru              ########           ####   */
/*                                                  ########           ####   */
/*                                              ####                   ####   */
/*   Created: 2023-01-01                        ####                   ####   */
/*   Updated: 2023-01-20                            ############       ####   */
/*                                                  ############       ####   */
/* ************************************************************************** */

#ifndef INCLUDES_LIST_H_
#define INCLUDES_LIST_H_

#include <iostream>
#include <iterator>
#include <ostream>
#include <stdexcept>
#include <utility>

namespace s21 {

// -------------------------------------------------------

template <typename T>

class List {
 private:
  struct Node;
  struct Iterator;
  struct IteratorConst;

 public:
  using value_type = T;
  using const_value_type = T const;
  using value_reference = T &;
  using const_reference = T const &;
  using iterator = Iterator;
  // using const_iterator = IteratorConst;
  using size_type = std::size_t;
  using node_type = Node;
  using const_node_type = Node const;

 public:
  List() : head_(new node_type{}), size_(0U) {}

  explicit List(size_type size) {
    while (size > 0) {
      push_back(value_type());
      --size;
    }
  }

  List(const List &other) {
    for (auto value : other) {
      push_back(value);
      ++size_;
    }
  }

  List(std::initializer_list<value_type> init_list)
      : head_(new Node()), size_(0U) {
    for (auto const &item : init_list) {
      push_back(item);
    }
  }

  List &operator=(List const &other) {
    size_ = 0;
    head_ = nullptr;
    (void)other;
    return (*this);
  }

  List &operator=(List &&other) {
    size_ = 0;
    head_ = nullptr;
    if (this != other) {
      // TODO(probiuss): release
    }
    return (*this);
  }

  ~List() { destroy(); }

  friend std::ostream &operator<<(std::ostream &os, List const &lst) {
    for (auto const &value : lst) {
      std::cout << value << std::endl;
    }
    return (os);
  }

  /**
   * @brief
   *
   * @param pos
   * @param value
   *
   * @return
   */
  Iterator insert(iterator pos,
                  const_reference value) {  // TODO(probiuss): change iterator
                                            //  to const_iterartor
    node_type *tmp = new node_type(value);
    pos.node_->AddPrev(tmp);
    ++size_;

    return Iterator(tmp);
  }

  value_reference font() { return *begin(); }
  value_reference back() { return *end(); }
  void push_front(T value) { insert(begin(), value); }
  void push_back(T value) { insert(end(), value); }

  void erase(iterator pos) noexcept {
    if (pos != end()) {
      node_type *tmp = pos.node_;
      pos.node_->prev_->next_ = pos.node_->next_;
      pos.node_->next_->prev_ = pos.node_->prev_;

      tmp->prev_ = nullptr;
      tmp->next_ = nullptr;
      delete tmp;
      tmp = nullptr;
      --size_;
    }
  }

  void clear() {
    if (size_ > 0) {
      // TODO(probiuss): erase
    }
  }

  bool empty() { return (end() == begin()); }

  unsigned size() const { return size_; }
  void resize(unsigned num) { (void)num; }
  void resize(unsigned from, unsigned to) {
    (void)from;
    (void)to;
  }
  void AllocateMemory();

  /* *****  ***** */

  inline Iterator begin() const {
    return Iterator(head_->next_);
    // return head_iter_;
  }
  inline Iterator end() const {
    return Iterator(head_);
    // return tail_iter_;
  }

 private:
  void destroy() {
    node_type *tmp_type = begin().node_;
    auto finish = end().node_;

    for (auto start = tmp_type; start != finish;) {
      start = start->next_;
      delete tmp_type;
      tmp_type = start;
    }
    delete tmp_type;
  }

  /**
   * @brief A node of a doubly linked list.
   */
  struct Node {
    Node() : value_(value_type{}), next_(this), prev_(this) {}
    explicit Node(const_reference value) noexcept
        : value_(value), next_(nullptr), prev_(nullptr) {
      prev_ = nullptr;
    }
    explicit Node(value_type &&value) noexcept
        : value_(std::move(value)), next_(nullptr), prev_(nullptr) {}
    ~Node() = default;

    /* *****  ***** */

    void AddPrev(node_type *node) {
      node->prev_ = prev_;
      node->next_ = this;
      prev_->next_ = node;
      prev_ = node;
    }

    value_type value_;
    node_type *next_;
    node_type *prev_;
  };

  /**
   * @brief Iterator structure for a list.
   *
   * @details Concepts. Linear doubly linked (bidirectional).
   * - node (node of list)
   * - node->next -- Pointer to the first element.
   * - node->prev -- Pointer to the end element.
   *
   * If the list is empty, it points to itself.
   */
  struct Iterator {
    // TODO(probiuss): desctiprion below.
    // using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = List::value_type;
    using pointer = value_type *;
    using value_reference = value_type &;

    // Dont't use an empty iterator.
    Iterator() = delete;
    explicit Iterator(node_type *node) : node_(node) {}
    Iterator(Iterator const &other) : node_(other.node_) {}
    Iterator &operator=(Iterator const &other) {
      node_ = other.node_;
      return *this;
    }

    bool operator==(Iterator const &other) const {
      return (node_ == other.node_);
    }

    bool operator!=(Iterator const &other) const { return !(other == *this); }

    /**
     * @brief Iterator transition (forward) to the next element.
     *
     * @return (Iterator &) Getting a link to a new element.
     */
    Iterator &operator++() noexcept {
      node_ = node_->next_;
      return *this;
    }

    /**
     * @brief Iterator transition (forward) to the next element.
     *
     * @return (Iterator) Getting a value to a new element.
     */
    Iterator operator++(int) noexcept {
      Iterator tmp(node_);
      ++(*this);

      return tmp;
    }

    Iterator &operator--() {
      node_ = node_->prev_;
      return *this;
    }
    // Iterator operator--(int);

    value_reference operator*() const {
      if (node_ == 0)
        throw std::out_of_range(
            "[ERROR] tried to dereference an empty iterator");
      return node_->value_;
    }

    Node *node_;
  };  // Iterator

  /**
   * @brief IteratorConst structure for a list.
   *            You cannot change the list items.
   *
   * @details Concepts. Linear doubly linked (bidirectional).
   * - node (node of list)
   * - node->next -- Pointer to the first element.
   * - node->prev -- Pointer to the end element.
   *
   * If the list is empty, it points to itself.
   */
  struct IteratorConst {
    // using iterator_category = std::bidirectional_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = List::value_type;
    using pointer = const_value_type *;
    using value_reference = const_value_type &;

    IteratorConst() = delete;
    explicit IteratorConst(const_node_type *node) : node_(node) {}
    // explicit IteratorConst(const_iterator &iter) : node_(iter.node_) {}

    const_node_type *node_;
  };  // IteratorConst

  node_type *head_;
  // node_type *tail_;

  // Iterator head_iter_;
  // Iterator tail_iter_;
  size_t size_;
};  // List

}  // namespace s21

// -------------------------------------------------------

#endif  // INCLUDES_LIST_H_
