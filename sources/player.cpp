#include "player.hpp"
#include <stdexcept> //for exceptions

using namespace std;

ariel::Player::Player(string name) //constructor
{
    this->name_ = name;
    this->num_of_win_cards_ = 0;
    this->size_of_stack_ = 0;
    this->num_of_win_round_ = 0;
    this->isPlaying = false;
}

int ariel::Player::stacksize() const{ //return the amount of cards left
    return this->size_of_stack_;
}

//func can throw an exception
void ariel::Player::setstacksize(int size) //change the size_of_stack_
{
    if(size >= 0)
    {
        this->size_of_stack_ = size;
    }
    else
    {
        throw invalid_argument("Stack size must be positive or 0"); // throw an exception
    }
    
}

//func can throw an exception
void ariel::Player::subStacksize(int tosub) //decrease by tosub the size_of_stack_
{
    if(((this->size_of_stack_)-tosub) >= 0)
    {
        this->size_of_stack_ -= tosub;
    }
    else
    {
        throw invalid_argument("Stack size must be positive or 0"); // throw an exception
    }
}

int ariel::Player::cardesTaken() const{ //return the amount of cards this player has won
    return this->num_of_win_cards_;
}

//func can throw an exception
void ariel::Player::setcardesTaken(int num) //change the num_of_win_round_
{
    if(num>0 && num<53) 
    {
        this->num_of_win_cards_ = num;
    }
    else
    {
        throw invalid_argument("Cards won must be between 0 and 52"); // throw an exception
    }
}

//func can throw an exception
void ariel::Player::addTocardesTaken(int toadd) //increase by toadd the num_of_win_cards_
{
    int number = this->num_of_win_cards_ + toadd;
    if(number>0 && number<53) 
    {
        this->num_of_win_cards_ += toadd;
    }
    else
    {
        throw invalid_argument("Cards won must be between 0 and 52"); // throw an exception
    }
}

string ariel::Player::getName() const{
    return this->name_;
}

int ariel::Player::getRoundWon() const //return the amount of rounds this player has won (num_of_win_round_)
{
    return this->num_of_win_round_;
}

//func can throw an exception
void ariel::Player::setRoundWon(int num) //change the num_of_win_round_
{
    if(num >= 0)
    {
        this->num_of_win_round_ = num;
    }
    else
    {
        throw invalid_argument("Rounds won must be positive or 0"); // throw an exception
    }
}

//func can throw an exception
void ariel::Player::addToRoundWon(int toadd) //increase by toadd the num_of_win_round_
{
    int number = this->num_of_win_round_ + toadd;
    if(number >= 0)
    {
        this->num_of_win_round_ += toadd;
    }
    else
    {
        throw invalid_argument("Rounds won must be positive or 0"); // throw an exception
    }
}

bool ariel::Player::getIsPlaying() const{ //is this player in a game or not
    return this->isPlaying;
}

void ariel::Player::setIsPlaying(bool state) //change if this player in a game or done
{
    this->isPlaying = state;
}