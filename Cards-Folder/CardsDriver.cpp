#include "Cards.h"
// #include "Orders.h"
// #include "Player.h"

using namespace std;

int main(){
    //*****demo A1*****
    
    //create and show a deck
    Deck deck1;
    cout << deck1;

    //create a hand
    Hand hand1;

    //draw cards to hand from deck
    hand1.addCardToHand(deck1.draw());
    hand1.addCardToHand(deck1.draw());
    hand1.addCardToHand(deck1.draw());
    //show hand
    cout << hand1;

    //show cards remaining in deck
    cout << deck1;

    //*****end demo A1*****

    
    //*****debugging area*****
    
    // *****create class objects with pointers, using "new" deck (working)*****
    // Deck *deckptr = new Deck();
    // cout << *deckptr;
    // (*deckptr).draw();
    // cout << *deckptr;

    // // hand (working)
    // Hand *handptr = new Hand();
    // cout << *handptr;
    // (*handptr).addCardToHand((*deckptr).draw());
    // cout << *deckptr;
    // cout << *handptr;

    // *****card copy constructor test (working)*****
    // Card card1;
    // cout << card1;
    // Card card2 = Card(card1);
    // cout << card2;
    // Card card3;
    // cout << card3;
    // Card card4 = Card(card1);
    // cout << card4;

    // *****deck copy constructor test (working)*****
    // Deck deck01;
    // cout << deck01;
    // Deck deck02 = Deck(deck01);
    // cout << deck02;
    // Hand hand01;
    // hand01.addCardToHand(deck02.draw());
    // hand01.addCardToHand(deck02.draw());
    // cout << deck01;
    // cout << deck02;
    // cout << hand01;

    // *****hand copy constructor test (working)*****
    // Hand hand001;
    // cout << "hand001 is: " << hand001;
    // Hand hand002 = Hand(hand001);
    // cout << "hand002 is: " << hand002;
    // Deck deck001;
    // cout << deck001;
    // hand001.addCardToHand(deck001.draw());
    // cout << "\nCard drawn from deck should now be in hand001. hand002 should remain empty." << endl;
    // cout << "hand001 is: " << hand001;
    // cout << "hand002 is: " << hand002;

    return 0;
}
