#include "GameEngine.h"
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <map>
#include <sstream>

#define BOARD_SIZE 26
#define NO_OF_EACH_TILE 2
#define MAX_NO_OF_TILE 72

GameEngine::GameEngine()
{
  std::cout << "ENGINE CREATED" << std::endl;
  numPlayers = 0;
  turn = 0;
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
  outFile << playerArray[0]->getName() << std::endl;
  outFile << playerArray[0]->getScore() << std::endl;
  // Would probabbly want a toString method for LinkedList so that it prints out
  // the list in the format needed. Would be way more efficent than doing it in
  // the GameEngine ('for' loop that would call some sort of getAt(i) method).
  outFile << playerArray[0]->getHand().toString2() << std::endl;

  outFile << playerArray[1]->getName() << std::endl;
  outFile << playerArray[1]->getScore() << std::endl;
  outFile << playerArray[1]->getHand().toString2() << std::endl;

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
  outFile << tileBag.toString2() << std::endl;

  // Writing out current player to file
  outFile << currentPlayer->getName() << std::endl;

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

void GameEngine::placeTile(std::string tile, std::string location, int index)
{
  //String manipulation to access letter and number as ints
  std::string lstring = location.substr(0, 1);
  char *lchar = &lstring[0u];
  int letter = letterToNumber(*lchar);
  int number = std::stoi(location.substr(1, 2));

  Tile *tileObj = currentPlayer->getHandPtr()->getTileAt(index);
  if (turn == 0)
  {
    currentPlayer->getHandPtr()->deleteAt(index);
    currentPlayer->drawTile(tileBag.getTileAt(0));
    tileBag.deleteFront();
    board[letter][number] = tileObj;
  }
  else
  {
    if (checkSurround(letter, number))
    {
      currentPlayer->getHandPtr()->deleteAt(index);
      currentPlayer->drawTile(tileBag.getTileAt(0));
      tileBag.deleteFront();
      board[letter][number] = tileObj;
    }
    else
    {
      std::cout << "You can't place a tile there" << std::endl;
      readInCommand();
    }
  }
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
    if (letter == alphabet[i])
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
      Tile *tile = tileBag.getTileAt(0);
      tileBag.deleteFront();
      p->drawTile(tile);
    }
  }
}

//The main loop between player's turns.
void GameEngine::mainLoop()
{
  currentPlayer = &*playerArray[0];
  clearBoardMemory();
  while (tileBag.getSize() > 0 && currentPlayer->getHand().getSize() > 0)
  {

    std::cout << currentPlayer->getName() << ", it's your turn" << std::endl;
    for (int i = 0; i < numPlayers; i++)
    {
      std::cout << "Score for " << playerArray[i]->getName() << ": " << playerArray[i]->getScore() << std::endl;
    }
    printBoard();
    currentPlayer->printTiles();
    readInCommand();
  }
}

void GameEngine::readInCommand()
{
  std::string action;
  std::cout << ">";
  //Eat the line if necessary
  std::getline(std::cin, action);
  if (action == "")
  {
    std::getline(std::cin, action);
  }
  executeCommand(action);
}

void GameEngine::alternateTurns()
{
  if (currentPlayer == playerArray[0])
  {
    currentPlayer = playerArray[1];
    turn++;
  }
  else
  {
    currentPlayer = playerArray[0];
    turn++;
  }
}

void GameEngine::clearBoardMemory()
{
  //Makes sure there isn't any memory in array already (remove later)
  for (int k = 0; k < 26; k++)
  {
    for (int l = 0; l < 26; l++)
    {
      board[k][l] = 0;
    }
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
      if (board[i][j] != 0)
      {
        std::cout << "|" << board[i][j]->toString2();
      }
      else
      {
        std::cout << "|  ";
      }
    }
    std::cout << "|" << std::endl;
  }
}

void GameEngine::makeBag()
{
  std::default_random_engine engine(1);
  std::map<int, char> colourMap = {{0, RED}, {1, ORANGE}, {2, YELLOW}, {3, GREEN}, {4, BLUE}, {5, PURPLE}};
  std::map<int, int> shapeMap = {{0, CIRCLE}, {1, STAR_4}, {2, DIAMOND}, {3, SQUARE}, {4, STAR_6}, {5, CLOVER}};
  LinkedList* fullTileBag = new LinkedList();

  for (unsigned int x = 0; x < colourMap.size(); x++)
  {
    for (unsigned int y = 0; y < shapeMap.size(); y++)
    {
      for (unsigned int z = 0; z < NO_OF_EACH_TILE; z++)
      {
        fullTileBag->addBack(new Tile(colourMap[x], shapeMap[y]));
      }
    }
  }

  int index = 0;
  for (int i = 0; i < MAX_NO_OF_TILE; i++)
  {
    std::uniform_int_distribution<int> uniform_dist(0, MAX_NO_OF_TILE - 1 - i);
    index = uniform_dist(engine);
    tileBag.addBack(new Tile( *(fullTileBag->getTileAt(index) )));
    fullTileBag->deleteAt(index);
  }
}


void GameEngine::executeCommand(std::string action)
{
  bool valid = false;
  int index = 0;
  if (action.substr(0, 5) == "place" && action.substr(9, 2) == "at")
  {
    std::string tile = action.substr(6, 2);

    //If tile is in hand, call place Tile
    for (int i = 0; i < currentPlayer->getHand().getSize(); i++)
    {
      Tile *tileObj = currentPlayer->getHand().getTileAt(i);
      if (tileObj->toString2() == tile)
      {
        valid = true;
        index = i;
        //Early Termination
        i = currentPlayer->getHand().getSize();
      }
    }
    if (valid)
    {
      std::string location = action.substr(12, 14);

      placeTile(tile, location, index);
      alternateTurns();
    }
    else
    {
      std::cout << "You don't have that tile" << std::endl;
      readInCommand();
    }
  }
  else if (action.substr(0, 4) == "help")
  {
    help();
  }
  else if (action.substr(0, 4) == "save")
  {
    std::string filename = action.substr(5);
    saveGame(filename);
  }
  else
  {
    std::cout << "Unrecognised command" << std::endl;
    std::getline(std::cin, action);
    executeCommand(action);
  }
}

//Passes in the coordinate of the tile being placed
//Checks if there are tiles surrounding it
bool GameEngine::checkSurround(int letter, int number)
{
  bool left = false;
  bool up = false;
  bool right = false;
  bool down = false;
  bool retVal;
  //Check left
  if (number - 1 >= 0)
  {
    if (board[letter][number - 1] != 0)
    {
      if (countTiles(letter, number - 1, 0) < 6)
      {
        left = true;
      }
    }
  }
  //Check right
  if (number + 1 <= 25)
  {
    if (board[letter][number + 1] != 0)
    {
      if (countTiles(letter, number + 1, 2) < 6)
      {
        right = true;
      }
    }
  }
  //Check down
  if (letter + 1 <= 25)
  {
    if (board[letter + 1][number] != 0)
    {
      if (countTiles(letter + 1, number, 3) < 6)
      {
        down = true;
      }
    }
  }
  //Check up
  if (letter - 1 >= 0)
  {
    if (board[letter - 1][number] != 0)
    {
      if (countTiles(letter + 1, number, 1) < 6)
      {
        up = true;
      }
    }
  }
  if (right || left || up || down)
  {
    retVal = true;
  }
  else
  {
    retVal = false;
  }
  return retVal;
}

int GameEngine::countTiles(int letter, int number, int direction)
{
  int numTiles = 0;
  if (direction == 0)
  {
    //Count left
    for (int i = 0; i < 6; i++)
    {
      if (number - i >= 0)
      {
        if (board[letter][number - i] != 0)
        {
          numTiles++;
        }
      }
    }
  }
  else if (direction == 1)
  {
    //Count up
    for (int i = 0; i < 6; i++)
    {
      if (letter - i >= 0)
      {
        if (board[letter - i][number] != 0)
        {
          numTiles++;
        }
      }
    }
  }
  else if (direction == 2)
  {
    //Count right
    for (int i = 0; i < 6; i++)
    {
      if (number + i >= 0)
      {
        if (board[letter][number + i] != 0)
        {
          numTiles++;
        }
      }
    }
  }
  else
  {
    //Count down
    for (int i = 0; i < 6; i++)
    {
      if (letter + i >= 0)
      {
        if (board[letter + i][number] != 0)
        {
          numTiles++;
        }
      }
    }
  }
  return numTiles;
}

// HIGHSCORE FUNCTIONALITY
void GameEngine::printHighScores()
{
  std::string filename = "highscore.txt";
  std::ifstream in;
  in.open(filename);

  if (in.fail())
  {
    std::cout << "No highscores yet" << std::endl;
  }
  else
  {
    std::string line;
    while (std::getline(in, line))
    {
      std::cout << line << std::endl;
    }
  }
}

void GameEngine::saveHighScores()
{
  // Loads players from highscore file to a vector
  std::string filename = "highscore.txt";
  std::ifstream in;
  in.open(filename);

  std::vector<Player *> players;
  std::string line;
  while (std::getline(in, line))
  {
    // String stream to break up playerName from playerScore
    std::istringstream lineStream(line);

    std::string playerName;
    std::getline(lineStream, playerName, ',');

    std::string playerScoreString;
    std::getline(lineStream, playerScoreString, ',');
    int playerScore = std::stoi(playerScoreString);

    Player *playerPtr = new Player(playerName);
    playerPtr->addPoints(playerScore);
    // Vector has player in order from largest points to smallest points
    players.push_back(playerPtr);
  }
  in.close();

  // Compares the players currently in play with the players on the leader board
  for (int i = 0; i < 2; i++)
  {
    unsigned int j = 0;
    int insertAt = players.size();
    bool endLoop = false;
    while (j < players.size() && !endLoop)
    {
      if (players[j]->getScore() < playerArray[i]->getScore())
      {
        insertAt = j;
        endLoop = true;
      }
      j++;
    }
    players.insert(players.begin() + insertAt, playerArray[i]);
  }

  // Prints  out the top 5 highscores, leaving off player whose scores are less
  // than the top 5
  std::ofstream out;
  out.open(filename);
  for (unsigned int i = 0; i < players.size() && i < 5; i++)
  {
    out << players[i]->getName() << "," << players[i]->getScore() << std::endl;
  }
  out.close();

  // Deallocating memory
  for (unsigned int i = 0; i < players.size(); i++)
  {
    delete players[i];
  }
}

int GameEngine::countPoints(int letter, int number){
  int linesAffected = 0;
  int pointsScored = 0;
  int leftCount = countTiles(letter, number, 0);
  int rightCount = countTiles(letter, number, 2);
  int upCount = countTiles(letter, number, 1);
  int downCount = countTiles(letter, number, 3);

  int check [] = {leftCount, rightCount, upCount, downCount};

  for(int surrTiles : check){
    if(surrTiles > 0){
      linesAffected++;
      pointsScored++;
      pointsScored+=surrTiles;
      //qwirkle check
      if(surrTiles == 5){
        pointsScored += 6;
      }
    }
  }
  return pointsScored;
}

void GameEngine::help()
{
  std::cout << "Qwirkle Game version 1.0- release Help Guide\n"
            << "List of functions the user can call on the Qwirkle game\n\n"
            << "help\n"
            << "Displays all the possible commands that can be called by the user on the Qwirkle game.\n\n"
            << "place <tile> at <grid location>\n"
            << "Adds tile to the specified location if both tile and location are legal arguments and represents a placement of a tile that is legal according to the rules of Qwirkle.\n\n"
            << "replace <tile>\n"
            << "Replaces the specified tile in the player's hand into the bag and the player draws one new tile from the bag.\n\n"
            << "save <filename>\n"
            << "Saves the current state of the game in an output file with the name the user specified.\n\n"
            << "Tile Syntax of Tile is Colours+Shapes (Tile codes defined below)\n"
            << "RED 'R', ORANGE 'O', YELLOW 'Y', GREEN  'G', BLUE   'B', PURPLE 'P'\n"
            << "CIRCLE  1, STAR_4  2, DIAMOND  3, SQUARE  4, STAR_6  5, CLOVER  6\n";
}
