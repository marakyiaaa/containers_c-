#ifndef CONTAINERS_QUEUE_H
#define CONTAINERS_QUEUE_H

#include "../list/s21_list.h"
#include "iostream"

namespace s21 {
template <class T>
class queue : protected list<T> {
 public:
  // Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  // Functions
  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);
  queue(queue &&q) noexcept;
  ~queue();

  queue &operator=(queue &&q) noexcept;

  // Element access
  using list<T>::front;
  using list<T>::back;

  // Capacity
  using list<T>::empty;
  using list<T>::size;

  //   Modifiers
  void push(const_reference value);
  using list<T>::pop_front;
  void swap(queue &other);

  // Modifiers DOP
  template <class... Args>
  void insert_many_back(Args &&...args);
};

////////////////////////////////// Constructor ///////////////////////////////
template <class T>
queue<T>::queue() : list<T>() {}

template <class T>
queue<T>::queue(std::initializer_list<value_type> const &items)
    : list<T>(items) {}

template <class T>
queue<T>::queue(const queue &q) : list<T>(q) {}

template <class T>
queue<T>::queue(queue &&q) noexcept : list<T>(std::move(q)) {}

template <class T>
queue<T>::~queue() {}

//////////////////////////// Operator Constructor /////////////////?//////////
template <class T>
queue<T> &queue<T>::operator=(queue &&q) noexcept {
  if (this != &q) {
    list<T>::operator=(std::move(q));
  }
  return *this;
}

////////////////////////////////// Modifiers //////////////////////////////////
template <class T>
void queue<T>::push(const_reference value) {
  list<T>::push_back(value);
}

template <class T>
void queue<T>::swap(queue &other) {
  list<T>::swap(other);
}

/////////////////////////////// Modifiers DOP ///////////////////////////////
template <class T>
template <typename... Args>
void queue<T>::insert_many_back(Args &&...args) {
  list<T>::insert_many_back(args...);
}

}  // namespace s21

#endif  // CONTAINERS_QUEUE_H