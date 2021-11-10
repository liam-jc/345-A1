// #include "GameEngine.h"
#include "CommandProcessing.h"


using namespace std;

int main(){
    CommandProcessor cp; //make a CommandProcessor
    //GameEngine GE;
    cp.getCommand(); //request command input from terminal
    cp.getCommand(); //request another command input from terminal

    for (int i=0; i<cp.commandCollection.size(); i++){ //show commands
        cout << cp.commandCollection.at(i);
    }


    return 0;
}
