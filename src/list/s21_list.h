#ifndef CPP2_S21_CONTAINERS_1_LIST_H
#define CPP2_S21_CONTAINERS_1_LIST_H

#include <iostream>
#include <limits>

namespace s21 {
template <class T>
class list {
 public:
  // Member type
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

  class ListIterator;
  using iterator = ListIterator;
  using const_iterator = ListIterator;

  // Functions
  list();
  explicit list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& l);
  list& operator=(const list& l);
  list(list&& l) noexcept;
  list& operator=(list&& l) noexcept;
  ~list();

  // Element access
  const_reference front();
  const_reference back();

  // Iterator
  iterator begin() const;
  iterator end() const;

  // Capacity
  [[nodiscard]] bool empty() const;
  [[nodiscard]] size_type size() const;
  [[nodiscard]] size_type max_size() const;

  // Modifiers
  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void push_front(const_reference value);
  void pop_front();
  void swap(list& other);
  void merge(list& other);
  void splice(const_iterator pos, list& other);
  void reverse();
  void unique();
  void sort();

  // Modifiers DOP
  template <class... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <class... Args>
  void insert_many_back(Args&&... args);
  template <class... Args>
  void insert_many_front(Args&&... args);

 private:
  struct node {
    node* next;
    node* prev;
    T value;

    node() = default;
    node(node* next, node* prev, T value)
        : next(next), prev(prev), value(value){};
  };
  node* head_ = nullptr;
  node* tail_ = nullptr;
  node* end_node_ = nullptr;

  size_t size_ = 0;
};

template <class T>
class list<T>::ListIterator {
  friend class list<T>;

 public:
  ListIterator() = default;

  ListIterator& operator=(node& other);
  value_type operator*();
  ListIterator operator++();
  void operator++(int);
  ListIterator operator--();
  void operator--(int);
  bool operator==(list<T>::ListIterator iterator) const;
  bool operator!=(list<T>::ListIterator iterator) const;

 private:
  node* node_;
};

////////////////////////////////// Constructor ///////////////////////////////
template <class T>
list<T>::list() : head_(nullptr), tail_(nullptr), size_(0) {
  end_node_ = new node;
}

template <class T>
list<T>::list(size_type n) : list() {
  for (size_type i = 0; i < n; ++i) {
    push_back(T{});
  }
}

template <class T>
list<T>::list(std::initializer_list<value_type> const& items)
    : head_(nullptr), tail_(nullptr), size_(0) {
  end_node_ = new node;
  for (const auto& item : items) {
    push_back(item);
  }
}

template <class T>
list<T>::list(const list& l) {
  end_node_ = new node;
  for (auto i = l.begin(); i != l.end(); ++i) {
    push_back(*i);
  }
}

template <class T>
list<T>::list(list&& l) noexcept {
  swap(l);
}

template <class T>
list<T>::~list() {
  clear();
  delete end_node_;
}

//////////////////////////// Operators Constructor ///////////////////////////
template <class T>
list<T>& list<T>::operator=(const list& l) {
  if (this != &l) {
    clear();
    for (auto i = l.begin(); i != l.end(); ++i) {
      push_back(*i);
    }
  }
  return *this;
}

template <class T>
list<T>& list<T>::operator=(list&& l) noexcept {
  if (this == &l) {
    return *this;
  }
  clear();
  swap(l);
  return *this;
}

////////////////////////////////// Modifiers //////////////////////////////////
template <class T>
void list<T>::push_back(const_reference value) {
  auto* new_node = new node(end_node_, nullptr, value);
  if (!head_) {
    head_ = new_node;
    tail_ = new_node;
    end_node_->next = head_;
  } else {
    new_node->prev = tail_;
    tail_->next = new_node;
    tail_ = new_node;
  }
  end_node_->prev = tail_;
  ++size_;
}

template <class T>
void list<T>::push_front(const_reference value) {
  auto* new_node = new node(head_, nullptr, value);
  if (!head_) {
    head_ = new_node;
    tail_ = new_node;
  } else {
    head_->prev = new_node;
    head_ = new_node;
  }
  end_node_->next = head_;
  ++size_;
}

template <class T>
void list<T>::pop_back() {
  if (!head_) {
    return;
  }

  auto* old_tail_ = tail_;
  if (head_ == tail_) {
    head_ = end_node_;
    tail_ = end_node_;
  } else {
    tail_ = tail_->prev;
    end_node_->prev = tail_;
    tail_->next = end_node_;
  }
  delete old_tail_;
  --size_;
}

template <class T>
void list<T>::pop_front() {
  if (!head_ || head_ == end_node_) {
    return;
  }
  auto* old_head = head_;
  if (head_ == tail_) {
    head_ = end_node_;
    tail_ = end_node_;
  } else {
    head_ = head_->next;
    head_->prev = nullptr;
  }
  end_node_->next = head_;
  delete old_head;
  --size_;
}

template <class T>
void s21::list<T>::clear() {
  while (!empty()) {
    pop_front();
  }
}

template <class T>
void list<T>::swap(list& other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(end_node_, other.end_node_);
  std::swap(size_, other.size_);
}

template <class T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  node* tmp = nullptr;
  iterator itr;
  if (size_ == 0) {
    tmp = new node(end_node_, nullptr, value);
    head_ = tmp;
    tail_ = tmp;
    end_node_->prev = tail_;

    end_node_->next = head_;
  } else if (pos == begin()) {
    tmp = new node(head_, nullptr, value);
    head_->prev = tmp;
    head_ = tmp;

    end_node_->next = head_;
  } else if (pos == end()) {
    tmp = new node(end_node_, tail_, value);
    tail_->next = tmp;
    tail_ = tmp;
    end_node_->prev = tail_;
  } else {
    tmp = new node(pos.node_, pos.node_->prev, value);
    pos.node_->prev->next = tmp;
    pos.node_->prev = tmp;
  }
  itr = *tmp;
  ++size_;
  return itr;
}

template <class T>
void list<T>::splice(const_iterator pos, list& other) {
  if (this == &other) {
    return;
  }
  while (!other.empty()) {
    insert(pos, front());
    other.pop_front();
  }
}

template <class T>
void list<T>::erase(list::iterator pos) {
  node* current = pos.node_;
  if (current == nullptr || current == end_node_) {
    return;
  }
  if (current->prev) {
    current->prev->next = current->next;
  } else {
    head_ = current->next;
    end_node_->next = head_;
  }
  if (current->next) {
    current->next->prev = current->prev;
  } else {
    tail_ = current->prev;
  }
  delete current;
  --size_;
}

template <class T>
void list<T>::reverse() {
  if (!head_ || !head_->next) return;
  node* current = head_;
  while (current) {
    node* tmp = current->prev;
    node* next_node = current->next;
    current->next = tmp;
    current->prev = next_node;
    current = next_node;
  }
  std::swap(head_, tail_);
  tail_->next = end_node_;
  end_node_->prev = tail_;
}

template <class T>
void list<T>::sort() {
  if (size_ < 2) return;

  for (iterator itr = begin(); itr != end(); ++itr) {
    T val = *itr;
    iterator next_pos = itr;
    ++next_pos;
    erase(itr);

    iterator insert_pos = begin();
    while (insert_pos != end() && *insert_pos <= val) {
      ++insert_pos;
    }
    insert(insert_pos, val);
    itr = next_pos;
  }
}

template <class T>
void list<T>::unique() {
  if (size_ < 2) return;

  iterator itr = begin();
  iterator next_pos = itr;
  ++next_pos;

  while (next_pos != end()) {
    if (*next_pos == *itr) {
      erase(next_pos);
      next_pos = itr;
      ++next_pos;
    } else {
      itr = next_pos;
      ++next_pos;
    }
  }
}

template <class T>
void list<T>::merge(list& other) {
  if (this != &other && !other.empty()) {
    while (!other.empty()) {
      push_back(*other.begin());
      other.erase(other.begin());
    }
  }
}

////////////////////////////////// iterator //////////////////////////////////
template <class T>
typename list<T>::iterator list<T>::begin() const {
  list<T>::iterator itr = iterator();
  itr = head_ ? *head_ : *end_node_;
  return itr;
}

template <class T>
typename list<T>::iterator list<T>::end() const {
  list<T>::iterator iterator;
  if (end_node_) {
    iterator = *end_node_;
  }
  return iterator;
}

////////////////////////////////// Capacity //////////////////////////////////
template <class T>
bool list<T>::empty() const {
  return !size_;
}

template <class T>
typename list<T>::size_type list<T>::size() const {
  return size_;
}

template <class T>
typename list<T>::size_type list<T>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(node);
}

////////////////////////////////// Access //////////////////////////////////
template <class T>
typename list<T>::const_reference list<T>::front() {
  static const T default_value = T{};
  if (head_) {
    return head_->value;
  } else {
    return default_value;
  }
}

template <class T>
typename list<T>::const_reference list<T>::back() {
  static const T default_value = T{};
  if (tail_) {
    return tail_->value;
  } else {
    return default_value;
  }
}

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

template <class T>
typename list<T>::ListIterator& list<T>::ListIterator::operator=(node& other) {
  node_ = &other;
  return *this;
}

template <class T>
typename list<T>::value_type list<T>::iterator::operator*() {
  return node_->value;
}

template <class T>
typename list<T>::ListIterator list<T>::iterator::operator++() {
  if (node_) {
    node_ = node_->next;
  }
  return *this;
}

template <class T>
void list<T>::ListIterator::operator++(int) {
  ++(*this);
}

template <class T>
typename list<T>::ListIterator list<T>::iterator::operator--() {
  if (node_ && node_->prev) {
    node_ = node_->prev;
  }
  return *this;
}

template <class T>
void list<T>::ListIterator::operator--(int) {
  --(*this);
}

template <class T>
bool list<T>::iterator::operator==(const list<T>::ListIterator iterator) const {
  return node_ == iterator.node_;
}

template <class T>
bool list<T>::iterator::operator!=(const list<T>::ListIterator iterator) const {
  return node_ != iterator.node_;
}

/////////////////////////////// Modifiers DOP ///////////////////////////////
template <class T>
template <typename... Args>
typename list<T>::ListIterator list<T>::insert_many(iterator pos,
                                                    Args&&... args) {
  iterator itr = pos;
  for (auto arg : {args...}) {
    insert(itr, arg);
  }
  return itr;  //--irt
}

template <class T>
template <typename... Args>
void list<T>::insert_many_back(Args&&... args) {
  for (auto arg : {args...}) {
    push_back(arg);
  }
}

template <class T>
template <typename... Args>
void list<T>::insert_many_front(Args&&... args) {
  for (auto arg : {args...}) {
    push_front(arg);
  }
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_LIST_H