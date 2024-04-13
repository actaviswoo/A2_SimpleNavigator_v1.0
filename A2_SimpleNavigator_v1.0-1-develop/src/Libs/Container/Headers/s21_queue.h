#ifndef A2_SIMPLENAVIGATOR_SRC_LIBS_CONTAINER_HEADERS_S21_QUEUE_H
#define A2_SIMPLENAVIGATOR_SRC_LIBS_CONTAINER_HEADERS_S21_QUEUE_H

#include <iostream>

namespace s21 {
template <typename T>
class Queue {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using reference = value_type&;
  using const_reference = const value_type&;

  Queue();
  Queue(std::initializer_list<value_type> const& items);
  Queue(const Queue& q);
  Queue(Queue&& q);
  ~Queue();

  Queue& operator=(Queue&& other);

  reference front();
  const_reference front() const;
  reference back();
  const_reference back() const;

  bool empty() const;
  size_type size() const;

  void push(const value_type& value);
  void push(value_type&& value);
  void pop();
  void swap(Queue& other);

 private:
  struct Node {
    value_type data;
    Node* next;
    Node(const T& value) : data(value), next(nullptr){};
  };
  Node* head_;
  Node* tail_;
  size_type size_;
};
}  // namespace s21

#include "../Sources/s21_queue.tpp"

#endif  // A2_SIMPLENAVIGATOR_SRC_LIBS_CONTAINER_HEADERS_S21_QUEUE_H