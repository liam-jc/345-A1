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



void GameEngine::AssignReinforcement(){
    cout<<"\n-----------------\nREINFORCEMENT PHASE\n-----------------\n"<<endl;
    for(int i=0;i<Players.size();i++){
        cout << "\nWould you assign reinforcement "+ Players[i].name+"?" << endl;
        cout << "Please enter (yes) for assign reinforcement" << endl;
        cin >> this->input;
        if (input == "yes"){
            
            // Determing the number of new solider the player has

            //Minimum number
            int numberOfSoliders=3+Players[i].territories.size()/3;
            vector<int> PlayerterritoriesID;
            
            //Back up
            for(int j=0;j<Players[i].territories.size();j++){
                    PlayerterritoriesID.push_back(Players[i].territories[j]->getID()); 
            }

            sort(PlayerterritoriesID.begin(),PlayerterritoriesID.end());
            vector<int> ContinentTerritoriesID; //This vector will allow to compare with each vector of territory of each continent
            
            for(int j=0;j<mainMap.continents.size();j++){ //for loop that iterates trought the continents
                for (int k = 0; k < mainMap.continents[j].c_countries.size(); k++){  //for loop that iterates trought the countrie of the continents
                    ContinentTerritoriesID.push_back(mainMap.continents[j].c_countries[k].getID()); //store all the ID in the vector
                }
                sort(ContinentTerritoriesID.begin(),ContinentTerritoriesID.end());
                if(includes(PlayerterritoriesID.begin(),PlayerterritoriesID.end()
                    ,ContinentTerritoriesID.begin(),ContinentTerritoriesID.end())){ //compare

                        cout<<Players[i].name+" owns "+mainMap.continents[j].continentName<<endl;
                        cout<<"He will receive 7 more soliders"<<endl;
                        numberOfSoliders+=7;

                }
                ContinentTerritoriesID.clear();
                
            }

            cout<<"You have "+to_string(numberOfSoliders)+" in reinforcement"<<endl;
            cout<<"Here is all your territories: "<<endl;

             for (int j = 0; j < Players[i].territories.size(); j++){
                    cout<<Players[i].territories[j]->toString()<<endl;
             }

             //Assigning reinforcement

             while(numberOfSoliders!=0){
                 int InputID;
                 int backup;
                 
                 cout<<"Please enter the territory ID that you want to reinforce"<<endl;
                 cin>>InputID;
                 cout<<"Please enter the number of soliders you want to add"<<endl;
                 cin>> backup;

                for(int j=0;j<Players[i].territories.size();j++){
                    if(InputID==Players[i].territories[j]->getID()){
                        Players[i].territories[j]->numberOfSolider=Players[i].territories[j]->getSoliders()+backup;
                        numberOfSoliders-=backup;
                    }
                }
                cout<<"Here is the number of soliders remaining: "+ to_string(numberOfSoliders)<<endl;
             }
            cout << "'\nReinforcement Assigned for "+Players[i].name<< endl;
            cout<<"Here is all your territories: "<<endl;
             for (int j = 0; j < Players[i].territories.size(); j++){
                    cout<<Players[i].territories[j]->toString()<<endl;
             }  
        }
    }
    state = 5;    
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
    cout << "Your enemy has beed defeated, You won!" << endl;
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

/*Assignment 2 Part 2:
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

}*/

//Assignment 2 Part 2:
void GameEngine::StartUpPhase(){ //this takes the place of Loop()
    bool key=true;
    while(key){
        cout<< "Please load a map by entering (loadmap filename.map)" << endl;
        cout<< "Enter \"validatemap\" if you want to make sure to your map is valid for play" << endl;
        cout<<"Enter \"addplayer\" if you want to add new player"<<endl;
        cout<<"Enter \"start\" if you want to start the game"<<endl; 
        cp.getCommand(); //prompts user for commands, stores in collection
        input = cp.commandCollection.at(0).command; //accesses first command given
        cp.commandCollection.pop_back(); //removes command from collection
        if (regex_match(input, regex("(loadmap )(.*)"))){
            MapLoader ml(input.substr(8,input.length()-1)); //GameEngine uses Map for loadmap in StartUpPhase()
            this->mainMap=ml.mainMap;
            



        }
        else if(input == "validatemap"){
            cout<<this->mainMap.isAValidMap()<<endl;
            cout<< "Map has been validated" << endl;
        }
        //else if(regex_match(input, regex("(addplayer )(.*)"))){
        else if(input=="addplayer"){
            int numberOfPlayers;
            cout<<"Please enter the number of player"<<endl;
            cin>> numberOfPlayers;
            for(int i=0;i<numberOfPlayers;i++){
                cout<< "Please enter the name of the player"<<endl;
                string playerName;
                cin>>playerName;
                Player *p= new Player(playerName);
                Players.push_back(*p);  
            }
            //delete p;
            //p=NULL;
        }
        else if(input == "start"){

        //Deteriming the order
                    
            random_shuffle(Players.begin(),Players.end());
            cout<<" The order of play is :"<<endl;
            for(int i=0;i<Players.size();i++){
                cout<< Players[i].name<<endl;
            }




            //Distrubting territories to players
                   
            if (mainMap.world.size()%Players.size()==0){
                cout<<"The number of territory is divisble by the number of players"<<endl;
                int TerritoriesForEachPlayer=mainMap.world.size()/Players.size();
                cout<<"Each player will have "+to_string(TerritoriesForEachPlayer)+" territories"<< endl;
            }
            else{
                cout<<"The number of territory is not divisible by the number of players, some player will have more territories than others"<<endl;
            }
            int counter=0;
            for(int i=0;i<mainMap.world.size();i++){
                cout<<counter<<endl;
                //Territory *ptr=new Territory(mainMap.world[i]);
                
                Players[counter].setTerritories(mainMap.world[i]);
                counter+=1;
                if(counter==Players.size())counter=0;
                //delete ptr;
                //ptr=NULL;
            }
        
            //Give 50 initals armies

            for(int i=0;i<Players.size();i++){
                int limit=Players[i].territories.size();
                int counter=0;
                for(int j=0;j<50;j++){
                    Players[i].territories[counter]->numberOfSolider=Players[i].territories[counter]->getSoliders()+1;
                    counter+=1;
                    if (counter==limit)counter=0;
                }
            }

            cout<<"The soliders have been installed"<<endl;
            cout<<mainMap.toString()<<endl;
            cout<<"Territories of each player"<<endl;
            for (int i = 0; i <Players.size(); i++)
            {
                cout<<"\n"+Players[i].name+" has " + to_string(Players[i].territories.size())+ " territories:"<<endl;
                for (int j = 0; j < Players[i].territories.size(); j++)
                {
                    cout<<Players[i].territories[j]->toString()<<endl;
                }
                
            }
            

            // Each player draw 2 cards from the deck

            //gameDeck=Deck(); //Initialized at the start
                    
            for(int i=0;i<Players.size();i++){
                cout<<"\nIt is the turn of "+Players[i].name+" to draw 2 cards:"<<endl;
                Players[i].hand->addCardToHand(gameDeck.draw());
                Players[i].hand->addCardToHand(gameDeck.draw());
            }

            //ending the loop and proceeding to the next phase 

            key=false;

        }
    }    

}
