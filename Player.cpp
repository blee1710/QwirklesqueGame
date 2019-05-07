#include "GameEngine.h"
#include "Player.h"
#include <iostream>
#include <string>

Player::Player(std::string name)
{
    //To check things, not needed
    std::cout<<"Player created"<<std::endl;
    this->name = name;
    this->score = 0;
}

void Player::addPoints(int points)
{
    this->score += points;
}

void Player::drawTile()
{

}

//Getters

LinkedList Player::getHand()
{
    return hand;
}

std::string Player::getName()
{
    return name;
}

int Player::getScore()
{
    return score;
}
