#ifndef CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_QUEUE_S21_QUEUE_H_
#define CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_QUEUE_S21_QUEUE_H_

#include "../../s21_containers.h"

namespace s21 {
template <typename T,
          typename Container =
              s21::list<T>>  // Cоздаем шаблон и присваиваем ему имя T
class queue {
 public:
  // Внутриклассовые преопределение типов
  using value_type = T;  // тип элемента контейнера
  using reference = T &;  // тип определение ссылки на объект
  using const_reference = const T &;  // тип определение константной ссылки на
  using size_type = size_t;  // тип индекса контейнера
  // Основные публичные методы для взаимодействия с классом
  queue();
  queue(std::initializer_list<value_type> const &items);
  queue(const queue &q);  // copy constructor
  queue(queue &&q);       // move constructor
  ~queue();
  // Операторы
  queue &operator=(const queue &q);
  queue &operator=(queue &&q);
  // Публичные медоты для доступа к элементам класса
  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;
  // Публичные методы для доступа к информации о наполнении контейнера
  bool empty() const;
  size_type size() const;
  // Методы для изменения контейнера
  void push(const_reference value);
  void pop();
  void swap(queue &other);

  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  Container Queue;
};  // queue
};  // namespace s21

#include "s21_queue.tpp"

#endif  // CPP2_S21_CONTAINERS_SRC_S21_CONTAINERS_QUEUE_S21_QUEUE_H_