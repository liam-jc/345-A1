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

