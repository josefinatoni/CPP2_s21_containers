#ifndef CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_SET_SET_TPP_
#define CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_SET_SET_TPP_

#include "s21_set.h"

namespace s21 {

template <typename Key>
set<Key>::set() = default;

template <typename Key>
set<Key>::set(std::initializer_list<value_type> const& items) {
  for (const auto& item : items) {
    insert(item);
  }
}

template <typename Key>
set<Key>::set(const set& other) : tree_(other.tree_) {}

template <typename Key>
set<Key>::set(set&& other) noexcept : tree_(std::move(other.tree_)) {}

template <typename Key>
set<Key>::~set() {
  clear();
}

template <typename Key>
set<Key>& set<Key>::operator=(const set& other) {
  if (this != &other) {
    tree_ = other.tree_;
  }
  return *this;
}

template <typename Key>
set<Key>& set<Key>::operator=(set&& other) noexcept {
  if (this != &other) {
    tree_ = std::move(other.tree_);
  }
  return *this;
}

template <typename Key>
typename set<Key>::iterator set<Key>::begin() noexcept {
  return tree_.begin();
}

template <typename Key>
typename set<Key>::iterator set<Key>::end() noexcept {
  return tree_.end();
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::begin() const noexcept {
  return tree_.cbegin();
}

template <typename Key>
typename set<Key>::const_iterator set<Key>::end() const noexcept {
  return tree_.cend();
}

template <typename Key>
bool set<Key>::empty() const noexcept {
  return tree_.empty();
}

template <typename Key>
typename set<Key>::size_type set<Key>::size() const noexcept {
  return tree_.size();
}

template <typename Key>
typename set<Key>::size_type set<Key>::max_size() const noexcept {
  return tree_.max_size();
}

template <typename Key>
void set<Key>::clear() noexcept {
  tree_.clear();
}

template <typename Key>
std::pair<typename set<Key>::iterator, bool> set<Key>::insert(
    const value_type& value) {
  auto it = tree_.find(value);
  bool inserted = (it == tree_.end());
  if (inserted) {
    tree_.Insert(value, value);
  }
  return std::make_pair(find(value), inserted);
}

template <typename Key>
void set<Key>::erase(iterator pos) {
  if (pos != end()) {  // Проверяем, что итератор не равен end()
    tree_.erase_it(pos);
  }
}

template <typename Key>
void set<Key>::swap(set& other) noexcept {
  tree_.swap(other.tree_);
}

template <typename Key>
void set<Key>::merge(set& other) {
  tree_.merge(other.tree_);
}

template <typename Key>
typename set<Key>::iterator set<Key>::find(const Key& key) {
  return tree_.find(key);
}

template <typename Key>
bool set<Key>::contains(const Key& key) const {
  auto it = tree_.cfind(key);
  return it != tree_.cend();  // Используем cend() для const итератора
}

template <typename Key>
template <typename... Args>
std::vector<std::pair<typename set<Key>::iterator, bool>> set<Key>::insert_many(
    Args&&... args) {
  std::vector<std::pair<iterator, bool>> result;
  (result.push_back(insert(std::forward<Args>(args))), ...);
  return result;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_SET_SET_TPP_
