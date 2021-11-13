#include "GameEngine.h"
#include <iostream>

int main(){
    GameEngine GE;
    GE.StartUpPhase();
    GE.AssignReinforcement();
    GE.IssueOrders();

    return 0;
}