#include "Player.h"
#include "CheaterStrategy.h"
#include <algorithm> 
using namespace std;

class Order;
class OrdersList;

CheaterStrategy::CheaterStrategy() {
    cout << "Cheater strategy created." << endl;
    strategyType = "NEUTRAL";
}

// NeutralStrategy::NeutralStrategy(Player* p) {
// 	this->playerOfStrategy = p;
//     this->playerOfStrategy = p;
//     strategyType = "NEUTRAL";
//     cout << "Neutral strategy created for player " << p->name << endl;
// }


CheaterStrategy::CheaterStrategy(const CheaterStrategy& toCopy) {
	this->playerOfStrategy = toCopy.playerOfStrategy;
    this->strategyType = toCopy.strategyType;
}

//destructor
CheaterStrategy::~CheaterStrategy(){}; 

//outstream operator overloading
ostream& operator << (ostream& outputStream, const CheaterStrategy& p){ 
	outputStream << "\n*****Player Strategy Info:*****" << endl; 
	outputStream << "Name: " << p.playerOfStrategy << endl;
	outputStream << "Strategy Type: " << p.strategyType << endl;
	return outputStream;
};

vector<Territory*> CheaterStrategy::toAttack(){ 
	//return a list of territories that are to be attacked
	vector<Territory*> territoriesToAttack;
	vector<int> territoryIDcounter;


	//Get all egdes
	for(int i=0; i<playerOfStrategy->territories.size();i++){
		for(int j=0;j<playerOfStrategy->territories[i]->edges.size();j++){
			//cout<<territories[i]->edges[j]->getName()<<endl; debug helper
			if(!(find(territoryIDcounter.begin(),territoryIDcounter.end(),playerOfStrategy->territories[i]->edges[j]->getID())!=territoryIDcounter.end())){
				//cout<<territories[i]->edges[j]->getName()<<endl; debug helper
				territoriesToAttack.push_back(playerOfStrategy->territories[i]->edges[j]);
				territoryIDcounter.push_back(playerOfStrategy->territories[i]->edges[j]->getID());
			}	
		}
	}

	vector<int> PlayerterritoriesID;
    for(int j=0;j<playerOfStrategy->territories.size();j++){
        PlayerterritoriesID.push_back(playerOfStrategy->territories[j]->getID()); 
	}

	cout<<"Here is the ID of your territories:"<<endl;
	 for(int j=0;j<PlayerterritoriesID.size();j++){
        cout<<PlayerterritoriesID[j]<<endl;
	}



	//Remove edges that point to a territory owned by the player
	for(int i=0;i<territoriesToAttack.size();i++){
		if(find(PlayerterritoriesID.begin(),PlayerterritoriesID.end(),territoriesToAttack[i]->getID())!=PlayerterritoriesID.end()){
			//cout<<territoriesToAttack[i]->getName()<<endl; debug helper
			territoriesToAttack.erase(territoriesToAttack.begin()+i);
			i-=1;
		}
	}

	//Remove duplicates
	//territoriesToAttack.erase( unique( territoriesToAttack.begin(), territoriesToAttack.end() ), territoriesToAttack.end() );
	cout<<"Here are the territories that you can attack: "<<endl;
	return territoriesToAttack;
};

vector<Territory*> CheaterStrategy::toDefend(){ //return a list of territories that are to be defended
	vector<int> PlayerterritoriesID;
	vector<Territory*> territoriesToDefend;
    
	//vector of ID of the territory that the player own
	for(int j=0;j<playerOfStrategy->territories.size();j++){
        PlayerterritoriesID.push_back(playerOfStrategy->territories[j]->getID()); 
	}

	//Verify if a territory has an enemy territory in its egdes
	for(int i=0; i<playerOfStrategy->territories.size();i++){
		bool edgesOutside=false;
		for(int j=0;j<playerOfStrategy->territories[i]->edges.size();j++){
			if(!(find(PlayerterritoriesID.begin(),PlayerterritoriesID.end(),playerOfStrategy->territories[i]->edges[j]->getID())!=PlayerterritoriesID.end())){
				edgesOutside=true;
			}
		}
		if(edgesOutside){
			territoriesToDefend.push_back(playerOfStrategy->territories[i]);
		}
	}
	return territoriesToDefend;
};

// Order* CheaterStrategy::issueOrder(){ //implemented in GameEngine.cpp
//     vector<Territory*> territoriesToSteal = playerOfStrategy.toAttack(); //get attackable territories
//     for (int i = 0; i < territoriesToSteal.size(); i++){ //steal territories
//         //make variables to use as arguments for Advance Order constructor
//         Player* p = playerOfStrategy;
//         // Player* p2 = territoriesToSteal[i]->owner; //doesn't work because owner of a Territory is a string, needs to be changed to a Player
//         // Territory* source = //TODO get neighbouring territory owned by attacking player
//         Territory* target = territoriesToSteal[i];
//         // int numToAdvance = //TODO get number of armies from attacking player's territory, -1
//         Advance a(p, p2, source, target, numToAdvance); //Advance has been changed in Orders so that if a Player's Strategy is CHEATER, they will win the territory outright
//     }


// 	    Order* o; //TODO sort out logic with returned Order
// 	    return o;
// };

