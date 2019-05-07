#ifndef ASSIGN2_PLAYER_H
#define ASSIGN2_PLAYER_H

#include <string>

#include "LinkedList.h"

class Player
{
  public:
    Player(std::string name);
    void addPoints(int points);
    void drawTile();
    //Getters and Setters
    LinkedList getHand();
    std::string getName();
    int getScore();

  private:
    std::string name;
    int score;
    LinkedList hand;
};

#endif // ASSIGN2_PLAYER_H
