
#ifndef ASSIGN2_GAME_ENGINE_H
#define ASSIGN2_GAME_ENGINE_H

#include <string>

#include "LinkedList.h"
#include "Player.h"
#include "Tile.h"

class GameEngine
{
public:
  //Setup Functions
  GameEngine();
  ~GameEngine();
  void saveGame(std::string filename);
  void loadGame(std::string filename);
  void addTile(Tile tile);

  //Game Functions
  void addPlayer(std::string);
  void placeTile(Tile tile, char letter, int number);
  void replaceTile();

  //NewGame Functions
  LinkedList* makeBag();
  void drawInitialTiles();
  void mainLoop();
  void alternateTurns();
  void printBoard();

  //Other Functions
  int letterToNumber(char letter);
  char numberToLetter(int number);


private:
  LinkedList tileBag;
  Player* currentPlayer;
  Player* playerArray[2];
  int numPlayers;
  Tile board[][26];
};

#endif // ASSIGN2_GAME_ENGINE_H
