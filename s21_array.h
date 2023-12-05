#ifndef S21_CONTAINERS_SRC_ARRAY_H_
#define S21_CONTAINERS_SRC_ARRAY_H_

#include <iostream>
#include <iterator>

namespace s21 {

template <class T, size_t N>
class array {
 public:
  using iterator = T *;
  using const_iterator = const T *;

  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  array(std::initializer_list<T> init_list);
  array() = default;
  array(const array &right) {
    for (size_type i = 0; i < N; i++) ptr_[i] = right.ptr_[i];
  }
  array(array &&other) noexcept;
  array &operator=(const array &right);
  array &operator=(array &&right) noexcept;
  ~array() noexcept = default;

  reference operator[](const size_type n);
  const_reference operator[](const size_type n) const;

  /**
   * @brief Returns an iterator to the beginning of the array.
   *
   * @return -> (iterator) An iterator to the beginning of the array.
   */
  iterator begin() noexcept;

  /**
   * @brief Returns a constant iterator to the beginning of the array.
   *
   * @return -> (const T *) A constant iterator to the beginning of the
   * array.
   */
  const_iterator begin() const noexcept;

  /**
   * @brief Returns a constant iterator to the beginning of the array.
   *
   * @return -> (const T *) A constant iterator to the beginning of the array.
   */
  const_iterator cbegin() const noexcept;

  /**
   * @brief Returns an iterator to the end of the array.
   *
   * @return -> (T *) An iterator to the end of the array.
   */
  iterator end() noexcept;
  const_iterator end() const noexcept;
  const_iterator cend() const noexcept;

  /**
   * @brief Returns a reference to the element at the specified position in the
   * array.
   *
   * @param position The position of the element to return.
   * @return -> (T &) A reference to the element at the specified position in
   * the array.
   */
  reference at(size_type position);

  const_reference at(size_type position) const;
  reference back();
  const_reference back() const;
  reference front();

  /**
   * @brief Returns a constant reference to the first element in the array.
   *
   * @return -> (T *) A constant reference to the first element in the array.
   */
  const_reference front() const;

  /**
   * @brief Returns a pointer to the underlying array.
   *
   * @return -> (T *) A pointer to the underlying array.
   */
  T *data();

  /**
   * @brief Returns a constant pointer to the underlying array.
   *
   * @return -> (const T *) A constant pointer to the underlying array.
   */
  const T *data() const;

  constexpr bool empty() const;

  /**
   * @brief Fills the array with the given value.
   *
   * @param value -> (const T&) The value to fill the array with.
   */
  void fill(const_reference value);

  constexpr size_type size() const;

  /**
   * @brief Returns the maximum possible size of the array.
   *
   * @return - (size_t)
   */
  constexpr size_type max_size() const;

  /**
   * @brief Swaps the content of the array with another array.
   *
   * This function swaps the content of the array
   *   with another array of the same type and size.
   *
   * @param -> (array) right The array to swap with.
   */
  void swap(array &right);

 private:
  value_type ptr_[N + 1] = {};

  /**
   * @brief Copies the content of the initializer list into the array.
   *
   * This function copies the content of the initializer list
   *   into the array, replacing its current content.
   *
   * @param init_list The initializer list to copy from.
   */
  void CopyList(std::initializer_list<T> init_list);
};

// ----------------------------------------------------------------------------

template <class T, size_t N>
void array<T, N>::swap(array &right) {
  array<value_type, N> tmp = std::move(right);
  right = std::move(*this);
  *this = std::move(tmp);
}

// -- -------------------------------------------- --

template <class T, size_t N>
constexpr typename array<T, N>::size_type array<T, N>::size() const {
  return N;
}

// -- -------------------------------------------- --

template <class T, size_t N>
constexpr typename array<T, N>::size_type array<T, N>::max_size() const {
  return N;
}

// -- -------------------------------------------- --

template <class T, size_t N>
typename array<T, N>::const_reference array<T, N>::front() const {
  return *ptr_;
}

// -- -------------------------------------------- --

template <class T, size_t N>
typename array<T, N>::reference array<T, N>::front() {
  return *ptr_;
}

// -- -------------------------------------------- --

template <class T, size_t N>
typename array<T, N>::reference array<T, N>::at(size_type position) {
  if (N <= position) throw std::out_of_range("going outside the array");
  return *(ptr_ + position);
}

// -- -------------------------------------------- --

template <class T, size_t N>
typename array<T, N>::const_reference array<T, N>::at(
    size_type position) const {
  if (N <= position) throw std::out_of_range("going outside the array");
  return *(ptr_ + position);
}

// -- -------------------------------------------- --

template <class T, size_t N>
void array<T, N>::fill(const_reference value) {
  array tmp;
  for (size_type i = 0; i < N; i++) tmp.ptr_[i] = value;
  swap(tmp);
}

// -- -------------------------------------------- --

template <class T, size_t N>
constexpr bool array<T, N>::empty() const {
  return !N;
}

// -- -------------------------------------------- --

template <class T, size_t N>
const T *array<T, N>::data() const {
  return ptr_;
}

// -- -------------------------------------------- --

template <class T, size_t N>
T *array<T, N>::data() {
  return ptr_;
}

// -- -------------------------------------------- --

template <class T, size_t N>
typename array<T, N>::reference array<T, N>::back() {
  return *(ptr_ + N - 1);
}

// -- -------------------------------------------- --

template <class T, size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
  return *(ptr_ + N - 1);
}

// -- -------------------------------------------- --

template <class T, size_t N>
void array<T, N>::CopyList(std::initializer_list<T> init_list) {
  auto it = init_list.begin();
  for (size_type i = 0; i < init_list.size(); i++) ptr_[i] = *it++;
}

// -- -------------------------------------------- --

template <class T, size_t N>
array<T, N>::array(array &&other) noexcept {
  for (size_type i = 0; i < N; i++) ptr_[i] = std::move(other.ptr_[i]);
}

// -- -------------------------------------------- --

template <class T, size_t N>
array<T, N>::array(std::initializer_list<T> init_list) {
  CopyList(init_list);
}

// -- -------------------------------------------- --

template <class T, size_t N>
array<T, N> &array<T, N>::operator=(const array<T, N> &right) {
  for (size_type i = 0; i < N; i++) ptr_[i] = right.ptr_[i];
  return *this;
}

// -- -------------------------------------------- --

template <class T, size_t N>
array<T, N> &array<T, N>::operator=(array<T, N> &&right) noexcept {
  for (size_type i = 0; i < N; i++) ptr_[i] = std::move(right.ptr_[i]);
  return *this;
}

// -- -------------------------------------------- --

template <class T, size_t N>
typename array<T, N>::reference array<T, N>::operator[](const size_type n) {
  return *(ptr_ + n);
}

// -- -------------------------------------------- --

template <class T, size_t N>
typename array<T, N>::const_reference array<T, N>::operator[](
    const size_type n) const {
  return *(ptr_ + n);
}

// -- -------------------------------------------- --

template <class T, size_t N>
typename array<T, N>::const_iterator array<T, N>::end() const noexcept {
  return ptr_ + N;
}

// -- -------------------------------------------- --

template <class T, size_t N>
typename array<T, N>::const_iterator array<T, N>::cend() const noexcept {
  return ptr_ + N;
}

// -- -------------------------------------------- --

template <class T, size_t N>
typename array<T, N>::iterator array<T, N>::end() noexcept {
  return ptr_ + N;
}

// -- -------------------------------------------- --

template <class T, size_t N>
typename array<T, N>::iterator array<T, N>::begin() noexcept {
  return ptr_;
}

// -- -------------------------------------------- --

template <class T, size_t N>
typename array<T, N>::const_iterator array<T, N>::begin() const noexcept {
  return static_cast<const_iterator>(ptr_);
}

// -- -------------------------------------------- --

template <class T, size_t N>
typename array<T, N>::const_iterator array<T, N>::cbegin() const noexcept {
  return static_cast<const_iterator>(ptr_);
}

}  // namespace s21
#endif  // S21_CONTAINERS_SRC_ARRAY_H_
