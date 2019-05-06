
#include "LinkedList.h"

LinkedList::LinkedList() :
head(nullptr),
tail(nullptr)
{
   // TODO
}

LinkedList::~LinkedList(LinkedList& other) {
}

void LinkedList::addFront(Tile* tile) {
  Node* temp = new Node(tile, head);
  if (head == nullptr) {
    head = temp;
    tail = temp;
  } else {
    head = temp;
  }
}

void LinkedList::addBack(Tile* tile) {
  Node* temp = new Node(tile, nullptr);
  if (head == nullptr){
    head = temp;
    tail = temp;
    temp = nullptr;
  } else {
    tail->next = temp;
    tail = temp;
  }
}

void LinkedList::deleteFront() {
  Node* temp = head;
  head = head->next;
  delete temp;
}

//code to delete back of list... faster if double linked list is implemented?
void LinkedList::deleteBack() {
  Node* curr = head;
  Node* last;

  while(curr->next != nullptr){
    last = curr;
    curr = curr->next;
  }
  tail = last;
  last->next = nullptr;
  delete curr;
}
