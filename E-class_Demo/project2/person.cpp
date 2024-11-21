#include <cctype>
#include <string>
#include "classes.hpp"
using namespace std;

int person::counter=0;//initialization

person::person(){   //constructor
        //vooiiiidddd
};
person::~person(){   //destructor
        //voooiiiid
};


//getters
string person::get_name() const{     
        string full_name;
        full_name = name + " " + surname;

        return full_name;
} 

string person::get_first_name() const{
        return name;
}

string person::get_surname() const{     
        return surname;
}

string person::get_id() const{
        return id;
}