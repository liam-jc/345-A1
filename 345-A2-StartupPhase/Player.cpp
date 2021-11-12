#include "Player.h"
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
	return territoriesToAttack;
};

vector<Territory*> Player::toDefend(){ //return a list of territories that are to be defended
	vector<Territory*> territoriesToDefend;
	return territoriesToDefend;
};

void Player::issueOrder(string orderToAdd){ //creates an Order object and puts it in the player’s list of orders
	Orders* newOrder = new Orders(orderToAdd);
	this->orders->addOrder(newOrder);
};

void Player::setTerritories(Territory x){
	this->territories.push_back(new Territory (x));
};

