#ifndef CPP2_S21_CONTAINERS_1_S21_CONTAINERSPLUS_H
#define CPP2_S21_CONTAINERS_1_S21_CONTAINERSPLUS_H

#include <initializer_list>
#include <utility>

#include "../tree/tree.h"

namespace s21 {

template <typename Key>
class multiset {
 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename BinaryTree<Key>::iterator;
  using const_iterator = typename BinaryTree<Key>::const_iterator;
  using size_type = std::size_t;

  // Constructors
  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& ms);
  multiset(multiset&& ms);
  ~multiset();

  // Operators
  multiset& operator=(multiset&& ms);

  // Iterator
  iterator begin();
  iterator end();

  // Capacity
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  // Modifiers
  void clear();
  iterator insert(const value_type& value);
  void erase(iterator pos);
  void swap(multiset& other);
  void merge(multiset& other);

  // Search operations
  size_type count(const key_type& key) const;
  iterator find(const key_type& key);
  bool contains(const key_type& key) const;
  std::pair<iterator, iterator> equal_range(const key_type& key) const;
  iterator lower_bound(const key_type& key) const;
  iterator upper_bound(const key_type& key) const;

  template <typename... Args>
  std::vector<std::pair<iterator, bool> > insert_many(Args&&... args);

 private:
  BinaryTree<Key> tree_;
};

// Realization of functions

template <typename Key>
multiset<Key>::multiset() : tree_() {}

template <typename Key>
multiset<Key>::multiset(std::initializer_list<value_type> const& items)
    : tree_() {
  for (const auto& item : items) {
    tree_.insert(item);
  }
}

template <typename Key>
multiset<Key>::multiset(const multiset& ms) : tree_(ms.tree_) {}

template <typename Key>
multiset<Key>::multiset(multiset&& ms) : tree_(std::move(ms.tree_)) {}

template <typename Key>
multiset<Key>::~multiset() {}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(multiset&& ms) {
  if (this != &ms) {
    tree_ = std::move(ms.tree_);
  }
  return *this;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::begin() {
  return tree_.begin();
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::end() {
  return tree_.end();
}

template <typename Key>
bool multiset<Key>::empty() const {
  return tree_.empty();
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::size() const {
  return tree_.size();
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::max_size() const {
  return tree_.max_size();
}

template <typename Key>
void multiset<Key>::clear() {
  tree_.clear();
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::insert(
    const value_type& value) {
  return tree_.insert(value);
}

template <typename Key>
void multiset<Key>::erase(iterator pos) {
  tree_.erase(pos);
}

template <typename Key>
void multiset<Key>::swap(multiset& other) {
  tree_.swap(other.tree_);
}

template <typename Key>
void multiset<Key>::merge(multiset& other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    tree_.insert(*it);
  }
  other.clear();
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(
    const key_type& key) const {
  size_type count = 0;
  for (auto it = tree_.begin(); it != tree_.end(); ++it) {
    if (*it == key) {
      ++count;
    }
  }
  return count;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::find(const key_type& key) {
  return tree_.find(key);
}

template <typename Key>
bool multiset<Key>::contains(const key_type& key) const {
  return tree_.find(key) != tree_.end();
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const key_type& key) const {
  return std::make_pair(lower_bound(key), upper_bound(key));
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(
    const key_type& key) const {
  auto it = tree_.begin();
  for (; it != tree_.end(); ++it) {
    if (*it >= key) {
      break;
    }
  }
  return it;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(
    const key_type& key) const {
  auto it = tree_.begin();
  for (; it != tree_.end(); ++it) {
    if (*it > key) {
      break;
    }
  }
  return it;
}

template <typename Key>
template <typename... Args>
std::vector<std::pair<typename multiset<Key>::iterator, bool> >
multiset<Key>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool> > res;
  (res.emplace_back(tree_.insert(std::forward<Args>(args))), ...);
  return res;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_S21_CONTAINERSPLUS_H
