#include "GameEngine.h"
#include <iostream>
#include <string>

#define EXIT_SUCCESS    0

//Functions
void menu();
void newGame();
void loadGame();
void showStudentInfo();
void newSinglePlayerGame();
GameEngine* ge;

int main(void)
{
   // LinkedList* list = new LinkedList();
   // delete list;


   std::cout << "Welcome to Qwirkle" << std::endl;
   std::cout << "------------------" << std::endl;

   ge = new GameEngine();

   menu();



   return EXIT_SUCCESS;
}

void menu()
{
   int command;
   std::cout << "Menu" << std::endl;
   std::cout << "----" << std::endl;
   std::cout << "1. New Game" << std::endl;
   std::cout << "2. New Game (SinglePlayer) WIP" << std::endl;
   std::cout << "3. Load Game" << std::endl;
   std::cout << "4. Show student information" << std::endl;
   std::cout << "5. Quit" << std::endl;

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
      showStudentInfo();
   }
   else
   {
      std::cout<<"Goodbye!"<<std::endl;
   }
   // do
   // {
   //    std::cout << "Menu" << std::endl;
   //    std::cout << "----" << std::endl;
   //    std::cout << "1. New Game" << std::endl;
   //    std::cout << "2. Load Game" << std::endl;
   //    std::cout << "3. Show student information" << std::endl;
   //    std::cout << "4. Quit" << std::endl;

   //    std::cin >> command;
   //    if(command == 1)
   //    {
   //       newGame();
   //    }
   //    else if (command == 2)
   //    {
   //       loadGame();
   //    }
   //    else if (command == 3)
   //    {
   //       showStudentInfo();
   //    }
   //    else
   //    {

   //    }

   // } while (command != 4);
}

void newGame()
{
   std::string playerName;
   std::string playerCount;
   bool valid = false;
   int playerAmount;
   std::cout << "Starting a New Game\n"<< std::endl;

   while(!valid) {
     std::cout << "Please enter amount of players (2-4)" << '\n';
     std::cin >> playerCount;
     playerAmount = std::stoi(playerCount);
     if(playerAmount > 0 && playerAmount <= 4){
       valid = true;
     }
   }

   for(int i = 0; i < playerAmount; i++){
     std::cout << "Enter a name for player " + std::to_string(i+1) + " (uppercase characters only)" << '\n';
     std::cin >> playerName;
     ge->addPlayer(playerName);
   }


   // //----------
   // std::cout << "Enter a name for player 1 (uppercase characters only)" << std::endl;
   // std::cin >> player1;
   // ge->addPlayer(player1);
   // std::cout << "Enter a name for player 2 (uppercase characters only)" << std::endl;
   // std::cin >> player2;
   // ge->addPlayer(player2);
   // std::cout << "Alright, " << player1 << " and " << player2 << ", Let's Play!" << std::endl;
   //----------

   //Add random tiles to tileBag with Danny's random tile generation method.
   ge->makeBag();
   //Draw 6 tiles into each player's hands
   ge->drawInitialTiles();
   //Start with player 1 then keep Alternating between player's turns until game ends.
   ge->mainLoop();
}

void newSinglePlayerGame(){
  std::string playerName;
  std::cout << "Starting a New Game\n"<< std::endl;

  std::cout << "Enter a name for player 1 (uppercase characters only)" << '\n';
  std::cin >> playerName;
  ge->addPlayer(playerName);

  //Add random tiles to tileBag with Danny's random tile generation method.
  ge->makeBag();
  //Draw 6 tiles into each player's hands
  ge->drawInitialTiles();
  //Start with player 1 then keep Alternating between player's turns until game ends.
  ge->mainLoop();
}

void loadGame()
{
   std::cout<<"Enter the filename to load a game"<<std::endl;
   std::string filename;
   std::cin >> filename;
   ge->loadGame(filename);
   ge->mainLoop();
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

//
