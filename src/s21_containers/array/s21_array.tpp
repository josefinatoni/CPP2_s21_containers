#ifndef CCP2_CONTAINERS_SRC_S21_CONTAINERS_ARRAY_S21_ARRAY_TPP_
#define CCP2_CONTAINERS_SRC_S21_CONTAINERS_ARRAY_S21_ARRAY_TPP_

#include "s21_array.h"

namespace s21 {
template <typename T, size_t N>
array<T, N>::array() : size_(N) {}

template <typename T, size_t N>
array<T, N>::array(std::initializer_list<value_type> const &items)
    : size_(items.size()) {
  size_type min_size = std::min(N, items.size());
  for (size_type i = 0; i < min_size; ++i) {
    data_[i] = *(items.begin() + i);
  }
}

template <typename T, size_t N>
array<T, N>::array(array const &a) {
  for (size_type i = 0; i < N; ++i) {
    data_[i] = a.data_[i];
  }
}

template <typename T, size_t N>
array<T, N>::array(array &&a) : size_(a.size_) {
  for (size_type i = 0; i < N; ++i) {
    data_[i] = std::move(a.data_[i]);
  }
  a.size_ = 0;
}

template <typename T, size_t N>
array<T, N>::~array() {}

template <typename T, size_t N>
array<T, N> &array<T, N>::operator=(array &&a) {
  if (this != &a) {
    for (size_type i = 0; i < N; ++i) {
      data_[i] = a.data_[i];
    }
  }
  return *this;
}

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("Index out of limit");
  }
  return data_[pos];
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::at(size_type pos) const {
  if (pos >= N) {
    throw std::out_of_range("Index out of limit");
  }
  return data_[pos];
}

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::operator[](size_type pos) {
  if (pos >= N) {
    throw std::out_of_range("Index out of limit");
  }
  return data_[pos];
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::operator[](
    size_type pos) const {
  if (pos >= N) {
    throw std::out_of_range("Index out of limit");
  }
  return data_[pos];
}

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::front() {
  return data_[0];
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::front() const {
  return data_[0];
}

template <typename T, size_t N>
typename array<T, N>::reference array<T, N>::back() {
  return data_[N - 1];
}

template <typename T, size_t N>
typename array<T, N>::const_reference array<T, N>::back() const {
  return data_[N - 1];
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::data() noexcept {
  return data_;
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::data() const noexcept {
  return data_;
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::begin() noexcept {
  return &data_[0];
}

template <typename T, size_t N>
typename array<T, N>::const_iterator array<T, N>::begin() const noexcept {
  return &data_[0];
}

template <typename T, size_t N>
typename array<T, N>::iterator array<T, N>::end() noexcept {
  return &data_[N];
}

template <typename T, size_t N>
typename array<T, N>::const_iterator array<T, N>::end() const noexcept {
  return &data_[N];
}

template <typename T, size_t N>
bool array<T, N>::empty() const noexcept {
  bool size = false;
  if (size_ == 0) {
    size = true;
  }
  return size;
}

template <typename T, size_t N>
typename array<T, N>::size_type array<T, N>::size() const noexcept {
  return size_;
}

template <typename T, size_t N>
typename array<T, N>::size_type array<T, N>::max_size() const noexcept {
  return N;
}

template <typename T, size_t N>
void array<T, N>::swap(array &other) noexcept {
  for (size_type i = 0; i < N; ++i) {
    std::swap(data_[i], other.data_[i]);
  }
}

template <typename T, size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_type i = 0; i < N; ++i) {
    data_[i] = value;
  }
  size_ = N;
}
};  // namespace s21

#endif  // CCP2_CONTAINERS_SRC_S21_CONTAINERS_ARRAY_S21_ARRAY_TPP_