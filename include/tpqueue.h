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
    Node() : data(), next(nullptr) {}
    explicit Node(const T& value) : data(value), next(nullptr) {}
  };

  Node* head;

 public:
  TPQueue() {
    head = new Node();
  }

  ~TPQueue() {
    while (head != nullptr) {
      Node* temp = head;
      head = head->next;
      delete temp;
    }
  }

  void push(const T& element) {
    Node* newNode = new Node(element);
    Node* current = head;

    while (current->next != nullptr && current->next->data.prior >= element.prior) {
      current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
  }

  T pop() {
    if (head->next == nullptr) {
      throw std::out_of_range("Queue is empty");
    }
    Node* targetNode = head->next;
    T value = targetNode->data;
    
    head->next = targetNode->next;
    delete targetNode;
    
    return value;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
