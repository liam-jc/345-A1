#include "CommandProcessing.h"




//********CommandProcessor**********
        CommandProcessor::CommandProcessor(){} //default constructor

        void CommandProcessor::saveCommand(string s){
            Command c;
            c.command = s; //assign command type from input
            c.saveEffect(s);
            this->commandCollection.push_back(c); //save the command to collection
        };

        void CommandProcessor::readCommand(){
            cout << "Please input a command." << endl;
            cin >> this->commandStr;
            saveCommand(commandStr);
        };

        void CommandProcessor::getCommand(){
            readCommand();
        };


        //destructor
        CommandProcessor::~CommandProcessor(){};


//********Command**********
        Command::Command(){}  //default constructor

        void Command::saveEffect(string s){
            //assign effect corresponding to input
            if (s == "loadmap *"){ //TODO: replace * with regex 
                this->effect = "Load map from file, transition to maploaded state.";
            }
            if (s == "validatemap"){
                this->effect = "Validate map, transition to mapvalidated state.";
            }
            if (s == "addplayer *"){ //TODO: replace * with regex 
                this->effect = "Adds a player, transition to playersadded state.";
            }
            if (s == "gamestart"){
                this->effect = "Start game, transition to assignreinforcement state.";
            }
            if (s == "replay"){
                this->effect = "Restart new game, transition to start state.";
            }
            if (s == "quit"){
                this->effect = "Quit game, exit program.";
            }
        };


        //destructor
        Command::~Command(){};

//*******FileLineReader********
        FileLineReader::FileLineReader(){} //default constructor




        //destructor
        FileLineReader::~FileLineReader(){};
