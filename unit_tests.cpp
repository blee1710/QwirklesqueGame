#include "qwirkle.h"

#include <iostream>
#include <fstream>
#include <string>

#define EXIT_SUCCESS     0
#define REQUIRED_ARGS    1

void checkArgs(int argc, char** argv);
void checkFile(std::string &filename);
void loadInput(char** argv);
void loadInput();

int main(int argc, char** argv) {
  try {
      checkArgs(argc, argv);
      loadInput(argv);
  } catch(std::runtime_error &exception) {
      std::cout << "ERROR: " << exception.what() << std::endl;
  }

  return EXIT_SUCCESS;
}

void checkArgs(int argc, char** argv) {
  if(argc != REQUIRED_ARGS + 1) {
    throw std::runtime_error("Incorrect no. of file names provided");
  }

  std::string inputFilename = argv[1] + std::string(".in");
  std::string outputFilename = argv[1] + std::string(".out");

  checkFile(inputFilename);
  checkFile(outputFilename);
}

// Checks that there are the correct number of command line arguments
// and that both input and output files exist
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
  std::string inputFilename = argv[1] + std::string(".in");
  std::ifstream in;

  for (int i = 0; i < 2; i++) {
    std::string playerName;
    in >> playerName;
    // call add player method

    int playerScore;
    in >> playerScore;
    // call set player score method

    std::string playerHand;
    in >> playerHand;
    //while loop to add all cards in string to player hand
  }
}

// Checks wether the expected output matches the quirkle games saved
// data
void loadOutput() {

}
