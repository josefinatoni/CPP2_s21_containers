#ifndef CPP2_CONTAINERS_SRC_S21_CONTAINERS_S21_ARRAY_H_
#define CPP2_CONTAINERS_SRC_S21_CONTAINERS_S21_ARRAY_H_

#include <cstddef>
#include <iostream>

namespace s21 {
template <typename T, size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array();
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a);
  ~array();
  array &operator=(array &&a);

  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  iterator data() noexcept;
  iterator data() const noexcept;

  iterator begin() noexcept;
  const_iterator begin() const noexcept;
  iterator end() noexcept;
  const_iterator end() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept;
  size_type max_size() const noexcept;

  void swap(array &other) noexcept;
  void fill(const_reference value);

 private:
  value_type data_[N];
  size_type size_ = N;
};
};  // namespace s21

#include "s21_array.tpp"

#endif  // CPP2_CONTAINERS_SRC_S21_CONTAINERS_S21_ARRAY_H_