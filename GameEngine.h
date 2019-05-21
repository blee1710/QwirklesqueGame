#ifndef ASSIGN2_GAME_ENGINE_H
#define ASSIGN2_GAME_ENGINE_H

#include <string>
#include <vector>

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
  bool placeTile(std::string tile, std::string location, int index);
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
  bool checkSurround(Tile *tile, int letter, int number);

  int countTiles(int letter, int number, int direction);
  void readInCommand();
  int countPoints(int letter, int number);
  bool replaceTile(int index);

  void help();
  bool checkDuplicate(Tile *tile, int letter, int number);
  bool checkPriorDuplicate(int letter, int number);
  bool oneTileCheck(Tile *tile, int letter, int number, int direction);
  bool manyTileCheck(Tile *tile, int tileCount, int letter, int number, int direction);
  void setLN(int &l, int &n, int direction);
  void giveHint();
  void aiMove();
  void loadPlaceTile(int x, int y, Tile* tile);
  int getNumPlayers();

  void saveHighScores();
  void printHighScores();

  struct locationAndScore {
      int l;
      int n;
      int score;
      Tile* tile;
  };
  std::vector<GameEngine::locationAndScore> generateHints();
  Player *currentPlayer;
private:
  LinkedList tileBag;
//  Player *playerArray[4];
  std::vector<Player*> playerArray;
  int numPlayers;
  int turn;
  Tile *board[26][26];
  int currentTurn = 0;
  int tilesPlaced = 0;
  bool isSinglePlayer = false;
};

#endif // ASSIGN2_GAME_ENGINE_H
