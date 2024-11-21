#include <string>
#include "secretary.hpp"
#include "person.hpp"
secretary::secretary(){ //constructor
    cout<<"Constructing Secretary..."<<endl; 
}

secretary::~secretary(){ //destructor
    cout<<"Destructing Secretary..."<<endl;

    vec.clear();

}

secretary::secretary(const secretary& s){ //copy constructor

    // Copy the contents of the vector from 's' to the new object's vector 'vec'
    vec = s.vec;
    cout << "Secretary Copy Constructor Called" << endl;
   
}

bool secretary::find_person(const string& id) const { //person finder
    for (const person& p : vec) {   //search all the vector nodes 
        if (p.get_id() == id) {     //check if one of them has the input id
            cout << p << endl;      //if true print out the person info using << overload
            return true;
        }
    }
    cout <<endl<< "Person with ID " << id << " not found." << endl;
    //if not found print error message
    return false;
}



void secretary::operator+(const person& p) {
    
    vec.push_back(p);
    // overload + operator so we can do s(secretary class) + p(person class) action
}


ostream& operator<<(ostream& output , const secretary& s){ //operator << overload
    cout<<endl<<"---------------------------------"<<endl;
    cout<<endl<<"---------------------------------"<<endl;
    cout<<endl<<"All the people that are enlisted: "<<endl;
    
    //print out person class counter
    cout<<person::get_counter()<<" people have enlisted."<<endl;

    //print out all the vector nodes
    for(const person& p : s.vec){
        cout<< p <<endl;
    }

    return output;
}


istream& operator>>(istream& input, secretary& s) {  //operator >> overload
    char check = 'Y'; // Initialize with 'Y' to enter the loop
    char c;

    while (check == 'Y') {
        person p;
        input >> p; // Enter person details
        
        s + p; // Add person to the secretary's vector
        
        cout << endl << "To make another register press Y. Press any other key to exit." << endl;
        input >> c;
        check = toupper(c); // Input for continuing or exiting the loop
    }

    return input;
}



