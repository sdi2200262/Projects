#ifndef D5BA7D44_C784_40C1_B169_BE0FE004A240
#define D5BA7D44_C784_40C1_B169_BE0FE004A240
#include<iostream>
#include<cstring>
#include<string>
using namespace std;

class person{
    private:
    string name;
    string surname;
    string id;
    char role;
    static int counter;
    

    public:
    person();//constructor + counter
    ~person(); //destructor

    //getters
    string get_name() const;
    string get_surname() const;
    string get_id() const;
    char get_role() const;
    static int get_counter();

    //<< and >> operator overloads
    friend istream &operator>>( istream  &input, person &p );  //input overload
    friend ostream &operator<<( ostream &output, const person &p );  //output overload

};



#endif /* D5BA7D44_C784_40C1_B169_BE0FE004A240 */
