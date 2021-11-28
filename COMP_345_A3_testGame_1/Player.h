#ifndef Player_h
#define Player_h

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Orders.h"
#include "Cards.h"
#include "Map.h"
// #include "Orders.h"

using namespace std;

//forward declarations
class Order;
class OrdersList;
class Hand;
static int idMaker;

class Player {
private:
	// OrdersList* ordersList;
	// vector<Order*> orders;

public:
	//Order tempOrder;
	OrdersList* ordersList;		
	int id;
	int reinforcementsAvailable;
	bool isNeutral = false;
	vector<Territory*> territories;
	vector<Player*> unattackable;
	string name;
	Hand* hand;
	friend class Order; //to allow Order.validate() and Order.execute() to access Player functions

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
	// void issueOrder(string orderToAdd);
	void setTerritories(Territory* x);
	vector<Territory*> getOwnedTerit();
	void setOwnedTerit(vector<Territory*> tv);
	int getReinforce(); //getter for reinforcementsAvailable member
	void setReinforce(int i); //setter for reinforcementsAvailable member
	int getPlayerId();
	vector<Player*> getUnattackable();
	void setUnattackable(vector<Player*> pv);

};

#endif
