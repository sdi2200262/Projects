#include<iostream>
#include<string>
#include<vector>
#include"classes.hpp"
using namespace std;

student::student():person(){ //constructor
    cout<<"constructing student..."<<endl;
    //initialize vals
    s_semester=1;
    total_ects=0;
    total_mandatory_passed=0;
}

student::~student(){ //destructor
    //voiddddddd
}

//constructor for auto data download
//constructor overload
student::student( string& n,  string& sn,  string& i, int sem) : person() {
    s_semester = sem;
    total_ects = 0;
    total_mandatory_passed = 0;
    name = n;
    surname = sn;
    id = i;
}

//select a course for the current semester
void student::select_course(const course* course_ptr) {
    // Check if student is eligible to add this course
    if (s_semester < course_ptr->get_semester()) {
        cout << "Student is not yet eligible to select this course" << endl;
        return;
    }

    // Check if the course is already selected
    for (const auto& selected_course : selected_courses) {
        if (selected_course == course_ptr) {
            cout << "Course " << course_ptr->get_name() << " is already selected by the student." << endl;
            return;
        }
    }

    // Add course to student vector
    const course* new_course = course_ptr;

    // Check if new_course is valid (non-null) before proceeding
    if (new_course != nullptr) {
        // Add new_course to the student's selected_courses vector
        selected_courses.push_back(new_course);

        // Add student pointer to course vector using "this"
        const_cast<course*>(course_ptr)->add_student(this);
        cout << endl<<"Course " << new_course->get_name() << " added to student " << get_id() << "'s selected courses." << endl;
    } else {
        cout << "Error: Invalid course pointer" << endl;
    }
}

//print selected courses of current semester
void student::print_selected_courses() const {
    if (selected_courses.empty()) {
        cout << "No courses selected for the current semester." << endl; //check if empty first
    } else {
        cout << "Selected Courses for the Current Semester:" << endl;
        for (const auto& course_ptr : selected_courses) { 
            cout<< course_ptr->get_name() << "   ";
        }
        cout<< "----------------------------------------" << endl;
    }
}

int student::get_semester() const{
    return s_semester;
}

int student::get_ects() const{
    return total_ects;
} 

int student::get_passed() const{
    return total_mandatory_passed;
}

void student::show_stats() const{
    for(const auto& course_grade : grades){
        cout<<"----------------------------------------"<<endl;
        cout<<"Course Name: "<<course_grade.course_name<<endl;
        cout<<"Course Semester: "<<course_grade.semester<<endl;
        cout<<"Course Grade: "<<course_grade.grade<<endl;
    }
}

void student::show_stats(ostream& output) const {
    for (const auto& course_grade : grades) {
        output << "----------------------------------------" << endl;
        output << "Course Name: " << course_grade.course_name << endl;
        output << "Course Semester: " << course_grade.semester << endl;
        output << "Course Grade: " << course_grade.grade << endl;
    }
}

//return the grade if the course that is entered as a parameter
double student::get_specific_grade(const course* course_ptr) const{
    //set found val
    bool found=false;
    //temp val
    string temp_course_name;
    //search in student's selected courses to see if he has selected this course
    for(const auto& ptr : selected_courses){
        if(ptr==course_ptr){
            found=true;
            temp_course_name = ptr->get_name();
            break;//if found continue
        }
    }
    if(!found){
        cout<<"Student has not selected this course"<<endl;
        return -1;//no point in continuing searching
    }
    if(found){
        //search in the student's grades vector for the specific course's grade
        for(const auto& ptr : grades){
            if(ptr.course_name==temp_course_name){//when found return grade
                return ptr.grade;
            }
        }
    }
    return -1;  
}

ostream &operator<<(ostream &output, const student &s){ // operator << overload
    //print out all info
    cout<<endl<<"----------------------------------------"<<endl;
    cout<<"Name: "<<s.get_name()<<endl;
    cout<<"ID: "<<s.get_id()<<endl;
    cout<<"Total ECTS points: "<<s.get_ects()<<endl;
    cout<<"Student Semester: "<<s.get_semester()<<"th"<<endl;
    
    return output;
};

istream &operator>>( istream  &input, student &s ){ // operator >> overload
    cout<<"----------------------------------------"<<endl<<endl;
    cout<<"Enter Name: "<<endl;
    input>>s.name;
    cout<<"Enter Surname: "<<endl;
    input>>s.surname;
    cout<<"Enter ID: "<<endl;
    input>>s.id;

    return input;
}