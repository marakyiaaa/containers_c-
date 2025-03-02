#ifndef CONTAINERS_STACK_H
#define CONTAINERS_STACK_H

#include "../list/s21_list.h"
#include "iostream"

namespace s21 {
template <class T>
class stack : protected list<T> {
 public:
  // Member type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  // Functions
  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &q);
  stack(stack &&q) noexcept;
  ~stack();

  stack &operator=(stack &&q) noexcept;

  // Element access
  const_reference top();

  // Capacity
  using list<T>::empty;
  using list<T>::size;

  //   Modifiers
  void push(const_reference value);
  void pop();
  void swap(stack &other);

  // Modifiers DOP
  template <class... Args>
  void insert_many_front(Args &&...args);
};

////////////////////////////////// Constructor ///////////////////////////////
template <class T>
stack<T>::stack() : list<T>() {}

template <class T>
stack<T>::stack(std::initializer_list<value_type> const &items)
    : list<T>(items) {}

template <class T>
stack<T>::stack(const stack &q) : list<T>(q) {}

template <class T>
stack<T>::stack(stack &&q) noexcept : list<T>(std::move(q)) {}

template <class T>
stack<T>::~stack() {}

//////////////////////////// Operator Constructor /////////////////?//////////
template <class T>
stack<T> &stack<T>::operator=(stack &&q) noexcept {
  if (this != &q) {
    list<T>::operator=(std::move(q));
  }
  return *this;
}

////////////////////////////////// Access //////////////////////////////////
template <class T>
typename stack<T>::const_reference stack<T>::top() {
  return list<T>::back();
}

////////////////////////////////// Modifiers //////////////////////////////////
template <class T>
void stack<T>::push(const_reference value) {
  list<T>::push_back(value);
}

template <class T>
void stack<T>::pop() {
  list<T>::pop_back();
}

template <class T>
void stack<T>::swap(stack &other) {
  list<T>::swap(other);
}

/////////////////////////////// Modifiers DOP ///////////////////////////////
template <class T>
template <typename... Args>
void stack<T>::insert_many_front(Args &&...args) {
  list<T>::insert_many_front(args...);
}

}  // namespace s21

#endif  // CONTAINERS_STACK_H
