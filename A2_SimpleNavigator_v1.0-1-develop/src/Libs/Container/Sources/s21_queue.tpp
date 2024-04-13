namespace s21 {
template <class T>
Queue<T>::Queue() : head_(nullptr), tail_(nullptr), size_(0) {}

template <class T>
Queue<T>::Queue(std::initializer_list<value_type> const& items)
    : head_(nullptr), tail_(nullptr), size_(0) {
  for (const auto item : items) {
    push(item);
  }
}

template <class T>
Queue<T>::Queue(const Queue& q)
    : head_(nullptr), tail_(nullptr), size_(q.size_) {
  Node* current = q.head_;
  Node* temp = nullptr;
  while (current != nullptr) {
    Node* tmp = new Node(current->data);
    if (head_ == nullptr) {
      head_ = tail_ = temp = tmp;
    } else {
      tail_->next = tmp;
      tail_ = tmp;
    }
    current = current->next;
  }
}

template <class T>
Queue<T>::Queue(Queue&& q) : head_(nullptr), tail_(nullptr), size_(0) {
  swap(q);
}

template <class T>
Queue<T>::~Queue() {
  while (head_ != nullptr) {
    pop();
  }
}

template <class T>
Queue<T>& Queue<T>::operator=(Queue&& other) {
  if (this != &other) {
    swap(other);
  }
  return *this;
}

template <class T>
typename Queue<T>::reference Queue<T>::front() {
  if (empty()) {
    throw std::runtime_error("queue is empty");
  }
  return head_->data;
}

template <class T>
typename Queue<T>::const_reference Queue<T>::front() const {
  if (empty()) {
    throw std::runtime_error("queue is empty");
  }
  return head_->data;
}

template <class T>
typename Queue<T>::reference Queue<T>::back() {
  if (empty()) {
    throw std::runtime_error("queue is empty");
  }
  return tail_->data;
}

template <class T>
typename Queue<T>::const_reference Queue<T>::back() const {
  if (empty()) {
    throw std::runtime_error("queue is empty");
  }
  return tail_->data;
}

template <class T>
bool Queue<T>::empty() const {
  return size_ == 0;
}

template <class T>
typename Queue<T>::size_type Queue<T>::size() const {
  return size_;
}

template <class T>
void Queue<T>::push(const value_type& value) {
  Node* temp = new Node(value);
  if (empty()) {
    head_ = temp;
  } else {
    tail_->next = temp;
  }
  tail_ = temp;
  size_++;
}

template <class T>
void Queue<T>::push(value_type&& value) {
  Node* temp = new Node(value);
  if (empty()) {
    head_ = temp;
  } else {
    tail_->next = temp;
  }
  tail_ = temp;
  size_++;
}

template <class T>
void Queue<T>::pop() {
  if (empty()) {
    return;
  }
  Node* temp = head_;
  head_ = head_->next;
  delete temp;
  size_--;
}

template <class T>
void Queue<T>::swap(Queue& other) {
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(size_, other.size_);
}

}  // namespace s21