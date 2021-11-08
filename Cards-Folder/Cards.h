#ifndef Cards_h
#define Cards_h

#pragma once
#include<iostream>
#include<cstdlib>
#include <string>
#include <vector>
//  #include "Orders.h"
//  #include "Player.h"

using namespace std;


class Card{
    public:     
        // int* ptr;
        static int typeNumber;
        string typeOfCard;
        Card(); //default constructor
        Card(int, Card*);
        Card(const Card &inputCard); //copy costructor
        friend ostream& operator << (ostream& outputStream, const Card& c); //outstream overload
        void play();
        ~Card(); //destructor
};

class Deck{
    public:
        int randomCardNumber;
        int numCardsInDeck;  
        Deck();
        Deck(const Deck &inputDeck); // copy constructor
        friend ostream& operator << (ostream& outputStream, const Deck& d); //outstream overload
        std::__1::vector<Card> deckOfCards;
        Card draw();
        ~Deck(); //destructor
};

class Hand{
    public:
        Hand();
        Hand(const Hand &inputHand); // copy constructor
        void addCardToHand(Card toAdd);
        std::__1::vector<Card> handOfCards;
        friend ostream& operator << (ostream& outputStream, const Hand& h); //outstream overload
        ~Hand(); //destructor
};

#endif
