namespace s21 {
template <class T>
Stack<T>::Stack() : head_(nullptr), size_(0) {}

template <class T>
Stack<T>::Stack(std::initializer_list<value_type> const& items)
    : head_(nullptr), size_(0) {
  for (const auto item : items) {
    push(item);
  }
}

template <class T>
Stack<T>::Stack(const Stack& s) : head_(nullptr), size_(s.size_) {
  Node* current = s.head_;
  Node* temp = nullptr;
  while (current != nullptr) {
    Node* tmp = new Node(current->data);
    if (head_ == nullptr) {
      head_ = temp = tmp;
    } else {
      temp->next = tmp;
      temp = tmp;
    }
    current = current->next;
  }
}
template <class T>
Stack<T>::Stack(Stack&& s) : head_(nullptr), size_(0) {
  swap(s);
}

template <class T>
Stack<T>::~Stack() {
  while (!empty()) {
    pop();
  }
}

template <class T>
Stack<T>& Stack<T>::operator=(Stack&& other) {
  if (this != &other) {
    swap(other);
  }
  return *this;
}

template <class T>
typename Stack<T>::reference Stack<T>::top() {
  if (empty()) {
    throw std::runtime_error("stack is empty");
  }
  return head_->data;
}

template <class T>
typename Stack<T>::const_reference Stack<T>::top() const {
  if (empty()) {
    throw std::runtime_error("stack is empty");
  }
  return head_->data;
}

template <class T>
bool Stack<T>::empty() const {
  return head_ == nullptr;
}

template <class T>
typename Stack<T>::size_type Stack<T>::size() const {
  return size_;
}

template <class T>
void Stack<T>::push(const value_type& value) {
  Node* temp = new Node(value);
  if (empty()) {
    head_ = temp;
  } else {
    temp->next = head_;
    head_ = temp;
  }
  size_++;
}

template <class T>
void Stack<T>::push(value_type&& value) {
  Node* temp = new Node(value);
  if (empty()) {
    head_ = temp;
  } else {
    temp->next = head_;
    head_ = temp;
  }
  size_++;
}

template <class T>
void Stack<T>::pop() {
  if (empty()) {
    return;
  }
  Node* temp = head_;
  head_ = head_->next;
  delete temp;
  size_--;
}

template <class T>
void Stack<T>::swap(Stack& other) {
  std::swap(head_, other.head_);
  std::swap(size_, other.size_);
}
}  // namespace s21