// #include "GameEngine.h"
#include "CommandProcessing.h"


using namespace std;

int main(){
    string userInput;
    cout << "Welcome to Warzone CommandProcessor. \nWould you like to load commands from console or a file? \n(Type '-console' or '-file')" << endl; //-file should be -file <filename>
    cin >> userInput;
    if (userInput == "-console"){ //console option uses CommandProcessor      
        
        // GameEngine GE;
        CommandProcessor cp; //make a CommandProcessor
        // cp.validate();
        cp.getCommand(); //request command input from terminal
        // cp.getCommand(); //request another command input from terminal

        for (int i=0; i<cp.commandCollection.size(); i++){ //show commands
            cout << cp.commandCollection.at(i);
        }
    }
    else if (userInput == "-file"){ //file option uses FileCommandProcessorAdapter
        FileCommandProcessorAdapter fcpa;
        fcpa.getCommand(); //request command input from file
        fcpa.getCommand(); //request command input from file
        fcpa.getCommand(); //request command input from file
        for (int i=0; i<fcpa.commandCollection.size(); i++){ //show commands
            cout << fcpa.commandCollection.at(i);
        }
    }
    else {
        cout << "Invalid input. Goodbye!";
    }

    return 0;
}