#include "GameEngine.h"

#include <iostream>
#include <string>
#include <fstream>

GameEngine::GameEngine() {
  for (int y = 0; y < BOARD_SIZE; y++) {
    for(int x = 0; x < BOARD_SIZE; x++) {
      board[y][x] = nullptr;
    }
  }
}

GameEngine::~GameEngine() {

}

// Barebones imlementation of saveGame method.
void GameEngine::saveGame(std::string filename) {
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

  for (int i = 0; i < BOARD_SIZE; i++) {
    // ASCII character table states that capital letters begin at 65, so with
    // each iteration the character goes up (From 'A' to 'B' to 'C'...).
    char letter = i + 65;
    outFile << letter << " |";
    for (int j = 0; j < BOARD_SIZE; j++) {
      if(/*board[i][j] != null*/0) {
        outFile << /*board[i][j] << */ "|";
      }
      else {
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

void GameEngine::loadGame(std::string filename) {

}

bool GameEngine::placeTile(Tile* tile, int x, int y) {
  bool tilePlaced = false;

  if (board[y][x] == nullptr) {
    board[y][x] = tile;
    tilePlaced = true;
  }

  return tilePlaced;
}

bool GameEngine::replaceTile(Tile* tile) {
  bool tilePlaced = false;
  return tilePlaced;
}

void GameEngine::print() {
  std::cout << "ENGINE CREATED" << std::endl;
}
