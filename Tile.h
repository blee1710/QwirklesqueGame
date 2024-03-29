#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <string>

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
public:
   Colour colour;
   Shape  shape;

   Tile(Colour colour, Shape shape);
   Tile(Tile& otherTile);
   std::string toString();
   std::string toString2();
   Colour getColour();
   Shape getShape();
};

#endif // ASSIGN2_TILE_H
