#ifndef CheaterStrategy_h
#define CheaterStrategy_h

#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "PlayerStrategies.h"
using namespace std;


class CheaterStrategy : public PlayerStrategy{
    private:


    public:
        Player* playerOfStrategy;
        string strategyType = "CHEATER";

        /*-----------Constructors-------------*/
        CheaterStrategy();
        // NeutralStrategy(Player* p);
        CheaterStrategy(const CheaterStrategy& toCopy);

        /*------------Destructor----------------*/
        ~CheaterStrategy();

        /*------------Methods-------------------*/
        friend ostream& operator << (ostream& outputStream, const CheaterStrategy& p); //outstream overload
        vector<Territory*> toAttack();
        vector<Territory*> toDefend();
        // Order* issueOrder(); //implemented in GameEngine.cpp
};

#endif
