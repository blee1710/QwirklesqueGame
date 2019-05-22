#include "GameEngine.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#define EXIT_SUCCESS            0

#define REQUIRED_ARGS           1
#define NO_OF_SKIPPED_LINES    32
#define NUM_PLAYER_LINES        3

//Functions
void menu();
void newGame();
void loadGame();
void showStudentInfo();
void newSinglePlayerGame();
void quit();
GameEngine* ge;

bool checkArgs(int argc, char** argv);
bool checkFile(std::string &filename);
void executeCommands(char** argv);
bool isNameUpper(std::string name);

int main(int argc, char** argv)
{
   ge = new GameEngine();
   bool startUnitTest = false;

   startUnitTest = checkArgs(argc, argv);

   if (startUnitTest) {
     executeCommands(argv);
   }
   else {
     std::cout << "Welcome to Qwirkle" << std::endl;
     std::cout << "------------------" << std::endl;
     menu();
   }

   delete ge;
   return EXIT_SUCCESS;
}

void menu()
{
   int command;
   std::cout << "Menu" << std::endl;
   std::cout << "----" << std::endl;
   std::cout << "1. New Game" << std::endl;
   std::cout << "2. New Game (Single Player)" << std::endl;
   std::cout << "3. Load Game" << std::endl;
   std::cout << "4. Display Highscores" << std::endl;
   std::cout << "5. Show student information" << std::endl;
   std::cout << "6. Quit" << std::endl;

   std::cin >> command;
   std::cout<<std::endl;
   if (command == 1)
   {
      newGame();
   }
   else if (command == 2)
   {
      newSinglePlayerGame();
   }
   else if (command == 3)
   {
      loadGame();
   }
   else if (command == 4)
   {
     ge->printHighScores();
   }
   else if (command == 5)
   {
      showStudentInfo();
   }
   else
   {
      std::cout<<"Goodbye!"<<std::endl;
      quit();
   }
}



void newGame()
{
   std::string playerName;
   std::string playerCount;
   bool valid = false;
   int playerAmount;
   std::cout << "Starting a New Game\n"<< std::endl;

   while(!valid) {
     std::cout << "Please enter amount of players (2-4)" << std::endl
               << "> ";
     std::cin >> playerCount;
     playerAmount = std::stoi(playerCount);
     if(playerAmount > 0 && playerAmount <= 4){
       valid = true;
     }
   }


   for(int i = 0; i < playerAmount; i++){
     valid = false;
     while(!valid){
       std::cout << "Enter a name for player " << std::to_string(i+1)
                 << " (uppercase characters only)" << std::endl << "> ";
       std::cin >> playerName;
       std::cin.ignore(256, '\n');
       valid = isNameUpper(playerName);
     }
     ge->addPlayer(playerName);
   }

   //Add random tiles to tileBag with Danny's random tile generation method.
   ge->makeBag();
   //Draw 6 tiles into each player's hands
   ge->drawInitialTiles();
   //Start with player 1 then keep Alternating between player's turns until game ends.
   ge->mainLoop();
   ge->saveHighScores();
   quit();
   //ending sequence
   // quit function

}

void newSinglePlayerGame(){
  std::string playerName;
  std::cout << "Starting a New Game\n"<< std::endl;

  bool valid = false;
  while(!valid){
    std::cout << "Enter a name for player 1 (uppercase characters only)"
              << std::endl << "> ";
    std::cin >> playerName;
    std::cin.ignore(256, '\n');
    valid = isNameUpper(playerName);
  }

  ge->addPlayer(playerName);
  //Add random tiles to tileBag with Danny's random tile generation method.
  ge->makeBag();
  //Draw 6 tiles into each player's hands
  ge->drawInitialTiles();
  //Start with player 1 then keep Alternating between player's turns until game ends.
  ge->mainLoop();

  ge->saveHighScores();

  quit();
}

void loadGame()
{
  bool valid = false;
  std::string filename;
  
  while(!valid){
     std::cout << "Enter the filename to load a game" << std::endl
               << "> ";
     std::cin >> filename;
     std::ifstream in;
     in.open(filename);

     if(in.fail()){
       std::cout << "Please enter a correct load filename" << std::endl;
     } else{
       valid = true;
     }
     in.close();

  }

   ge->loadGame(filename);
   ge->mainLoop();
   ge->saveHighScores();
}

void showStudentInfo()
{
   std::cout<<"------------------------------"<<std::endl;
   std::cout<<"Name: Wesley Lee"<<std::endl;
   std::cout<<"Student ID: s3719843"<<std::endl;
   std::cout<<"Email: s3719843@student.rmit.edu.au"<<std::endl;
   std::cout<<"------------------------------"<<std::endl;
   std::cout<<"Name: Matthew Samuel"<<std::endl;
   std::cout<<"Student ID: s3717393"<<std::endl;
   std::cout<<"Email: s3717393@student.rmit.edu.au"<<std::endl;
   std::cout<<"------------------------------"<<std::endl;
   std::cout<<"Name: Brandon Lee"<<std::endl;
   std::cout<<"Student ID: s3707616"<<std::endl;
   std::cout<<"Email: s3707616@student.rmit.edu.au"<<std::endl;
   std::cout<<"------------------------------"<<std::endl;
   std::cout<<"Name: Danny Le"<<std::endl;
   std::cout<<"Student ID: s3722067"<<std::endl;
   std::cout<<"Email: s3722067@student.rmit.edu.au"<<std::endl;
   std::cout<<"------------------------------"<<std::endl;
   menu();
}

bool checkArgs(int argc, char** argv) {
  bool retVal = false;

  if(argc == REQUIRED_ARGS + 1) {
    std::string inputFilename = argv[1];
    retVal = checkFile(inputFilename);
  }
  else if (argc > REQUIRED_ARGS + 1) {
    std::cout << "Incorrect no. of file names provided" << std::endl;
  }

  return retVal;
}

bool checkFile(std::string &filename) {
  bool validFile = true;

  std::ifstream in;
  in.open(filename);
  if (in.fail()) {
    validFile = false;
    std::cout << "Could not open " << filename << std::endl;
  }
  in.close();

  return validFile;
}

void executeCommands(char** argv) {
  std::string filename = argv[1];
  std::ifstream in;
  in.open(filename);

  ge->loadGame(filename);

  std::string command;
  int numPlayerLines = NUM_PLAYER_LINES * ge->getNumPlayers();
  for (int i = 0; i < NO_OF_SKIPPED_LINES + numPlayerLines; i++) {
    std::getline(in, command);
  }

  std::cout << "INITIAL BOARD STATE" << std::endl;
  ge->printBoard();

  while(std::getline(in, command)) {
    std::cout << command << std::endl;

    ge->executeCommand(command);
    if (ge->currentPlayer->getName() == "AI") {
      ge->aiMove();
    }
    ge->printBoard();
  }
  in.close();

  if (ge->gameEndCheck()) {
    ge->saveGame("savedGame");
  }
}

bool isNameUpper(std::string name){
  for(char c:name){
    if(!isupper(c)){
      return false;
    }
  }
  return true;
}

void quit(){
  std::cout << "Goodbye!" << '\n';
  exit(0);
}
