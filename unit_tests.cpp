#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "GameEngine.h"

#define EXIT_SUCCESS     0
#define REQUIRED_ARGS    1

void checkArgs(int argc, char** argv);
void checkFile(std::string &filename);
void loadInput(char** argv);
int findMax(std::string yVal);

// DELETE LATER
void printHighScores();
void saveHighScores();
// END DELETE

int main(int argc, char** argv) {
  try {
      checkArgs(argc, argv);
      loadInput(argv);
      printHighScores();
  } catch(std::runtime_error &exception) {
      std::cout << "ERROR: " << exception.what() << std::endl;
  }

  return EXIT_SUCCESS;
}

// Checks that there are the correct number of command line arguments and that
// both input and output files exist
void checkArgs(int argc, char** argv) {
  if(argc != REQUIRED_ARGS + 1) {
    throw std::runtime_error("Incorrect no. of file names provided");
  }

  std::string inputFilename = argv[1] + std::string(".in");
  checkFile(inputFilename);
}

void checkFile(std::string &filename) {
  std::ifstream in;
  in.open(filename);
  if (in.fail()) {
    throw std::runtime_error("Could not open " + filename);
  }
  in.close();
}

// Sets up inital state of the game for actions to be preformed on
void loadInput(char** argv) {
  std::string filename = argv[1] + std::string(".in");
  std::ifstream in;
  in.open(filename);

  // Reading player 1 and 2 data from file.
  // Loop runs twice to load in data for each player
  for (int i = 0; i < 2; i++) {
    std::string playerName;
    std::getline(in, playerName);
    // CALL ADD PLAYER METHOD HERE
    std::cout << "Player " << i + 1 << " name: "<<  playerName << std::endl;

    std::string playerScoreString;
    std::getline(in, playerScoreString);
    int playerScore = std::stoi(playerScoreString);
    // CALL SET PLAYER SCORE HERE
    std::cout << "Player " << i + 1 << " score: "<<  playerScore << std::endl;

    std::string playerHand;
    std::getline(in, playerHand);
    std::cout << "Player " << i + 1 << " hand: "<<  playerHand << std::endl;
    // while loop to add all tiles in the string to player hand.
    std::istringstream playerHandStream(playerHand);
    std::string tile;
    while (std::getline(playerHandStream, tile, ',')) {
      // CALL ADD TILE TO PLAYER HAND METHOD
      std::cout << tile << std::endl;
    }
  }

  // Reading board state from file.
  std::string boardRow;
  // Skips over first two lines that contain no useful information.
  std::getline(in, boardRow);
  std::getline(in, boardRow);
  // Loop runs for the number of rows of the board
  for (int i = 0; i < 26; i++) {
    std::getline(in, boardRow);
    std::cout << boardRow << std::endl;
    // Begins scanning the single row, checking if each 'space' is empty.
    // 'k' value used for keeping track of the currnt column (x value) the
    // program is at. Current row (y value) is 'i'.
    int k = 0;
    for (int j = 3; j < boardRow.length() - 1; j += 3) {
      if (boardRow.at(j) != ' ') {
        // CALL ADD TITLE TO BOARD METHOD HERE
        std::cout << "Found tile at " << i << ", " << k << ": " <<
          boardRow.at(j) << boardRow.at(j + 1) << std::endl;
      }
      k++;
    }
  }

  // Reading the tile bag form file
  std::string tileBag;
  std::getline(in, tileBag);
  std::cout << tileBag << std::endl;
  // while loop to add all tiles in the string to tile bag
  std::istringstream tileBagStream(tileBag);
  std::string tile;
  while (std::getline(tileBagStream, tile, ',')) {
    // CALL ADD TILE TO TIL BAG METHOD HERE
    std::cout << tile << std::endl;
  }

  // Reading the current player from file
  std::string currentPlayer;
  std::getline(in, currentPlayer);
  std::cout << "Current player: " << currentPlayer << std::endl;
  // CALL SET CURRENT PLAYER TURN METHOD HEREE

  // Reading and processing commands from file
  std::string command;
  while(std::getline(in, command)) {
    std::cout << command << std::endl;
    std::istringstream commandStream(command);
    std::string action;
    std::getline(commandStream, action, ' ');
    if (action == "place") {
      std::string tileToPlace;
      std::getline(commandStream, tileToPlace, ' ');
      std::string coordinate;
      std::getline(commandStream, coordinate, ' ');
      std::getline(commandStream, coordinate, ' ');
      // CALL PLACE TILE METHOD FOR CURRENT PLAYER HERE
    }
    else if (action == "replace") {
      std::string tileToReplace;
      std::getline(commandStream, tileToReplace, ' ');
      // CALL REPLACE TILE METHOD FOR CURRENT PLAYER HERE
    }
    else if (action == "save") {
      std::string filename;
      std::getline(commandStream, filename, ' ');
      // CALL SAVE GAME METHOD HERE
      //   pass in 'filename'
    }
  }
  in.close();
}

// Finds the largest Y length for the board
int findMax(std::string yVal) {
  int num = 0, currMax = 0;
  for (int i = 0; i<yVal.length(); i++) {
    if (yVal[i] >= '0' && yVal[i] <= '9'){
      num = num * 10 + (yVal[i] - '0');
    } else {
      currMax = std::max(currMax, num);

      num = 0;
    }
  }
  return std::max(currMax, num);
}

// FUNCTION BELONGS IN GAMEENGINE. PLACED HERE RIGHT NOW TO AVOID
// MERGE ERRORS WITH GITHUB
void printHighScores()
{
  std::string filename = "highscore.txt";
  std::ifstream in;
  in.open(filename);

  std::string line;
  while(std::getline(in, line))
  {
    std::cout << line << std::endl;
  }
}

void saveHighScores()
{
  // Loads players from highscore file to a vector
  std::string filename = "highscore.txt";
  std::ifstream in;
  in.open(filename);

  std::vector<Player*> players;
  std::string line;
  while(std::getline(in, line))
  {
    // String stream to break up playerName from playerScore
    std::istringstream lineStream(line);

    std::string playerName;
    std::getline(lineStream, playerName, ',');

    std::string playerScoreString;
    std::getline(lineStream, playerScoreString, ',');
    int playerScore = std::stoi(playerScoreString);

    Player* playerPtr = new Player(playerName);
    playerPtr->addPoints(playerScore);
    // Vector has player in order from largest points to smallest points
    players.push_back(playerPtr);
  }
  in.close();

  // Compares the players currently in play with the players on the leader board
  for (int i = 0; i < 2; i++)
  {
    int j = 0;
    int insertAt = players.size();
    bool endLoop = false;
    while (j < players.size() && !endLoop)
    {
      if (players[j]->getScore() < currentPlayers[i]->getScore())
      {
        insertAt = j;
        endLoop = true;
      }
      j++;
    }
    players.insert(players.begin() + insertAt, currentPlayers[i]);
  }

  // Prints  out the top 5 highscores, leaving off player whose scores are less
  // than the top 5
  std::ofstream out;
  outFile.open(filename);
  for (int i = 0; i < players.size() && i < 5; i++)
  {
    out << players[i]->getName() << "," << players[i]->getScore() << std::endl;
  }
  out.close();
}
