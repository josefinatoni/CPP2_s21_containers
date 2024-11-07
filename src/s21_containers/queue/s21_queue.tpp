#ifndef CPP2_CONTAINERS_SRC_S21_CONTAINERS_QUEUE_S21_QUEUE_TPP_
#define CPP2_CONTAINERS_SRC_S21_CONTAINERS_QUEUE_S21_QUEUE_TPP_

#include <list>  // Временно пока не готова реализация s21::list

#include "s21_queue.h"

namespace s21 {
// Основные публичные методы
template <typename T, typename Container>
queue<T, Container>::queue() : Queue() {}

template <typename T, typename Container>
queue<T, Container>::queue(std::initializer_list<value_type> const &items)
    : Queue(items) {}

template <typename T, typename Container>
queue<T, Container>::queue(const queue &q) : Queue(q.Queue) {}

template <typename T, typename Container>
queue<T, Container>::queue(queue &&q) : Queue(std::move(q.Queue)) {}

template <typename T, typename Container>
queue<T, Container>::~queue() = default;

template <typename T, typename Container>
queue<T, Container> &queue<T, Container>::operator=(const queue &q) {
  if (this != &q) {
    Queue = q.Queue;
  }
  return *this;
}

template <typename T, typename Container>
queue<T, Container> &queue<T, Container>::operator=(queue &&q) {
  if (this != &q) {
    Queue = std::move(q.Queue);
  }
  return *this;
}
// Публичные методы для доступа к элементам класса
template <typename T, typename Container>
typename queue<T, Container>::reference queue<T, Container>::front() {
  return Queue.front();
}

template <typename T, typename Container>
typename queue<T, Container>::const_reference queue<T, Container>::front()
    const {
  return Queue.front();
}

template <typename T, typename Container>
typename queue<T, Container>::reference queue<T, Container>::back() {
  return Queue.back();
}

template <typename T, typename Container>
typename queue<T, Container>::const_reference queue<T, Container>::back()
    const {
  return Queue.back();
}
// Публичные методы для доступа к информации о наполнении контейнера
template <typename T, typename Container>
bool queue<T, Container>::empty() const {
  return Queue.empty();
}

template <typename T, typename Container>
typename queue<T, Container>::size_type queue<T, Container>::size() const {
  return Queue.size();
}
//  Методы для изменения контейнера
template <typename T, typename Container>
void queue<T, Container>::push(const T &value) {
  Queue.push_back(value);
}

template <typename T, typename Container>
void queue<T, Container>::pop() {
  Queue.pop_front();
}

template <typename T, typename Container>
void queue<T, Container>::swap(queue &other) {
  Queue.swap(other.Queue);
}

template <typename T, typename Container>
template <typename... Args>
void queue<T, Container>::insert_many_back(Args &&...args) {
  (Queue.push_back(std::forward<Args>(args)), ...);
}
}  // namespace s21

#endif  //  CPP2_CONTAINERS_SRC_S21_CONTAINERS_QUEUE_S21_QUEUE_TPP_
