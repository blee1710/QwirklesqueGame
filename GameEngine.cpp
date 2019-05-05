#include "GameEngine.h"

#include <string>
#include <fstream>

#define BOARD_SIZE  26

// Barebones imlementation of saveGame method.
void GameEngine::saveGame(std::string filename) {
  std::ofstream outFile;
  outFile.open(filename);

  // Writing out player data
  outFile << /*player1 <<*/ std::endl;

  // Would probabbly want a toString method for LinkedList so that it prints out
  // the list in the format needed. Would be way more efficent than doing it in
  // in the GameEngine ('for' loop that would call some sort of getAt(i) method).

  // Writing out board to file
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
  out << /*getCurrentPlayer() << */ std::endl;

  outFile.close();
}

void GameEngine::loadGame(std::string filename) {

}
