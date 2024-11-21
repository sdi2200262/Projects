#include <cctype>
#include "person.hpp"
#include"classes.hpp"
using namespace std;

int person::counter=0;//initialization

person::person(){   //constructor
        cout<<"constructing..."<<endl;
        counter++;
};
person::~person(){   //destructor
        //voooiiiid
};


//getters
string person::get_name() const{     
        return name;
}       

string person::get_surname()const{
        return surname;
}

string person::get_id() const{
        return id;
}

char person::get_role() const{
        return role;
}

int person::get_counter() {
        return counter;
}

istream &operator>>( istream  &input, person &p ){ // operator >> overload
        char r;

        cout<<"---------------------"<<endl;
        cout<<"Enter Name: "<<endl;
        input>> p.name;
        cout<<"Enter Surname: "<<endl;
        input>>p.surname;
        cout<<"Enter SDI: "<<endl;
        input>>p.id;
        while(true){    //make a loop so we can check if the role user input is correct
                cout<<endl<<"Enter Person Role (S for Student or T for Teacher):  "<<endl;
                input>>r;
                p.role = toupper(r);  //convert lowercase character input to uppercase
                if(p.get_role() != 'T' && p.get_role() != 'S') cout<<"Wrong User Input. Try Again."<<endl;
                else break;
        }
        return input;

};



ostream &operator<<(ostream &output, const person &p){ // operator << overload

        //print out all student or teacher info
        cout<<endl<<"---------------------------------"<<endl;
        cout<<"Student Name: "<<p.get_name()<<" "<<p.get_surname()<<endl;
        cout<<"SDI: "<<p.get_id()<<endl;
        if(p.get_role() == 'T') cout<<"--> Teacher"<<endl;
        if(p.get_role() == 'S') cout<<"--> Student"<<endl;
        cout<<"---------------------------------"<<endl;
        return output;
};
