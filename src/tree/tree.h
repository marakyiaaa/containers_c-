#ifndef CPP2_S21_CONTAINERS_1_TREE_H
#define CPP2_S21_CONTAINERS_1_TREE_H

#include <algorithm>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <utility>

namespace s21 {

template <class Key>
class BinaryTree {
 public:
  class tree_iterator;

  using key_type = Key;
  using value_type = Key;
  using reference = value_type;
  using const_reference = const value_type &;
  using size_type = size_t;

  using iterator = tree_iterator;
  using const_iterator = const tree_iterator;

  // Constructors
  BinaryTree() : root_(nullptr), tree_size_(0) {}
  BinaryTree(const BinaryTree &other);
  BinaryTree(std::initializer_list<value_type> const &items);
  BinaryTree(BinaryTree &&other);
  BinaryTree &operator=(BinaryTree &&other);
  BinaryTree &operator=(BinaryTree &other);
  ~BinaryTree();

  // Iterator
  iterator begin() const;
  iterator end() const;

  // Capacity
  bool empty() const;
  size_type size() const;
  size_type max_size() const;

  // Modifiers
  void clear();
  void erase(iterator &pos);
  void swap(BinaryTree &other);
  void merge(BinaryTree &other);
  std::pair<iterator, bool> insert(const value_type &value);

  // Lookup
  iterator find(const Key &key) const;

  // Operators
  bool operator==(const BinaryTree<Key> &other) const;

  BinaryTree &operator=(const BinaryTree &other) {
    if (this != &other) {
      clear();
      copyTree(root_, other.root_, nullptr);
    }
    return *this;
  }

 private:
  struct node {
    node *left;
    node *right;
    node *parent;
    int height;
    Key value;

    node(const Key &val)
        : left(nullptr),
          right(nullptr),
          parent(nullptr),
          height(1),
          value(val) {}
  };

  node *root_;
  size_type tree_size_;

  // Internal functions
  void copyTree(node *&oldnode, node *otherNode, node *parent);
  void destroy(node *n);

  int height(node *n) const;
  int getBalance(node *n) const;

  node *balance(node *n);
  node *rotationLeft(node *left);
  node *rotationRight(node *right);

  std::pair<node *, node *> insertNode(node *node2, const Key &value);

  node *recursiveErase(node *root_, const Key &key);
  node *minNode(node *nods);

  bool for_operators(const node *a, const node *b) const;
};

// Constructor

template <class Key>
BinaryTree<Key>::BinaryTree(const BinaryTree &other)
    : root_(nullptr), tree_size_(0) {
  copyTree(root_, other.root_, nullptr);
}

template <class Key>
BinaryTree<Key>::BinaryTree(std::initializer_list<value_type> const &items)
    : root_(nullptr), tree_size_(0) {
  for (const auto &item : items) {
    insert(item);
  }
}

template <class Key>
BinaryTree<Key>::BinaryTree(BinaryTree &&other)
    : root_(other.root_), tree_size_(other.tree_size_) {
  other.root_ = nullptr;
  other.tree_size_ = 0;
}

template <class Key>
BinaryTree<Key> &BinaryTree<Key>::operator=(BinaryTree &other) {
  if (this != &other) {
    clear();
    copyTree(root_, other.root_, nullptr);
    tree_size_ = other.tree_size_;
  }
  return *this;
}

template <class Key>
BinaryTree<Key> &BinaryTree<Key>::operator=(BinaryTree &&other) {
  if (this != &other) {
    clear();
    root_ = other.root_;
    tree_size_ = other.tree_size_;
    other.root_ = nullptr;
    other.tree_size_ = 0;
  }
  return *this;
}

template <class Key>
BinaryTree<Key>::~BinaryTree() {
  clear();
}

// Iterator

template <class Key>
typename BinaryTree<Key>::iterator BinaryTree<Key>::begin() const {
  node *ptr = root_;
  if (!ptr) {
    return iterator(nullptr);
  }
  while (ptr->left) {
    ptr = ptr->left;
  }
  return iterator(ptr);
}

template <class Key>
typename BinaryTree<Key>::iterator BinaryTree<Key>::end() const {
  return iterator(nullptr);
}

// Capacity

template <class Key>
bool BinaryTree<Key>::empty() const {
  return tree_size_ == 0;
}

template <class Key>
typename BinaryTree<Key>::size_type BinaryTree<Key>::size() const {
  return tree_size_;
}

template <class Key>
typename BinaryTree<Key>::size_type BinaryTree<Key>::max_size() const {
  return std::numeric_limits<size_type>::max() / sizeof(node);
}

// Modifiers

template <class Key>
void BinaryTree<Key>::clear() {
  destroy(root_);
  root_ = nullptr;
  tree_size_ = 0;
}

template <class Key>
void BinaryTree<Key>::swap(BinaryTree &other) {
  std::swap(root_, other.root_);
  std::swap(tree_size_, other.tree_size_);
}

template <class Key>
void BinaryTree<Key>::merge(BinaryTree &other) {
  if (this == &other) return;

  for (auto it = other.begin(); it != other.end(); ++it) {
    insert(*it);
  }

  other.clear();
}

template <class Key>
std::pair<typename BinaryTree<Key>::iterator, bool> BinaryTree<Key>::insert(
    const Key &value) {
  auto result = insertNode(root_, value);
  if (result.second) {
    if (root_ == nullptr) {
      root_ = result.first;
    }
    tree_size_++;
  }
  return std::make_pair(iterator(result.second), result.second);
}

template <class Key>
void BinaryTree<Key>::erase(iterator &pos) {
  if (pos == end()) return;

  root_ = recursiveErase(root_, *pos);
  tree_size_--;
}

// Lookup

template <class Key>
typename BinaryTree<Key>::iterator BinaryTree<Key>::find(const Key &key) const {
  node *cur = root_;
  while (cur != nullptr) {
    if (key < cur->value) {
      cur = cur->left;
    } else if (key > cur->value) {
      cur = cur->right;
    } else {
      return iterator(cur);
    }
  }
  return end();
}

// Operators

template <class Key>
bool BinaryTree<Key>::operator==(const BinaryTree<Key> &other) const {
  return for_operators(root_, other.root_);
}

// Other functions

template <class Key>
void BinaryTree<Key>::copyTree(node *&oldnode, node *otherNode, node *parent) {
  if (otherNode) {
    oldnode = new node(otherNode->value);
    oldnode->parent = parent;
    oldnode->height = otherNode->height;
    copyTree(oldnode->left, otherNode->left, oldnode);
    copyTree(oldnode->right, otherNode->right, oldnode);
    tree_size_++;
  }
}

template <class Key>
void BinaryTree<Key>::destroy(node *n) {
  if (n) {
    destroy(n->left);
    destroy(n->right);
    delete n;
  }
}

template <class Key>
int BinaryTree<Key>::height(node *n) const {
  return n ? n->height : 0;
}

template <class Key>
int BinaryTree<Key>::getBalance(node *n) const {
  return n ? height(n->left) - height(n->right) : 0;
}

template <class Key>
typename BinaryTree<Key>::node *BinaryTree<Key>::rotationRight(node *y) {
  node *x = y->left;
  node *T2 = x->right;

  x->right = y;
  y->left = T2;

  if (T2 != nullptr) {
    T2->parent = y;
  }
  x->parent = y->parent;

  if (y->parent == nullptr) {
    root_ = x;
  } else if (y == y->parent->left) {
    y->parent->left = x;
  } else {
    y->parent->right = x;
  }

  y->parent = x;

  y->height = std::max(height(y->left), height(y->right)) + 1;
  x->height = std::max(height(x->left), height(x->right)) + 1;

  return x;
}

template <class Key>
typename BinaryTree<Key>::node *BinaryTree<Key>::rotationLeft(node *x) {
  node *y = x->right;
  node *T2 = y->left;

  y->left = x;
  x->right = T2;

  if (T2 != nullptr) {
    T2->parent = x;
  }
  y->parent = x->parent;

  if (x->parent == nullptr) {
    root_ = y;
  } else if (x == x->parent->left) {
    x->parent->left = y;
  } else {
    x->parent->right = y;
  }
  x->parent = y;

  x->height = std::max(height(x->left), height(x->right)) + 1;
  y->height = std::max(height(y->left), height(y->right)) + 1;

  return y;
}

template <class Key>
typename BinaryTree<Key>::node *BinaryTree<Key>::balance(node *n) {
  if (!n) return n;

  int balance = getBalance(n);

  if (balance > 1) {
    if (getBalance(n->left) < 0) {
      n->left = rotationLeft(n->left);
    }
    return rotationRight(n);
  }

  if (balance < -1) {
    if (getBalance(n->right) > 0) {
      n->right = rotationRight(n->right);
    }
    return rotationLeft(n);
  }

  return n;
}

template <class Key>
std::pair<typename BinaryTree<Key>::node *, typename BinaryTree<Key>::node *>
BinaryTree<Key>::insertNode(node *node2, const Key &value) {
  if (!node2) {
    node *newNode = new node(value);
    return std::make_pair(newNode, newNode);
  }

  std::pair<node *, node *> result;
  result.first = nullptr;
  result.second = nullptr;

  if (value < node2->value) {
    result = insertNode(node2->left, value);
    node2->left = result.first;
    if (result.second) {
      node2->left->parent = node2;
    }
  } else if (value > node2->value) {
    result = insertNode(node2->right, value);
    node2->right = result.first;
    if (result.second) {
      node2->right->parent = node2;
    }
  } else {
    return std::make_pair(node2, nullptr);
  }

  node2->height = std::max(height(node2->left), height(node2->right)) + 1;
  node *node = balance(node2);
  if (node2 == root_) root_ = node;
  return std::make_pair(node, result.second);
}

template <class Key>
typename BinaryTree<Key>::node *BinaryTree<Key>::minNode(node *n) {
  while (n->left != nullptr) {
    n = n->left;
  }
  return n;
}

template <class Key>
typename BinaryTree<Key>::node *BinaryTree<Key>::recursiveErase(
    node *root_, const Key &key) {
  if (root_ == nullptr) {
    return nullptr;
  }

  if (key < root_->value) {
    root_->left = recursiveErase(root_->left, key);
  } else if (key > root_->value) {
    root_->right = recursiveErase(root_->right, key);
  } else {
    if (root_->left == nullptr) {
      node *temp = root_->right;
      delete root_;
      return temp;
    } else if (root_->right == nullptr) {
      node *temp = root_->left;
      delete root_;
      return temp;
    }

    node *temp = minNode(root_->right);
    root_->value = temp->value;
    root_->right = recursiveErase(root_->right, temp->value);
  }

  root_->height = std::max(height(root_->left), height(root_->right)) + 1;
  return balance(root_);
}

template <class Key>
bool BinaryTree<Key>::for_operators(const node *a, const node *b) const {
  if (!a && !b) return true;
  if (a && b) {
    return (a->value == b->value) && for_operators(a->left, b->left) &&
           for_operators(a->right, b->right);
  }
  return false;
}

template <class Key>
class BinaryTree<Key>::tree_iterator {
 public:
  using value_type = Key;
  using reference = value_type &;
  using pointer = value_type *;
  using iterator = tree_iterator;
  using const_iterator = const tree_iterator;

  tree_iterator(node *ptr = nullptr) : current(ptr) {}

  reference operator*() const { return current->value; }
  pointer operator->() const { return &(current->value); }

  tree_iterator &operator++() {
    if (current->right) {
      current = current->right;
      while (current->left) {
        current = current->left;
      }
    } else {
      node *parent = current->parent;
      while (parent && current == parent->right) {
        current = parent;
        parent = parent->parent;
      }
      current = parent;
    }
    return *this;
  }

  tree_iterator operator++(int) {
    tree_iterator tmp = *this;
    ++(*this);
    return tmp;
  }

  tree_iterator &operator--() {
    if (current->left) {
      current = current->left;
      while (current->right) {
        current = current->right;
      }
    } else {
      node *parent = current->parent;
      while (parent && current == parent->left) {
        current = parent;
        parent = parent->parent;
      }
      current = parent;
    }
    return *this;
  }

  tree_iterator operator--(int) {
    tree_iterator tmp = *this;
    --(*this);
    return tmp;
  }

  bool operator==(const tree_iterator &other) const {
    return current == other.current;
  }

  bool operator!=(const tree_iterator &other) const {
    return current != other.current;
  }

 private:
  node *current;
};

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_1_TREE_H
