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

    explicit Node(const T& val) : data(val), next(nullptr) {}
  };

  Node* listHead;

 public:
  TPQueue() : listHead(nullptr) {}

  ~TPQueue() {
    while (listHead != nullptr) {
      Node* itemToDelete = listHead;
      listHead = listHead->next;
      delete itemToDelete;
    }
  }

  void push(const T& element) {
    Node* insertedNode = new Node(element);

    if (listHead == nullptr || element.prior > listHead->data.prior) {
      insertedNode->next = listHead;
      listHead = insertedNode;
      return;
    }

    Node* iterator = listHead;
    while (iterator->next != nullptr &&
           iterator->next->data.prior >= element.prior) {
      iterator = iterator->next;
    }

    insertedNode->next = iterator->next;
    iterator->next = insertedNode;
  }

  T pop() {
    if (listHead == nullptr) {
      throw std::out_of_range("Queue is empty");
    }

    Node* topNode = listHead;
    T resultValue = topNode->data;
    listHead = listHead->next;
    
    delete topNode;
    return resultValue;
  }
};

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
