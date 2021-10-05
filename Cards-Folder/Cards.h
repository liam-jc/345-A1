#include<iostream>
#include<cstdlib>
#include <string>
#include <vector>

using namespace std;

class Player{
    public:
        Player();
};



class Card{
        // string type;
    public:     
        int* ptr;
        static int typeNumber;
        string typeOfCard;
        void showCard();
        Card(); //default constructor
        // Card(const Card &obj); //copy constructor
        // {
        //     int random;
        // };
        // void initialyze();
        // int rand;
        // string getType();
        void play();
        // {
        //     void createOrder();
        //     void toPlayerOrderList();
        //     void returnToDeck();
        // };
};

class Deck{
    public:
        int randomCardNumber;
        int numCardsInDeck;
        // Card toReturn;
        void showDeck();
        Deck();
        std::__1::vector<Card> deckOfCards;
        Card draw();
};

class Hand{
    public:
        Hand();
        void addCardToHand(Card toAdd);
        std::__1::vector<Card> handOfCards;
        void showHand();
};