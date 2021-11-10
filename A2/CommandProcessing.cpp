#include "CommandProcessing.h"

using namespace std;


//********CommandProcessor**********
        //CommandProcessor has a collection of Commands
        vector<Command> commandCollection;

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


        bool CommandProcessor::validate(Command toValidate){

        };

        //copy constructor
        CommandProcessor::CommandProcessor(const CommandProcessor &inputCP){ 
            this->commandCollection = inputCP.commandCollection;
            this->commandStr = inputCP.commandStr;
            // cout << "\nCommandProcessor copied." << endl; //for debugging
        };
        
        //ostream overload
        ostream& operator << (ostream& outputStream, const CommandProcessor& c){
            outputStream << "CommandProcessor has: \ncommandCollection:" << endl;
            for (int i=0; i<c.commandCollection.size(); i++){ //show commands
                outputStream << c.commandCollection.at(i) << endl;
            }
            outputStream << "commandStr: " << c.commandStr << endl;
            return outputStream;
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
            if (s != "loadmap *" && s != "validatemap" && s != "replay" && s != "gamestart" && s != "replay" && s != "quit"){
                //case of invalid input should save a record of this in the effect variable
                this->effect = "Invalid command entered. No effect on game.";
            }
        };


        //copy constructor
        Command::Command(const Command &inputCommand){ 
            this->command = inputCommand.command;
            this->effect = inputCommand.effect;
            // cout << "\nCommand copied." << endl; //for debugging
        };
        
        //ostream overload
        ostream& operator << (ostream& outputStream, const Command& c){
            outputStream << "Command has: \ncommand:" << c.command << endl;
            outputStream << "effect: " << c.effect << endl;
            return outputStream;
        };

        //destructor
        Command::~Command(){};

//*******FileLineReader********
        FileLineReader::FileLineReader(){} //default constructor



        //copy constructor
        FileLineReader::FileLineReader(const FileLineReader &input){ 
            //no members
        };
        
        //ostream overload
        ostream& operator << (ostream& outputStream, const FileLineReader& f){
            outputStream << "FileLineReader ostream." << endl;
            return outputStream;
        };  

        //destructor
        FileLineReader::~FileLineReader(){};
