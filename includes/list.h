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
#include <limits>
#include <memory>
#include <ostream>
#include <stdexcept>
#include <utility>

namespace s21 {

// -------------------------------------------------------

template <typename T, typename A = std::allocator<T>>
class List {
 private:
  struct Node;
  struct Iterator;
  struct IteratorConst;
  struct InputIterator;
  struct IteratorReverse;

 public:
  using value_type = T;
  // using allocator_type Allocator
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;
  using reference = T &;
  using const_reference = T const &;
  using pointer = value_type *;
  using const_pointer = value_type const *;
  using iterator = Iterator;
  using reverse_iterator = IteratorReverse;
  using node_allocator =
      typename std::allocator_traits<A>::template rebind_alloc<Node>;
  // using const_iterator = IteratorConst;
  // using reverse_iterator = std::reverse_iterator<iterator>;
  // using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  /* *****  ***** */

  using const_value_type = T const;
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

  List(List &&other) noexcept {
    head_ = other.head_;
    size_ = other.size_;
    other.head_ = nullptr;
    other.size_ = 0;
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

  List &operator=(List &&other) noexcept {
    if (this != &other) {
      Destroy();
      head_ = other.head_;
      size_ = other.size_;
      other.head_ = nullptr;
      other.size_ = 0;
    }
    return (*this);
  }

  ~List() { Destroy(); }

  // void assign(std::initializer_list<value_type> lst);

  // void assign(size_type n_elem, value_type const &val);
  // void assign(InputIterator first, InputIterator last);

  // -------------------------------------------------------

  friend std::ostream &operator<<(std::ostream &os, List const &lst) {
    for (auto const &value : lst) {
      std::cout << value << std::endl;
    }
    return (os);
  }

  // -------------------------------------------------------

  /**
   * @brief Insert the elements at any position of list. This function takes 2
   *            elements, position and value to insert.
   *
   * @param pos -> Position in the container where the new elements are
   *                    inserted.
   * @param value -> Valueto be copied (or moved) to the inserted elements.
   *
   * @return -> This function returns an interator
   *                 that points to the first of the newly inserted elements.
   */
  Iterator insert(iterator pos,
                  const_reference value) {  // TODO(probiuss): change iterator
                                            //  to const_iterartor
    node_type *tmp = new node_type(value);
    pos.node_->AddPrev(tmp);
    ++size_;

    return Iterator(tmp);
  }

  // -------------------------------------------------------

  /**
   * @brief Insert the elements at any position of list. This function takes 3
   *            elements, position, number of elements to insert
   *            and value to insert. If not mentioned,
   *            number of elements is default set to 1.
   *
   * @param pos -> Position in the container where the new elements are
   *                    inserted.
   * @param n_elem -> Number of elements to insert. Each elements is initizlized
   *                       to a copy of val.
   * @param value -> Valueto be copied (or moved) to the inserted elements.
   *
   *
   * @return -> This function returns an interator
   *                 that points to the first of the newly inserted elements
   */
  Iterator insert(iterator pos, size_type n_elem, const_reference value) {
    node_type *res = new node_type(value);
    pos.node_->AddPrev(res);
    ++size_;
    --n_elem;

    for (; n_elem > 0; --n_elem) {
      node_type *tmp = new node_type(value);
      pos.node_->AddPrev(tmp);
      ++size_;
    }

    return Iterator(res);
  }

  // -------------------------------------------------------

  /**
   * @brief Insert the elements at any position of list. This function takes 2
   *            elements, position and values to insert.
   *
   *            example -- tmp_list.insert(iter.begin(), {1, 2, 3});
   *
   * @param pos -> Position in the container where the new elements are
   *                    inserted.
   * @param value -> Values to be copied (or moved) to the inserted elements.
   *
   * @return -> This function returns an interator
   *                 that points to the first of the newly inserted elements
   */
  Iterator insert(iterator pos, std::initializer_list<value_type> values) {
    node_type *res = nullptr;
    for (auto const &value : values) {
      node_type *tmp = new node_type(value);
      if (res == nullptr) {
        res = tmp;
      }
      pos.node_->AddPrev(tmp);
      ++size_;
    }

    return Iterator(res);
  }

  // -------------------------------------------------------

  reference font() { return *begin(); }
  reference back() { return *(--end()); }
  void push_front(value_type value) { insert(begin(), value); }
  void push_back(value_type value) { insert(end(), value); }

  // -------------------------------------------------------

  /**
   * @brief Delete elements from a list container.
   *                Decrement (size)
   *
   * @param pos -> This parameter is used when the function is used to delete a
   *                    single element. This parameter refers to an iterator
   *                    which points to the element which is need to be erased
   *                    from the list container.
   *
   * @return -> This function returns an iterator pointing to the element
   *                in the list container which followed the last
   *                element erased from the list container.
   */
  Iterator erase(iterator pos) noexcept {
    iterator res = pos;
    if (pos != end()) {
      ++res;
      node_type *tmp = pos.node_;
      pos.node_->prev_->next_ = pos.node_->next_;
      pos.node_->next_->prev_ = pos.node_->prev_;

      tmp->prev_ = nullptr;
      tmp->next_ = nullptr;
      delete tmp;
      tmp = nullptr;
      --size_;
    }

    return (res);
  }

  // -------------------------------------------------------

  void clear() {
    for (auto iter = begin(); size_ > 0 || begin() != end(); iter = begin()) {
      erase(iter);
    }
  }

  // -------------------------------------------------------

  /* ** ***** Capacity ***** ** */

  bool empty() { return (end() == begin()); }
  unsigned size() const { return size_; }
  size_type max_size() const { return allocator.max_size(); }

  /* ** ***** ******** ***** ** */

  void resize(unsigned num) { (void)num; }
  void resize(unsigned from, unsigned to) {
    (void)from;
    (void)to;
  }

  // -------------------------------------------------------

  inline Iterator begin() const {
    return Iterator(head_->next_);
    // return head_iter_;
  }

  inline reverse_iterator rbegin() const {
    return IteratorReverse(head_->prev_);
    // return head_iter_;
  }

  inline Iterator end() const {
    return Iterator(head_);
    // return tail_iter_;
  }

  inline reverse_iterator rend() const {
    return IteratorReverse(head_->next_);
    // return tail_iter_;
  }

  // -------------------------------------------------------

 private:
  void Destroy() {
    node_type *tmp_type = begin().node_;
    auto finish = end().node_;

    for (auto start = tmp_type; start != finish;) {
      start = start->next_;
      delete tmp_type;
      tmp_type = start;
    }
    delete tmp_type;
  }

  // -------------------------------------------------------

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

  // -------------------------------------------------------

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
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = List::value_type;
    using difference_type = std::ptrdiff_t;
    using pointer = value_type *;
    using reference = value_type &;

    // Dont't use an empty iterator.
    Iterator() = delete;
    explicit Iterator(node_type *node) : node_(node) {}
    Iterator(Iterator const &other) : node_(other.node_) {}
    Iterator &operator=(Iterator const &other) {
      node_ = other.node_;
      return *this;
    }

    /* ** Non-member functions ** */

    bool operator==(Iterator const &other) const {
      return (node_ == other.node_);
    }
    bool operator!=(Iterator const &other) const { return !(other == *this); }

    // TODO(probiuss): in question !!!
    // bool operator<(Iterator const &other);
    // bool operator<=(Iterator const &other);
    // bool operator>(Iterator const &other);
    // bool operator>=(Iterator const &other);

    /* ** ******************** ** */

    /**
     * @brief Iterator transition (forward) to the next element.
     *
     * @return (Iterator &) Getting a link to a new element.
     */
    Iterator &operator++() noexcept {
      node_ = node_->next_;
      return *this;
    }

    // -------------------------------------------------------

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

    reference operator*() const {
      if (node_ == 0)
        throw std::out_of_range(
            "[ERROR] tried to dereference an empty iterator");
      return node_->value_;
    }

    Node *node_;
  };  // Iterator

  // -------------------------------------------------------

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
    using reference = const_value_type &;

    IteratorConst() = delete;
    explicit IteratorConst(const_node_type *node) : node_(node) {}
    // explicit IteratorConst(const_iterator &iter) : node_(iter.node_) {}

    const_node_type *node_;
  };  // IteratorConst

  struct IteratorReverse {
    node_type *node_;
  };  // IteratorReverse

  // -------------------------------------------------------

  // TODO(probiuss): Prepare iterator reverse
  node_type *head_;
  size_t size_;
  node_allocator allocator;
  // node_type *tail_;

  // Iterator head_iter_;
  // Iterator tail_iter_;
};  // List

}  // namespace s21

// -------------------------------------------------------

#endif  // INCLUDES_LIST_H_
