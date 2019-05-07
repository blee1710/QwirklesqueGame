
#ifndef ASSIGN2_GAME_ENGINE_H
#define ASSIGN2_GAME_ENGINE_H

#define BOARD_SIZE  26

#include <string>

#include "LinkedList.h"
#include "Tile.h"

class GameEngine {
public:

  GameEngine();
  ~GameEngine();
  void saveGame(std::string filename);
  void loadGame(std::string filename);
  bool placeTile(Tile* tile, int x, int y);
  bool replaceTile(Tile* tile);
  void print();
  
private:

  Tile* board[BOARD_SIZE][BOARD_SIZE];
  LinkedList tileBag;
  LinkedList player1Hand;
  LinkedList player2Hand;
};

#endif // ASSIGN2_GAME_ENGINE_H
