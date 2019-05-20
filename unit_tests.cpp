#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "GameEngine.h"

#define EXIT_SUCCESS     0
#define REQUIRED_ARGS    1
#define NO_OF_SKIPPED_LINES    36

void checkArgs(int argc, char** argv);
void checkFile(std::string &filename);
void executeCommands(char** argv, GameEngine* ge);

int main(int argc, char** argv) {
  GameEngine* ge = new GameEngine();
  try {
      checkArgs(argc, argv);
      executeCommands(argv, ge);
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

  std::string inputFilename = argv[1];
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
void executeCommands(char** argv, GameEngine* ge) {
  std::string filename = argv[1];
  std::ifstream in;
  in.open(filename);

  ge->loadGame(filename);

  std::string command;
  for (int i = 0; i < NO_OF_SKIPPED_LINES; i++) {
    std::getline(in, command);
  }

  std::cout << "INITIAL BOARD STATE" << std::endl;
  ge->printBoard();

  while(std::getline(in, command)) {
    ge->executeCommand(command);
    std::cout << command << std::endl;
    ge->printBoard();

  }
  in.close();
}
