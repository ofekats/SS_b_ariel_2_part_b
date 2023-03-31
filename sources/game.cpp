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
        if (!this->statsFile.is_open()) 
        {
            throw invalid_argument("Failed to open stats file"); // throw an exception
        }
        //change players to playing a game
        this->p1_.setIsPlaying(true);
        this->p2_.setIsPlaying(true);
        p1_.setstacksize(26);
        p2_.setstacksize(26);
        //cardssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss
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
        int nCard_this_round = 0; //cards in the game this round
        bool half = false; //if each player need to get half the cards
        this->num_of_rounds_++; 
        Card c1 = p1_.pop_stack();
        Card c2 = p2_.pop_stack();
        p1_.subStacksize(1);
        p2_.subStacksize(1);
        nCard_this_round += 2;
        //stat 
        statsFile << p1_.getName() << " played " << c1.getCnum() << " of " << c1.getCshape() << " ";
        statsFile << p2_.getName() << " played " << c2.getCnum() << " of " << c2.getCshape() << ". ";
        while(c1.getCnum() == c2.getCnum())
        {
            this->num_of_drow_++;
            //stat 
            statsFile << " Drow.";
            if(p1_.stacksize() == 0 && p2_.stacksize() == 0)
            {
                half=true; //cards are gone in drow -> each player need to get half the cards
                //stat 
                statsFile << "cards are gone- no winner to this round." << endl;
                break;
            }
            //opposite cards
            p1_.pop_stack();
            p2_.pop_stack();
            p1_.subStacksize(1);
            p2_.subStacksize(1);
            nCard_this_round += 2;
            if(p1_.stacksize() == 0 && p2_.stacksize() == 0)
            {
                half=true; //cards are gone in drow -> each player need to get half the cards
                //stat 
                statsFile << "cards are gone- no winner to this round." << endl;
                break;
            }
            //play again after drow
            c1 = p1_.pop_stack();
            c2 = p2_.pop_stack();
            p1_.subStacksize(1);
            p2_.subStacksize(1);
            nCard_this_round += 2;
            //stat
            statsFile << p1_.getName() << " played " << c1.getCnum() << " of " << c1.getCshape() << " ";
            statsFile << p2_.getName() << " played " << c2.getCnum() << " of " << c2.getCshape() << ". ";
        }
        if(half) //cards are gone in drow -> each player need to get half the cards
        {
            p1_.addTocardesTaken(nCard_this_round/2);
            p2_.addTocardesTaken(nCard_this_round/2);
            endOfGame(); //finish the game 
        }
        else //not end of game
        {
            int x1 = c1.getCnum();
            int x2 = c2.getCnum();
            //Ace
            if(x1 == 1)
            {
                if(x2 != 2)
                {
                    x1 =14;
                }
            }
            if(x2 == 1)
            {
                if(x1 != 2)
                {
                    x2 =14;
                }
            }

            if(x1 > x2) //player1 won this round
            {
                p1_.addTocardesTaken(nCard_this_round);
                p1_.addToRoundWon(1);
                //stat 
                statsFile << p1_.getName() << " wins." << endl;
            }
            else //player2 won this round
            {
                p2_.addTocardesTaken(nCard_this_round);
                p2_.addToRoundWon(1);
                //stat 
                statsFile << p2_.getName() << " wins." << endl;
            }
            if(p1_.stacksize() == 0 && p2_.stacksize() == 0) //cards are gone after this round
            {
                endOfGame(); //finish the game 
            }

        }
    }
    else
    {
        throw invalid_argument("No cards remain to the players"); // throw an exception
    }
}

//func can throw an exception
void ariel::Game::printLastTurn() // print the last turn stats
{
    ifstream file("stats.txt");
    if (!file.is_open()) 
    {
        throw invalid_argument("Failed to open stats file"); // throw an exception
    }

    string lastLine, line;
    while (getline(file, line)) {
        lastLine = line;
    }
    cout << lastLine << endl;
    //to throw exception if there is no turn that was????????????????????????????????????????????????????????????????????????????????
    file.close();
}

void ariel::Game::playAll() //playes the game untill the end
{
    while(p1_.stacksize() > 0 && p2_.stacksize() > 0)
    {
        playTurn();
    }
}

void ariel::Game::printWiner() // prints the name of the winning player
{
    //to throw exception if there is no winner yet?????????????????????????????????????????????????????????????????????????????????
    if(p1_.cardesTaken() > p2_.cardesTaken())
    {
        cout << p1_.getName() << " is the winner!" << endl;
    }
    else if (p1_.cardesTaken() < p2_.cardesTaken())
    {
        cout << p2_.getName() << " is the winner!" << endl;
    }
    else
    {
        cout << "tie! no winner" << endl; // or to throw exception?????????????????????????????????????????????????????????????????
    }
    
}

//func can throw an exception
void ariel::Game::printLog() // prints all the turns played one line per turn
{
    ifstream file("stats.txt");
    if (!file.is_open()) 
    {
        throw invalid_argument("Failed to open stats file"); // throw an exception
    }

    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    
    //to throw exception if there is no turn that was????????????????????????????????????????????????????????????????????????????????
    file.close();
}

void ariel::Game::printStats() // for each player prints basic statistics: win rate, cards won, <other stats you want to print>. Also print the draw rate and amount of draws that happand. (draw within a draw counts as 2 draws. )
{
    
}

void ariel::Game::endOfGame() //remove tje players from the game
{
    this->end = true;
    //
}