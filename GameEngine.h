
#ifndef ASSIGN2_GAME_ENGINE_H
#define ASSIGN2_GAME_ENGINE_H

#include <string>

#include "LinkedList.h"

class GameEngine {
public:

  GameEngine();
  ~GameEngine();
  void saveGame(std::string filename);
  void loadGame(std::string filename);
  
  void print();
private:

  LinkedList tileBag;
  LinkedList player1Hand;
  LinkedList player2Hand;
};

#endif // ASSIGN2_GAME_ENGINE_H
