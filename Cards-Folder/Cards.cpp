#include<iostream>
#include<cstdlib>
#include <string>
#include <vector>
#include <random>
#include "Cards.h"

using namespace std;


//********************************* PLAYER *********************************
        //A Player holds a Hand object
        
        //default constructor
        Player::Player(){
        };

//********************************* CARD *********************************
    //Card has a randomly assigned type at construction. 
    //Cards are used in Deck and Hand.
        
        string typeOfCard;
        int Card::typeNumber = 0;
       
        //default constructor
        Card::Card(){ 
            //cycles through the 5 types of card, changes every time a Card object is created.
            typeNumber = typeNumber%5;
            typeNumber++;
            // cout << "type number is " << typeNumber << endl; //for debugging
            switch(typeNumber) {
                case 1  :
                    typeOfCard = "Bomb";
                    break;
                case 2  :
                    typeOfCard = "Reinforcement";
                    break;
                case 3  :
                    typeOfCard = "Blockade";
                    break;
                case 4  :
                    typeOfCard = "Airlift";
                    break;
                case 5  :
                    typeOfCard = "Diplomacy";
                    break;
                default :
                    typeOfCard = "PROBLEM";
            }
            
        };

        //TODO copy constructor
        // Card::Card(const Card &obj) { 
                // Card newCard;
                // newCard.typeOfCard = obj.typeOfCard;
        //     cout << "Copy constructor allocating ptr." << endl;
        //     ptr = new int;
        //     *ptr = *obj.ptr; // copy the value
        // }

        void Card::showCard(){
            cout << "Card type is " << typeOfCard << endl;
        };
        
        void Card::play(){
            void createOrder();
            void toPlayerOrderList();
            void returnToDeck();
        };


//********************************* DECK *********************************
    //A Deck contains a finite collection of Cards.
    
        int numCardsInDeck;
        std::__1::vector<Card> deckOfCards;
        //default constructor
        Deck::Deck(){
            //calls Card constructor, creates Deck of random Cards.
            cout << "How many cards in a deck? " << endl;
            cin >> numCardsInDeck;
            for (int i = 0; i < numCardsInDeck; i++){
                Card cardInDeck;
                deckOfCards.push_back(cardInDeck);
            }

        };
        void Deck::showDeck(){
            cout << "Deck contains: " << endl;
            for (int i = 0; i < deckOfCards.size(); i++){
                deckOfCards.at(i).showCard();
            }
            
        };

         //draw() draws a Card at random from remaining Cards in Deck and places in a Player's Hand.
        //Then removes chosen Card from Deck.
        int randomCardNumber=0;
        Card Deck::draw(){
            std::random_device rd; //random number generator from slide 16 @ https://view.officeapps.live.com/op/view.aspx?src=http%3a%2f%2fvideo.ch9.ms%2fsessions%2fgonat%2f2013%2fSTLGN13rand.pptx
            std::mt19937 mt(rd());
            std::uniform_real_distribution<double> dist(1.0, deckOfCards.size());
            randomCardNumber = dist(mt);
            cout << "randomCardNumber is " << randomCardNumber << endl; //for debugging
            Card toReturn; 
            toReturn.typeOfCard = deckOfCards.at(randomCardNumber).typeOfCard;
            deckOfCards.erase( std::next(deckOfCards.begin(), randomCardNumber));
            return toReturn;
        };
       


//********************************* HAND *********************************
    //A Hand contains a finite collection of Cards.
        std::__1::vector<Card> handOfCards;

        //default constructor
        Hand::Hand(){       
        };

        void Hand::showHand(){
            cout << "Hand contains: " << endl;
            for (int i = 0; i < handOfCards.size(); i++){
                handOfCards.at(i).showCard();
            }
        };

        void Hand::addCardToHand(Card toAdd){
            handOfCards.push_back(toAdd);
        };
