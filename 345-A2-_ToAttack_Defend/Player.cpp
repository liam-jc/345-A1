#include "Player.h"
#include <algorithm> 
using namespace std;



Player::Player() {
	this->territories = vector<Territory*>();
	this->hand = new Hand();
	this->orders = new OrdersList();
	this->name = "";
}

Player::Player(string name) {
	this->territories = vector<Territory*>();
	this->hand = new Hand();
	this->orders = new OrdersList();
	this->name = name;
}

Player::Player(vector<Territory*> territories, Hand* hand, OrdersList* orders, string name) {
	this->territories = territories;
	this->hand = hand;
	this->orders = orders;
	this->name = name;
}

Player::Player(const Player& toCopy) {
	this->territories = territories;
	this->orders = toCopy.orders;
	this->hand = toCopy.hand;
	this->name = toCopy.name;
}

//destructor
Player::~Player(){}; 

//outstream operator overloading
ostream& operator << (ostream& outputStream, const Player& p){ 
	outputStream << "\n*****Player Info:*****" << endl; 
	outputStream << "Name: " << p.name << endl;
	outputStream << "Hand: " << *(p.hand) << endl;
	outputStream << "Orders: " << endl;
	for(int i = 0; i<(p.orders->getOrdersList()).size(); i++){ //vector iterator
        outputStream<<(p.orders->getOrdersList()).at(i)<<", ";
    }
	outputStream << "\nTerritories: " << endl;
	for(int i = 0; i<p.territories.size(); i++){ //vector iterator
        outputStream<<p.territories.at(i)<<", ";
    }
	return outputStream;
};

vector<Territory*> Player::toAttack(){ //return a list of territories that are to be attacked
	vector<Territory*> territoriesToAttack;
	vector<int> territoryIDcounter;


	//Get all egdes
	for(int i=0; i<territories.size();i++){
		for(int j=0;j<territories[i]->edges.size();j++){
			//cout<<territories[i]->edges[j]->getName()<<endl; debug helper
			if(!(find(territoryIDcounter.begin(),territoryIDcounter.end(),territories[i]->edges[j]->getID())!=territoryIDcounter.end())){
				//cout<<territories[i]->edges[j]->getName()<<endl; debug helper
				territoriesToAttack.push_back(territories[i]->edges[j]);
				territoryIDcounter.push_back(territories[i]->edges[j]->getID());
			}	
		}
	}

	vector<int> PlayerterritoriesID;
    for(int j=0;j<territories.size();j++){
        PlayerterritoriesID.push_back(territories[j]->getID()); 
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
	cout<<"Here are the territories: "<<endl;
	return territoriesToAttack;
};

vector<Territory*> Player::toDefend(){ //return a list of territories that are to be defended
	//vector<Territory*> territoriesToAttack=this->toAttack();
	//vector<int> territoryIDcounter;
	vector<int> PlayerterritoriesID;
	vector<Territory*> territoriesToDefend;
    
	//vector of ID of the territory that the player own
	for(int j=0;j<territories.size();j++){
        PlayerterritoriesID.push_back(territories[j]->getID()); 
	}

	//Verify if a territory has an enemy territory in its egdes
	for(int i=0; i<territories.size();i++){
		bool edgesOutside=false;
		for(int j=0;j<territories[i]->edges.size();j++){
			if(!(find(PlayerterritoriesID.begin(),PlayerterritoriesID.end(),territories[i]->edges[j]->getID())!=PlayerterritoriesID.end())){
				edgesOutside=true;
			}
		}
		if(edgesOutside){
			territoriesToDefend.push_back(territories[i]);
		}
	}
	return territoriesToDefend;
};

void Player::issueOrder(string orderToAdd){ //creates an Order object and puts it in the player’s list of orders
	Orders* newOrder = new Orders(orderToAdd);
	this->orders->addOrder(newOrder);
};

void Player::setTerritories(Territory x){
	this->territories.push_back(new Territory (x));
};

