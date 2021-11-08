#include <iostream>
#include "Player.h"
using namespace std;

int main(){
    Player player1("Name");
    cout << "The player's name is: " << player1.name << endl;
    cout << "The player's hand is: " << *(player1.hand) << endl;
    return 0;
}
