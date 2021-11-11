#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>
#include <regex>
#include "GameEngine.h"

GameEngine::GameEngine() : input (""), state(0){
    
}

// friend int GameEngine::getState(){
//     return this->state;
// };

GameEngine::GameEngine(const GameEngine& GE){
    state = GE.state;
    input = GE.input;
}

GameEngine& GameEngine::operator=(const GameEngine& GE) {
    state = GE.state;
    input = GE.input;
    return *this;
}

//ostream overload
// ostream& operator << (ostream& outputStream, const GameEngine& c){
//     outputStream << this->state;
//     return outputStream;
// };

void GameEngine::Start(){
    cout<< "Welcome to play Warzone" << endl;
    cout<< "please enter (start) to play the game" << endl;
    cout<< "otherwise will keep this info untll you enter start!";
    // cp.getCommand(); //prompts user for commands, stores in collection
    // input = cp.commandCollection.at(0).command; //accesses first command given
    // cp.commandCollection.pop_back(); //removes command from collection
    cin >> this->input;
    if (input == "start"){
        state = 1;
    }
}

void GameEngine::MapLoaded(){
    cout<< "Would you like to load the map?" << endl;
    cout<< "Please load a map by entering ( loadmap filename.map)" << endl;
    cp.getCommand(); //prompts user for commands, stores in collection
    // cout << cp.commandCollection.at(0).command; //****for debugging
    input = cp.commandCollection.at(0).command; //accesses first command given
    // cout << "input is: " << input; //****for debugging
    cp.commandCollection.pop_back(); //removes command from collection
    //cin >> this->input; //replaced by CommandProcessor.getCommand()
    if (regex_match(input, regex("(loadmap )(.*).map"))){
        MapLoader ml(input); //GameEngine uses Map for loadmap in StartUpPhase()
        cout<< "Map loading... will you validate the map?" << endl;
        cout<< "Enter (yes) for load a new map, enter (validated) for validated the map.";
        cin >> this->input;
        if (input == "yes"){
            state = 1;
        }
        else if (input == "validated"){
            state = 2;
        }
        else if (input != "validated" && input != "load"){
            state = 1;
            cout << "Wrong input, please enter the rignt one" << endl;
        }
    }
}

void GameEngine::MapValidated(){
    cout<< "Map has been validated" << endl;
    state = 3;
}

void GameEngine::PlayersAdded(){
    cout<<"Would You like to add players?" <<endl;
    cout<<"please enter (addplayer_*) to add player" <<endl;
    cp.getCommand(); //prompts user for commands, stores in collection
    input = cp.commandCollection.at(0).command; //accesses first command given
    cp.commandCollection.pop_back(); //removes command from collection
    //cin >> this->input; //replaced by CommandProcessor.getCommand()
    if (input == "addplayer_*"){ //TODO: replace * with regex
        cout << "player has been added!" << endl;
        cout << "would you like to add other one?" << endl;
        cout << "enter (addplayer_*) for add other one, enter (gamestart) to start game with current players.";
        cin >> this->input;
        if (input == "addplayer_*"){ //TODO: replace * with regex
            cout << "Add other player!" << endl;
            state = 3;
        }
        else if (input == "gamestart"){
            cout << "Game starting!" << endl;
            state = 4;
        }
        
    }
}

void GameEngine::AssignReinforcement(){
    cout << "Would you assign reinforcement?" << endl;
    cout << "Please enter (yes) for assign reinforcement" << endl;
    cin >> this->input;
    if (input == "yes"){
        cout << "Assigned" << endl;
        state = 5;
    }
}

void GameEngine::IssueOrders(){
    cout << "would you issue orders?" <<endl;
    cout << "enter (yes) for issue the order" <<endl;
    cin >> this->input;
    if (input == "yes"){
        cout << "order comfirmed!" << endl;
        cout << "would you issue other order" << endl;
        cout << "enter (yes) for issue the order, enter (no) for excute" <<endl;
        cin >> this->input;
        if (input == "yes"){
            state = 5;
        }
        else if (input == "no"){
            state = 6;
        }
    }
}

void GameEngine::ExecuteOrders(){
    cout << "Your orders have beed excuted!" <<endl;
    cout << "Now you have to choose to win the game or not!" <<endl;
    cout << "Type (win) for win the game!" <<endl;
    cin >> this->input;//type win, if win, otherwise program will keep running
    if (input == "win"){
        state = 7;
    }
    else {
        cout << "The war is keep going on! will you excute your order again?" << endl;
        cout << "enter (excute) for repeat your order, enter (new) for issue new order" << endl;
        cin >> this->input;
        if (input == "excute"){
            state = 6;
        }
        else if (input == "new"){
            state = 5;
        }
    }
}

void GameEngine::Win(){
    cout << "Your enermy has beed defeated, You won!" << endl;
    cout << "Do you want to play again ?(new game)" << endl;
    cout << "enter (replay) to play again, or (quit) to quit." << endl;
    cp.getCommand(); //prompts user for commands, stores in collection
    input = cp.commandCollection.at(0).command; //accesses first command given
    cp.commandCollection.pop_back(); //removes command from collection
    //cin >> this->input; //replaced by CommandProcessor.getCommand()
    if (input == "replay"){
        state = 0;
        cout << "game is resetting!";
    }

    else if (input == "quit") {
        cout << "Thank you for playing this game!!!";
        state = 8; // shut down the loop
    }
}

//Assignment 2 Part 2:
void GameEngine::StartUpPhase(){
    while(state == 0){
        Start();
        while (state == 1){
            MapLoaded();
        }
        while (state == 2){
            MapValidated();
        }
        while (state == 3){
            PlayersAdded();
        }
        while (state == 4){
            AssignReinforcement();
            while (state == 5){
                IssueOrders ();
            }
            while (state == 6){
                ExecuteOrders();
            }
            while (state == 7){
                Win();
            }
        }

    }

}

// //Assignment 2 Part 2:
// void GameEngine::StartUpPhase(){ //this takes the place of Loop()
//     cout<< "Please load a map by entering (loadmap filename.map)" << endl;
//     cp.getCommand(); //prompts user for commands, stores in collection
//     input = cp.commandCollection.at(0).command; //accesses first command given
//     cp.commandCollection.pop_back(); //removes command from collection
//     //cin >> this->input; //replaced by CommandProcessor.getCommand()
//     if (regex_match(input, regex("(loadmap )(.*)"))){
//         MapLoader ml(input); //GameEngine uses Map for loadmap in StartUpPhase()
//     }
//     else if(input == "validatemap"){

//     }
//     else if(regex_match(input, regex("(addplayer )(.*)"))){

//     }
//     else if(input == "start"){
        
//     }

// }
