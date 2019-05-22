#ifndef ASSIGN2_GAME_ENGINE_H
#define ASSIGN2_GAME_ENGINE_H

#include <string>
#include <vector>

#include "LinkedList.h"
#include "Player.h"
#include "Tile.h"
#include "TileCodes.h"

#define BOARD_SIZE 26
#define NO_OF_EACH_TILE 2
#define MAX_NO_OF_TILE 72
#define LEFT 0
#define UP 1
#define RIGHT 2
#define DOWN 3
#define INITIAL_NUM_PLAYERS 0
#define INITIAL_TURN_COUNT 0
#define NULL_TILE 0
#define MAX_HAND_SIZE 6

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
  bool executeCommand(std::string action);
  bool checkSurround(Tile *tile, int letter, int number);
  bool checkAroundLocation(int letter, int number);
  int countTiles(int letter, int number, int direction);
  bool checkTiles(Tile* tile, int letter, int number, int axis);
  void readInCommand();
  int countPoints(int letter, int number);
  bool replaceTile(int index);

  void help();
  bool checkDuplicate(Tile *tile, int letter, int number);
  bool checkPriorDuplicate(int letter, int number);
  bool oneTileCheck(Tile *tile, int letter, int number, int direction);
  bool manyTileCheck(Tile *tile, int tileCount, int letter, int number, int direction);
  bool gameEndCheck();
  void setLN(int &l, int &n, int direction);
  void giveHint();
  void aiMove();
  void loadPlaceTile(int x, int y, Tile* tile);
  int getNumPlayers();

  void saveHighScores();
  void printHighScores();

  struct location {
      int letter;
      int number;
  };
  struct locationAndScore {
      int letter;
      int number;
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
