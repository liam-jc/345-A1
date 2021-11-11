#include "Orders.h"
#include <type_traits>

using namespace std;
Orders::Orders(){
 this->order_type = "ORDER";
}
Orders::Orders(string s){
 this->order_type = s;
}
Orders::Orders(const Orders &order){ // copy constructor
 this->order_type = order.order_type;

}
Orders::~Orders(){}

string Orders::getOrder_type(){
 return order_type;
}


ostream& operator <<(ostream &stream1, Orders &x){ //Overloading Stream insertion operator
 return stream1 << "type of order: " << x.getOrder_type();
}

Orders& Orders::operator =(const Orders &order){ // Overloading Assignment operator
 this->order_type = order.order_type;
 return *this;
}


OrdersList::OrdersList(){}
OrdersList::OrdersList(vector<Orders*> x){
 this->o_list = x;
}

OrdersList::~OrdersList(){
 for(Orders* order : o_list){
 delete order;
 order = nullptr;
 }
}

vector<Orders*> OrdersList::getOrdersList(){
 return o_list;
}

void OrdersList::setOrdersList(vector<Orders*> o_list){
 this->o_list = o_list;
}

void OrdersList::addOrder(Orders* o){
 o_list.push_back(o);
}

void OrdersList::removeOrder(int index){
 int i = 0;
 for(Orders* order : o_list){
 if(i==index){
 delete order;
 order = nullptr;
 }
 i++;
 }
 o_list.erase(o_list.begin() + index);
}

void OrdersList::moveOrder(int start, int finish){
 Orders* x = o_list[start];
 o_list.erase(o_list.begin() + (start));
 o_list.insert(o_list.begin() + finish, x);
}


