
#include "LinkedList.h"

LinkedList::LinkedList() :
head(nullptr),
tail(nullptr)
{
  size = 0;
}

LinkedList::~LinkedList() {
}

void LinkedList::addFront(Tile* tile) {
  Node* temp = new Node(tile, head, nullptr);
  if (head == nullptr) {
    head = temp;
    tail = temp;
  } else {
    head = temp;
  }
  size++;
}

void LinkedList::addBack(Tile* tile) {
  Node* temp = new Node(tile, nullptr, tail);
  if (head == nullptr){
    head = temp;
    tail = temp;
    temp = nullptr;
  } else {
    tail->next = temp;
    tail = temp;
  }
  size++;
}

void LinkedList::deleteFront() {
  Node* temp = head;
  head = head->next;
  delete temp;
  size--;
}

//code to delete back of list... faster if double linked list is implemented?
void LinkedList::deleteBack() {
     Node* temp = tail;
     tail = tail->prev;
     delete temp;
     size--;
}


//code to return nodes as a string
std::string LinkedList::toString() {
  std::string listString;
  for(i = 0; i < size; i++) {
    Node* curr = head;
    listString += (curr->toString() + " ")
    curr = curr->next
  }
  return listString;
}

//Getter
int LinkedList::getSize() {
  return size;
}
