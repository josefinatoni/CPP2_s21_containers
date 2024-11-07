#include "s21_map.h"

namespace s21 {

template <typename Key, typename T>
map<Key, T>::map(const map& m) : tree_(m.tree_) {}

template <typename Key, typename T>
map<Key, T>::map(map&& m) noexcept {
  this->swap(m);
}

template <typename Key, typename T>
map<Key, T>::map(std::initializer_list<value_type> const& items) {
  for (auto const& item : items) {
    insert(item.first, item.second);
  }
}

template <typename Key, typename T>
map<Key, T>& map<Key, T>::operator=(const map& m) {
  if (this != &m) {
    tree_ = m.tree_;
  }
  return *this;
}

template <typename Key, typename T>
map<Key, T>& map<Key, T>::operator=(map&& m) noexcept {
  if (this != &m) {
    tree_ = std::move(m.tree_);
  }
  return *this;
}

template <typename Key, typename T>
T& map<Key, T>::at(const Key& key) {
  return tree_.at(key);
}

template <typename Key, typename T>
T& map<Key, T>::operator[](const Key& key) {
  return tree_.operator[](key);
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::begin() noexcept {
  return tree_.begin();
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::end() noexcept {
  return tree_.end();
}

template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::begin() const noexcept {
  return tree_.cbegin();
}

template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::end() const noexcept {
  return tree_.cend();
}

template <typename Key, typename T>
bool map<Key, T>::empty() const noexcept {
  return tree_.empty();
}

template <typename Key, typename T>
bool map<Key, T>::contains(const Key& key) const noexcept {
  return tree_.contains(key);
}

template <typename Key, typename T>
void map<Key, T>::erase(iterator pos) {
  if (pos != end()) {
    tree_.erase(pos);
  }
}

template <typename Key, typename T>
void map<Key, T>::clear() noexcept {
  tree_.clear();
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::size() const noexcept {
  return tree_.size();
}

template <typename Key, typename T>
typename map<Key, T>::size_type map<Key, T>::max_size() const noexcept {
  return tree_.max_size();
}

template <typename Key, typename T>
void map<Key, T>::swap(map& other) noexcept {
  tree_.swap(other.tree_);
}

template <typename Key, typename T>
void map<Key, T>::merge(map& other) {
  tree_.merge(other.tree_);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const value_type& value) {
  iterator it = tree_.NodeFind(value.first);
  if (it != tree_.end()) {
    return {it, false};
  } else {
    tree_.Insert(value.first, value.second);
    it = tree_.NodeFind(value.first);
    return {it, true};
  }
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert(
    const Key& key, const T& obj) {
  value_type value(key, obj);
  return insert(value);
}

template <typename Key, typename T>
std::pair<typename map<Key, T>::iterator, bool> map<Key, T>::insert_or_assign(
    const Key& key, const T& obj) {
  iterator it = tree_.NodeFind(key);
  if (it != tree_.end()) {
    (*it).second = obj;
    return {it, false};
  } else {
    tree_.Insert(key, obj);
    it = tree_.NodeFind(key);
    return {it, true};
  }
}

template <typename Key, typename T>
template <typename... Args>
s21::vector<std::pair<typename map<Key, T>::iterator, bool>>
map<Key, T>::insert_many(Args&&... args) {
  s21::vector<std::pair<iterator, bool>> result;
  (result.push_back(insert(std::forward<Args>(args))), ...);
  return result;
}

template <typename Key, typename T>
typename map<Key, T>::iterator map<Key, T>::find(const Key& key) {
  auto node = tree_.NodeFind(key);
  if (node != nullptr) {
    return iterator(node);
  }
  return end();
}

template <typename Key, typename T>
typename map<Key, T>::const_iterator map<Key, T>::find(const Key& key) const {
  auto node = tree_.NodeFind(key);
  if (node != nullptr) {
    return const_iterator(node);
  }
  return end();
}

}  // namespace s21
