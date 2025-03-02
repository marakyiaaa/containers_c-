#ifndef CPP2_S21_CONTAINERS_1_S21_VECTOR_H
#define CPP2_S21_CONTAINERS_1_S21_VECTOR_H

#include <cstring>
#include <initializer_list>
#include <iostream>

namespace s21 {
template <class T>
class vector {
 public:
  //  Vector Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  //  Vector Member functions
  vector();
  vector(size_type n);
  vector(std::initializer_list<value_type> const &items);
  vector(const vector &v);
  vector(vector &&v) noexcept;
  ~vector();

  vector &operator=(vector &&v) noexcept;

  //  Vector Element access
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  T *data();

  //  Vector Iterators
  iterator begin();
  iterator end();

  //  Vector Capacity
  bool empty();
  size_type size();
  size_type max_size();
  void reserve(size_type size);
  size_type capacity();
  void shrink_to_fit();

  //  Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other);

  void fill();

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args);

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  size_type size_{};
  size_type capacity_{};
  T *begin_{};

  void redistribute();
};

// CONSTRUCTOR

template <class T>
vector<T>::vector() = default;

template <class T>
vector<T>::vector(vector::size_type n) {
  begin_ = new T[n];
  capacity_ = n;
  size_ = n;
}

template <class T>
vector<T>::vector(const std::initializer_list<value_type> &items)
    : vector(items.size()) {
  std::copy(items.begin(), items.end(), begin_);
}

template <class T>
vector<T>::vector(const vector &v) : size_(v.size_), capacity_(v.capacity_) {
  begin_ = new T[capacity_];
  std::memcpy(begin_, v.begin_, v.size_ * sizeof(T));
}

template <class T>
vector<T>::vector(vector &&v) noexcept {
  if (this != &v) {
    if (begin_) {
      delete[] begin_;
    }
    begin_ = nullptr;
    capacity_ = 0;
    size_ = 0;
    std::swap(size_, v.size_);
    std::swap(capacity_, v.capacity_);
    std::swap(begin_, v.begin_);
  }
}

template <class T>
vector<T>::~vector() {
  clear();
}

template <class T>
void vector<T>::clear() {
  delete[] begin_;
  begin_ = nullptr;
  size_ = 0;
  capacity_ = 0;
}

template <class T>
typename s21::vector<T> &s21::vector<T>::operator=(vector<T> &&v) noexcept {
  if (begin_) {
    delete[] begin_;
  }
  begin_ = nullptr;
  capacity_ = 0;
  size_ = 0;
  std::swap(begin_, v.begin_);
  std::swap(size_, v.size_);
  std::swap(capacity_, v.capacity_);
  return *this;
}

//  Vector Element access

template <class T>
T &vector<T>::at(vector::size_type pos) {
  if (pos > size_) {
    throw std::out_of_range("out_of_range");
  }
  return begin_[pos];
}

template <class T>
T &vector<T>::operator[](vector::size_type pos) {
  return begin_[pos];
}

template <class T>
const T &vector<T>::front() {
  return begin_[0];
}

template <class T>
const T &vector<T>::back() {
  return begin_[size_ - 1];
}

template <class T>
T *vector<T>::data() {
  return begin_;
}

// Iterator

template <class T>
typename s21::vector<T>::iterator vector<T>::begin() {
  return begin_;
}

template <class T>
typename s21::vector<T>::iterator vector<T>::end() {
  return begin_ + size_;
}

//  Vector Capacity

template <class T>
bool vector<T>::empty() {
  return this->begin() == this->end();
}

template <class T>
typename vector<T>::size_type vector<T>::size() {
  return size_;
}

template <class T>
size_t vector<T>::max_size() {
  return std::numeric_limits<size_t>::max() / sizeof(T);
}

template <class T>
void vector<T>::reserve(vector::size_type size) {
  if (capacity_ < size) {
    capacity_ = size;
    T *new_array = new T[capacity_];
    std::memcpy(new_array, begin_, size_ * sizeof(T));
    delete begin_;
    begin_ = new T[capacity_];
    std::memcpy(begin_, new_array, size_ * sizeof(T));
    delete[] new_array;
  }
}

template <class T>
typename vector<T>::size_type vector<T>::capacity() {
  return capacity_;
}

template <class T>
void vector<T>::shrink_to_fit() {
  if (size_ != capacity_) {
    T *temp = new T[size_];
    capacity_ = size_;
    std::memcpy(temp, begin_, size_ * sizeof(T));
    delete begin_;
    begin_ = temp;
  }
}

// Modifiers

template <class T>
typename s21::vector<T>::iterator vector<T>::insert(vector::iterator pos,
                                                    const_reference value) {
  if (pos == end()) {
    push_back(value);
  } else if (pos == begin_) {
    T *temp = new T[capacity_ + 1]();
    begin_[0] = value;
    std::memcpy(temp + 1, begin_, size_ * sizeof(T));
    ++size_;
    redistribute();
    std::memcpy(begin_, temp, size_ * sizeof(T));
    delete[] temp;
  } else {
    T *temp = new T[capacity_ + 1]();
    long int insert = pos - begin_;
    size_t start = (pos - begin_) * sizeof(T);
    size_t stop = (end() - pos + 1) * sizeof(T);
    std::memcpy(temp, begin_, start);
    temp[pos - begin_] = value;
    std::memcpy(temp + insert + 1, pos, stop);
    ++size_;
    redistribute();
    std::memcpy(begin_, temp, size_ * sizeof(T));
    pos = insert + begin_;
    delete[] temp;
  }
  return pos;
}

template <class T>
void vector<T>::erase(vector::iterator pos) {
  T *temp = new T[capacity_];
  int del_pos = pos - begin_;
  size_t start = sizeof(T) * del_pos;
  size_--;
  size_t position = sizeof(T) * (begin_ + size_ - pos);
  size_t end = position;
  std::memcpy(temp, begin_, start);
  std::memcpy(temp + del_pos, begin_ + del_pos + 1, end);
  std::memcpy(begin_, temp, size_ * sizeof(T));
  delete[] temp;
}

template <class T>
void vector<T>::push_back(const_reference value) {
  redistribute();
  begin_[size_] = value;
  size_++;
}

template <class T>
void vector<T>::pop_back() {
  erase(end() - 1);
}

template <class T>
void vector<T>::swap(vector &other) {
  std::swap(capacity_, other.capacity_);
  std::swap(size_, other.size_);
  std::swap(begin_, other.begin_);
}

template <class T>
void vector<T>::redistribute() {
  if (!size_ && !capacity_) {
    capacity_ = 1;
  } else if (size_ == capacity_) {
    capacity_ = (size_t)(capacity_ * 2);
  }
  T *temp = new T[capacity_];
  std::memcpy(temp, begin_, size_ * sizeof(T));
  delete begin_;
  begin_ = new T[capacity_];
  std::memcpy(begin_, temp, size_ * sizeof(T));
  delete[] temp;
}

template <class T>
void vector<T>::fill() {
  for (size_t i = 0; i < size_; i++) {
    begin_[i] = i + 10;
  }
}

template <class T>
template <typename... Args>
typename s21::vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                         Args &&...args) {
  size_t countEl = sizeof...(args);
  size_t it = pos - begin_;

  if (size_ + countEl > capacity_) {
    redistribute();
  }
  std::memmove(begin_ + it + countEl, begin_ + it, (size_ - it) * sizeof(T));
  T temp[] = {T(std::forward<Args>(args))...};
  std::memmove(begin_ + it, temp, countEl * sizeof(T));

  size_ += countEl;

  return begin_ + it;
}

template <class T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  size_t countEl = sizeof...(args);
  if (size_ + countEl > capacity_) {
    reserve(size_ + countEl);
  }
  T temp[] = {T(std::forward<Args>(args))...};
  std::memcpy(begin_ + size_, temp, countEl * sizeof(T));
  size_ += countEl;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_S21_VECTOR_H
