
#include "LinkedList.h"

LinkedList::LinkedList() :
head(nullptr),
tail(nullptr)
{
  size = 0;
}

LinkedList::~LinkedList() {
  //clear();
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
  Node* curr = head;
  for(int i = 0; i < size; i++) {
    listString += (curr->getTile()->toString() + " ");
    curr = curr->next;
  }
  return listString;
}

std::string LinkedList::toString2() {
  std::string listString;
  Node* curr = head;
  for(int i = 0; i < size - 1 ; i++) {
    listString += (curr->getTile()->toString2() + ",");
    curr = curr->next;
  }
  listString += curr->getTile()->toString2();

  return listString;
}


void LinkedList::deleteAt(int pos)
{
  if (pos > size)
  {
    return;
  }
  if (pos == 0)
  {
    deleteFront();
  }
  else if (pos == size - 1)
  {
    deleteBack();
  }
  else
  {
    Node *curr = head;
    for (int i = 0; i < pos; i++)
    {
      curr = curr->next;
    }
    curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
    delete curr;
    size--;
  }
}

//Getters
int LinkedList::getSize() {
  return size;
}

//returns node, used for replacing tiles?? will possibly need to adj
// to remove from the list as well
Node* LinkedList::getNode(Tile* tile) {
  Node* foundNode = nullptr;
  Node* curr = head;
  while(curr != nullptr && foundNode == nullptr){
    if (curr->getTile() == tile){
      foundNode = curr;
    }
    curr = curr->next;
  }
  return foundNode;
}

Tile *LinkedList::getTileAt(int index)
{
  int i = 0;
  Node *curr = head;
  Tile *tile;
  while (i < index)
  {
    curr = curr->next;
    i++;
  }
  tile = curr->getTile();
  return tile;
}

void LinkedList::clear(){
  while(this->head != nullptr){
    Node* toDelete = this-> head;
    head = toDelete->next;
    delete toDelete;
  }
  tail = nullptr;
}
