#ifndef CPP2_S21_CONTAINERS_1_SRC_LIST_S21_LIST_H_
#define CPP2_S21_CONTAINERS_1_SRC_LIST_S21_LIST_H_

#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class list {
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;

 private:
  struct Node;
  struct Iterator;
  struct ConstIterator;

 public:
  using iterator = typename list<T>::Iterator;
  using const_iterator = typename list<T>::ConstIterator;

  // constructors
  list();
  list(size_type n);
  list(std::initializer_list<value_type> const& items);
  list(const list& other);
  list(list&& other) noexcept;
  ~list();

  list& operator=(const list& other);
  list& operator=(list&& other) noexcept;

  // method
  reference front();
  reference back();

  const_reference front() const;
  const_reference back() const;

  iterator begin() { return iterator(head_); }
  iterator end() { return iterator(nullptr); }

  const_iterator begin() const { return const_iterator(head_); }
  const_iterator end() const { return const_iterator(nullptr); }

  const_iterator cbegin() const { return const_iterator(head_); }
  const_iterator cend() const { return const_iterator(nullptr); }

  bool empty() const;
  size_type size() const;
  size_type max_size();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  iterator erase_it(iterator pos);
  void push_back(const_reference data);
  void pop_back();
  void push_front(const_reference data);
  void pop_front();
  void swap(list& other);
  void merge(list& other);
  template <typename InputIterator>
  void splice(InputIterator pos, list& other) noexcept;
  void reverse();
  void unique();
  void sort();

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);
  template <typename... Args>
  void insert_many_back(Args&&... args);
  template <typename... Args>
  void insert_many_front(Args&&... args);

 private:
  typedef struct Node {
    value_type value_;
    Node* pnext_;
    Node* pprev_;

    Node(const T& value) : value_(value), pnext_(nullptr), pprev_(nullptr){};
  } Node;

  // Класс итератора
  struct Iterator {
   public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    Iterator(Node* node, list* list = nullptr) : node_(node), list_(list) {}

    reference operator*() const { return node_->value_; }
    pointer operator->() const { return &node_->value_; }
    Node* GetNext() const { return node_->pnext_; }
    Node* GetPrev() const { return node_->pprev_; }
    Node* GetNode() const { return node_; }

    Iterator& operator++() {
      if (node_ == nullptr && list_) {
        node_ = list_->head_;
      } else {
        node_ = node_ ? node_->pnext_ : nullptr;
      }
      return *this;
    }

    Iterator operator++(int) {
      Iterator temp(*this);
      ++(*this);
      return temp;
    }

    bool operator==(const Iterator& other) const {
      return node_ == other.node_;
    }

    bool operator!=(const Iterator& other) const { return !(*this == other); }

    Iterator& operator--() {
      if (node_ == nullptr && list_) {
        node_ = list_->tail_;
      } else {
        node_ = node_ ? node_->pprev_ : nullptr;
      }
      return *this;
    }

    Iterator operator--(int) {
      Iterator temp(*this);
      --(*this);
      return temp;
    }

   private:
    Node* node_;
    list* list_;
  };

  struct ConstIterator {
   public:
    using value_type = T;
    using pointer = const T*;
    using reference = const T&;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;

    Node* GetNode() const { return node_; }
    ConstIterator(Node* node = nullptr) : node_(node) {}
    ConstIterator(ConstIterator& other) : node_(other.node_) {}
    reference operator*() const { return node_->value_; }
    pointer operator->() const { return &node_->value_; }
    operator iterator() const { return iterator(node_); }

    ConstIterator& operator++() {
      node_ = node_ ? node_->pnext_ : nullptr;
      return *this;
    }

    ConstIterator operator++(int) {
      ConstIterator temp(*this);
      ++(*this);
      return temp;
    }
    ConstIterator operator--(int) {
      ConstIterator temp(*this);
      --(*this);
      return temp;
    }
    ConstIterator& operator--() {
      if (node_ != nullptr) {
        node_ = node_->pprev_;
      } else if (list_) {
        node_ = list_->tail_;
      }
      return *this;
    }

    bool operator==(const ConstIterator& other) const {
      return node_ == other.node_;
    }

    bool operator!=(const ConstIterator& other) const {
      return !(*this == other);
    }

   private:
    Node* node_;
    list* list_;
  };

 private:
  template <typename InputIterator>
  void assign(InputIterator first, InputIterator last);

  template <typename InputIterator>
  list(InputIterator first, InputIterator last);

  Node* head_;
  Node* tail_;
  size_t size_;
};

}  // namespace s21

#include "s21_list.tpp"

#endif  // CPP2_S21_CONTAINERS_1_SRC_LIST_S21_LIST_H_
