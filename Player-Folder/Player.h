#pragma once
#include "iostream";
#include "vector";
#include "string";
#include "Cards.h"
#include "Map.h";
#include "Orders.h"

using namespace std;

class Player {
private:
	vector<Territory*> territories;
	OrdersList* orders;
	

public:
	string name;
	Hand* hand;


	/*-----------Constructors-------------*/
	Player();
	Player(string name);
	Player(string name, vector<Territory*> territories, Hand* hand, OrdersList* orders);
	Player(const Player& toCopy);

	/*------------Destructor----------------*/
	~Player();

	/*------------Methods-------------------*/
	void toAttack();
	void toDefend();
	void issueOrder();
};
