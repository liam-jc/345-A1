// #include "GameEngine.h"
#include "CommandProcessing.h"


using namespace std;

int main(){
    string userInput;
    cout << "Welcome to Warzone CommandProcessor. \nWould you like to load commands from console or a file?" << endl;
    cin >> userInput;
    if (userInput == "console"){    
        //console option uses CommandProcessor
        CommandProcessor cp; //make a CommandProcessor
        //GameEngine GE;
        cp.getCommand(); //request command input from terminal
        cp.getCommand(); //request another command input from terminal

        for (int i=0; i<cp.commandCollection.size(); i++){ //show commands
            cout << cp.commandCollection.at(i);
        }
    }
    else if (userInput == "file"){
        //file option uses FileCommandProcessorAdapter
    }
    else {
        cout << "Invalid input. Goodbye!";
    }

    return 0;
}
