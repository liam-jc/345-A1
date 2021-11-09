#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

class CommandProcessor{
    private:      
        // readCommand: 
        // •gets commands from the console as a string,
        // •stores the command internally in a collection of Command objects using saveCommand()
        // •provides a public getCommand() to other objects such as the GameEngine or the Player
        void readCommand(); 
        void saveCommand(string s);

    public:     
        vector<Command> commandCollection;
        string commandStr;
        CommandProcessor(); //default constructor
        CommandProcessor(const CommandProcessor &commandProcessorToCopy); //copy costructor
        friend ostream& operator << (ostream& outputStream, const CommandProcessor& c); //outstream overload
        void getCommand();
        //void saveEffect(Command inputCommand);
        bool validate(Command toValidate);
        ~CommandProcessor(); //destructor
};

class Command{
    private:
    

    public:
    void saveEffect(string s);
    string command;
    string effect;
    Command(); //default constructor
    Command(const Command &commandToCopy); //copy costructor
    friend ostream& operator << (ostream& outputStream, const Command& c); //outstream overload
    ~Command(); //destructor
};

class FileCommandProcessorAdapter:CommandProcessor{
        private:      
        // readCommand: 
        // •gets commands from the console as a string,
        // •stores the command internally in a collection of Command objects using saveCommand()
        // •provides a public getComman() to other objects such as the GameEngine or the Player
        void readCommand(); 

    public:     
        string commandStr;
        FileLineReader flr;
        FileCommandProcessorAdapter(); //default constructor
        FileCommandProcessorAdapter(const FileCommandProcessorAdapter &commandProcessorToCopy); //copy costructor
        friend ostream& operator << (ostream& outputStream, const FileCommandProcessorAdapter& c); //outstream overload
        void getCommand();
        ~FileCommandProcessorAdapter(); //destructor
};

class FileLineReader{
    private:
    void readLineFromFile();

    public:
    FileLineReader(); //default constructor
    FileLineReader(const FileLineReader &commandToCopy); //copy costructor
    friend ostream& operator << (ostream& outputStream, const FileLineReader& c); //outstream overload
    ~FileLineReader(); //destructor
};
