#include "s21_list.h"
namespace s21 {

template <typename T>
list<T>::list() : head_(nullptr), tail_(nullptr), size_(0) {}

template <typename T>
list<T>::list(std::initializer_list<value_type> const& items) : list() {
  for (auto i = items.begin(); i != items.end(); ++i) {
    push_back(*i);
  }
}

template <typename T>
list<T>::list(size_type n) : head_(nullptr), tail_(nullptr), size_(0) {
  if (n > 0) {
    for (int i = 0; i < static_cast<int>(n); ++i) {
      push_back(T());
    }
  } else {
    throw std::out_of_range("n <= 0");
  }
}

template <typename T>
list<T>::list(const list& other) : head_(nullptr), tail_(nullptr), size_(0) {
  Node* node = other.head_;
  while (node != nullptr) {
    push_back(node->value_);
    node = node->pnext_;
  }
}

template <typename T>
list<T>::list(list&& other) noexcept
    : head_(other.head_), tail_(other.tail_), size_(other.size_) {
  other.head_ = other.tail_ = nullptr;
  other.size_ = 0;
}

template <typename T>
list<T>::~list() {
  clear();
}

template <typename T>
list<T>& list<T>::operator=(const list& other) {
  if (this != &other) {
    clear();
    Node* node = other.head_;
    while (node != nullptr) {
      push_back(node->value_);
      node = node->pnext_;
    }
  }
  return *this;
}

template <typename T>
list<T>& list<T>::operator=(list&& other) noexcept {
  if (this != &other) {
    clear();
    head_ = other.head_;
    tail_ = other.tail_;
    size_ = other.size_;
    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;
  }
  return *this;
}

template <typename T>
typename list<T>::reference list<T>::front() {
  if (head_ != nullptr) {
    return head_->value_;
  } else {
    throw std::out_of_range("List is empty");
  }
}

template <typename T>
typename list<T>::reference list<T>::back() {
  if (tail_ != nullptr) {
    return tail_->value_;
  } else {
    throw std::out_of_range("List is empty");
  }
}

template <typename T>
typename list<T>::const_reference list<T>::front() const {
  if (head_ != nullptr) {
    return head_->value_;
  } else {
    throw std::out_of_range("List is empty");
  }
}

template <typename T>
typename list<T>::const_reference list<T>::back() const {
  if (tail_ != nullptr) {
    return tail_->value_;
  } else {
    throw std::out_of_range("List is empty");
  }
}

template <typename T>
bool list<T>::empty() const {
  return size_ == 0;
}

template <typename T>
typename list<T>::size_type list<T>::size() const {
  return size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() {
  return (std::numeric_limits<std::size_t>::max() / sizeof(Node) / 2);
}

template <typename T>
void list<T>::clear() {
  while (head_ != nullptr) {
    pop_front();
  }
}

template <typename T>
typename list<T>::iterator list<T>::insert(iterator pos,
                                           const_reference value) {
  Node* new_node = new Node(value);

  if (size_ == 0) {
    head_ = tail_ = new_node;
  } else if (pos == begin()) {
    new_node->pnext_ = head_;
    head_->pprev_ = new_node;
    head_ = new_node;
  } else if (pos == end()) {
    tail_->pnext_ = new_node;
    new_node->pprev_ = tail_;
    tail_ = new_node;
  } else {
    Node* current = pos.GetNode();
    Node* prev_node = current->pprev_;
    prev_node->pnext_ = new_node;
    new_node->pprev_ = prev_node;
    new_node->pnext_ = current;
    current->pprev_ = new_node;
  }

  ++size_;
  return iterator(new_node);
}

template <typename T>
void list<T>::erase(iterator pos) {
  if (pos.GetNode() == nullptr) {
    return;
  }
  Node* to_delete = pos.GetNode();
  if (to_delete == head_) {
    head_ = head_->pnext_;
    if (head_) {
      head_->pprev_ = nullptr;
    } else {
      tail_ = nullptr;
    }
  } else if (to_delete == tail_) {
    tail_ = tail_->pprev_;
    if (tail_) {
      tail_->pnext_ = nullptr;
    }
  } else {
    Node* prev_node = to_delete->pprev_;
    Node* next_node = to_delete->pnext_;
    prev_node->pnext_ = next_node;
    next_node->pprev_ = prev_node;
  }
  delete to_delete;
  --size_;
}

template <typename T>
void list<T>::push_back(const_reference value) {
  Node* new_node = new Node(value);

  if (tail_ == nullptr) {
    head_ = tail_ = new_node;
  } else {
    tail_->pnext_ = new_node;
    new_node->pprev_ = tail_;
    tail_ = new_node;
  }
  ++size_;
}

template <typename T>
void list<T>::pop_back() {
  if (tail_ != nullptr) {
    Node* temp = tail_;
    tail_ = tail_->pprev_;
    if (tail_ != nullptr) {
      tail_->pnext_ = nullptr;
    } else {
      head_ = nullptr;
    }
    delete temp;
    --size_;
  }
}

template <typename T>
void list<T>::push_front(const_reference value) {
  Node* new_node = new Node(value);

  if (head_ == nullptr) {
    head_ = tail_ = new_node;
  } else {
    new_node->pnext_ = head_;
    head_->pprev_ = new_node;
    head_ = new_node;
  }
  ++size_;
}

template <typename T>
void list<T>::pop_front() {
  if (head_ != nullptr) {
    Node* temp = head_;
    head_ = head_->pnext_;
    if (head_ != nullptr) {
      head_->pprev_ = nullptr;
    } else {
      tail_ = nullptr;
    }
    delete temp;
    --size_;
  }
}

template <typename T>
void list<T>::swap(list& other) {
  Node* tmp_head = head_;
  Node* tmp_tail = tail_;
  size_t tmp_size = size_;

  head_ = other.head_;
  tail_ = other.tail_;
  size_ = other.size_;

  other.head_ = tmp_head;
  other.tail_ = tmp_tail;
  other.size_ = tmp_size;
}

template <typename T>
void list<T>::merge(list& other) {
  if (this != &other) {
    iterator it_this = this->begin();
    iterator it_other = other.begin();

    while (!other.empty()) {
      if (it_this == end() || *it_other < *it_this) {
        insert(it_this, *it_other);
        auto temp = it_other++;
        other.erase(temp);
      } else {
        ++it_this;
      }
    }
  }
}

template <typename T>
template <typename InputIterator>
void list<T>::splice(InputIterator pos, list& other) noexcept {
  if (!other.empty()) {
    Node* pos_node = const_cast<Node*>(pos.GetNode());
    if (this->empty()) {
      head_ = other.head_;
      tail_ = other.tail_;
    } else if (pos_node == nullptr) {
      tail_->pnext_ = other.head_;
      other.head_->pprev_ = tail_;
      tail_ = other.tail_;
    } else {
      if (pos_node == head_) {
        other.tail_->pnext_ = head_;
        head_->pprev_ = other.tail_;
        head_ = other.head_;
      } else {
        Node* prev_node = pos_node->pprev_;
        prev_node->pnext_ = other.head_;
        other.head_->pprev_ = prev_node;
        other.tail_->pnext_ = pos_node;
        pos_node->pprev_ = other.tail_;
      }
    }
    size_ += other.size_;
    other.head_ = other.tail_ = nullptr;
    other.size_ = 0;
  }
}

template <typename T>
void list<T>::reverse() {
  if (size_ > 1) {
    Node* head_ptr = head_;
    Node* tail_ptr = tail_;
    for (size_t i = 0; i < size_ / 2; ++i) {
      std::swap(head_ptr->value_, tail_ptr->value_);
      head_ptr = head_ptr->pnext_;
      tail_ptr = tail_ptr->pprev_;
    }
  }
}

template <typename T>
void list<T>::unique() {
  if (size_ > 1) {
    iterator it = begin();
    iterator next = it;
    ++next;
    while (next != end()) {
      if (*it == *next) {
        next = erase_it(next);
      } else {
        ++it;
        ++next;
      }
    }
  }
}

template <typename T>
void list<T>::sort() {
  if (size_ < 2) {
    return;  // Уже отсортировано
  }

  Node* current = head_;
  while (current != nullptr) {
    Node* next_node = current->pnext_;
    while (next_node != nullptr) {
      if (current->value_ > next_node->value_) {
        std::swap(current->value_, next_node->value_);
      }
      next_node = next_node->pnext_;
    }
    current = current->pnext_;
  }
}

template <typename T>
template <typename... Args>
typename list<T>::iterator list<T>::insert_many(const_iterator pos,
                                                Args&&... args) {
  if constexpr (sizeof...(args) != 0) {
    if (empty()) {
      // Если список пуст, добавляем элементы в конец
      for (const auto& arg : {args...}) {
        push_back(arg);
      }
      return begin();
    } else {
      // Вставка в конец
      if (pos.GetNode() == tail_) {
        for (const auto& arg : {args...}) {
          push_back(arg);  // Добавляем в конец
        }
        return iterator(tail_);  // Возвращаем итератор на новый tail_
      } else {
        // Вставка в середину списка
        for (const auto& arg : {args...}) {
          insert(pos, arg);  // Вставляем на указанную позицию
        }
      }
    }
  }
  return pos;  // Возвращаем итератор на позицию вставки
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_back(Args&&... args) {
  if constexpr (sizeof...(args) != 0) {
    for (const auto& arg : {args...}) {
      push_back(arg);
    }
  }
}

template <typename T>
template <typename... Args>
void list<T>::insert_many_front(Args&&... args) {
  if constexpr (sizeof...(args) != 0) {
    // Временный список для хранения элементов
    std::initializer_list<value_type> temp_list{args...};
    // Вставляем элементы в обратном порядке
    for (auto it = temp_list.end(); it != temp_list.begin();) {
      --it;
      push_front(*it);  // Вставляем элементы в начало списка
    }
  }
}

template <typename T>
template <typename InputIterator>
void list<T>::assign(InputIterator first, InputIterator last) {
  clear();
  for (; first != last; ++first) {
    push_back(*first);
  }
}

template <typename T>
template <typename InputIterator>
list<T>::list(InputIterator first, InputIterator last) : list() {
  assign(first, last);
}

template <typename T>
typename list<T>::iterator list<T>::erase_it(iterator pos) {
  if (size_ > 0) {
    Node* cur = pos.GetNode();
    iterator return_it =
        iterator(cur->pnext_);  // Сразу получаем следующий элемент

    if (cur == tail_) {
      pop_back();
      return return_it;
    } else if (cur == head_) {
      pop_front();
      return iterator(head_);  // Теперь head может быть изменён, поэтому
                               // возвращаем новый head
    } else {
      Node* prev = cur->pprev_;
      Node* next = cur->pnext_;
      prev->pnext_ = next;  // Соединяем предыдущий узел с следующим
      if (next != nullptr) {  // Проверка, если следующий узел существует
        next->pprev_ = prev;  // Соединяем следующий узел с предыдущим
      }
      delete cur;  // Удаляем текущий узел
      --size_;     // Уменьшаем размер списка
      return return_it;  // Возвращаем итератор на следующий элемент
    }
  }
  return end();  // Если список пуст, возвращаем итератор конца списка
}

}  // namespace s21
