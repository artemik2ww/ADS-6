#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

template <class T>
class TPQueue {
 private:
  struct Node {
    T data;
    Node* next;

    explicit Node(const T& value) : data(value), next(nullptr) {}
  };

  Node* head;

 public:
  TPQueue() : head(nullptr) {}

  ~TPQueue() {
    while (head != nullptr) {
      Node* tmp = head;
      head = head->next;
      delete tmp;
    }
  }

  void push(const T& value) {
    Node* node = new Node(value);

    if (head == nullptr || value.prior > head->data.prior) {
      node->next = head;
      head = node;
      return;
    }

    Node* current = head;

    while (current->next != nullptr &&
           current->next->data.prior >= value.prior) {
      current = current->next;
    }

    node->next = current->next;
    current->next = node;
  }

  T pop() {
    T result = head->data;
    Node* tmp = head;

    head = head->next;
    delete tmp;

    return result;
  }

  bool empty() const {
    return head == nullptr;
  }
};
