#include "card.hpp"

using namespace std;

ariel::Card::Card(int num, string shape) //constructor
{
    this->cardNum_ = num;
    this->cardShape_ = shape;
}

int ariel::Card::getCnum() const{ //return the card number
    return this->cardNum_;
}

string ariel::Card::getCshape() const{ //return the card shape
    return this->cardShape_;
}