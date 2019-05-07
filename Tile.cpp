#include "Tile.h"
#include "TileCodes.h"

Tile::Tile(Colour colour, Shape shape)
{
    this->colour = colour;
    this->shape = shape;
}

std::string Tile::toString()
{
    std::string tile;
    tile += colour;
    tile += shape;
    return tile;
}
