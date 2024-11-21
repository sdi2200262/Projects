#include <iostream>
#include <cstring>
#include "secretary.hpp"
//#include "person.hpp"
using namespace std;


int main(){

        secretary s;
        cin>>s; //testing the secretary input overload
        cout<<s; //testing the secretary output overload


        //testing the find_person function
        char check = 'Y';
        char c;
        string sdi;

        while (check == 'Y') {
                cout << "To search for a person in the secretary database, press Y. Press any other key to exit." << endl;
                cin >> c;
                check = toupper(c);

                if (check == 'Y') {
                cout << "Enter person SDI: ";
                cin >> sdi;
                cout << "The person you are looking for is: " << endl;
                s.find_person(sdi); // Call the member function find_person of the secretary object s
                }
        }

        //testing the secretary copy-constructor
        cout<<endl<<endl;
        secretary scp=s;
        cout<<endl<<"The copied secretary data base: "<<endl;
        cout<<s;

return 0;
}




