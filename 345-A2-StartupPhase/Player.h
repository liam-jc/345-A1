#ifndef Player_h
#define Player_h

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Cards.h"
#include "Map.h"
#include "Orders.h"

using namespace std;

class Player {
private:
	OrdersList* orders;
	

public:
	vector<Territory*> territories;
	string name;
	Hand* hand;


	/*-----------Constructors-------------*/
	Player();
	Player(string name);
	Player(vector<Territory*> territories, Hand* hand, OrdersList* orders, string name);
	Player(const Player& toCopy);

	/*------------Destructor----------------*/
	~Player();

	/*------------Methods-------------------*/
    	friend ostream& operator << (ostream& outputStream, const Player& p); //outstream overload
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
	void issueOrder(string orderToAdd);
	void setTerritories(Territory x);
};

#endif
