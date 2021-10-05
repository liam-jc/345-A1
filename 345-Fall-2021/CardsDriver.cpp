#include "Cards.h"
// #include<iostream>
// #include<cstdlib>
// #include <string>

using namespace std;

int main(){
    
    // Card card1;
    // Card card2;
    // Card card3;
    // Card card4;
    // Card card5;
    // Card card6;
    // card1.showCard();
    // card2.showCard();
    // card3.showCard();
    // card4.showCard();
    // card5.showCard();
    // card6.showCard();
    
    // cout << "accessing card1 variable typeOfCard gives " << card1.typeOfCard << "\n******" << endl;

    string hello = "hello";  
    cout << hello << endl;
    Deck deck1;
    deck1.showDeck();
    Hand hand1;
    hand1.addCardToHand(deck1.draw());
    hand1.addCardToHand(deck1.draw());
    hand1.addCardToHand(deck1.draw());
    hand1.showHand();
    return 0;
}