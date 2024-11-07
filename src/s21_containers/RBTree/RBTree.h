#ifndef CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_RBTREE_RBTREE_H_
#define CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_RBTREE_RBTREE_H_

#include <initializer_list>
#include <iostream>
#include <limits>
#include <memory>
#include <variant>
#include <vector>

namespace s21 {

template <typename Key, typename T, bool IsMap>
class RBTree {
 private:
  enum class Color { RED, BLACK };
  struct Node;
  struct Iterator;
  struct ConstIterator;

 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::conditional_t<IsMap, std::pair<Key, T>, Key>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using size_type = std::size_t;

  using iterator = typename RBTree<Key, T, IsMap>::Iterator;
  using const_iterator = typename RBTree<Key, T, IsMap>::ConstIterator;

  RBTree() : root_(nullptr){};
  ~RBTree() { DeleteNode(root_); };
  RBTree(const RBTree& other);
  RBTree(std::initializer_list<value_type> const& items);
  RBTree(RBTree&& other) noexcept;

  RBTree& operator=(const RBTree& other);
  RBTree& operator=(RBTree&& other) noexcept;

  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  void Insert(const Key& key, const T& value);
  void Insert(const Key& key);
  typename RBTree<Key, T, IsMap>::Node* NodeFind(const Key& key) const;
  iterator find(const Key& key);
  const_iterator cfind(const Key& key) const;

  void erase(iterator pos);
  iterator erase_it(iterator pos);
  bool empty() const noexcept;
  bool contains(const Key& key) const;
  void clear() noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;
  void swap(RBTree& other) noexcept;
  void merge(RBTree& other);

  T& at(const Key& key);
  T& operator[](const Key& key);

  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);
  const_iterator clower_bound(const Key& key) const;
  const_iterator cupper_bound(const Key& key) const;

 private:
  struct Node {
    value_type data_;
    Node* parent_ = nullptr;  // Указатель на родителя
    Node* left_ = nullptr;  // Указатель на левый потомок
    Node* right_ = nullptr;  // Указатель на правый потомок
    Color color_ = Color::RED;

    Node(const Key& key, const T& value = T());
  };
  struct Iterator {
    friend class RBTree<Key, T, IsMap>;

   public:
    using value_type = RBTree::value_type;
    using reference = value_type&;
    using pointer = value_type*;
    using difference_type = std::ptrdiff_t;

    Iterator() = delete;
    Iterator(Node* node = nullptr) : current_(node){};

    iterator& operator++() noexcept;
    iterator operator++(int) noexcept;
    iterator& operator--() noexcept;
    iterator operator--(int) noexcept;
    reference operator*() const noexcept;
    pointer operator->() const noexcept;
    bool operator==(const iterator& other) const noexcept;
    bool operator!=(const iterator& other) const noexcept;

    Node* GetCurrent() const { return current_; }

   private:
    Node* current_;
    RBTree* tree_;
  };

  struct ConstIterator {
   public:
    using value_type = RBTree::value_type;
    using reference = const value_type&;
    using pointer = const value_type*;
    using difference_type = std::ptrdiff_t;

    ConstIterator() = delete;
    ConstIterator(const Node* node = nullptr) : current_(node){};

    const_iterator& operator++() noexcept;
    const_iterator operator++(int) noexcept;
    const_iterator& operator--() noexcept;
    const_iterator operator--(int) noexcept;
    reference operator*() const noexcept;
    pointer operator->() const noexcept;
    bool operator==(const const_iterator& other) const noexcept;
    bool operator!=(const const_iterator& other) const noexcept;

    const Node* GetCurrent() const { return current_; }

   private:
    const Node* current_;
    const RBTree* tree_;
  };

  Node* root_ = nullptr;

  Node* CopySubtree(Node* node, Node* parent);
  size_type CountNodes(Node* node) const;
  void DeleteNode(Node* node);
  void Insert(Node* new_node);
  Node* EraseNode(iterator pos);
  void RotateLeft(Node* node);
  void RotateRight(Node* node);
  void InsertFixup(Node* node);
  void RemoveFixup(Node* node);
  void ReplaceNodes(Node* to_node, Node* from_node);
  bool NodeExists(Node* node) const { return node != nullptr; };
  int GetChildren(Node* node) const;
  Node* FindNext(Node* node) const;
  Node* FindPrev(Node* node) const;
  const Node* FindNext(const Node* node) const;
  const Node* FindPrev(const Node* node) const;
  Node* FindMin(Node* node) const;
  Node* FindMax(Node* node) const;
  Node* GetMin() noexcept;
  Node* GetMax() noexcept;
  bool BothChildrenAreBlack(Node* node);

  void PrintTree() const;
  void PrintTree(Node* node, int depth, std::string prefix) const;
};

}  // namespace s21

#include "RBTree.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_RBTREE_RBTREE_H_