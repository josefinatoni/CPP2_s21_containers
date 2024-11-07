#ifndef CPP2_S21_CONTAINERS_SRC_S21_CONTAINERSPLUS_S21_MULTISET_TPP_
#define CPP2_S21_CONTAINERS_SRC_S21_CONTAINERSPLUS_S21_MULTISET_TPP_

#include "s21_multiset.h"

namespace s21 {

// Конструкторы
template <typename Key>
multiset<Key>::multiset() : tree_() {}

template <typename Key>
multiset<Key>::multiset(std::initializer_list<value_type> const& items)
    : tree_() {
  for (const auto& item : items) {
    insert(item);
  }
}

template <typename Key>
multiset<Key>::multiset(const multiset& other) : tree_(other.tree_) {}

template <typename Key>
multiset<Key>::multiset(multiset&& other) noexcept
    : tree_(std::move(other.tree_)) {}

template <typename Key>
multiset<Key>::~multiset() {}

// Операторы присваивания
template <typename Key>
multiset<Key>& multiset<Key>::operator=(const multiset& other) {
  if (this != &other) {
    tree_ = other.tree_;
  }
  return *this;
}

template <typename Key>
multiset<Key>& multiset<Key>::operator=(multiset&& other) noexcept {
  if (this != &other) {
    tree_ = std::move(other.tree_);
  }
  return *this;
}

// Итераторы
template <typename Key>
typename multiset<Key>::iterator multiset<Key>::begin() {
  return tree_.begin();
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::end() {
  return tree_.end();
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::cbegin() const {
  return tree_.cbegin();
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::cend() const {
  return tree_.cend();
}

// Вместимость
template <typename Key>
bool multiset<Key>::empty() const noexcept {
  return tree_.empty();
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::size() const noexcept {
  return tree_.size();
}

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::max_size() const noexcept {
  return tree_.max_size();
}

// Модификаторы
template <typename Key>
void multiset<Key>::clear() noexcept {
  tree_.clear();
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::insert(
    const value_type& value) {
  tree_.Insert(value);

  // Находим узел с данным значением и возвращаем его итератор
  return find(value);
}

template <typename Key>
void multiset<Key>::erase(iterator pos) {
  tree_.erase(pos);
}

template <typename Key>
void multiset<Key>::swap(multiset& other) noexcept {
  tree_.swap(other.tree_);
}

template <typename Key>
void multiset<Key>::merge(multiset& other) {
  tree_.merge(other.tree_);
}

// Операции поиска

template <typename Key>
typename multiset<Key>::size_type multiset<Key>::count(const Key& key) const {
  auto range = equal_range(key);
  size_type count = 0;
  for (auto it = range.first; it != range.second; ++it) {
    ++count;
  }
  return count;
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::find(const Key& key) {
  return tree_.find(key);
}

template <typename Key>
bool multiset<Key>::contains(const Key& key) const {
  return tree_.contains(key);
}

template <typename Key>
std::pair<typename multiset<Key>::iterator, typename multiset<Key>::iterator>
multiset<Key>::equal_range(const Key& key) {
  return {lower_bound(key), upper_bound(key)};
}

template <typename Key>
std::pair<typename multiset<Key>::const_iterator,
          typename multiset<Key>::const_iterator>
multiset<Key>::equal_range(const Key& key) const {
  return {tree_.clower_bound(key), tree_.cupper_bound(key)};
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::lower_bound(const Key& key) {
  return tree_.lower_bound(key);
}

template <typename Key>
typename multiset<Key>::iterator multiset<Key>::upper_bound(const Key& key) {
  return tree_.upper_bound(key);
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::lower_bound(
    const Key& key) const {
  return tree_.clower_bound(key);
}

template <typename Key>
typename multiset<Key>::const_iterator multiset<Key>::upper_bound(
    const Key& key) const {
  return tree_.cupper_bound(key);
}

template <typename Key>
template <typename... Args>
std::vector<std::pair<typename multiset<Key>::iterator, bool>>
multiset<Key>::insert_many(Args&&... args) {
  std::vector<std::pair<iterator, bool>> result;
  (result.push_back(std::make_pair(insert(std::forward<Args>(args)), true)),
   ...);
  return result;
}

}  // namespace s21

#endif  // CPP2_S21_CONTAINERS_SRC_S21_CONTAINERSPLUS_S21_MULTISET_TPP_