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
   void clear();
   void deleteAt(int pos);
   //Getters
   int getSize();
   std::string toString();
   Node* getNode(Tile* tile);

private:
   Node* head;
   Node* tail;
   int size;

};

#endif // ASSIGN2_LINKEDLIST_H
