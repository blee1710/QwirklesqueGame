#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

   LinkedList();
   ~LinkedList();
   void addFront(Tile* tile);
   void addBack(Tile* tile);
   void deleteFront();
   void deleteBack();

   //Getters
   int getSize();


private:
   Node* head;
   Node* tail;
   int size;
};

#endif // ASSIGN2_LINKEDLIST_H
