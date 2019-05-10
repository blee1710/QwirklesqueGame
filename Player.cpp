#include "GameEngine.h"
#include "Player.h"
#include <iostream>
#include <string>

Player::Player(std::string name)
{
    //To check things, not needed
    std::cout << "Player created" << std::endl;
    this->name = name;
    this->score = 0;
}

void Player::addPoints(int points)
{
    this->score += points;
}

//Adds a tile to their hand
void Player::drawTile(Tile *tile)
{
    hand.addBack(tile);
}

void Player::printTiles()
{
    std::cout << "Your hand is" << std::endl;
    for (int i = 0; i < hand.getSize(); i++)
    {
        if (i < 5)
        {
            std::cout << hand.getTileAt(i)->toString2() << ", ";
        }
        else
        {
            std::cout << hand.getTileAt(i)->toString2()<<std::endl<<std::endl;
        }
        
    }
}

//Getters

LinkedList Player::getHand()
{
    return hand;
}

LinkedList* Player::getHandPtr()
{
    LinkedList* handPtr = new LinkedList();
    handPtr = &hand;
    return handPtr;
}

std::string Player::getName()
{
    return name;
}

int Player::getScore()
{
    return score;
}
