#ifndef CPP2_S21_CONTAINERS_MAP_H
#define CPP2_S21_CONTAINERS_MAP_H

#include <initializer_list>
#include <stdexcept>
#include <tuple>
#include <utility>

#include "../tree/tree.h"

namespace s21 {

template <class K, class V>
class map {
 private:
  struct map_pair {
    K first;
    V second;

    map_pair(const K &k = K(), const V &v = V()) : first(k), second(v) {}

    bool operator<(const map_pair &other) const { return first < other.first; }

    bool operator==(const map_pair &other) const {
      return first == other.first;
    }

    bool operator>(const map_pair &other) const { return first > other.first; }

    bool operator<=(const map_pair &other) const {
      return first <= other.first;
    }

    bool operator>=(const map_pair &other) const {
      return first >= other.first;
    }

    bool operator!=(const map_pair &other) const {
      return first != other.first;
    }
  };

 public:
  using value_type = map_pair;
  using iterator = typename BinaryTree<value_type>::iterator;
  using const_iterator = typename BinaryTree<value_type>::const_iterator;
  using size_type = typename BinaryTree<value_type>::size_type;

  map() = default;
  map(std::initializer_list<value_type> init);

  std::pair<iterator, bool> insert(const value_type &value);
  std::pair<iterator, bool> insert(const K &key, const V &value);
  std::pair<iterator, bool> insert_or_assign(const K &key, const V &obj);

  V &operator[](const K &key);
  V &at(const K &key);

  void erase(iterator pos);
  void clear();
  void swap(map &other);
  void merge(map &other);

  iterator find(const K &key);
  const_iterator find(const K &key) const;

  bool empty() const;
  size_type size() const;

  iterator begin();
  iterator end();

  template <typename... Args>
  std::vector<std::pair<iterator, bool> > insert_many(Args &&...args);

 private:
  BinaryTree<map_pair> tree_;
  void eraseByKey(const K &key);
};

template <class K, class V>
map<K, V>::map(std::initializer_list<value_type> init) {
  for (const auto &value : init) {
    insert(value);
  }
}

template <class K, class V>
std::pair<typename map<K, V>::iterator, bool> map<K, V>::insert(
    const value_type &value) {
  return tree_.insert(value);
}

template <class K, class V>
std::pair<typename map<K, V>::iterator, bool> map<K, V>::insert(
    const K &key, const V &value) {
  return insert(value_type(key, value));
}

template <class K, class V>
std::pair<typename map<K, V>::iterator, bool> map<K, V>::insert_or_assign(
    const K &key, const V &obj) {
  auto it = tree_.find(value_type(key, V()));
  if (it != tree_.end()) {
    it->second = obj;
    return std::make_pair(it, false);
  }
  return tree_.insert(value_type(key, obj));
}

template <class K, class V>
V &map<K, V>::operator[](const K &key) {
  auto result = insert(key, V());
  return result.first->second;
}

template <class K, class V>
V &map<K, V>::at(const K &key) {
  auto it = find(key);
  if (it == end()) {
    throw std::out_of_range("NotKey");
  }
  return it->second;
}

template <class K, class V>
void map<K, V>::erase(iterator pos) {
  if (pos != end()) {
    tree_.erase(pos);
  }
}

template <class K, class V>
void map<K, V>::clear() {
  tree_.clear();
}

template <class K, class V>
void map<K, V>::swap(map &other) {
  tree_.swap(other.tree_);
}

template <class K, class V>
typename map<K, V>::iterator map<K, V>::find(const K &key) {
  return tree_.find(value_type(key, V()));
}

template <class K, class V>
typename map<K, V>::const_iterator map<K, V>::find(const K &key) const {
  return tree_.find(value_type(key, V()));
}

template <class K, class V>
bool map<K, V>::empty() const {
  return tree_.empty();
}

template <class K, class V>
typename map<K, V>::size_type map<K, V>::size() const {
  return tree_.size();
}

template <class K, class V>
typename map<K, V>::iterator map<K, V>::begin() {
  return tree_.begin();
}

template <class K, class V>
typename map<K, V>::iterator map<K, V>::end() {
  return tree_.end();
}

template <class K, class V>
void map<K, V>::merge(map &other) {
  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }
}

template <class K, class V>
template <typename... Args>
std::vector<std::pair<typename map<K, V>::iterator, bool> >
map<K, V>::insert_many(Args &&...args) {
  std::vector<std::pair<iterator, bool> > res;
  res.reserve(sizeof...(args));
  auto elem = std::make_tuple(std::forward<Args>(args)...);

  auto lambda = [&](auto &&...pair) {
    (..., res.push_back(insert(
              value_type(std::forward<decltype(pair.first)>(pair.first),
                         std::forward<decltype(pair.second)>(pair.second)))));
  };

  std::apply(lambda, elem);
  return res;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_MAP_H
