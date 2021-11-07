#include <iostream>
#include <vector>
#include <string>
#pragma once


using namespace std;

class Orders{ // orders superclass




public:

     string order_type;
     Orders();
     explicit Orders(string order_type);
     Orders(const Orders &order);
     virtual ~Orders();
     virtual string getOrder_type();
     friend ostream& operator <<(ostream &stream1, Orders &x);
     virtual Orders& operator =(const Orders &order);
     bool validate();
     void execute ();



};

class Deploy : public Orders  {

public:
    string order_type;
    Deploy(string d): Orders(d){};
     bool validate();
     void execute ();


};
class Advance : public Orders  {

public:
    string order_type;
    Advance(string a): Orders(a){};
    bool validate();
    void execute ();

};
class Bomb : public Orders  {

public:
    string order_type;
    Bomb(string b): Orders(b){};
    bool validate();
    void execute ();

};
class Blockade : public Orders  {

public:
    string order_type;
    Blockade(string b): Orders(b){};
    bool validate();
    void execute ();

};
class Airlift : public Orders  {

public:
    string order_type;
    Airlift(string a): Orders(a){};
    bool validate();
    void execute ();

};
class Negotiate : public Orders  {

public:
    string order_type;
    Negotiate(string n): Orders(n){};
    bool validate();
    void execute ();

};

class OrdersList {
private:

 vector<Orders*> o_list;
public:

 OrdersList();
 OrdersList(vector<Orders*> orderList);
 OrdersList(const OrdersList &orderList);

 ~OrdersList();

 vector<Orders*> getOrdersList();

 void setOrdersList(vector<Orders*> o_list);

 void addOrder(Orders* o);

 void removeOrder(int i);

 void moveOrder(int start, int finish);


};
