#include "Tile.h"
#include "TileCodes.h"

Tile::Tile(Colour colour, Shape shape)
{
    this->colour = colour;
    this->shape = shape;
}

std::string Tile::toString()
{
    // Setting text colour using ANSI colour codes (default is black)
    std::string colourCode = "\033[30m";
    if (colour == RED) colourCode = "\033[31m";
    else if (colour == ORANGE) colourCode = "\033[91m";
    else if (colour == YELLOW) colourCode = "\033[33m";
    else if (colour == GREEN) colourCode = "\033[32m";
    else if (colour == BLUE) colourCode = "\033[94m";
    else if (colour == PURPLE) colourCode = "\033[35m";

    std::string shapeCode = "";
    if (shape == CIRCLE) shapeCode = "\U000025CB";
    else if (shape == STAR_4) shapeCode = "\U00002B51";
    else if (shape == DIAMOND) shapeCode = "\U000025CA";
    else if (shape == SQUARE) shapeCode = "\U000025A1";
    else if (shape == STAR_6) shapeCode = "\U00002734";
    else if (shape == CLOVER) shapeCode = "\U00002663";

    return colourCode + colour + shapeCode + "\033[0m";
}
