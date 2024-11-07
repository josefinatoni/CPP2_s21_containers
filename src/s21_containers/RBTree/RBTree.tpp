#include "RBTree.h"

namespace s21 {

template <typename Key, typename T, bool IsMap>
RBTree<Key, T, IsMap>::Node::Node(const Key& key, const T& value)
    : parent_(nullptr), left_(nullptr), right_(nullptr), color_(Color::RED) {
  if constexpr (IsMap) {
    data_ = std::pair<Key, T>(key, value);
  } else {
    data_ = key;
  }
}

template <typename Key, typename T, bool IsMap>
RBTree<Key, T, IsMap>::RBTree(const RBTree& other) : root_(nullptr) {
  if (other.root_ != nullptr) {
    root_ = CopySubtree(other.root_, nullptr);
  } else {
    root_ = nullptr;
  }
}

template <typename Key, typename T, bool IsMap>
RBTree<Key, T, IsMap>::RBTree(std::initializer_list<value_type> const& items) {
  for (const auto& item : items) {
    if constexpr (IsMap) {
      Insert(item.first, item.second);
    } else {
      Insert(item);
    }
  }
}

template <typename Key, typename T, bool IsMap>
RBTree<Key, T, IsMap>::RBTree(RBTree&& other) noexcept : root_(other.root_) {
  other.root_ = nullptr;
}

template <typename Key, typename T, bool IsMap>
void RBTree<Key, T, IsMap>::DeleteNode(Node* node) {
  if (node != nullptr) {
    DeleteNode(node->left_);
    DeleteNode(node->right_);
    delete node;
  }
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::Node* RBTree<Key, T, IsMap>::CopySubtree(
    Node* node, Node* parent) {
  if (node == nullptr) {
    return nullptr;
  }
  Node* new_node = nullptr;
  if constexpr (IsMap) {
    new_node = new Node(node->data_.first, node->data_.second);
  } else {
    new_node = new Node(node->data_);
  }
  new_node->color_ = node->color_;
  new_node->parent_ = parent;
  new_node->left_ = CopySubtree(node->left_, new_node);
  new_node->right_ = CopySubtree(node->right_, new_node);
  return new_node;
}

template <typename Key, typename T, bool IsMap>
RBTree<Key, T, IsMap>& RBTree<Key, T, IsMap>::operator=(const RBTree& other) {
  if (this != &other) {
    DeleteNode(root_);
    root_ = nullptr;
    if (other.root_ != nullptr) {
      root_ = CopySubtree(other.root_, nullptr);
    }
  }
  return *this;
}

template <typename Key, typename T, bool IsMap>
RBTree<Key, T, IsMap>& RBTree<Key, T, IsMap>::operator=(
    RBTree&& other) noexcept {
  if (this != &other) {
    DeleteNode(root_);
    root_ = other.root_;
    other.root_ = nullptr;
  }
  return *this;
}

template <typename Key, typename T, bool IsMap>
void RBTree<Key, T, IsMap>::Insert(const Key& key, const T& value) {
  Node* new_node = new Node(key, value);
  if (root_ == nullptr) {
    root_ = new_node;
    root_->color_ = Color::BLACK;
  } else {
    Insert(new_node);
  }
}

template <typename Key, typename T, bool IsMap>
void RBTree<Key, T, IsMap>::Insert(const Key& key) {
  Node* new_node = new Node(key);
  if (root_ == nullptr) {
    root_ = new_node;
    root_->color_ = Color::BLACK;
  } else {
    Insert(new_node);
  }
}

template <typename Key, typename T, bool IsMap>
void RBTree<Key, T, IsMap>::Insert(Node* node) {
  Node* current = root_;
  Node* parent = nullptr;
  // Лямбда-функция -- Если IsMap, используем key_ из data_, если нет -
  // используем key_ напрямую
  auto getKey = [](const Node* n) -> const Key& {
    if constexpr (IsMap) {
      return n->data_.first;
    } else {
      return n->data_;
    }
  };
  while (current != nullptr) {
    parent = current;
    if (getKey(node) < getKey(current)) {
      current = current->left_;
    } else {
      current = current->right_;
    }
  }
  node->parent_ = parent;
  if (parent == nullptr) {
    root_ = node;
  } else if (getKey(node) < getKey(parent)) {
    parent->left_ = node;
  } else {
    parent->right_ = node;
  }
  node->left_ = nullptr;
  node->right_ = nullptr;
  node->color_ = Color::RED;
  InsertFixup(node);
}

// Вспомогательные методы для балансировки
template <typename Key, typename T, bool IsMap>
void RBTree<Key, T, IsMap>::RotateLeft(Node* node) {
  Node* pivot = node->right_;
  pivot->parent_ = node->parent_;
  if (node->parent_ == nullptr) {
    root_ = pivot;
  } else if (node == node->parent_->left_) {
    node->parent_->left_ = pivot;
  } else {
    node->parent_->right_ = pivot;
  }
  node->right_ = pivot->left_;
  if (pivot->left_ != nullptr) {
    pivot->left_->parent_ = node;
  }
  pivot->left_ = node;
  node->parent_ = pivot;
}

template <typename Key, typename T, bool IsMap>
void RBTree<Key, T, IsMap>::RotateRight(Node* node) {
  Node* pivot = node->left_;
  pivot->parent_ = node->parent_;
  if (node->parent_ == nullptr) {
    root_ = pivot;
  } else if (node == node->parent_->left_) {
    node->parent_->left_ = pivot;
  } else {
    node->parent_->right_ = pivot;
  }
  node->left_ = pivot->right_;
  if (pivot->right_ != nullptr) {
    pivot->right_->parent_ = node;
  }
  pivot->right_ = node;
  node->parent_ = pivot;
}

template <typename Key, typename T, bool IsMap>
void RBTree<Key, T, IsMap>::InsertFixup(Node* node) {
  while (node != root_ && node->parent_->color_ == Color::RED) {
    Node* parent = node->parent_;
    Node* grandparent = node->parent_->parent_;
    if (grandparent == nullptr) break;
    if (parent == grandparent->left_) {
      Node* uncle = grandparent->right_;
      if (uncle != nullptr && uncle->color_ == Color::RED) {
        parent->color_ = Color::BLACK;
        uncle->color_ = Color::BLACK;
        grandparent->color_ = Color::RED;
        node = grandparent;
      } else {
        if (node == parent->right_) {
          node = parent;
          RotateLeft(node);
        }
        parent->color_ = Color::BLACK;
        grandparent->color_ = Color::RED;
        RotateRight(grandparent);
      }
    } else {
      Node* uncle = grandparent->left_;
      if (uncle != nullptr && uncle->color_ == Color::RED) {
        parent->color_ = Color::BLACK;
        uncle->color_ = Color::BLACK;
        grandparent->color_ = Color::RED;
        node = grandparent;
      } else {
        if (node == parent->left_) {
          node = parent;
          RotateRight(node);
        }
        parent->color_ = Color::BLACK;
        grandparent->color_ = Color::RED;
        RotateLeft(grandparent);
      }
    }
  }
  root_->color_ = Color::BLACK;
}

template <typename Key, typename T, bool IsMap>
void RBTree<Key, T, IsMap>::ReplaceNodes(Node* to_node, Node* from_node) {
  if (to_node == root_) {
    root_ = from_node;
  } else if (to_node == to_node->parent_->left_) {
    to_node->parent_->left_ = from_node;
  } else {
    to_node->parent_->right_ = from_node;
  }
  if (from_node != nullptr) {
    from_node->parent_ = to_node->parent_;
  }
}

template <typename Key, typename T, bool IsMap>
int RBTree<Key, T, IsMap>::GetChildren(Node* node) const {
  int count = 0;
  if (NodeExists(node->left_)) count += 1;
  if (NodeExists(node->right_)) count += 1;
  return count;
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::iterator RBTree<Key, T, IsMap>::erase_it(
    iterator pos) {
  Node* node_to_remove = pos.GetCurrent();
  if (node_to_remove == nullptr) {
    return end();
  }
  iterator next = pos;
  ++next;
  erase(pos);
  return next;
}

template <typename Key, typename T, bool IsMap>
void RBTree<Key, T, IsMap>::erase(iterator pos) {
  Node* result = EraseNode(pos);
  delete result;
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::Node* RBTree<Key, T, IsMap>::EraseNode(
    iterator pos) {
  if (pos == end()) return nullptr;
  Node* del_node = pos.GetCurrent();
  Node* current_root = root_;
  if (del_node->left_ != nullptr && del_node->right_ != nullptr) {
    Node* replace = FindMin(del_node->right_);
    ReplaceNodes(del_node, replace);
  }
  if (del_node->color_ == Color::BLACK &&
      ((del_node->left_ == nullptr && del_node->right_ != nullptr) ||
       (del_node->left_ != nullptr && del_node->right_ == nullptr))) {
    Node* replace =
        (del_node->left_ != nullptr) ? del_node->left_ : del_node->right_;
    ReplaceNodes(del_node, replace);
  }
  if (del_node->color_ == Color::BLACK && del_node->left_ == nullptr &&
      del_node->right_ == nullptr) {
    RemoveFixup(del_node);
  }
  if (del_node == current_root) {
    if (del_node->left_ != nullptr || del_node->right_ != nullptr) {
      Node* replace = (del_node->right_ != nullptr) ? FindMin(del_node->right_)
                                                    : del_node->left_;
      if (replace == del_node->left_) {
        replace->right_ = del_node->right_;
      } else {
        replace->left_ = del_node->left_;
      }
      if (replace->left_ != nullptr) replace->left_->parent_ = replace;
      if (replace->right_ != nullptr) replace->right_->parent_ = replace;
      root_ = replace;
    } else {
      root_ = nullptr;
    }
    if (root_ != nullptr) root_->parent_ = nullptr;
  } else {
    if (del_node == del_node->parent_->left_) {
      del_node->parent_->left_ = nullptr;
    } else {
      del_node->parent_->right_ = nullptr;
    }
  }
  del_node->left_ = nullptr;
  del_node->right_ = nullptr;
  del_node->parent_ = nullptr;
  del_node->color_ = Color::RED;
  return del_node;
}

template <typename Key, typename T, bool IsMap>
void RBTree<Key, T, IsMap>::RemoveFixup(Node* node) {
  while (node != root_ && node->color_ == Color::BLACK) {
    Node* parent = node->parent_;
    Node* sibling = node == parent->left_ ? parent->right_ : parent->left_;
    if (sibling->color_ == Color::RED) {
      std::swap(sibling->color_, parent->color_);
      if (node == parent->left_) {
        RotateLeft(parent);
      } else {
        RotateRight(parent);
      }
      sibling = node == parent->left_ ? parent->right_ : parent->left_;
    }
    if (BothChildrenAreBlack(sibling)) {
      sibling->color_ = Color::RED;
      node = parent;
    } else {
      Node* child = node == parent->left_ ? sibling->right_ : sibling->left_;
      if (!NodeExists(child) || child->color_ == Color::BLACK) {
        Node* other_child =
            node == parent->left_ ? sibling->left_ : sibling->right_;
        other_child->color_ = Color::BLACK;
        sibling->color_ = Color::RED;
        if (node == parent->left_) {
          RotateRight(sibling);
        } else {
          RotateLeft(sibling);
        }
        sibling = node == parent->left_ ? parent->right_ : parent->left_;
        child = node == parent->left_ ? sibling->right_ : sibling->left_;
      }
      sibling->color_ = parent->color_;
      parent->color_ = Color::BLACK;
      child->color_ = Color::BLACK;
      if (node == parent->left_) {
        RotateLeft(parent);
      } else {
        RotateRight(parent);
      }
      node = root_;
    }
  }
  if (node != nullptr) node->color_ = Color::BLACK;
}

template <typename Key, typename T, bool IsMap>
bool RBTree<Key, T, IsMap>::BothChildrenAreBlack(Node* node) {
  return (!NodeExists(node->left_) || node->left_->color_ == Color::BLACK) &&
         (!NodeExists(node->right_) || node->right_->color_ == Color::BLACK);
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::Node* RBTree<Key, T, IsMap>::NodeFind(
    const Key& key) const {
  Node* current = root_;
  auto getKey = [](const auto& node) -> const Key& {
    if constexpr (IsMap) {
      return node->data_.first;
    } else {
      return node->data_;
    }
  };
  while (current != nullptr) {
    if (key < getKey(current)) {
      current = current->left_;
    } else if (key > getKey(current)) {
      current = current->right_;
    } else {
      return current;
    }
  }
  return nullptr;
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::iterator RBTree<Key, T, IsMap>::find(
    const Key& key) {
  Node* found_node = NodeFind(key);
  if (found_node == nullptr) {
    return end();
  } else {
    return iterator(found_node);
  }
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::const_iterator RBTree<Key, T, IsMap>::cfind(
    const Key& key) const {
  Node* found_node = NodeFind(key);
  if (found_node) {
    return const_iterator(found_node);
  } else {
    return cend();
  }
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::Node* RBTree<Key, T, IsMap>::FindNext(
    Node* node) const {
  if (node == nullptr) return nullptr;
  if (node->right_ != nullptr) {
    node = node->right_;
    while (node->left_ != nullptr) {
      node = node->left_;
    }
    return node;
  }
  Node* parent = node->parent_;
  while (parent != nullptr && node == parent->right_) {
    node = parent;
    parent = parent->parent_;
  }
  return parent;  // Может вернуть nullptr, если это был самый правый узел
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::Node* RBTree<Key, T, IsMap>::FindPrev(
    Node* node) const {
  if (node == nullptr) return nullptr;
  if (node->left_ != nullptr) {
    node = node->left_;
    while (node->right_ != nullptr) {
      node = node->right_;
    }
    return node;
  }
  Node* parent = node->parent_;
  while (parent != nullptr && node == parent->left_) {
    node = parent;
    parent = parent->parent_;
  }
  return parent;  // Может вернуть nullptr, если это был самый правый узел
}

template <typename Key, typename T, bool IsMap>
const typename RBTree<Key, T, IsMap>::Node* RBTree<Key, T, IsMap>::FindNext(
    const Node* node) const {
  if (node == nullptr) return nullptr;
  if (node->right_ != nullptr) {
    node = node->right_;
    while (node->left_ != nullptr) {
      node = node->left_;
    }
    return node;
  }
  const Node* parent = node->parent_;
  while (parent != nullptr && node == parent->right_) {
    node = parent;
    parent = parent->parent_;
  }
  return parent;  // Может вернуть nullptr, если это был самый правый узел
}

template <typename Key, typename T, bool IsMap>
const typename RBTree<Key, T, IsMap>::Node* RBTree<Key, T, IsMap>::FindPrev(
    const Node* node) const {
  if (node == nullptr) return nullptr;
  if (node->left_ != nullptr) {
    node = node->left_;
    while (node->right_ != nullptr) {
      node = node->right_;
    }
    return node;
  }
  const Node* parent = node->parent_;
  while (parent != nullptr && node == parent->left_) {
    node = parent;
    parent = parent->parent_;
  }
  return parent;  // Может вернуть nullptr, если это был самый правый узел
}

/*---------------------------- iterators ------------------------------------*/

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::Node* RBTree<Key, T, IsMap>::FindMin(
    Node* node) const {
  if (node == nullptr) return nullptr;
  while (node->left_ != nullptr) {
    node = node->left_;
  }
  return node;
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::Node* RBTree<Key, T, IsMap>::FindMax(
    Node* node) const {
  if (node == nullptr) return nullptr;
  while (node->right_ != nullptr) {
    node = node->right_;
  }
  return node;
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::iterator&
RBTree<Key, T, IsMap>::Iterator::operator++() noexcept {
  current_ = tree_->FindNext(current_);
  return *this;
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::iterator
RBTree<Key, T, IsMap>::Iterator::operator++(int) noexcept {
  Iterator tmp = *this;
  ++(*this);
  return tmp;
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::iterator&
RBTree<Key, T, IsMap>::Iterator::operator--() noexcept {
  current_ = tree_->FindPrev(current_);
  return *this;
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::iterator
RBTree<Key, T, IsMap>::Iterator::operator--(int) noexcept {
  Iterator tmp = *this;
  --(*this);
  return tmp;
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::Iterator::reference
RBTree<Key, T, IsMap>::Iterator::operator*() const noexcept {
  return current_->data_;
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::Iterator::pointer
RBTree<Key, T, IsMap>::Iterator::operator->() const noexcept {
  return &(current_->data_);
}

template <typename Key, typename T, bool IsMap>
bool RBTree<Key, T, IsMap>::Iterator::operator==(
    const iterator& other) const noexcept {
  return current_ == other.current_;
}

template <typename Key, typename T, bool IsMap>
bool RBTree<Key, T, IsMap>::Iterator::operator!=(
    const iterator& other) const noexcept {
  return current_ != other.current_;
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::iterator
RBTree<Key, T, IsMap>::begin() noexcept {
  return iterator(FindMin(root_));
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::iterator RBTree<Key, T, IsMap>::end() noexcept {
  return iterator(nullptr);
}

/*------------------------- const iterators ----------------------------------*/

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::const_iterator&
RBTree<Key, T, IsMap>::ConstIterator::operator++() noexcept {
  current_ = tree_->FindNext(current_);
  return *this;
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::const_iterator
RBTree<Key, T, IsMap>::ConstIterator::operator++(int) noexcept {
  ConstIterator tmp = *this;
  ++(*this);
  return tmp;
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::const_iterator&
RBTree<Key, T, IsMap>::ConstIterator::operator--() noexcept {
  current_ = tree_->FindPrev(current_);
  return *this;
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::const_iterator
RBTree<Key, T, IsMap>::ConstIterator::operator--(int) noexcept {
  ConstIterator tmp = *this;
  --(*this);
  return tmp;
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::ConstIterator::reference
RBTree<Key, T, IsMap>::ConstIterator::operator*() const noexcept {
  return current_->data_;
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::ConstIterator::pointer
RBTree<Key, T, IsMap>::ConstIterator::operator->() const noexcept {
  return &(current_->data_);
}

template <typename Key, typename T, bool IsMap>
bool RBTree<Key, T, IsMap>::ConstIterator::operator==(
    const const_iterator& other) const noexcept {
  return current_ == other.current_;
}

template <typename Key, typename T, bool IsMap>
bool RBTree<Key, T, IsMap>::ConstIterator::operator!=(
    const const_iterator& other) const noexcept {
  return current_ != other.current_;
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::const_iterator RBTree<Key, T, IsMap>::cbegin()
    const noexcept {
  return const_iterator(FindMin(root_));
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::const_iterator RBTree<Key, T, IsMap>::cend()
    const noexcept {
  return const_iterator(nullptr);
}

/*--------------------- container methods ---------------------------*/

template <typename Key, typename T, bool IsMap>
bool RBTree<Key, T, IsMap>::empty() const noexcept {
  return root_ == nullptr;
}

template <typename Key, typename T, bool IsMap>
bool RBTree<Key, T, IsMap>::contains(const Key& key) const {
  return NodeFind(key) != nullptr;
}

template <typename Key, typename T, bool IsMap>
void RBTree<Key, T, IsMap>::clear() noexcept {
  DeleteNode(root_);
  root_ = nullptr;
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::size_type RBTree<Key, T, IsMap>::size()
    const noexcept {
  return CountNodes(root_);
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::size_type RBTree<Key, T, IsMap>::CountNodes(
    Node* node) const {
  if (node == nullptr) {
    return 0;
  }
  return 1 + CountNodes(node->left_) + CountNodes(node->right_);
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::size_type RBTree<Key, T, IsMap>::max_size()
    const noexcept {
  // return std::numeric_limits<size_type>::max() / sizeof(Node);
  return std::allocator_traits<std::allocator<Node>>::max_size(
      std::allocator<Node>());
}

template <typename Key, typename T, bool IsMap>
void RBTree<Key, T, IsMap>::swap(RBTree& other) noexcept {
  std::swap(root_, other.root_);
}

template <typename Key, typename T, bool IsMap>
void RBTree<Key, T, IsMap>::merge(RBTree& other) {
  if (this != &other) {
    for (auto it = other.begin(); it != other.end();) {
      const auto& key = [&]() -> const Key& {
        if constexpr (IsMap) {
          return (*it).first;
        } else {
          return *it;
        }
      }();

      if (!this->contains(key)) {
        if constexpr (IsMap) {
          this->Insert((*it).first, (*it).second);
        } else {
          this->Insert(*it);
        }
        it = other.erase_it(it);
      } else {
        ++it;
      }
    }
  }
}

template <typename Key, typename T, bool IsMap>
T& RBTree<Key, T, IsMap>::at(const Key& key) {
  Node* node = NodeFind(key);
  if (node == nullptr) {
    throw std::out_of_range("Key not found");
  }
  return node->data_.second;
}

template <typename Key, typename T, bool IsMap>
T& RBTree<Key, T, IsMap>::operator[](const Key& key) {
  Node* node = NodeFind(key);
  if (node == nullptr) {
    Insert(key, T());
    node = NodeFind(key);
  }
  return node->data_.second;
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::iterator RBTree<Key, T, IsMap>::lower_bound(
    const Key& key) {
  Node* current = root_;
  Node* result = nullptr;

  while (current != nullptr) {
    if (key <= current->data_) {
      result = current;
      current = current->left_;
    } else {
      current = current->right_;
    }
  }
  if (result != nullptr) {
    return iterator(result);
  }
  return end();
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::iterator RBTree<Key, T, IsMap>::upper_bound(
    const Key& key) {
  Node* current = root_;
  Node* result = nullptr;

  while (current != nullptr) {
    if (key < current->data_) {
      result = current;
      current = current->left_;
    } else {
      current = current->right_;
    }
  }
  if (result != nullptr) {
    return iterator(result);
  }
  return end();
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::const_iterator
RBTree<Key, T, IsMap>::clower_bound(const Key& key) const {
  Node* current = root_;
  Node* result = nullptr;

  while (current != nullptr) {
    if (key <= current->data_) {
      result = current;
      current = current->left_;
    } else {
      current = current->right_;
    }
  }
  if (result != nullptr) {
    return const_iterator(result);
  }
  return cend();
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::const_iterator
RBTree<Key, T, IsMap>::cupper_bound(const Key& key) const {
  Node* current = root_;
  Node* result = nullptr;

  while (current != nullptr) {
    if (key < current->data_) {
      result = current;
      current = current->left_;
    } else {
      current = current->right_;
    }
  }
  if (result != nullptr) {
    return const_iterator(result);
  }
  return cend();
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::Node* RBTree<Key, T, IsMap>::GetMin() noexcept {
  Node* node = root_;
  while (node && node->left_ != nullptr) {
    node = node->left_;
  }
  return node;
}

template <typename Key, typename T, bool IsMap>
typename RBTree<Key, T, IsMap>::Node* RBTree<Key, T, IsMap>::GetMax() noexcept {
  Node* node = root_;
  while (node && node->right_ != nullptr) {
    node = node->right_;
  }
  return node;
}

/*-----------------------------------------------------------------------------*/

template <typename Key, typename T, bool IsMap>
void RBTree<Key, T, IsMap>::PrintTree() const {
  std::cout << "Tree contents:" << std::endl;
  PrintTree(root_, 0, "");
}

template <typename Key, typename T, bool IsMap>
void RBTree<Key, T, IsMap>::PrintTree(Node* node, int depth,
                                      std::string prefix) const {
  if (node == nullptr) return;

  // Печать текущего узла
  std::cout << prefix;
  std::cout << (node->color_ == Color::RED ? "R: " : "B: ");
  std::cout << node->data_ << std::endl;

  // Преобразование префикса для дочерних узлов
  std::string childPrefix = prefix;
  childPrefix += (node->parent_ == nullptr)
                     ? ""
                     : (node == node->parent_->left_ ? "├── " : "└── ");

  // Печать левого и правого узлов с соответствующими префиксами
  PrintTree(node->left_, depth + 1, childPrefix + "│   ");
  PrintTree(node->right_, depth + 1, childPrefix + "    ");
}

}  // namespace s21