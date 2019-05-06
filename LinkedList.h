
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

   LinkedList();
   ~LinkedList();
   addFront(Tile* tile);
   addBack(Tile* tile);
   deleteFront();
   deleteBack();

private:
   Node* head;
   Node* tail;
};

#endif // ASSIGN2_LINKEDLIST_H
