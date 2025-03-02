#ifndef CPP2_S21_CONTAINERS_1_S21_SET_H
#define CPP2_S21_CONTAINERS_1_S21_SET_H

#include <initializer_list>

#include "../tree/tree.h"
#include "../vector/s21_vector.h"

namespace s21 {

template <class Key>
class set {
 public:
  using value_type = Key;
  using size_type = typename BinaryTree<Key>::size_type;
  using iterator = typename BinaryTree<Key>::iterator;
  using const_iterator = typename BinaryTree<Key>::const_iterator;

  set() = default;
  set(const set &other);
  set &operator=(const set &other);
  set(std::initializer_list<value_type> init);
  set(set &&other);
  ~set() = default;

  std::pair<iterator, bool> insert(const value_type &value);
  void erase(iterator pos);
  void clear();
  void swap(set &other);
  bool contains(const Key &key);
  void merge(set &other);

  iterator find(const Key &key) const;

  bool empty() const;
  size_type size() const;

  iterator begin();
  iterator end();
  const_iterator begin() const;
  const_iterator end() const;

  //  friend class BinaryTree<Key>;

  template <typename... Args>
  std::vector<std::pair<iterator, bool> > insert_many(Args &&...args);

 private:
  BinaryTree<Key> tree_;
  void copyFrom(const set &other);
};

template <class Key>
set<Key>::set(const set &other) : tree_(other.tree_) {}

template <class Key>
set<Key>::set(set &&other) : tree_(std::move(other.tree_)) {}

template <class Key>
set<Key>::set(std::initializer_list<value_type> init) : set() {
  for (const auto &value : init) {
    insert(value);
  }
}

template <class Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const value_type &value) {
  return tree_.insert(value);
}

template <class Key>
void set<Key>::erase(iterator pos) {
  tree_.erase(pos);
}

template <class Key>
void set<Key>::clear() {
  tree_.clear();
}

template <class Key>
void set<Key>::swap(set &other) {
  tree_.swap(other.tree_);
}

template <class Key>
typename set<Key>::iterator set<Key>::find(const Key &key) const {
  return tree_.find(key);
}

template <class Key>
bool set<Key>::empty() const {
  return tree_.empty();
}

template <class Key>
typename set<Key>::size_type set<Key>::size() const {
  return tree_.size();
}

template <class Key>
typename set<Key>::iterator set<Key>::begin() {
  return tree_.begin();
}

template <class Key>
typename set<Key>::iterator set<Key>::end() {
  return tree_.end();
}

template <class Key>
typename set<Key>::const_iterator set<Key>::begin() const {
  return tree_.begin();
}

template <class Key>
typename set<Key>::const_iterator set<Key>::end() const {
  return tree_.end();
}

template <class Key>
void set<Key>::copyFrom(const set &other) {
  BinaryTree<Key>::copyTree(tree_, other.root_, nullptr);
}

template <class Key>
set<Key> &set<Key>::operator=(const set &other) {
  if (this != &other) {
    tree_ = other.tree_;
  }
  return *this;
}

template <class Key>
bool set<Key>::contains(const Key &key) {
  return this->find(key) != this->end();
}

template <class Key>
void set<Key>::merge(set &other) {
  if (this != &other) {
    for (auto it = other.begin(); it != other.end(); ++it) {
      this->insert(*it);
    }
    other.clear();
  }
}

template <class Key>
template <typename... Args>
std::vector<std::pair<typename set<Key>::iterator, bool> >
set<Key>::insert_many(Args &&...args) {
  std::vector<std::pair<iterator, bool> > res;
  (res.push_back(this->insert(std::forward<Args>(args))), ...);
  return res;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_S21_SET_H
