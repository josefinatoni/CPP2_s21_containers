#ifndef CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_STACK_S21_STACK_H_
#define CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_STACK_S21_STACK_H_

#include "../../s21_containers.h"

namespace s21 {
template <typename T, typename Container = s21::list<T>>
class stack {
 public:
  // Memeber type
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;
  // Member functions
  stack();
  stack(std::initializer_list<value_type> const &items);
  stack(const stack &a);
  stack(stack &&a);
  ~stack();
  // Операторы
  stack &operator=(const stack &a);
  stack &operator=(stack &&a);
  // Element access
  reference top();
  const_reference top() const;
  // Capacity
  bool empty() const;
  size_type size() const;
  // Modifiers
  void push(const_reference value);
  void pop();
  void swap(stack &other);

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  Container Stack;
};  // class stack
};  // namespace s21

#include "s21_stack.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_STACK_S21_STACK_H_