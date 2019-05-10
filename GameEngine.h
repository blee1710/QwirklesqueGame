
#ifndef ASSIGN2_GAME_ENGINE_H
#define ASSIGN2_GAME_ENGINE_H

#include <string>

#include "LinkedList.h"
#include "Player.h"
#include "Tile.h"
#include "TileCodes.h"

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
  void addPlayer(std::string name);
  void placeTile(std::string tile, std::string location, int index);
  void replaceTile();

  //NewGame Functions
  void makeBag();
  void drawInitialTiles();
  void mainLoop();
  void alternateTurns();
  void printBoard();

  //Other Functions
  int letterToNumber(char letter);
  char numberToLetter(int number);
  void clearBoardMemory();
  void executeCommand(std::string action);
  bool checkSurround(int letter, int number);
  int countTiles(int letter, int number, int direction);
  void readInCommand();

  void help();


private:
  LinkedList tileBag;
  Player* currentPlayer;
  Player* playerArray[2];
  int numPlayers;
  int turn;
  Tile* board[26][26];

  void saveHighScores();
  void printHighScores();
};

#endif // ASSIGN2_GAME_ENGINE_H
