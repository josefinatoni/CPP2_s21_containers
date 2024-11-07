#include "s21_vector.h"

namespace s21 {
template <typename T>
vector<T>::vector() : arr_(nullptr), current_size_(0), capacity_(0) {}

template <typename T>
vector<T>::vector(size_type n) : current_size_(n), capacity_(n) {
  arr_ = allocator_.allocate(n);
  allocator_ = std::allocator<T>();
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const& items)
    : vector(items.size()) {
  for (size_type i = 0; i < current_size_; ++i) {
    new (&arr_[i]) T(items.begin()[i]);
  }
}

template <typename T>
vector<T>::vector(const vector& v) : vector(v.current_size_) {
  for (size_type i = 0; i < current_size_; ++i) {
    new (&arr_[i]) T(v.arr_[i]);
  }
}

template <typename T>
vector<T>::vector(vector&& v) noexcept
    : arr_(v.arr_), current_size_(v.current_size_), capacity_(v.capacity_) {
  v.arr_ = nullptr;
  v.current_size_ = 0;
  v.capacity_ = 0;
}

template <typename T>
vector<T>::~vector() {
  for (size_t i = 0; i < current_size_; ++i) {
    std::allocator_traits<std::allocator<T>>::destroy(
        allocator_, arr_ + i);  // Разрушаем каждый объект
  }
  allocator_.deallocate(arr_, capacity_);
}

template <typename T>
vector<T>& vector<T>::operator=(vector&& v) noexcept {
  if (this != &v) {
    swap(v);
  }
  return *this;
}

template <typename T>
vector<T>& vector<T>::operator=(const vector<T>& v) {
  if (this != &v) {
    delete[] arr_;
    current_size_ = v.current_size_;
    capacity_ = v.capacity_;
    arr_ = new value_type[capacity_];
    std::copy(v.arr_, v.arr_ + v.current_size_, arr_);
  }
  return *this;
}

// // Методы...
template <typename T>
typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= current_size_ || !current_size_) {
    throw std::out_of_range("Index out of range");
  }
  return arr_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::at(size_type pos) const {
  if (pos >= current_size_) {
    throw std::out_of_range("Index out of range");
  }
  return arr_[pos];
}

template <typename T>
typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return arr_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::operator[](size_type pos) const {
  return arr_[pos];
}

template <typename T>
typename vector<T>::const_reference vector<T>::front() {
  if (!current_size_) {
    throw std::out_of_range("Vector is empty");
  }
  return *arr_;
}

template <typename T>
typename vector<T>::const_reference vector<T>::back() {
  if (!current_size_) {
    throw std::out_of_range("Vector is empty");
  }
  return arr_[current_size_ - 1];
}

template <typename T>
T* vector<T>::data() noexcept {
  return arr_;
}

template <typename T>
typename vector<T>::iterator vector<T>::begin() noexcept {
  return arr_;
}

template <typename T>
typename vector<T>::iterator vector<T>::end() noexcept {
  return arr_ + current_size_;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::begin() const noexcept {
  return arr_;
}

template <typename T>
typename vector<T>::const_iterator vector<T>::end() const noexcept {
  return arr_ + current_size_;
}

template <typename T>
bool vector<T>::empty() const noexcept {
  return !current_size_;
}

template <typename T>
typename vector<T>::size_type vector<T>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max();
}

template <typename T>
void vector<T>::reserve(size_type size) {
  if (size > max_size()) {
    throw std::length_error("Can't allocate memory of this size");
  }
  if (size >= current_size_) {
    vector<T> tmp(size);
    for (size_type i = 0; i < current_size_; ++i) {
      new (&tmp.arr_[i]) T(arr_[i]);
    }
    tmp.current_size_ = current_size_;
    *this = std::move(tmp);
  } else {
    capacity_ = size;
  }
}

template <typename T>
typename vector<T>::size_type vector<T>::capacity() const noexcept {
  return capacity_;
}

template <typename T>
void vector<T>::clear() {
  for (size_type i = 0; i < current_size_; ++i) {
    arr_[i].~T();
  }
  delete[] arr_;
  arr_ = nullptr;
  current_size_ = 0;
}

template <typename T>
void vector<T>::shrink_to_fit() {
  if (current_size_ < capacity_) {
    iterator new_data = new value_type[current_size_];
    std::copy(arr_, arr_ + current_size_, new_data);
    delete[] arr_;
    arr_ = new_data;
    capacity_ = current_size_;
  }
}

template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
                                               const_reference value) {
  if (pos < begin() || pos > end()) {
    throw std::out_of_range("Iterator is out of range");
  }
  size_type index = pos - begin();
  if (size() == capacity()) {
    reserve(size() * 2);
  }
  iterator new_pos = begin() + index;
  for (size_t i = 0; i > index; --i) {
    arr_[i] = arr_[i - 1];
  }
  for (iterator it = end(); it != new_pos; --it) {
    *it = *(it - 1);
  }
  *new_pos = value;
  ++current_size_;

  return new_pos;
}

template <typename T>
void vector<T>::erase(iterator pos) {
  vector<T> tmp(current_size_ - 1);
  size_type j = 0, position = pos - arr_;
  for (size_type i = 0; i < current_size_; ++i) {
    if (i != position) {
      new (&tmp.arr_[j++]) T(arr_[i]);
    }
  }
  *this = std::move(tmp);
}

template <typename T>
void vector<T>::push_back(const_reference value) {
  if (current_size_ >= capacity_) {
    reserve(capacity_ == 0 ? 1 : capacity_ * 2);
  }
  std::allocator_traits<std::allocator<T>>::construct(
      allocator_, arr_ + current_size_, value);
  ++current_size_;
}

template <typename T>
void vector<T>::pop_back() {
  current_size_ -= 1;
}

template <typename T>
void vector<T>::swap(vector& other) noexcept {
  T* tmp_arr = arr_;
  size_type tmp_current_size = current_size_;
  size_type tmp_capacity = capacity_;
  arr_ = other.arr_;
  current_size_ = other.current_size_;
  capacity_ = other.capacity_;
  other.arr_ = tmp_arr;
  other.current_size_ = tmp_current_size;
  other.capacity_ = tmp_capacity;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args&&... args) {
  (push_back(std::forward<Args>(args)), ...);
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(const_iterator pos,
                                                    Args&&... args) {
  iterator ret = nullptr;
  auto id = pos - begin();
  reserve(current_size_ + sizeof...(args));

  for (auto&& item : {std::forward<Args>(args)...}) {
    ret = insert(begin() + id, item);
    ++id;
  }

  return ret;
}

template <typename T>
void vector<T>::resize() {
  size_t new_capacity = capacity_ * 2;
  T* new_arr = allocator_.allocate(new_capacity);
  for (size_t i = 0; i < current_size_; ++i) {
    std::allocator_traits<std::allocator<T>>::construct(
        allocator_, new_arr + i, arr_[i]);  // Construct new elements
  }
  allocator_.deallocate(arr_, capacity_);
  arr_ = new_arr;
  capacity_ = new_capacity;
}

}  // namespace s21
