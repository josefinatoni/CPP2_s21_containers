#ifndef CPP2_S21_CONTAINERS_SRC_S21_CONTAINERSPLUS_S21_MULTISET_H_
#define CPP2_S21_CONTAINERS_SRC_S21_CONTAINERSPLUS_S21_MULTISET_H_

#include "../RBTree/RBTree.h"

namespace s21 {

template <typename Key>
class multiset {
 public:
  // Определение типов
  using key_type = Key;
  using value_type = Key;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename RBTree<Key, Key, false>::iterator;
  using const_iterator = typename RBTree<Key, Key, false>::const_iterator;
  using size_type = std::size_t;

  // Конструкторы
  multiset();
  multiset(std::initializer_list<value_type> const& items);
  multiset(const multiset& other);
  multiset(multiset&& other) noexcept;
  ~multiset();

  // Операторы
  multiset& operator=(const multiset& other);
  multiset& operator=(multiset&& other) noexcept;

  // Итераторы
  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  // Вместимость
  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  // Модификаторы
  void clear() noexcept;
  iterator insert(const value_type& value);
  void erase(iterator pos);
  void swap(multiset& other) noexcept;
  void merge(multiset& other);

  // Операции поиска
  size_type count(const Key& key) const;
  iterator find(const Key& key);
  bool contains(const Key& key) const;
  std::pair<iterator, iterator> equal_range(const Key& key);
  std::pair<const_iterator, const_iterator> equal_range(const Key& key) const;
  iterator lower_bound(const Key& key);
  iterator upper_bound(const Key& key);
  const_iterator lower_bound(const Key& key) const;
  const_iterator upper_bound(const Key& key) const;

  template <typename... Args>
  std::vector<std::pair<iterator, bool>> insert_many(Args&&... args);

 private:
  RBTree<Key, Key, false> tree_;  // Внутренняя реализация через дерево
};

}  // namespace s21

#include "s21_multiset.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_S21_CONTAINERSPLUS_S21_MULTISET_H_
