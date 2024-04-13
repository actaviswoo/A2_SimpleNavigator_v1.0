#ifndef A2_SIMPLENAVIGATOR_SRC_LIBS_CONTAINER_HEADERS_S21_STACK_H
#define A2_SIMPLENAVIGATOR_SRC_LIBS_CONTAINER_HEADERS_S21_STACK_H

#include <iostream>

namespace s21 {
template <typename T>
class Stack {
 public:
  using value_type = T;
  using size_type = std::size_t;
  using reference = value_type&;
  using const_reference = const value_type&;

  Stack();
  Stack(std::initializer_list<value_type> const& items);
  Stack(const Stack& s);
  Stack(Stack&& s);
  ~Stack();

  Stack& operator=(Stack&& other);

  reference top();
  const_reference top() const;

  bool empty() const;
  size_type size() const;

  void push(const value_type& value);
  void push(value_type&& value);
  void pop();
  void swap(Stack& other);

 private:
  struct Node {
    value_type data;
    Node* next;
    Node(const T& value) : data(value), next(nullptr){};
  };
  Node* head_;
  size_type size_;
};
}  // namespace s21

#include "../Sources/s21_stack.tpp"

#endif  // A2_SIMPLENAVIGATOR_SRC_LIBS_CONTAINER_HEADERS_S21_STACK_H