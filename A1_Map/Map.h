#ifndef Map_h
#define Map_h

#include <iostream>
#include <string>
#include <vector>
#include<fstream>
#include<cstdlib>
using namespace std;


//dummy class
class Player{
    public:
        Player(string x,int y);
        Player();

        string playerName;
        int playerID;

        string getPName();
        void setPName(string x);
        string toString();
};

class Territory{
    public:
    //Class variables
        int numberOfSolider;
        Player owner;
        int territoryID;
        string territoryName;
        vector<Territory*> edges; //Most important one
    
    //Constructors
        Territory(int id,string name,vector<Territory*> edges, Player owner, int soliders);
        Territory();
        Territory(int id,string name);

    //Get methods
        int getSoliders();
        Player getPlayer();
        int getID();
        string getName();
        vector<Territory*> getEdges();

    //Mutators
        void setSoliders(int x);
        void setPlayer(Player x);
        void setName(string x);
        void setEdges(Territory* x);

    // ToString
        string toString();

    // Method to show all the edges
        string showEdges();
};

class Continent{
    public:
        string continentName;
        vector<Territory> c_countries;
    
        Continent();
        Continent(string x, vector<Territory> y );
        Continent(string x);

        void setTerritories(Territory x);

        string toString();

        bool eularianMap();


};


class Map{
    public:
        string mapName;
        vector<Territory> world;
        vector<Continent> continents;
    
    // Constructor
        Map(string name, vector<Territory> world,vector<Continent> continents);
        Map();

    //Getter
        string getMapName();
        vector<Territory> getWorld();

    //Mutator
        void setMap();
        void setWorld();

    // Display every territory with its associated continent
        public:string toString();

    // Method to verify that every continent is an Eularian Map 
    // and that each territory is attributed to only one continent
        bool isAValidMap();
};


class MapLoader{
    public:
    
        string fileName;
        Map mainMap;

        MapLoader(string x);

        Map returnMap();
};

#endif