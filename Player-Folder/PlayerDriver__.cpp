#include <iostream>
#include "Player.h"
using namespace std;

int main(){
    Player player1("Name");
    cout << "The player's name (called by member) is: " << player1.name << endl;
    cout << "\nThe player's hand (called by member) is: " << *(player1.hand) << endl;
    cout << "Calling the player by ostream is: \n" << player1;
    return 0;
}
