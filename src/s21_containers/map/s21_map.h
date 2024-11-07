#ifndef CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_MAP_S21_MAP_H_
#define CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_MAP_S21_MAP_H_

#include <initializer_list>
#include <list>
#include <stdexcept>
#include <utility>
#include <vector>

#include "../RBTree/RBTree.h"
#include "../vector/s21_vector.h"

namespace s21 {

template <typename Key, typename T>
class map {
 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename RBTree<Key, T, true>::iterator;
  using const_iterator = typename RBTree<Key, T, true>::const_iterator;
  using size_type = size_t;

  map(){};
  map(std::initializer_list<value_type> const& items);
  map(const map& m);
  map(map&& m) noexcept;
  ~map() { clear(); };

  map& operator=(const map& m);
  map& operator=(map&& m) noexcept;

  // Map Element access
  T& at(const Key& key);
  T& operator[](const Key& key);

  // Map Iterators
  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;

  // Map Capacity
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Map Modifiers
  void clear() noexcept;
  std::pair<iterator, bool> insert(const value_type& value);
  std::pair<iterator, bool> insert(const Key& key, const T& obj);
  std::pair<iterator, bool> insert_or_assign(const Key& key, const T& obj);

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

  void erase(iterator pos);
  void swap(map& other) noexcept;
  void merge(map& other);

  bool contains(const Key& key) const noexcept;

  iterator find(const Key& key);
  const_iterator find(const Key& key) const;

 private:
  RBTree<Key, T, true> tree_;
};

}  // namespace s21

#include "s21_map.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_MAP_S21_MAP_H_