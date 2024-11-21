#include<iostream>
#include<string>
#include<vector>
#include"classes.hpp"
using namespace std;

course::course(){ //constructor
    cout<<"constructing course...."<<endl;
    assinged_professor=NULL;
}

course::~course(){ //destructor
    //voioioiddddd
    delete assinged_professor;
}

//constructor for auto data download
//constructor overload
course::course(const string& cn, int e, int sem, bool r) {
    cout << "Constructing course: " << cn << ", " << e << ", " << sem << ", " << r << endl;

    course_name = cn;
    ects = e;
    c_semester = sem;
    role = r;

    assinged_professor = nullptr;
}


//Assing courses professor
void course::assing_professor(professor*& professor_ptr){
    assinged_professor = professor_ptr;
}

void course::add_student(const student* student_ptr){
    students.push_back(student_ptr);
}

string course::get_professor() const{
    return assinged_professor->get_name();
}

string course::get_name() const{
    return course_name;
}

int course::get_ects() const{
    return ects;
}

int course::get_semester() const{
    return c_semester;
}

bool course::get_role() const{
    return role;
}

ostream &operator<<(ostream &output, const course &c){
    //print out all info
    cout<<endl<<"---------------------------------"<<endl;
    cout<<"Course Name: "<<c.get_name()<<endl;
    cout<<"Course ECTS: "<<c.get_ects()<<endl;
    cout<<"Course Semester: "<<c.get_semester()<<endl;
    cout<<"Course is "<<(c.role==true ? "mandatory" : "non-mandatory")<<endl;
    if(c.assinged_professor==NULL) cout<<"Course is not assinged to a professor"<<endl;
        else cout<<"Course Professor: "<<c.get_professor();
    return output;
}

istream &operator>>( istream  &input, course &c ){
    //temporary choice val
    int choice;

    cout<<"--------------------------------"<<endl<<endl;
    cout<<"Enter course name: "<<endl;
    cin>>c.course_name;
    cout<<"Enter ECTS points: "<<endl;
    cin>>c.ects;
    cout<<"Enter course semester (number): "<<endl;
    cin>>c.c_semester;
    while(true){
        cout<<"Enter 1 if course is mandatory or 0 if non-mandatory: "<<endl;
        cin>>choice;
        if(choice==1){
            c.role = true;
            break;
        }
        else if(choice==0){
            c.role = false;
            break;
        }
        else cout<<"Wrong Input"<<endl;
    }
    return input;
}