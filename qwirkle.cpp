#include "GameEngine.h"
#include <iostream>
#include <string>

#define EXIT_SUCCESS    0

//Functions
void menu();
void newGame();
void loadGame();
void showStudentInfo();

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
   std::cout << "2. Load Game" << std::endl;
   std::cout << "3. Show student information" << std::endl;
   std::cout << "4. Quit" << std::endl;

   std::cin >> command;
   std::cout<<std::endl;
   if (command == 1)
   {
      newGame();
   }
   else if (command == 2)
   {
      loadGame();
   }
   else if (command == 3)
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
   std::string player1;
   std::string player2;
   std::cout << "Starting a New Game\n"<< std::endl;
   std::cout << "Enter a name for player 1 (uppercase characters only)" << std::endl;
   std::cin >> player1;
   ge->addPlayer(player1);
   std::cout << "Enter a name for player 2 (uppercase characters only)" << std::endl;
   std::cin >> player2;
   ge->addPlayer(player2);
   std::cout << "Alright, " << player1 << " and " << player2 << ", Let's Play!" << std::endl;

   //Add random tiles to tileBag with Danny's random tile generation method.

   //Draw 6 tiles into each player's hands
   

   //Start with player 1 then keep Alternating between player's turns until game ends.




}

void loadGame()
{
   std::cout<<"Enter the filename to load a game"<<std::endl;

   //Check if file exists.
   //CHeck that the format of the file is correct.

   std::cout<<"Qwirkle game successfully loaded"<<std::endl;
}

void showStudentInfo()
{
   std::cout<<"------------------------------"<<std::endl;
   std::cout<<"Name: Wesley Lee"<<std::endl;
   std::cout<<"Student ID: s3719843"<<std::endl;
   std::cout<<"Email: s3719843@student.rmit.edu.au"<<std::endl;
}

//
