//push test
#ifndef ASSIGN2_NODE_H
#define ASSIGN2_NODE_H

#include "Tile.h"

class Node {
public:

   Node(Tile* tile, Node* next, Node* prev);
   Node(Node& other);

   Tile*    tile;
   Node*    next;
   Node*    prev;

   std::string toString();
   Tile* getTile();
};

#endif // ASSIGN2_NODE_H
