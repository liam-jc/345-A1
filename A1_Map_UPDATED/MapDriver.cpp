#include "Map.h"
#include <iostream>
#include<fstream>
#include <vector>
#include<cstdlib>
#include<string>
#include <sstream>


int main( ){
    
    // Reading the file and creating the Maploader object with the map inside it
    string x;
    cout<<"Please enter the name of the map file:";
    cin>>x;
    cout<<x<<endl;
    MapLoader m= MapLoader(x);
    Map world=m.returnMap();
    cout<<world.toString();

    // Displaying the info and the edges of the territory that the user want

    while(true){
        int input1;
        cout<<"\nEnter the terriory ID on which you want to get the info of: ";
        cin>>input1;
        cout<<"Here are the infos of territory : "+std::to_string(input1)<<endl;
        cout<<world.getWorld()[input1-1].toString();
        cout<<world.getWorld()[input1-1].showEdges();
        cout<<"\nDo you want to get the info of another territory? If yes press 1, if no press 0"<<endl;
        int input2;
        cin>>input2;
        if(input2==0) break;
    }

    cout<<world.isAValidMap()<<endl;


    return 0;
}
