#include "GameEngine.h"
#include "TileCodes.h"
#include "LinkedList.h"
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <map>
#define BOARD_SIZE 26
#define NO_OF_EACH_TILE 2
#define MAX_NO_OF_TILE 72

GameEngine::GameEngine()
{
  std::cout << "ENGINE CREATED" << std::endl;
  numPlayers = 0;
}

GameEngine::~GameEngine()
{
}

// Barebones imlementation of saveGame method.
void GameEngine::saveGame(std::string filename)
{
  std::ofstream outFile;
  outFile.open(filename);

  // Writing out player data
  outFile << /*player1->getName() << */ std::endl;
  outFile << /*player1->getPoints() << */ std::endl;
  // Would probabbly want a toString method for LinkedList so that it prints out
  // the list in the format needed. Would be way more efficent than doing it in
  // the GameEngine ('for' loop that would call some sort of getAt(i) method).
  outFile << /*player1->getHand.toString() << */ std::endl;

  outFile << /*player2->getName() << */ std::endl;
  outFile << /*player2->getPoints() << */ std::endl;
  outFile << /*player2->getHand.toString() << */ std::endl;

  // Writing out board to file
  outFile << "   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20"
          << " 22 23 24 25" << std::endl;
  outFile << "-----------------------------------------------------------------"
          << "----------------" << std::endl;

  for (int i = 0; i < BOARD_SIZE; i++)
  {
    // ASCII character table states that capital letters begin at 65, so with
    // each iteration the character goes up (From 'A' to 'B' to 'C'...).
    char letter = i + 65;
    outFile << letter << " |";
    for (int j = 0; j < BOARD_SIZE; j++)
    {
      if (/*board[i][j] != null*/ 0)
      {
        outFile << /*board[i][j] << */ "|";
      }
      else
      {
        outFile << "  |";
      }
    }
    outFile << std::endl;
  }

  // Writing out tile bag to file
  outFile << /*tileBag->toString(); << */ std::endl;

  // Writing out current player to file
  outFile << /*currentPlayer->getName() << */ std::endl;

  outFile.close();
}

void GameEngine::loadGame(std::string filename)
{
}

void GameEngine::addPlayer(std::string name)
{
  playerArray[numPlayers] = new Player(name);
  numPlayers++;
}

void GameEngine::placeTile(Tile tile, char letter, int y)
{
  //Check if tile exists in player's hand (using getter from Player)
  //currentPlayer.getLinkedList() etc

  //Puts the tile in the corresponding position
  int x = letterToNumber(letter);
  board[x][y] = tile;
}

void GameEngine::replaceTile()
{
}

//Function for converting A to 0, B to 1 etc.
int GameEngine::letterToNumber(char letter)
{
  int index;
  char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  for (int i = 0; i < 26; i++)
  {
    if (letter = alphabet[i])
    {
      index = i;
      //Early termination
      i = 26;
    }
  }
  return index;
}

//Function for converting A to 0, B to 1 etc.
char GameEngine::numberToLetter(int number)
{
  char alphabet[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
  return alphabet[number];
}

//Adds a tile to the tile bag(end of linked list)
//Ideally can call this when generating initial tiles in tileBag and also when replacing.
void GameEngine::addTile(Tile tile)
{
  //tilebag.addTile() etc
}

//All players populate their hands
void GameEngine::drawInitialTiles()
{
  for (Player *p : playerArray)
  {
    for (int i = 0; i < 6; i++)
    {
      p->drawTile();
    }
  }
}

//The main loop between player's turns.
void GameEngine::mainLoop()
{
  // while(tileBag.getHead() != null && currentPlayer->getHand().getHead() != null)
  currentPlayer = playerArray[0];

  std::cout << currentPlayer->getName() << ", it's your turn" << std::endl;
  for (int i = 0; i < numPlayers; i++)
  {
    std::cout << "Score for " << playerArray[i]->getName() << ": " << playerArray[i]->getScore() << std::endl;
  }
}

void GameEngine::alternateTurns()
{
  if (currentPlayer = playerArray[0])
  {
    currentPlayer = playerArray[1];
  }
  else
  {
    currentPlayer = playerArray[0];
  }
}

void GameEngine::printBoard()
{
  std::cout << "   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25" << std::endl;
  std::cout << "---------------------------------------------------------------------------------" << std::endl;
  //Print all 26 rows
  for (int i = 0; i < 26; i++)
  {
    char letter = numberToLetter(i);
    std::cout << letter << " ";
    for (int j = 0; j < 26; j++)
    {
      std::cout << "|" << board[i][j].toString();
    }
    std::cout << "|" << std::endl;
  }
}

LinkedList* GameEngine::makeBag()
{
  LinkedList* newTileBag = new LinkedList();
  std::default_random_engine engine(1);
  std::map<int,char> colourMap = {{0, RED}, {1, ORANGE}, {2, YELLOW}, {3, GREEN},{4, BLUE},{5, PURPLE}};
  std::map<int,int> shapeMap = {{0, CIRCLE}, {1, STAR_4}, {2, DIAMOND}, {3, SQUARE},{4, STAR_6},{5, CLOVER}};
  std::vector<Tile*> allTiles;
  for(unsigned int x = 0; x < colourMap.size(); x++)
  {
    for(unsigned int y = 0; y < shapeMap.size(); y++)
    {
      for(int z = 0; z < NO_OF_EACH_TILE; z++)
      {
        allTiles.push_back(new Tile(colourMap[x], shapeMap[y]));
      }
    }
  }
  int index = 0;
  for(int i = 0 ; i < MAX_NO_OF_TILE ; i++)
  {
    std::uniform_int_distribution<int> uniform_dist(0, MAX_NO_OF_TILE-1-i);
    index = uniform_dist(engine);
    newTileBag->addBack(allTiles.at(index));
    allTiles.erase(allTiles.begin() + index);
  }
  return newTileBag;
}
