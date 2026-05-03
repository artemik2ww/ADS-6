#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

template <class T>
class TPQueue {
 private:
  struct Node {
    T value;
    Node* next;

    Node(const T& val, Node* nxt = nullptr) : value(val), next(nxt) {}
  };

  Node* head;

 public:
  TPQueue() : head(nullptr) {}

  ~TPQueue() {
    while (head != nullptr) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
  }

  void push(const T& value) {
    Node* node = new Node(value);

    if (head == nullptr || value.prior > head->value.prior) {
      node->next = head;
      head = node;
      return;
    }

    Node* current = head;

    while (current->next != nullptr &&
           current->next->value.prior >= value.prior) {
      current = current->next;
    }

    node->next = current->next;
    current->next = node;
  }

  T pop() {
    T result = head->value;

    Node* temp = head;
    head = head->next;
    delete temp;

    return result;
  }

  bool isEmpty() const {
    return head == nullptr;
  }
};

#endif
