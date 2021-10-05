#include "Cards.h"

using namespace std;

int main(){
    //create and show a deck
    Deck deck1;
    deck1.showDeck();

    //create a hand
    Hand hand1;

    //draw cards to hand from deck
    hand1.addCardToHand(deck1.draw());
    hand1.addCardToHand(deck1.draw());
    hand1.addCardToHand(deck1.draw());
    hand1.showHand();

    //show cards remaining in deck
    deck1.showDeck();
    return 0;
}