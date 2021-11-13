#include "LoggingObserver.h"
#include <fstream>
#include <list>

Observer::Observer(){

}

Observer::~Observer() {

}

Subject::Subject() {
	_observers = new list<Observer*>;
}
Subject::~Subject() {
	delete _observers;
}
Subject::Subject(const Subject& s) {
	_observers = s._observers;
}
void Subject::Attach(Observer* o) {
	_observers->push_back(o);
};
void Subject::Detach(Observer* o) {
	_observers->remove(o);
};
void Subject::Notify(Ilogable& ilogable) {
	list<Observer*>::iterator i = _observers->begin();
	for (; i != _observers->end(); i++) {
		(*i)->Update(ilogable);
	}
};

LogObserver::LogObserver() {

};
LogObserver::LogObserver(const LogObserver& l) {
	_subject = l._subject;
	_subjectList = l._subjectList;
}
LogObserver::LogObserver(Subject* s) {
	_subject = s;
	_subject->Attach(this);
};
LogObserver::LogObserver(list<Subject*>* s) {
	list<Subject*>::iterator i = s->begin();
	_subjectList = s;
	for (; i != s->end(); i++) {
		(*i)->Attach(this);
	}
};
LogObserver::~LogObserver() {
	delete _subject;
	delete _subjectList;
}
void LogObserver::Update(Ilogable& ilogable) {
	fstream of;
	of.open("Log.txt", ofstream::app);
	of << ilogable.stringToLog() << endl;
	of.close();
}
