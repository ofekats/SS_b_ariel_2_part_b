#include "game.hpp"
#include <fstream> //for file
#include <iostream>
#include <stdexcept> //for exceptions

using namespace std;

//func can throw an exception
ariel::Game::Game(Player& p1_ref, Player& p2_ref) //constructor
{
    if(p1_ref.getIsPlaying() == false && p2_ref.getIsPlaying() == false)
    {
        this->p1_ = p1_ref;
        this->p2_ = p2_ref;
        this->num_of_drow_ =0;
        this->num_of_rounds_=0;
        this->end = false;
        this->statsFile.open("stats.txt", ios::app); // create file if it doesn't exist, otherwise append to end of file
        if (!this->statsFile.is_open()) {
            throw invalid_argument("Failed to open stats file"); // throw an exception
        }
        //change players to playing a game
        this->p1_.setIsPlaying(true);
        this->p2_.setIsPlaying(true);
    }
    else
    {
        throw invalid_argument("The players are already in a different game"); // throw an exception
    }
    
}

ariel::Game::~Game() //close the statFile
{
    this->statsFile.close();
}

//func can throw an exception
void ariel::Game::playTurn()
{
    if(p1_.stacksize() > 0 && p2_.stacksize() > 0)
    {
        int nCard_this_round = 0;
        bool half = false; //if each player need to get half the cards
        num_of_rounds_++;
        Card c1 = p1_.pop_stack();
        Card c2 = p2_.pop_stack();
        nCard_this_round += 2;
        //stat
        
        while(c1.getCnum() == c2.getCnum())
        {
            num_of_drow_++;
            if(p1_.stacksize() == 0 && p2_.stacksize() == 0)
            {
                half=true; //cards are gone in drow -> each player need to get half the cards
                break;
            }
            //opposite cards
            p1_.pop_stack();
            p2_.pop_stack();
            if(p1_.stacksize() == 0 && p2_.stacksize() == 0)
            {
                half=true; //cards are gone in drow -> each player need to get half the cards
                break;
            }
            //play again after drow
            c1 = p1_.pop_stack();
            c2 = p2_.pop_stack();
            nCard_this_round += 4;
        }
        if(half) //cards are gone in drow -> each player need to get half the cards
        {
            p1_.addTocardesTaken(nCard_this_round/2);
            p2_.addTocardesTaken(nCard_this_round/2);
            endOfGame(); //finish the game 
        }
        if(c1.getCnum() > c2.getCnum()) //player1 won this round
        {
            p1_.addTocardesTaken(nCard_this_round);
        }
        else //player2 won this round
        {
            p2_.addTocardesTaken(nCard_this_round);
        }
    }
    else
    {
        throw invalid_argument("No cards remain to the players"); // throw an exception
    }
}

void ariel::Game::printLastTurn() // print the last turn stats
{

}

void ariel::Game::playAll() //playes the game untill the end
{

}

void ariel::Game::printWiner() // prints the name of the winning player
{

}

void ariel::Game::printLog() // prints all the turns played one line per turn
{

}

void ariel::Game::printStats() // for each player prints basic statistics: win rate, cards won, <other stats you want to print>. Also print the draw rate and amount of draws that happand. (draw within a draw counts as 2 draws. )
{

}

void ariel::Game::endOfGame() //remove tje players from the game
{
    this->end = true;
    //
}