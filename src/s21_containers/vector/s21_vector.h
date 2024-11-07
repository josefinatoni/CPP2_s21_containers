#ifndef CPP2_S21_CONTAINERS_1_SRC_VECTOR_S21_VECTOR_H_
#define CPP2_S21_CONTAINERS_1_SRC_VECTOR_S21_VECTOR_H_

#include <algorithm>
#include <cstddef>
#include <cstring>
#include <iostream>
#include <limits>

namespace s21 {

template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using iterator = T*;
  using const_iterator = const T*;
  using size_type = std::size_t;

  vector();             // Конструктор по умолчанию
  vector(size_type n);  // Конструктор с размером
  vector(std::initializer_list<value_type> const&
             items);  // Конструктор из инициализатора
  vector(const vector& v);      // Конструктор копии
  vector(vector&& v) noexcept;  // Мобильный конструктор
  ~vector();                    // Деструктор
  vector& operator=(const vector& v);
  vector& operator=(vector&& v) noexcept;  // Оператор присваивания

  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference at(size_type pos) const;
  const_reference operator[](size_type pos) const;
  const_reference front();
  const_reference back();
  T* data() noexcept;

  iterator begin() noexcept;
  iterator end() noexcept;
  const_iterator begin() const noexcept;
  const_iterator end() const noexcept;

  bool empty() const noexcept;
  size_type size() const noexcept { return current_size_; }
  size_type max_size() const noexcept;
  void reserve(size_type size);
  size_type capacity() const noexcept;
  void shrink_to_fit();

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector& other) noexcept;

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args);

  template <typename... Args>
  void insert_many_back(Args&&... args);

  template <typename... Args>
  void emplace_back(Args&&... args);

 private:
  T* arr_;
  size_type current_size_;
  size_type capacity_;
  std::allocator<T> allocator_;

  template <typename... Args>
  iterator emplace(const_iterator pos, Args&&... args);

  void resize();
};

}  // namespace s21

#include "s21_vector.tpp"

#endif  // CPP2_S21_CONTAINERS_1_SRC_VECTOR_S21_VECTOR_H_