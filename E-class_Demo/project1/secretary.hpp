#include"person.hpp"
#include <vector>
class person; //forward

class secretary{
    private:
    vector<person> vec; //create a vector of person classes
    
    public:
    secretary(); //constructor
    ~secretary();  //destructor
    secretary(const secretary &ob); //copy constructor

    bool find_person(const string& id) const; // person finder
    void operator+(const person& ob); // plus sign overload
    friend ostream& operator<<(ostream& out , const secretary& ob); //output overload
    friend istream& operator>>(istream& out ,  secretary& ob);  //input overload

};