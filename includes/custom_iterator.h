#ifndef CUSTOM_ITERATOR_HPP
#define CUSTOM_ITERATOR_HPP

/*! \class CustomIterator
 *  \brief Brief class description
 *
 *  Detailed description
 */
template <typename T> class CustomIterator {
public:
  CustomIterator() : p_(nullptr) {}
  CustomIterator(T *value) : p_(value) {}
  CustomIterator(CustomIterator const &other) : p_(other.p_) {}
  virtual ~CustomIterator() {}

  bool operator != (CustomIterator const &other) const;
  bool operator == (CustomIterator const &other) const;
  // typename CustomIterator::reference operator*() const;
  CustomIterator &operator++();

private:
  T *p_;
};

// -------------------------------------------------------

template <typename T>
bool CustomIterator<T>::operator != (CustomIterator const &other) const {
    return (p_ != other.p_);
}

/* *****  ***** */

template <typename T>
bool CustomIterator<T>::operator == (CustomIterator const &other) const{
    return (p_ == other.p_);
}

/* *****  ***** */

template <typename T>
CustomIterator<T> &CustomIterator<T>::operator++() {
    ++p_;
    return *this;
}


#endif // CUSTOM_ITERATOR_HPP
