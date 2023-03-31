#pragma once

#include <string>

using namespace std;

namespace ariel{
    class Card{
        public:
            Card(); //defult constructor
            Card(int num, string shape); //constructor
            int getCnum() const; //return the card number
            string getCshape() const; //return the card shape
        private:
            int cardNum_;
            string cardShape_;
    };
}
