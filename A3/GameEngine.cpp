#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <string>
#include <sstream>
#include <regex>
#include "GameEngine.h"


using namespace std;


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
        cout << "\nWould you see your reinforcement "+ (*Players[i]).name+"?" << endl;
        cout << "Please enter (yes) to continue" << endl;
        cin >> this->input;
        if (input == "yes"){
            
            // Determing the number of new solider the player has

            //Minimum number
            int numberOfSoliders=3+(*Players[i]).territories.size()/3;
            vector<int> PlayerterritoriesID;
            
            //Back up
            for(int j=0;j<(*Players[i]).territories.size();j++){
                    PlayerterritoriesID.push_back((*Players[i]).territories[j]->getID()); 
            }

            sort(PlayerterritoriesID.begin(),PlayerterritoriesID.end());
            vector<int> ContinentTerritoriesID; //This vector will allow to compare with each vector of territory of each continent
            
            for(int j=0;j<(*mainMap).continents.size();j++){ //for loop that iterates trought the continents
                for (int k = 0; k < (*(*mainMap).continents[j]).c_countries.size(); k++){  //for loop that iterates trought the countries of the continents
                    ContinentTerritoriesID.push_back((*(*mainMap).continents[j]).c_countries[k]->getID()); //store all the ID in the vector
                }
                sort(ContinentTerritoriesID.begin(),ContinentTerritoriesID.end());
                if(includes(PlayerterritoriesID.begin(),PlayerterritoriesID.end()
                    ,ContinentTerritoriesID.begin(),ContinentTerritoriesID.end())){ //compare

                        cout<<(*Players[i]).name+" owns "+(*(*mainMap).continents[j]).continentName<<endl;
                        cout<<"He will receive 7 more soliders"<<endl;
                        numberOfSoliders+=7;

                }
                ContinentTerritoriesID.clear();
                
            }

            //Update player.reinforcementsAvailable member
            (*Players[i]).setReinforce(numberOfSoliders+(Players[i]->getReinforce()));
            cout<<"You have "+to_string(Players[i]->getReinforce())+" in reinforcement"<<endl;
            cout<<"Here is all your territories: "<<endl;
             for (int j = 0; j < (*Players[i]).territories.size(); j++){
                    cout<<(*Players[i]).territories[j]->toString()<<endl;
             }

             //Assigning reinforcement (This is replaced in the Deployment card)

             /*while(numberOfSoliders>0){
                 int InputID;
                 int backup;
                 //Inputs
                 cout<<"Please enter the territory ID that you want to reinforce"<<endl;
                 cin>>InputID;
                 cout<<"Please enter the number of soliders you want to add"<<endl;
                 cin>> backup;

                for(int j=0;j<(*Players[i]).territories.size();j++){
                    
                    //If the player wants to add more soliders than he can
                    if(backup>numberOfSoliders){
                        cout<<" You are trying to assing more soliders than you can, please re-enter your inputs"<<endl;
                        break;
                    }

                    //If the territory is found
                    if(InputID==(*Players[i]).territories[j]->getID()){
                        (*Players[i]).territories[j]->numberOfSolider=(*Players[i]).territories[j]->getSoliders()+backup;
                        numberOfSoliders-=backup;
                        break;
                    }

                    //If the territory is not found (end of the loop)
                    if(j==(*Players[i]).territories.size()-1){
                         cout<<"Territories ID not found"<<endl;
                    }
                }
                cout<<"Here is the number of soliders remaining: "+ to_string(numberOfSoliders)<<endl;
                //Update player.reinforcementsAvailable member
                (*Players[i]).setReinforce(numberOfSoliders);
             }

            cout << "'\nReinforcement Assigned for "+(*Players[i]).name<< endl;
            cout<<"Here is all your territories: "<<endl;
             for (int j = 0; j < (*Players[i]).territories.size(); j++){
                    cout<<(*Players[i]).territories[j]->toString()<<endl;
             }*/  
        }
    }
    state = 5;    
}

void GameEngine::IssueOrders(){
    cout<<"\n-----------------\nISSUE ORDER PHASE\n-----------------\n"<<endl;
    for(int i=0;i<Players.size();i++){
        cout << "would you issue orders "+(*Players[i]).name+"?" <<endl;
        cout << "enter (yes) for issue the order" <<endl;
        cin >> this->input;
        if (input == "yes"){

            //ToAttack (show territories that players can attack)
            vector<Territory*> attackTerritories;
            cout<<"Here is a list of territories that you can attack:"<<endl;
            // if (Players[i]->playerStrategy->toAttack() == NULL){
            //     cout << "No territories to attack." << endl;
            // }
            // else{
                cout << "*Player is " << *Players[i] << endl; //for debugging
                // cout << "Player is " << Players[i] << endl; //for debugging
                cout << "Player strategy is " << *((*Players[i]).playerStrategy) << endl; //for debugging
                attackTerritories=(*Players[i]).playerStrategy->toAttack();
                if (attackTerritories.size()!=0){ //in case of Neutral player where toAttack() is empty (because Neutral never attacks)
                    for(int j=0;j<attackTerritories.size();j++){
                        cout<<attackTerritories[j]->toString()<<endl;
                    }
                }
            // }

            


            //ToDefend (show territories that the players can defend)

            cout<<"\nHere is a list of territories that you can defend:"<<endl;
            vector<Territory*> defendTerritories=(*Players[i]).playerStrategy->toDefend();

            for(int j=0;j<defendTerritories.size();j++){
                cout<<defendTerritories[j]->toString()<<endl;
            }



            cout<<"The orders you can use are: "<<endl;
            cout<<"ADVANCE, or your cards: "<<endl;
            for(int z = 0; z < (*Players[i]).hand->handOfCards.size(); z++){
                cout<<(*Players[i]).hand->handOfCards.at(z)<<endl;
            }
            cout<<"What order will you use, "<<(*Players[i]).name<<"?"<<endl;
            string orderInput;
            cin>>orderInput;
            cout<<(*Players[i]).name<<" used "<<orderInput<<"!"<<endl;
            //this is where card.play() would be used if it worked 
            if (orderInput == "ADVANCE"){
                // Player a = Players[i]; //player using order
                // Player b; //player being attacked
                
                Territory* start;
                Territory* finish;
                int armies;
                Player * secondplayer;
                
                
                //Territory start
                bool key=true;
                while(key){
                    cout<<"Please enter the ID of territory to advance from:"<<endl;
                    int terr1;
                    cin>>terr1;
                    for (int j=0; j<Players[i]->territories.size();j++){
                        if(Players[i]->territories[j]->getID()==terr1){
                            start=Players[i]->territories[j];
                            key=false;
                        }
                    }
                    
                    if(key){
                        cout<<"Wrong input, you have no territories with ID "+terr1<<endl;
                        cout<<"Here is the list of all your territories:\n";
                        for(int j=0; j<Players[i]->territories.size();j++){
                            cout<<Players[i]->territories[j]->toString()<<endl;
                        }    
                    }
                }


                //Territory finish
                key=true;
                while(key){
                    cout<<"Please the ID of the territory that you want to advance to"<<endl;
                    cout<<(*start).showEdges()<<endl; 
                    int terr1;
                    cin>>terr1;
                    for (int j=0; j<(*start).edges.size();j++){
                        if((*start).edges[j]->getID()==terr1){
                            finish=(*start).edges[j];
                            key=false;
                        }
                    }

                    if(key){
                        cout<<"Wrong input, you can't attack "+terr1<<endl;
                        cout<<"Please re-enter your input: "<<endl;
                    }
                }
                
                
                
                //Don't need since each territories show its owner
                /*cout<<"Please enter name of player to advance on: "<<endl;
                string playerB;
                cin>>playerB;*/
                
                //finding second player
                for(int j=0; j < Players.size(); j++){ 
                    if ((*Players[j]).name == (*finish).owner){
                        secondplayer = Players[j];
                        break;
                    }
                }
                
                //num of Armies

                cout<<"Please enter number of armies to advance: "<<endl;
                int armiesIn;
                cin>>armiesIn;
                cout<<"Ok. "<<armiesIn<<" soliders."<<endl;
                cout<<"These soliders will advance in the order execution phase."<<endl;
               
               
               
               // Adding order to order list
               Advance* inputOrder=new Advance(Players[i],secondplayer,start,finish,armiesIn);
               (*Players[i]).ordersList->addOrder(inputOrder);
        
            }

            if (orderInput == "DIPLOMACY"){
               
                //finding second player
                Player* playerB;
                cout<<"Please enter name of player to Negotiate with: "<<endl;
                string namePlayerB;
                cin>>namePlayerB;
                int z = 0;
                for(z; z < Players.size(); z++){ //Players[z] will be player being negotiated with
                    if ((*Players[z]).name == namePlayerB){
                        cout<<"Ok."<<endl;
                        playerB = Players[z];
                        break;
                    }
                }

                //Adding order to order list
                Negotiate* inputOrder=new Negotiate(Players[i],playerB);
                Players[i]->ordersList->addOrder(inputOrder);

                cout<<"Order added, it will be executing in the next phase"<<endl;
            }

            if (orderInput == "BLOCKADE"){
                //finding territory
                Territory* terrToBlockade;
                cout<<"Please enter ID of territory to Blockade: "<<endl;
                int terr1;
                cin>>terr1;
                for(int z = 0; z < (*Players[i]).territories.size(); z++){
                    if ((*Players[i]).territories.at(z)->getID() == terr1){
                        cout<<"Ok. Territory "<<(*Players[i]).territories.at(z)->getName()<<endl;
                        terrToBlockade = (*Players[i]).territories.at(z);
                    }
                }
                Blockade* inputOrder= new Blockade (Players[i], terrToBlockade);
                Players[i]->ordersList->addOrder(inputOrder);
                cout<<"Order added, it will be executing in the next phase"<<endl;
            }

            // if (orderInput == "BOMB"){
            //     // Player a = Players[i]; //player using order
            //     Territory* terrToBomb;
            //     cout<<"Please enter name of territory to Bomb: "<<endl;
            //     string terr1;
            //     cin>>terr1;
            //     for(int k = 0; k < Players.size(); k++){
            //         for(int z = 0; z < Players[k].territories.size(); z++){
            //             if (Players[k].territories.at(z)->getName() == terr1){
            //                 cout<<"Ok. Territory "<<Players[k].territories.at(z)->getName()<<endl;
            //                 terrToBomb = Players[k].territories.at(z);
            //             }
            //         }
            //     }            
            //     Player* aP = new Player(Players[i]);
            //     Bomb ord1(aP, terrToBomb);
            //     ord1.validate();
            //     ord1.execute();
            // }

            if (orderInput == "BOMB"){
                Territory* toBomb;
                
                
                //Dont need this
                /*cout<<"Please enter name of player to bomb on: "<<endl;
                string playerB;
                cin>>playerB;
                int w = 0;
                for(w; w < Players.size(); w++){
                    if ((*Players[w]).name == playerB){
                        cout<<"Ok."<<endl;
                        break;
                        // b = Players[z];
                    }
                }*/
                bool key=true;
                while(key){
                    cout<<"Please enter the ID of the territory that you want to bomb (Must be in the territories that you can attack) "<<endl; 
                    int terr1;
                    cin>>terr1;
                    for (int j=0; j<attackTerritories.size();j++){
                        if((attackTerritories[j]->getID()==terr1)){
                            toBomb=attackTerritories[j];
                            key=false;
                        }
                    }
                    if(key){
                        cout<<"Wrong input, you can't attack territory number "+terr1<<endl;
                        cout<<"Please re-enter your input: "<<endl;
                    }
                }
                Bomb* inputOrder= new Bomb (Players[i], toBomb);
                cout<<"Bomb created"<<endl;
                Players[i]->ordersList->addOrder(inputOrder);
                cout<<"Bomb will be dropped in the next phase"<<endl;
            }

            if(orderInput=="AIRLIFT"){
                
                Territory* start;
                Territory* finish;
                int armies;


                //Territory start
                bool key=true;
                while(key){
                    cout<<"Please enter ID of territory to advance from:"<<endl;
                    int terr1;
                    cin>>terr1;
                    for (int j=0; j<Players[i]->territories.size();j++){
                        if(Players[i]->territories[j]->getID()==terr1){
                            start=Players[i]->territories[j];
                            key=false;
                            break;
                        }
                    }
                    if(key){
                        cout<<"Wrong input, you have no territories number  "+terr1<<endl;
                        cout<<"Here is the list of all your territories: "<<endl;
                        for(int j=0; j<Players[i]->territories.size();j++){
                            cout<<Players[i]->territories[j]->toString()<<endl;
                        }
                    }
                }


                //Territory finish
                key=true;
                while(key){
                    cout<<"Please enter ID of territory that you want to advance to: "<<endl;
                    int terr1;
                    cin>>terr1;
                    for (int j=0; j<Players[i]->territories.size();j++){
                        if(Players[i]->territories[j]->getID()==terr1){
                            finish=Players[i]->territories[j];
                            key=false;
                        }
                    }

                    if(key){
                        cout<<"Wrong input, you have no territories number  "+terr1<<endl;
                        cout<<"Here is the list of all your territories: ";
                        for(int j=0; j<Players[i]->territories.size();j++){
                            cout<<Players[i]->territories[j]->toString()<<endl;
                        }
                    }    
                }

                //Num of armies
                cout<<"Please enter number of armies to advance: "<<endl;
                cin>>armies;
                cout<<"Ok. "<<armies<<" soliders."<<endl;
                cout<<"These soliders will be transported in the order execution phase."<<endl;


                Airlift* inputOrder=new Airlift(Players[i],start,finish,armies);
                Players[i]->ordersList->addOrder(inputOrder);

            }

            if(orderInput=="REINFORCEMENT"){
                Territory* target;
                //Soliders to be deployed
                cout<<"Here are the soliders you have in backup: "+to_string((*Players[i]).getReinforce())<<endl;
                bool key=true;
                int numberOfSoliders=0;
                while(key){
                    cout<<" Enter how many soliders you want to assign"<<endl;
                    cin>>numberOfSoliders;
                    if(numberOfSoliders>Players[i]->getReinforce()){
                        cout<<"You are trying to assign more soliders than you, please re-enter your input "<<endl;
                    }
                    else{
                        break;
                    }
                }

                //Finding which territory he want to reinforce
                int InputID;
                cout<<"Here is all your territories: "<<endl;
                for (int j = 0; j < (*Players[i]).territories.size(); j++){
                    cout<<(*Players[i]).territories[j]->toString()<<endl;
                }
                cout<<"Please enter the territory ID that you want to reinforce"<<endl;
                cin>>InputID;

                for (int j = 0; j < (*Players[i]).territories.size(); j++){
                    if(InputID==Players[i]->territories[j]->getID()){
                        target=Players[i]->territories[j];
                    }
                }

                Deploy* inputOrder=new Deploy(Players[i],target,numberOfSoliders);
                Players[i]->ordersList->addOrder(inputOrder);
                //Assigning the soliders should be done in the execute method of the Deploy class
                /*while(numberOfSoliders>0){
                    int InputID;
                    int backup;
                    //Inputs
                    cout<<"Please enter the territory ID that you want to reinforce"<<endl;
                    cin>>InputID;
                    cout<<"Please enter the number of soliders you want to add"<<endl;
                    cin>> backup;

                    for(int j=0;j<(*Players[i]).territories.size();j++){
                    
                        //If the player wants to add more soliders than he can
                        if(backup>numberOfSoliders){
                            cout<<" You are trying to assing more soliders than you can, please re-enter your inputs"<<endl;
                            break;
                        }

                        //If the territory is found
                        if(InputID==(*Players[i]).territories[j]->getID()){
                            (*Players[i]).territories[j]->numberOfSolider=(*Players[i]).territories[j]->getSoliders()+backup;
                            numberOfSoliders-=backup;
                            break;
                        }

                        //If the territory is not found (end of the loop)
                        if(j==(*Players[i]).territories.size()-1){
                            cout<<"Territories ID not found"<<endl;
                        }
                    }
                    cout<<"Here is the number of soliders remaining: "+ to_string(numberOfSoliders)<<endl;
                }

                cout << "'\nReinforcement Assigned for "+(*Players[i]).name<< endl;
                cout<<"Here is all your territories: "<<endl;
                for (int j = 0; j < (*Players[i]).territories.size(); j++){
                    cout<<(*Players[i]).territories[j]->toString()<<endl;
                }*/  
            }
            cout << "order confirmed!" << endl;
            //cout << "would you issue other order" << endl;
            cout << "Please enter continue for the game to proceed" <<endl;
            cin >> this->input;
            if (input == "yes"){
                state = 5;
            }
            else if (input == "continue"){
                state = 6;
            }
        }
    }    
}


void GameEngine::ExecuteOrders(){
    cout<<"\n-----------------\nORDER EXECUTION PHASE\n-----------------\n"<<endl;
    for(int i=0;i<Players.size();i++){
        (*Players[i]).ordersList->getOrdersList().back()->execute();// execute last order in the list
        //(*Players[i]).ordersList->getOrdersList().erase((*Players[i]).ordersList->getOrdersList().begin()); // remove the  first order from order list
    }
    cout<<"HERE IS THE MAP AT THE END OF THIS EXEXCUTION PHASE:"<<endl;
    cout<<(*mainMap).toString()<<endl;


   cout<<" EACH PLAYER WILL NOW DRAW ONE CARD FROM THE DECK TO END THIS ROUND"<<endl;

    for(int i=0;i<Players.size();i++){
                cout<<"\nIt is the turn of "+(*Players[i]).name+" to draw 2 cards:"<<endl;
                (*Players[i]).hand->addCardToHand(gameDeck.draw());
            }
}



/*void GameEngine::ExecuteOrders(){
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
}*/


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

//Assignment 2 Part 2:
void GameEngine::StartUpPhase(){ //this takes the place of Loop()
    cout << gameDeck;
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
            mainMap= ml.returnMap();
        }
        else if(input == "validatemap"){
            cout<<(*mainMap).isAValidMap()<<endl;
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
                Player* p= new Player(playerName);
                cout<< "Please select the strategy of the player:"<<endl;
                cout<< "Enter (1) for Human Player" << endl;
                cout<< "Enter (2) for Aggressive Player" << endl;
                cout<< "Enter (3) for Benevolent Player" << endl;
                cout<< "Enter (4) for Neutral Player" << endl;
                cout<< "Enter (5) for Cheater Player" << endl;
                int strategyInput;
                cin>>strategyInput; //TODO error handling for wrong input
                AggressiveStrategy* newAggressiveStrategy = new AggressiveStrategy();
                NeutralStrategy* newNeutralStrategy = new NeutralStrategy();
                switch(strategyInput){
                    case 1:
                        //HumanStrategy newStrategy; //TODO
                        // newStrategy->playerOfStrategy = p;
                        // p->setStrategy(newStrategy);
                        break;
                    case 2:
                        
                        newAggressiveStrategy->playerOfStrategy = p;
                        cout << "newAggressiveStrategy is " << *newAggressiveStrategy <<endl; //for debugging
                        p->setStrategy(newAggressiveStrategy);
                        break;
                    case 3:
                        //BenevolentStrategy newStrategy; //TODO
                        // newStrategy->playerOfStrategy = p;
                        // p->setStrategy(newStrategy);
                        break;
                    case 4:
                        
                        newNeutralStrategy->playerOfStrategy = p; //assign player to Strategy so it can access Player members
                        cout << "newNeutralStrategy is " << *newNeutralStrategy <<endl; //for debugging
                        p->setStrategy(newNeutralStrategy); //assign Strategy to player
                        break;
                    case 5:
                        //CheaterStrategy newStrategy; //TODO
                        // newStrategy->playerOfStrategy = p;
                        // p->setStrategy(newStrategy);
                        break;
                }
                Players.push_back(p);  
            }
            //delete p;
            //p=NULL;
        }
        else if(input == "start"){

            //Deteriming the order
                    
            // random_shuffle(Players.begin(),Players.end()); //this gives me "error: use of undeclared identifier 'random_shuffle'", removed temporarily -Liam
            cout<<" The order of play is :"<<endl;
            for(int i=0;i<Players.size();i++){
                cout<< (*Players[i]).name<<endl;
            }




            //Distrubting territories to players
                   
            if ((*mainMap).world.size()%Players.size()==0){
                cout<<"The number of territory is divisble by the number of players"<<endl;
                int TerritoriesForEachPlayer=(*mainMap).world.size()/Players.size();
                cout<<"Each player will have "+to_string(TerritoriesForEachPlayer)+" territories"<< endl;
            }
            else{
                cout<<"The number of territory is not divisible by the number of players, some player will have more territories than others"<<endl;
            }
            int counter=0;
            for(int i=0;i<(*mainMap).world.size();i++){
                // cout<<counter<<endl; //for debugging
                //Territory *ptr=new Territory(mainMap.world[i]);
                (*Players[counter]).setTerritories((*mainMap).world[i]);
                (*mainMap).world[i]->owner=(*Players[counter]).name;
                (*mainMap).world[i]->ownerPlayer=Players[counter]; //NEW for use in AggressiveStrategy issueOrder()
                counter+=1;
                if(counter==Players.size())counter=0;
                //delete ptr;
                //ptr=NULL;
            }

            //Debugging: setting initial army to every territory to 10

            /*for(int i=0;i<(*mainMap).world.size();i++){
                (*(*mainMap).world[i]).numberOfSolider=10;
            }*/            
        
            //Give 50 initals armies

            for(int i=0;i<Players.size();i++){
                int limit=(*Players[i]).territories.size();
                int counter=0;
                for(int j=0;j<50;j++){
                    (*(*Players[i]).territories[counter]).numberOfSolider=(*(*Players[i]).territories[counter]).getSoliders()+1;
                    counter+=1;
                    if (counter==limit)counter=0;
                }
            }

            cout<<"The soliders have been installed"<<endl;


            //Debugging: verify if the map toString works well

            /*for(int i=0;i<(*mainMap).world.size();i++){
                cout<<(*(*mainMap).world[i]).toString()<<endl;
            }*/ 


            cout<<(*mainMap).toString()<<endl;
            cout<<"Territories of each player"<<endl;
            for (int i = 0; i <Players.size(); i++)
            {
                cout<<"\n"+(*Players[i]).name+" has " + to_string((*Players[i]).territories.size())+ " territories:"<<endl;
                for (int j = 0; j < (*Players[i]).territories.size(); j++)
                {
                    cout<<(*Players[i]).territories[j]->toString()<<endl;
                }
                
            }
            

            // Each player draw 2 cards from the deck

            //gameDeck=Deck(); //Initialized at the start
                    
            for(int i=0;i<Players.size();i++){
                cout<<"\nIt is the turn of "+(*Players[i]).name+" to draw 2 cards:"<<endl;
                (*Players[i]).hand->addCardToHand(gameDeck.draw());
                (*Players[i]).hand->addCardToHand(gameDeck.draw());
            }

            //ending the loop and proceeding to the next phase 

            key=false;
        }
    }    
}


bool GameEngine::testWinning(){
    for(int i=0;i<Players.size();i++){
        if(Players[i]->getOwnedTerit().size()==mainMap->world.size()){ //Compare the size of vector territories of each player with the world
            cout<<Players[i]->name+ " conquered "+mainMap->mapName+" !!!!\n GAME IS OVER"<<endl;
            return false;
        }
    }
    return true;
}





//Loop that run the game and tests all functions, phases and orders

void GameEngine::tesGame(){
    StartUpPhase();
    bool key=true;
    while (key){
        AssignReinforcement();
        IssueOrders();
        ExecuteOrders();
        key=testWinning();
    }
    Win();
}