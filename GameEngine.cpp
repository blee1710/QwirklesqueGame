#include "GameEngine.h"
#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <vector>
#include <map>
#include <sstream>

GameEngine::GameEngine()
{
  numPlayers = INITIAL_NUM_PLAYERS;
  turn = INITIAL_TURN_COUNT;

  for (int row = 0; row < BOARD_SIZE; row++)
  {
    for (int col = 0; col < BOARD_SIZE; col++)
    {
      board[row][col] = nullptr;
    }
  }
}

GameEngine::~GameEngine()
{
  for (int row = 0; row < BOARD_SIZE; row++)
  {
    for (int col = 0; col < BOARD_SIZE; col++)
    {
      delete board[row][col];
    }
  }

  for (unsigned int i = 0; i < playerArray.size(); i++)
  {
    delete playerArray[i];
  }
}

void GameEngine::saveGame(std::string filename)
{
  std::ofstream outFile;
  outFile.open(filename);

  outFile << turn << std::endl;
  outFile << numPlayers << std::endl;
  for (unsigned int i = 0; i < playerArray.size(); i++)
  {
    if (playerArray[i]->getName() == "AI")
    {
      outFile << "$AI" << std::endl;
    }
    else
      outFile << playerArray[i]->getName() << std::endl;
    outFile << playerArray[i]->getScore() << std::endl;
    outFile << playerArray[i]->getHand().toString2() << std::endl;
  }

  // Writing out board to file
  outFile << "   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 20"
          << " 21 22 23 24 25" << std::endl;
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
      if (board[i][j] != NULL_TILE)
      {
        outFile << board[i][j]->toString2() << "|";
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
  std::ifstream in;
  in.open(filename);

  std::string numTurns;
  std::getline(in, numTurns);
  turn = stoi(numTurns);

  std::string noPlayersString;
  std::getline(in, noPlayersString);
  int noPlayers = stoi(noPlayersString);

  // Reading player 1 and 2 data from file.
  // Loop runs twice to load in data for each player
  for (int i = 0; i < noPlayers; i++)
  {
    std::string playerName;
    std::getline(in, playerName);
    if (playerName == "$AI")
    {
      addPlayer("AI");
      isSinglePlayer = true;
    }
    else
      addPlayer(playerName);

    std::string playerScoreString;
    std::getline(in, playerScoreString);
    int playerScore = std::stoi(playerScoreString);
    playerArray.at(i)->addPoints(playerScore);

    std::string playerHand;
    std::getline(in, playerHand);
    // while loop to add all tiles in the string to player hand.
    std::istringstream playerHandStream(playerHand);
    std::string tile;
    while (std::getline(playerHandStream, tile, ','))
    {
      char colour = tile.at(0);
      int shape = stoi(tile.substr(1));
      playerArray.at(i)->drawTile(new Tile(colour, shape));
    }
  }

  // Reading board state from file.
  std::string boardRow;
  // Skips over first two lines that contain no useful information.
  std::getline(in, boardRow);
  std::getline(in, boardRow);
  // Loop runs for the number of rows of the board
  for (int i = 0; i < BOARD_SIZE; i++)
  {
    std::getline(in, boardRow);
    // Begins scanning the single row, checking if each 'space' is empty.
    // 'k' value used for keeping track of the currnt column (x value) the
    // program is at. Current row (y value) is 'i'.
    int k = 0;
    for (unsigned int j = 3; j < boardRow.length() - 1; j += 3)
    {
      if (boardRow.at(j) != ' ')
      {
        char colour = boardRow.at(j);
        int shape = stoi(boardRow.substr(j + 1));
        loadPlaceTile(k, i, new Tile(colour, shape));
      }
      k++;
    }
  }

  // Reading the tile bag form file
  std::string tileBagString;
  std::getline(in, tileBagString);
  // while loop to add all tiles in the string to tile bag
  std::istringstream tileBagStream(tileBagString);
  std::string tile;
  while (std::getline(tileBagStream, tile, ','))
  {
    char colour = tile.at(0);
    int shape = stoi(tile.substr(1));
    tileBag.addBack(new Tile(colour, shape));
  }

  // Reading the current player from file
  std::string currentPlayerString;
  std::getline(in, currentPlayerString);
  for (unsigned int i = 0; i < playerArray.size(); i++)
  {
    if (currentPlayerString == playerArray[i]->getName())
    {
      currentPlayer = playerArray[i];
      currentTurn = i;
    }
  }
  in.close();
}

// places tile when loading a game without checking the game rules
void GameEngine::loadPlaceTile(int x, int y, Tile *tile)
{
  board[y][x] = tile;
  tilesPlaced++;
}

int GameEngine::getNumPlayers()
{
  return numPlayers;
}

void GameEngine::addPlayer(std::string name)
{
  playerArray.push_back(new Player(name));
  std::cout << "Player created" << std::endl;
  //playerArray[numPlayers] = new Player(name);
  numPlayers++;
}

bool GameEngine::placeTile(std::string tile, std::string location, int index)
{
  //String manipulation to access letter and number as ints
  std::string lstring = location.substr(0, 1);
  char *lchar = &lstring[0u];
  int letter = letterToNumber(*lchar);
  int number = std::stoi(location.substr(1, 2));
  bool retVal;

  Tile *tileObj = currentPlayer->getHandPtr()->getTileAt(index);
  if (turn == INITIAL_TURN_COUNT)
  {
    currentPlayer->getHandPtr()->deleteAt(index);
    if (tileBag.getSize() > 0)
    {
      currentPlayer->drawTile(tileBag.getTileAt(0));
      tileBag.deleteFront();
    }
    board[letter][number] = tileObj;
    currentPlayer->addPoints(countPoints(letter, number));
    retVal = true;
  }
  else
  {
    if (board[letter][number] != NULL_TILE)
    {
      std::cout << "There's already a tile there!" << std::endl;
      retVal = false;
    }
    else
    {
      if (checkSurround(tileObj, letter, number))
      {
        currentPlayer->getHandPtr()->deleteAt(index);
        if (tileBag.getSize() > 0)
        {
          currentPlayer->drawTile(tileBag.getTileAt(0));
          tileBag.deleteFront();
        }
        board[letter][number] = tileObj;
        currentPlayer->addPoints(countPoints(letter, number));
        retVal = true;
      }
      else
      {
        std::cout << "You can't place a tile there" << std::endl;
        retVal = false;
      }
    }
  }
  return retVal;
}

bool GameEngine::replaceTile(int index)
{
  bool replaced = false;
  if (tileBag.getSize() > 0)
  {
    Tile *tileObj = currentPlayer->getHandPtr()->getTileAt(index);
    currentPlayer->getHandPtr()->deleteAt(index);
    tileBag.addBack(tileObj);
    // NOT DRAWING PROPERLY
    currentPlayer->drawTile(tileBag.getTileAt(0));
    tileBag.deleteFront();
    replaced = true;
  }
  else
  {
    std::cout << "No tiles in the bag to replace with" << std::endl;
  }
  return replaced;
}

//Function for converting A to 0, B to 1 etc.
int GameEngine::letterToNumber(char letter)
{
  int number = letter - 65;
  return number;
}

//Function for converting A to 0, B to 1 etc.
char GameEngine::numberToLetter(int number)
{
  char letter = number + 65;
  return letter;
}

//All players populate their hands
void GameEngine::drawInitialTiles()
{
  if (playerArray.size() == 1)
  {
    this->addPlayer("AI");
    isSinglePlayer = true;
  }
  for (Player *p : playerArray)
  {
    for (int i = 0; i < MAX_HAND_SIZE; i++)
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
  while (!gameEndCheck())
  {
    if (!isSinglePlayer || currentTurn % 2 == 0)
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
    else
    {
      std::cout << currentPlayer->getName() << ", it's your turn" << std::endl;
      for (int i = 0; i < numPlayers; i++)
      {
        std::cout << "Score for " << playerArray[i]->getName() << ": " << playerArray[i]->getScore() << std::endl;
      }
      printBoard();
      currentPlayer->printTiles();
      aiMove();
    }
  }
  printBoard();
  std::cout << "Game Over" << std::endl;
  int highestScore = 0;
  std::string winner;
  bool draw = false;
  for (Player *player : playerArray)
  {
    int endScore = player->getScore();
    if (endScore > highestScore)
    {
      highestScore = endScore;
      winner = player->getName();
    }
    else if (endScore == highestScore)
    {
      draw = true;
      winner += player->getName() + ' ';
    }
    std::cout << "Score for " << player->getName() << ": " << player->getScore() << std::endl;
  }

  if (draw)
  {
    std::cout << "Players " << winner << "drew!" << '\n';
  }
  else
  {
    std::cout << "Player " << winner << "won!" << '\n';
  }
}

void GameEngine::readInCommand()
{
  std::string action;
  std::cout << "> ";
  //Eat the line if necessary
  std::getline(std::cin, action);
  if (action == "")
  {
    std::getline(std::cin, action);
  }

  if (!executeCommand(action))
  {
    readInCommand();
  }
}

void GameEngine::alternateTurns()
{
  if ((unsigned)currentTurn == playerArray.size() - 1)
  {
    currentTurn = INITIAL_TURN_COUNT;
    turn++;
  }
  else
  {
    currentTurn++;
    turn++;
  }

  currentPlayer = playerArray[currentTurn];
}

void GameEngine::printBoard()
{
  std::cout << "   0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15 16 17 18 19 "
            << "20 21 22 23 24 25" << std::endl;
  std::cout << "---------------------------------------------------------------"
            << "------------------" << std::endl;
  //Print all 26 rows

  for (int i = 0; i < BOARD_SIZE; i++)
  {
    char letter = numberToLetter(i);
    std::cout << letter << " ";
    for (int j = 0; j < BOARD_SIZE; j++)
    {
      if (board[i][j] != NULL_TILE)
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

//Creates a linked list of tiles, populates the list with all the tiles of a qwirkle game
//and then randomly moves the tiles to the back of the list but ensuring that every tile
//is moved and moved to the back only once
void GameEngine::makeBag()
{
  std::random_device engine;
  std::map<int, char> colourMap = {{0, RED}, {1, ORANGE}, {2, YELLOW}, {3, GREEN}, {4, BLUE}, {5, PURPLE}};
  std::map<int, int> shapeMap = {{0, CIRCLE}, {1, STAR_4}, {2, DIAMOND}, {3, SQUARE}, {4, STAR_6}, {5, CLOVER}};
  for (unsigned int x = 0; x < colourMap.size(); x++)
  {
    for (unsigned int y = 0; y < shapeMap.size(); y++)
    {
      for (unsigned int z = 0; z < NO_OF_EACH_TILE; z++)
      {
        tileBag.addBack(new Tile(colourMap[x], shapeMap[y]));
      }
    }
  }
  int index = 0;
  for (int i = 0; i < MAX_NO_OF_TILE; i++)
  {
    std::uniform_int_distribution<int> uniform_dist(0, MAX_NO_OF_TILE - 1 - i);
    index = uniform_dist(engine);
    tileBag.addBack(new Tile(*(tileBag.getTileAt(index))));
    tileBag.deleteAt(index);
  }
}

bool GameEngine::executeCommand(std::string action)
{
  bool retVal = true;
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

      bool placeCheck = placeTile(tile, location, index);
      if (placeCheck)
      {
        tilesPlaced += 1;
        alternateTurns();
      }
    }
    else
    {
      std::cout << "You don't have that tile" << std::endl;
      retVal = false;
    }
  }
  else if (action.substr(0, 7) == "replace")
  {
    std::string tile = action.substr(8, 2);
    //bit of code duplication here
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
      bool replaceCheck = replaceTile(index);
      if (replaceCheck)
      {
        alternateTurns();
      }
    }
    else
    {
      std::cout << "You don't have that tile" << std::endl;
      retVal = false;
    }
  }
  else if (action.substr(0, 4) == "help")
  {
    help();
  }
  else if (action.substr(0, 4) == "hint")
  {
    giveHint();
  }
  else if (action.substr(0, 4) == "save")
  {
    std::string filename = action.substr(5);
    saveGame(filename);
  }
  else
  {
    std::cout << "Unrecognised command" << std::endl;
    retVal = false;
  }

  return retVal;
}

//Passes in the coordinate of the tile being placed
//Checks if there are tiles surrounding it
bool GameEngine::checkSurround(Tile *tile, int letter, int number)
{
  //Check if each direction is "valid".
  bool left = false;
  bool up = false;
  bool right = false;
  bool down = false;
  //Boolean to see whether or not a piece exists in that direction.
  bool leftExists = false;
  bool upExists = false;
  bool rightExists = false;
  bool downExists = false;
  //Boolean to check for the case where directional opposites both pass onetileCheck.
  //Need to ensure the same rules is applied in the entire column/row.
  bool leftOne = false;
  bool rightOne = false;
  bool downOne = false;
  bool upOne = false;

  bool retVal;
  int tileCount = 1;

  //Check left
  if (number - 1 >= 0)
  {
    //If there is a tile to the left of where we are placing the tile
    if (board[letter][number - 1] != NULL_TILE)
    {
      leftExists = true;
    }
  }
  //Check right
  if (number + 1 <= 25)
  {
    if (board[letter][number + 1] != NULL_TILE)
    {
      rightExists = true;
    }
  }
  //Check down
  if (letter + 1 <= 25)
  {
    if (board[letter + 1][number] != NULL_TILE)
    {
      downExists = true;
    }
  }
  //Check up
  if (letter - 1 >= 0)
  {
    if (board[letter - 1][number] != NULL_TILE)
    {
      upExists = true;
    }
  }
  //if there is at least one tile that exists
  if (rightExists || leftExists || upExists || downExists)
  {
    if (leftExists)
    {
      //If theres less than 6 tiles in the row
      tileCount = countTiles(letter, number, LEFT);
      if (tileCount < 6)
      {
        //If there is only one tile, then a rule hasn't been defined yet for that row
        if (tileCount == 1)
        {
          left = oneTileCheck(tile, letter, number, LEFT);
        }
        else
        {
          left = manyTileCheck(tile, tileCount, letter, number, LEFT);
        }
        leftOne = true;
      }
      else
      {
        std::cout << "Exceeding 6 tiles!" << std::endl;
      }
    }
    else
    {
      //If it doesn't exist then it's also true
      left = true;
    }
    if (rightExists)
    {
      //If theres less than 6 tiles in the row
      tileCount = countTiles(letter, number, RIGHT);
      if (tileCount < 6)
      {
        //If there is only one tile, then a rule hasn't been defined yet for that row
        if (tileCount == 1)
        {
          right = oneTileCheck(tile, letter, number, RIGHT);
        }
        else
        {
          right = manyTileCheck(tile, tileCount, letter, number, RIGHT);
        }
        rightOne = true;
      }
      else
      {
        std::cout << "Exceeding 6 tiles!" << std::endl;
      }
    }
    else
    {
      //If it doesn't exist then it's also true
      right = true;
    }
    if (upExists)
    {
      //If theres less than 6 tiles in the row
      tileCount = countTiles(letter, number, UP);
      if (tileCount < 6)
      {
        //If there is only one tile, then a rule hasn't been defined yet for that row
        if (tileCount == 1)
        {
          up = oneTileCheck(tile, letter, number, UP);
        }
        else
        {
          up = manyTileCheck(tile, tileCount, letter, number, UP);
        }
        upOne = true;
      }
      else
      {
        std::cout << "Exceeding 6 tiles!" << std::endl;
      }
    }
    else
    {
      //If it doesn't exist then it's also true
      up = true;
    }
    if (downExists)
    {
      //If theres less than 6 tiles in the row
      tileCount = countTiles(letter, number, DOWN);
      if (tileCount < 6)
      {
        //If there is only one tile, then a rule hasn't been defined yet for that row
        if (tileCount == 1)
        {
          down = oneTileCheck(tile, letter, number, DOWN);
        }
        else
        {
          down = manyTileCheck(tile, tileCount, letter, number, DOWN);
        }
        downOne = true;
      }
      else
      {
        std::cout << "Exceeding 6 tiles!" << std::endl;
      }
    }
    else
    {
      //If it doesn't exist then it's also true
      down = true;
    }
  }
  else
  {
    std::cout << "Must place next to a preexisting tile!" << std::endl;
    retVal = false;
  }

  if (left && up && right && down)
  {
    if (leftOne && rightOne)
    {
      retVal = checkTiles(tile, letter, number, LEFT);
    }
    else if (downOne && upOne)
    {
      retVal = checkTiles(tile, letter, number, UP);
    }
    else
    {
      retVal = true;
    }
  }
  else
  {
    retVal = false;
  }

  return retVal;
}

//Doesn't count the tile passed in, only the ones next to it
int GameEngine::countTiles(int letter, int number, int direction)
{
  int numTiles = 0;
  int l;
  int n;
  setLN(l, n, direction);
  for (int i = 1; i <= 6; i++)
  {
    //qwirle error
    int vert = letter + i * l;
    int hori = number + i * n;

    if (vert >= 0 && hori >= 0)
    {
      if (board[vert][hori] != NULL_TILE)
      {
        numTiles++;
      }
      else
      {
        //Early Termination
        i = 6;
      }
    }
  }
  return numTiles;
}

//Checks 3 tiles to see if they have matching rules. Returns true if passes test.
bool GameEngine::checkTiles(Tile *tile, int letter, int number, int axis)
{
  int l;
  int n;
  bool retVal;
  //Let axis 0 be horizontal
  setLN(l, n, axis);
  Tile *tile1 = tile;
  Tile *tile2 = board[letter + l][number + n];
  Tile *tile3 = board[letter - l][number - n];

  //Colour matches between all three
  if (tile1->getColour() == tile2->getColour())
  {
    if (tile3->getColour() == tile1->getColour())
    {
      retVal = true;
    }
    else
    {
      retVal = false;
    }
  }
  //Shape matches between all three
  else if (tile1->getShape() == tile2->getShape())
  {
    if (tile3->getShape() == tile1->getShape())
    {
      retVal = true;
    }
    else
    {
      retVal = false;
    }
  }
  else
  {
    retVal = false;
  }
  return retVal;
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
    players.clear();
}

//Pass in the position of the tile being placed
int GameEngine::countPoints(int letter, int number)
{
  //Count the tiles surrounding it
  int points = 0;
  if (turn == INITIAL_TURN_COUNT)
  {
    points++;
  }
  int array[4];
  array[0] = countTiles(letter, number, 0);
  array[1] = countTiles(letter, number, 1);
  array[2] = countTiles(letter, number, 2);
  array[3] = countTiles(letter, number, 3);

  for (int i = 0; i < 4; i++)
  {
    if (array[i] == 5)
    {
      std::cout << "QWIRKLE!" << std::endl;
      array[i] = 11;
    }
  }

  for (int score : array)
  {
    if (score > 0)
    {
      points++;
    }
    points += score;
  }

  return points;
}

//Help Function prints the the possible commands that can be called by the user on the Qwirkle game
void GameEngine::help()
{
  std::cout << "Qwirkle Game version 1.0- release Help Guide\n"
            << "List of functions the user can call on the Qwirkle game\n\n"
            << "help\n"
            << "Displays all the possible commands that can be called by the user on the Qwirkle game.\n\n"
            << "hint\n"
            << "Gives a hint as to where the current player can place the current tiles in their hand onto the board\n\n"
            << "place <tile> at <grid location>\n"
            << "Adds tile to the specified location if both tile and location are legal arguments and represents a placement of a tile that is legal according to the rules of Qwirkle.\n\n"
            << "replace <tile>\n"
            << "Replaces the specified tile in the player's hand into the bag and the player draws one new tile from the bag.\n\n"
            << "save <filename>\n"
            << "Saves the current state of the game in an output file with the name the user specified.\n\n"
            << "quit\n"
            << "Quits the current game of Qwirkle.\n\n"
            << "Tile Syntax of Tile is Colours+Shapes (Tile codes defined below)\n"
            << "\033[31mRED 'R'\033[0m, \033[91mORANGE 'O'\033[0m, \033[33mYELLOW 'Y'\033[0m, \033[32mGREEN  'G'\033[0m, \033[34mBLUE   'B'\033[0m, \033[35mPURPLE 'P'\033[0m\n"
            << "CIRCLE (\U000025CB)  1, STAR_4 (\U00002B51)  2, DIAMOND (\U000025CA)  3, SQUARE (\U000025A1)  4, STAR_6 (\U00002734)  5, CLOVER (\U00002663)  6\n";
}

bool GameEngine::oneTileCheck(Tile *tile, int letter, int number, int direction)
{
  int l;
  int n;
  bool retVal = false;
  setLN(l, n, direction);
  //If not a duplicate, check if either colour or shape match
  if (!checkDuplicate(tile, letter + l, number + n))
  {
    bool colourMatch = false;
    bool shapeMatch = false;
    if (tile->getColour() == board[letter + l][number + n]->getColour())
    {
      colourMatch = true;
    }
    else if (tile->getShape() == board[letter + l][number + n]->getShape())
    {
      shapeMatch = true;
    }
    if (colourMatch || shapeMatch)
    {
      retVal = true;
    }
    else
    {
      std::cout << "Colour or shape must match " << board[letter + l][number + n]->toString2() << std::endl;
      retVal = false;
    }
  }
  if (checkPriorDuplicate(letter, number))
  {
    retVal = false;
  }
  return retVal;
}

bool GameEngine::manyTileCheck(Tile *tile, int tileCount, int letter, int number, int direction)
{
  bool duplicates = false;
  bool retVal = false;
  int l;
  int n;
  setLN(l, n, direction);
  //Checks if there are duplicates in the row
  //Check for each tile in the direction.
  for (int i = 1; i <= tileCount; i++)
  {
    //Check if no duplicates
    if (checkDuplicate(tile, letter + l * i, number + n * i))
    {
      duplicates = true;
      //Terminate checking as soon as there is one duplicate
      i = tileCount;
    }
    else
    {
      duplicates = false;
    }
  }
  if (!duplicates)
  {
    //Determines rule
    Colour first = board[letter + l][number + n]->getColour();
    Colour second = board[letter + (2 * l)][number + (2 * n)]->getColour();
    //If colour matches, then the rule is colour
    if (first == second)
    {
      if (tile->getColour() == first)
      {
        retVal = true;
      }
      else
      {
        std::cout << "Colour doesn't match" << std::endl;
      }
    }
    //Rule is shape
    else
    {
      if (tile->getShape() == board[letter + l][number + n]->getShape())
      {
        retVal = true;
      }
      else
      {
        std::cout << "Shape doesn't match" << std::endl;
      }
    }
  }
  if (checkPriorDuplicate(letter, number))
  {
    retVal = false;
  }
  return retVal;
}

//A direction is passed in, and the corresponding horizontal and
//vertical translation is set in the method using l and n.
void GameEngine::setLN(int &l, int &n, int direction)
{
  if (direction == LEFT)
  {
    l = 0;
    n = -1;
  }
  else if (direction == UP)
  {
    l = -1;
    n = 0;
  }
  else if (direction == RIGHT)
  {
    l = 0;
    n = 1;
  }
  else
  {
    l = 1;
    n = 0;
  }
}

//Test for duplicate tiles in rows/columns, returns TRUE if duplicate
bool GameEngine::checkDuplicate(Tile *tile, int letter, int number)
{
  //Assume that board[letter][number] is never null
  bool duplicate = false;

  if (tile->getColour() == board[letter][number]->getColour() &&
      tile->getShape() == board[letter][number]->getShape())
  {
    std::cout << "Duplicate tile detected!" << std::endl;
    std::cout << tile->toString2() << " already exists at "
              << numberToLetter(letter) << number << std::endl;
    duplicate = true;
  }

  return duplicate;
}

//Checks for prior duplicates if the tile being placed connects two preexisting rows/cols
//Returns true if prior duplicates exist
bool GameEngine::checkPriorDuplicate(int letter, int number)
{
  bool retVal = true;
  //There aren't duplicates
  bool noRowDupe = true;
  bool noColDupe = true;
  int leftCount;
  int rightCount;
  int upCount;
  int downCount;

  //Count the tiles relative to the current tile being placed
  leftCount = countTiles(letter, number, 0);
  rightCount = countTiles(letter, number, 2);
  upCount = countTiles(letter, number, 1);
  downCount = countTiles(letter, number, 3);

  //Only 2 cases are:
  //If left AND right exists, or if up AND down exists
  if (leftCount > 0 && rightCount > 0)
  {
    for (int left = 1; left <= leftCount; left++)
    {
      for (int right = 1; right <= rightCount; right++)
      {
        std::string leftTile = board[letter][number - left]->toString2();
        std::string rightTile = board[letter][number + right]->toString2();
        //If any of the leftTiles are the same as any of the rightTiles
        if (leftTile == rightTile)
        {
          //There is a row dupe
          noRowDupe = false;
          left = leftCount + 1;
          right = rightCount + 1;
        }
      }
    }
  }
  if (upCount > 0 && downCount > 0)
  {
    for (int up = 1; up <= upCount; up++)
    {
      for (int down = 1; down <= downCount; down++)
      {
        std::string upTile = board[letter - up][number]->toString2();
        std::string downTile = board[letter + down][number]->toString2();
        //If any of the upTiles are the same as any of the downTiles
        if (upTile == downTile)
        {
          //There is a column dupe
          noColDupe = false;
          up = upCount + 1;
          down = downCount + 1;
        }
      }
    }
  }
  //If there is no row dupe and no column dupe retVal is true, as in no dupes
  if (noRowDupe && noColDupe)
  {
    retVal = false;
  }
  else
  {
    std::cout << "Placement would result in duplicates connecting" << std::endl;
  }

  return retVal;
}

//Generates the hints (Posible tile placement) and returns it as a vector of locationAndScore structs
std::vector<GameEngine::locationAndScore> GameEngine::generateHints()
{
  std::vector<GameEngine::locationAndScore> hints;
  std::vector<GameEngine::location> possiblePlacement;
  std::cout.setstate(std::ios_base::failbit);

  for (int j = 0; j < BOARD_SIZE; j++)
  {
    for (int i = 0; i < BOARD_SIZE; i++)
    {
      if (board[i][j] == NULL_TILE)
      {
        if (checkAroundLocation(i, j))
        {
          struct location newLocation = {i, j};
          possiblePlacement.push_back(newLocation);
        }
      }
    }
  }
  for (int x = 0; x < currentPlayer->getHandPtr()->getSize(); x++)
  {
    for (unsigned int y = 0; y < possiblePlacement.size(); y++)
    {
      if (checkSurround(currentPlayer->getHandPtr()->getTileAt(x), possiblePlacement.at(y).letter, possiblePlacement.at(y).number))
      {
        struct locationAndScore newHint = {possiblePlacement.at(y).letter, possiblePlacement.at(y).number, countPoints(possiblePlacement.at(y).letter, possiblePlacement.at(y).number), currentPlayer->getHandPtr()->getTileAt(x)};
        hints.push_back(newHint);
      }
    }
  }
  std::cout.clear();
  return hints;
}

//Generates and Prints out a signle hint to the current player at to where they could place one of their tiles
//if there are no legal tile placements the hint function advise the player to replace a tile
void GameEngine::giveHint()
{
  if (tilesPlaced == 0)
  {
    std::cout << "Board is empty so you can place your tile anywhere!" << std::endl;
  }
  else if (GameEngine::generateHints().empty())
  {
    std::cout << "You cannot place a tile. You need to replace a tile." << std::endl;
  }
  else
  {
    std::vector<GameEngine::locationAndScore> hints = GameEngine::generateHints();
    std::random_device engine;
    std::uniform_int_distribution<int> uniform_dist(0, hints.size() - 1);
    int randomIndex = uniform_dist(engine);
    std::cout << "Place Tile: " << hints.at(randomIndex).tile->getColour() << hints.at(randomIndex).tile->getShape()
              << " at " << numberToLetter(hints.at(randomIndex).letter) << hints.at(randomIndex).number << " Which gives you " << hints.at(randomIndex).score << " points." << std::endl;
  }
}

bool GameEngine::gameEndCheck()
{
  bool end = false;
  // checks tile and hand count
  for (Player *p : playerArray)
  {
    if (p->getHandPtr()->getSize() == 0 && tileBag.getSize() == 0)
    {
      end = true;
    }
  }

  return end;
}

//Contains the logic of moving an AI by generating hints (possible) tiles placements, reducing that to placements
//that generate the most score and randomly choosing the placement from that list and then executing the commands
//to place otherwise if no hints are generate the AI replaces its first tile in its hand.
void GameEngine::aiMove()
{

  bool placeAITile = true;

  if (GameEngine::generateHints().empty())
  {
    replaceTile(0);
    placeAITile = false;
  }

  if (placeAITile)
  {
    std::vector<GameEngine::locationAndScore> hints = GameEngine::generateHints();
    int largestScore = hints.at(0).score;
    std::vector<locationAndScore> maxHints;
    for (unsigned int i = 1; i < hints.size(); i++)
    {
      if (hints.at(i).score > largestScore)
      {
        largestScore = hints.at(i).score;
      }
    }
    for (unsigned int i = 0; i < hints.size(); i++)
    {
      if (hints.at(i).score == largestScore)
      {
        maxHints.push_back(hints.at(i));
      }
    }

    std::random_device engine;
    std::uniform_int_distribution<int> uniform_dist(0, maxHints.size() - 1);
    int randomIndex = uniform_dist(engine);

    std::string location = numberToLetter(maxHints.at(randomIndex).letter) + std::to_string(maxHints.at(randomIndex).number);
    std::string tile = maxHints.at(randomIndex).tile->toString2();
    //If tile is in hand, call place Tile
    int index = 0;
    for (int i = 0; i < currentPlayer->getHand().getSize(); i++)
    {
      Tile *tileObj = currentPlayer->getHand().getTileAt(i);
      if (tileObj->toString2() == tile)
      {
        index = i;
        //Early Termination
        i = currentPlayer->getHand().getSize();
      }
    }
    std::cout << "The AI has placed " << tile << " at " << location << std::endl;
    placeTile(tile, location, index);
    tilesPlaced++;
  }
  alternateTurns();
}

//Checks around a location to check for a tile
bool GameEngine::checkAroundLocation(int letter, int number)
{
  bool leftExists = false;
  bool upExists = false;
  bool rightExists = false;
  bool downExists = false;
  bool retVal = false;

  //Check left
  if (number - 1 >= 0)
  {
    //If there is a tile to the left of where we are placing the tile
    if (board[letter][number - 1] != NULL_TILE)
    {
      leftExists = true;
    }
  }
  //Check right
  if (number + 1 <= 25)
  {
    if (board[letter][number + 1] != NULL_TILE)
    {
      rightExists = true;
    }
  }
  //Check down
  if (letter + 1 <= 25)
  {
    if (board[letter + 1][number] != NULL_TILE)
    {
      downExists = true;
    }
  }
  //Check up
  if (letter - 1 >= 0)
  {
    if (board[letter - 1][number] != NULL_TILE)
    {
      upExists = true;
    }
  }

  if (rightExists || leftExists || upExists || downExists)
  {
    retVal = true;
  }
  return retVal;
}
