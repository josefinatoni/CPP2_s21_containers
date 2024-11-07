#ifndef CPP2_CONTAINERS_SRC_S21_CONTAINERS_S21_STACK_TPP_
#define CPP2_CONTAINERS_SRC_S21_CONTAINERS_S21_STACK_TPP_

#include "s21_stack.h"

namespace s21 {
// Основные публичные методы
template <typename T, typename Container>
stack<T, Container>::stack() : Stack(){};

template <typename T, typename Container>
stack<T, Container>::stack(std::initializer_list<value_type> const &items)
    : Stack(items){};

template <typename T, typename Container>
stack<T, Container>::stack(const stack &a) : Stack(a.Stack){};

template <typename T, typename Container>
stack<T, Container>::stack(stack &&a) : Stack(std::move(a.Stack)){};

template <typename T, typename Container>
stack<T, Container>::~stack() = default;

// Операторы
template <typename T, typename Container>
stack<T, Container> &stack<T, Container>::operator=(const stack &a) {
  if (this != &a) {
    Stack = a.Stack;
  }
  return *this;
}

template <typename T, typename Container>
stack<T, Container> &stack<T, Container>::operator=(stack &&a) {
  if (this != &a) {
    Stack = std::move(a.Stack);
  }
  return *this;
}
//  Element access
template <typename T, typename Container>
typename stack<T, Container>::reference stack<T, Container>::top() {
  return Stack.back();
}

template <typename T, typename Container>
typename stack<T, Container>::const_reference stack<T, Container>::top() const {
  return Stack.back();
}
//  Capacity
template <typename T, typename Container>
bool stack<T, Container>::empty() const {
  return Stack.empty();
}

template <typename T, typename Container>
typename stack<T, Container>::size_type stack<T, Container>::size() const {
  return Stack.size();
}
//  Modifiers
template <typename T, typename Container>
void stack<T, Container>::push(const_reference value) {
  Stack.push_back(value);
}

template <typename T, typename Container>
void stack<T, Container>::pop() {
  if (!empty()) {
    Stack.pop_back();
  }
}

template <typename T, typename Container>
void stack<T, Container>::swap(stack &other) {
  Stack.swap(other.Stack);
}

template <typename T, typename Container>
template <typename... Args>
void stack<T, Container>::insert_many_back(Args &&...args) {
  (Stack.push_back(std::forward<Args>(args)), ...);
}

};  // namespace s21

#endif  // CPP2_CONTAINERS_SRC_S21_CONTAINERS_S21_STACK_TPP_