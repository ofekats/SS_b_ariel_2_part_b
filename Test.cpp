#include "doctest.h"
#include "sources/game.hpp"
#include "sources/player.hpp"
#include "sources/card.hpp"
using namespace ariel;

TEST_CASE("can't do another game with the same players") {
    //create 3 new players
    Player p1("Alice");
    Player p2("Bob");
    Player p3("Rita");
    //create new game
    Game game(p1,p2);
    //try to create anther game with the same players- should throw exception
    CHECK_THROWS((Game(p1,p2))); 
    CHECK_THROWS((Game(p1,p3)));
    CHECK_THROWS((Game(p2,p3)));
    //finish the game
    CHECK_NOTHROW(game.playAll());
}

TEST_CASE("void not throws exception") {
    //create 2 new players
    Player p1("Alice");
    Player p2("Bob");
    //create new game
    Game game(p1,p2);
    //void function shouldnt throw exception
    CHECK_NOTHROW(game.playTurn());
    CHECK_NOTHROW(game.printLastTurn());
    CHECK_NOTHROW(game.playAll());
    //after the game is over
    CHECK_NOTHROW(game.printWiner());
    CHECK_NOTHROW(game.printLog());
    CHECK_NOTHROW(game.printStats());
}

TEST_CASE("playTurn when no more cards should throw exception") {
    //create 2 new players
    Player p1("Alice");
    Player p2("Bob");
    //create new game
    Game game(p1,p2);
    //finish the game
    CHECK_NOTHROW(game.playAll());
    //after game is over
    CHECK_THROWS(game.playTurn());
}

TEST_CASE("stack size checks") {
    //create 2 new players
    Player p1("Alice");
    Player p2("Bob");
    //create new game
    Game game(p1,p2);
    //start of game each player get half of the total cards (52/2=26)
    CHECK(p1.stacksize() == 26);
    CHECK(p2.stacksize() == 26);
    game.playTurn();
    //after 1 turn the stack size sould be 25 or less (if there was a draw)
    CHECK(p1.stacksize() < 26);
    CHECK(p2.stacksize() < 26);
    //finish the game
    CHECK_NOTHROW(game.playAll());
    //after the game no more cards to the players
    CHECK(p1.stacksize() == 0);
    CHECK(p2.stacksize() == 0);
}

TEST_CASE("cardes Taken checks") {
    //create 2 new players
    Player p1("Alice");
    Player p2("Bob");
    //create new game
    Game game(p1,p2);
    //in the begining no cards are taken
    CHECK(p1.cardesTaken() == 0);
    CHECK(p2.cardesTaken() == 0);
    game.playTurn();
    //after 1 turn one player should have won cards (1 or more if there was a draw) 
    CHECK((p1.cardesTaken() > 0 || p2.cardesTaken() > 0));
    //finish the game
    CHECK_NOTHROW(game.playAll());
}









