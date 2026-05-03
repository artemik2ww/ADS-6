// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_

#include <stdexcept>

template<typename T>
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
    if (head == nullptr) {
      throw std::out_of_range("TPQueue is empty");
    }

    Node* tmp = head;
    T value = tmp->data;
    head = head->next;
    delete tmp;

    return value;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
