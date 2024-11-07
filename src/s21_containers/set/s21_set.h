#ifndef CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_SET_S21_SET_H_
#define CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_SET_S21_SET_H_

#include "../RBTree/RBTree.h"

namespace s21 {

template <typename Key>
class set {
 private:
  RBTree<Key, Key, false> tree_;  // Используем RBTree с IsMap = false

 public:
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename RBTree<Key, Key, false>::iterator;
  using const_iterator = typename RBTree<Key, Key, false>::const_iterator;
  using size_type = typename RBTree<Key, Key, false>::size_type;

  // Default constructor
  set();

  // Initializer list constructor
  set(std::initializer_list<value_type> const& items);

  // Copy constructor
  set(const set& other);

  // Move constructor
  set(set&& other) noexcept;

  // Destructor
  ~set();

  // Copy assignment operator
  set& operator=(const set& other);

  // Move assignment operator
  set& operator=(set&& other) noexcept;

  // Iterators
  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;

  // Capacity
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Modifiers
  void clear() noexcept;
  std::pair<iterator, bool> insert(const value_type& value);
  void erase(iterator pos);
  void swap(set& other) noexcept;
  void merge(set& other);

  // Lookup
  iterator find(const Key& key);
  bool contains(const Key& key) const;

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);
};

}  // namespace s21

#include "s21_set.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_SET_S21_SET_H_
