#ifndef CONTAINERS_ARRAY_H
#define CONTAINERS_ARRAY_H

#include <algorithm>
#include <limits>
#include <stdexcept>

#include "iostream"

namespace s21 {
template <class T, std::size_t N>
class array {
 public:
  // Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = std::size_t;

  // Functions
  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a) noexcept;
  ~array();
  array &operator=(array &&a);

  // Element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();

  // Iterators
  iterator begin() const;
  iterator end() const;

  // capacity_
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  // Modifiers
  void swap(array &other);
  void fill(const_reference value);

 private:
  iterator array_;
  size_t capacity_ = N;
};

////////////////////////////////// Constructor ///////////////////////////////
template <class T, std::size_t N>
array<T, N>::array() {
  array_ = new T[N]();
}

template <class T, std::size_t N>
array<T, N>::array(const std::initializer_list<value_type> &items) {
  if (items.size() > capacity_) {
    throw std::length_error("Initializer is too large");
  }
  array_ = new T[N]();
  std::copy(items.begin(), items.end(), array_);
}

template <class T, std::size_t N>
array<T, N>::array(const array &a) : capacity_(N) {
  array_ = new T[N];
  std::copy(a.array_, a.array_ + N, array_);
}

template <class T, std::size_t N>
array<T, N>::array(array &&a) noexcept
    : array_(a.array_), capacity_(a.capacity_) {
  a.array_ = nullptr;
  a.capacity_ = 0;
}

template <class T, std::size_t N>
array<T, N>::~array() {
  delete[] array_;
}

//////////////////////////// Operator Constructor ///////////////////////////
template <class T, std::size_t N>
array<T, N> &array<T, N>::operator=(array &&a) {
  if (this != &a) {
    delete[] array_;
    array_ = a.array_;
    capacity_ = a.capacity_;
    a.array_ = nullptr;
    a.capacity_ = 0;
  }
  return *this;
}

////////////////////////////////// Capacity //////////////////////////////////
template <class T, std::size_t N>
bool array<T, N>::empty() const {
  return !capacity_;
}

template <class T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() const {
  return capacity_;
}

template <class T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const {
  return capacity_;
}

////////////////////////////////// Iterator //////////////////////////////////
template <class T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() const {
  return array_;
}

template <class T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() const {
  return array_ + capacity_;
}

////////////////////////////////// Modifiers //////////////////////////////////
template <class T, std::size_t N>
void array<T, N>::swap(array &other) {
  std::swap(capacity_, other.capacity_);
  std::swap(array_, other.array_);
}

template <class T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < capacity_; i++) {
    array_[i] = value;
  }
}

//////////////////////////////// Element Access //////////////////////////////
template <class T, std::size_t N>
T &array<T, N>::at(array::size_type pos) {
  if (pos >= capacity_) {
    throw std::out_of_range("out of range");
  }
  return array_[pos];
}

template <class T, std::size_t N>
T &array<T, N>::operator[](array::size_type pos) {
  return array_[pos];
}

template <class T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() {
  return array_[0];
}

template <class T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() {
  return array_[capacity_ - 1];
}

template <class T, std::size_t N>
T *array<T, N>::data() {
  return array_;
}
}  // namespace s21

#endif  // CONTAINERS_ARRAY_H
