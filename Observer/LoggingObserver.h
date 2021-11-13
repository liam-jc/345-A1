#pragma once
#include <list>
#include <iostream>
using namespace std;

class Observer {
public:
	~Observer();
	virtual void Update(Ilogable&) = 0;
protected:
	Observer();
};

class Subject {
public:
	virtual void Attach(Observer* o);
	virtual void Detach(Observer* o);
	virtual void Notify(Ilogable &);
	Subject();
	Subject(const Subject&);
	~Subject();
private:
	list<Observer*>* _observers;
};

class LogObserver : public Observer {
public:
	void Update(Ilogable &);
	LogObserver();
	LogObserver(Subject* s);
	LogObserver(list<Subject*>*);
	LogObserver(const LogObserver&);
	~LogObserver();
	Subject* _subject;
	list<Subject*>* _subjectList;

};

class Ilogable {
public:
	virtual string stringToLog() = 0;
};
