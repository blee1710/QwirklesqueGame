#include "Node.h"

Node::Node(Tile* tile, Node* next, Node* prev):tile(tile),next(next),prev(prev)
{
}

Node::Node(Node& other): tile(other.tile),next(other.next),prev(other.prev)
{
}

std::string Node::toString(){
  return tile->toString();
}

<<<<<<< HEAD
Tile* Node::getTile() {
=======
Tile* Node::getTile(){
>>>>>>> 13dd8c76aea86ff4832e1c5f4a604709d7c76ecc
  return tile;
}
