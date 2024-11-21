#include<iostream>
#include<string>
#include<vector>
#include"classes.hpp"
using namespace std;

professor::professor():person(){ //constructor
    cout<<"constructing professor...."<<endl;
}

professor::~professor(){ //destructor
    //voidddiddd
}

//constructor for auto data download
//constructor overload
professor::professor(const string& n, const string& sn, const string& i):person(){
    name = n;
    surname = sn;
    id = i;
}

void professor::add_course(const course* course_ptr){
    assinged_courses.push_back(course_ptr);
}

void professor::get_courses() const{
    for(const auto& course_ptr : assinged_courses){
        cout<<course_ptr->get_name();
    }
}

//grade a student in a specific course for this semester
void professor::grade_student(course*& course_ptr, student* student_ptr, double grade){
    //set found val
    bool found = false;
    //search in the professor's course vector to see if he is assinged this course
    for(const auto& ptr : assinged_courses){//ptr traverses vector to find pointer course_name
        if(ptr == course_ptr){
            found = true;
            break; //if found continue
        }
    }
    if(!found){ //if not found print error message
        cout<<"Professor is not assinged for this course."<<endl;
        return; //no point in continuing search
    }

    //reset found var
    found = false;
    //search in student's course vector to see if he has selcted
    for(const auto& ptr : student_ptr->selected_courses){
        if(ptr == course_ptr){
            found = true;
            break; //if found continue
        }
    }
    //now we check the student
    if(found){ //if the student has selected it 
        course_grade new_grade;
        //copy the data to the new struct 
        new_grade.course_name = course_ptr->get_name();
        new_grade.semester = course_ptr->get_semester();
        new_grade.grade = grade;

        //push it back on the student vector
        student_ptr->grades.push_back(new_grade);
    
       // Check if the grade is 5 and above, then store in passed_courses vector
        if (grade >= 5.0) {
            student_ptr->passed_courses.push_back(new_grade);
        }

    }

    else{//if not print error message
        cout<<"Student has not selected this course."<<endl;
    }
}

//show professors stats
void professor::show_stats(const course* course_ptr) const{
    cout<<endl<<endl<<"For course: "<<course_ptr->get_name()<<endl;
    if (course_ptr->students.empty()) {
        cout << "No Stats" << endl;
        return;
    }
    
    for(const auto& ptr : course_ptr->students){
       cout<<"----------------------------------"<<endl;
       cout<<"Student Name: "<<ptr->get_name()<<endl;
       cout<<"Student ID: "<<ptr->get_id()<<endl;
       cout<<"Student Grade: "<<ptr->get_specific_grade(course_ptr)<<endl;
    }   
}

void professor::show_stats(ostream& output, const course* course_ptr) const {
    output << endl << endl << "For course: " << course_ptr->get_name() << endl;
    if (course_ptr->students.empty()) {
        output << "No Stats" << endl;
        return;
    }

    for (const auto& ptr : course_ptr->students) {
        output << "----------------------------------" << endl;
        output << "Student Name: " << ptr->get_name() << endl;
        output << "Student ID: " << ptr->get_id() << endl;
        output << "Student Grade: " << ptr->get_specific_grade(course_ptr) << endl;
    }
}

ostream &operator<<(ostream &output, const professor &p){
    //print out all info
        cout<<endl<<"---------------------------------"<<endl;
        cout<<"Name: "<<p.get_name()<<endl;
        cout<<"ID: "<<p.get_id()<<endl;
        cout<<"Assinged lectures: ";
        if(p.assinged_courses.empty()) cout<<" No assinged courses"<<endl;
        else {
            cout<<endl;
            p.get_courses();
        }
        return output;
}

istream &operator>>( istream  &input, professor &p ){
    cout<<"--------------------------------"<<endl<<endl;
    cout<<"Enter Name: "<<endl;
    input>>p.name;
    cout<<"Enter Surname: "<<endl;
    input>>p.surname;
    cout<<"Enter ID: "<<endl;
    input>>p.id;
    return input;
}