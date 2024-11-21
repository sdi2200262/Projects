#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <string>
#include<vector>
#include <algorithm> // Include the algorithm header for find_if
#include <cstdlib>
#include <ctime>
#include"classes.hpp"
using namespace std;

const string studentfilepath = "database/students.txt";
const string professorfilepath = "database/professors.txt";
const string coursefilepath = "database/courses.txt";


secretary::secretary(){ //constructor
    cout<<"Constructing Secretary..."<<endl; 
}

secretary::~secretary(){ //destructor
    cout<<"Destructing Secretary..."<<endl;

    //clear all vectors
    svec.clear();
    pvec.clear();
    cvec.clear();
}


ostream& operator<<(ostream& output , const secretary& s){ //operator << overload
    
    return output;
}


istream& operator>>(istream& input, secretary& s) {  //operator >> overload
    
    return input;
}

void secretary::assing_professor(/*course& course_name, professor& professor_name*/){
    //temp vals
    string temp_course_name;
    string temp_professor_id;

    //temp class pointers
    course* temp_course_ptr=nullptr;
    professor* temp_professor_ptr=nullptr;

    bool foundCourse = false;
    bool foundProfessor = false; 

    cout<<endl;
    cout<<"Enter Course Name: ";
    cin>>temp_course_name;


    for(auto& temp_course : cvec ){ //search for course name in the course vector
        
        if(temp_course_name == temp_course.get_name()){
            foundCourse=true;
            temp_course_ptr = &temp_course; // Assign the found course pointer
            cout<<"Course Found:"<<endl<<*temp_course_ptr<<endl;
            break;
        }
    }           
    if(!foundCourse){
        cout<<endl<<"Wrong Course Input"<<endl;
        return;
    }

    cout<<endl;
    cout<<"Enter Professor ID: ";
    cin>>temp_professor_id;

    for(auto& temp_professor : pvec){ //search for professor id in the professor vector
        if(temp_professor_id == temp_professor.get_id()){
            foundProfessor = true;
            temp_professor_ptr = &temp_professor; // Assign the found professor pointer
            cout<<"Professor Found:"<<endl<<*temp_professor_ptr<<endl;
            break;
        }
    }    
    if(foundProfessor){
        temp_professor_ptr->add_course(temp_course_ptr); //push the course pointer back in the assinged courses vector of the professor
        temp_course_ptr->assing_professor(temp_professor_ptr); //assing the course professor
        cout<<endl<<"Course Assinged!"<<endl;
    }

    if(!foundProfessor){
        cout<<endl<<"Wrong Professor Input"<<endl;
    }    
        
    char exit;
    cout<<"Press E to Exit to Main MENU: ";
    cin>>exit;
    exit=toupper(exit);
    if(exit=='E')return;
}


void secretary::select_course_for_student() {
    // Loop until 'E' is pressed to exit
    while (true) {
        // Temp values
        string temp_id;
        string temp_course_name;
        student* temp_student_ptr = nullptr;
        course* temp_course_ptr = nullptr;

        // Ask user for student ID
        cout << "Enter Student ID: ";
        cin >> temp_id;

        // Search for student ID in the student vector
        for (auto& temp_student : svec) {
            if (temp_student.get_id() == temp_id) {
                temp_student_ptr = &temp_student;
                cout << "Student Found: " << endl << *temp_student_ptr << endl;
                break;
            }
        }

        // Check if the student was found
        if (temp_student_ptr == nullptr) {
            cout << "Student with ID " << temp_id << " not found." << endl;
            continue;
        }

        // Ask user for course name
        cout << "Enter Course Name: ";
        cin >> temp_course_name;

        // Search for course name in the course vector
        for (auto& temp_course : cvec) {
            if (temp_course_name == temp_course.get_name()) {
                temp_course_ptr = &temp_course;
                cout << "Course Found:" << endl << *temp_course_ptr << endl;
                break;
            }
        }

        // Check if the course was found
        if (temp_course_ptr == nullptr) {
            cout << "Course with name " << temp_course_name << " not found." << endl;
            continue;
        }

        // Call the select_course function for the found student and course
        temp_student_ptr->select_course(temp_course_ptr);

        // Press E to exit feature
        char exitChoice;
        cout << endl<<"Press 'E' to exit or any other key to select more courses: ";
        cin >> exitChoice;

        if (exitChoice == 'E' || exitChoice == 'e') {
            cout << "Exiting " << endl;
            break; // Exit the loop
        } else {
            cout <<endl<< "Add another course:" << endl<<endl;
        }
    }
}

bool secretary::do_they_graduate(const student& s){
    if(reqs.total_ects_needed < s.get_ects() && reqs.total_mandatory_courses_needed < s.get_passed())
    return 1; //they graduate
    else return 0; //sorryy
}

void secretary::show_graduates() {
    cout << "----------------------------------------" << endl;
    cout << endl<<endl;
    bool anyGraduates = false;

    auto it = svec.begin(); // Iterator to iterate through the vector

    while (it != svec.end()) {
        if (do_they_graduate(*it)) {
            anyGraduates = true;
            // Add the graduate student to the graduates vector
            graduated.push_back(*it);

            cout << *it << endl;
            cout << "----------------------------------------" << endl;
            cout << "Student " << it->get_name() << " is removed from the system." << endl;

            it = svec.erase(it); // Remove the graduate student and update iterator
        } else {
            ++it; // Move to the next student in the vector
        }
    }

    if (!anyGraduates) {
        cout << "No graduates this semester." << endl;
    }
}



void secretary::show_all_grades(const course& selected_course) {
    // Display grades for the selected course
    cout << "Grades for " << selected_course.get_name() << ":" << endl<<endl;

    // Iterate over students enrolled in the course
    for (const auto& temp_student : selected_course.students) {
        cout << temp_student->get_name() << " " << ": ";
        double temp_grade = temp_student->get_specific_grade(&selected_course);
        cout << temp_grade << endl;
    }
}

void secretary::show_who_passed(const course& selected_course) {
    // display students who passed the selected course
    cout << "Students who passed " << selected_course.get_name() << ":" << endl;

    bool anyStudentPassed = false;

    // go thru students who selected the course
    for (const auto& temp_student : selected_course.students) {
        double temp_grade = temp_student->get_specific_grade(&selected_course);

        // Only display information for students who passed
        if (temp_grade >= 5.0) {
            cout << temp_student->get_name() << " ---> ";
            cout << "Grade: " << temp_grade << endl;
            anyStudentPassed = true;
        }
    }

    // Display a message if no students passed the course
    if (!anyStudentPassed) {
        cout << "No students passed this course." << endl;
    }
}


void secretary::write_professor_report(const professor& professor) {
    const string reports_folder = "reports";
    
    const string filePath = reports_folder + "/professor_stats_" + professor.get_surname() + "_" + professor.get_id() + ".txt";
    ofstream outputFile(filePath);

    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open file " << filePath << endl;
        return;
    }

    outputFile << "Professor's " << professor.get_surname() << " stats: " << endl << endl;
    outputFile << "----------------------------------------" << endl << endl;

    // Filter courses based on the professor
    for (const auto& temp_course : professor.assinged_courses) {
        outputFile << "----------------------------------------" << endl << endl;

        professor.show_stats(outputFile, temp_course);

        outputFile << "----------------------------------------" << endl << endl;
    }

    outputFile.close();
    cout << endl << endl << "Professor stats saved to file: " << filePath << endl;
}


    


void secretary::write_student_report(const student& student) {

    const string reports_folder = "reports";
    
    const string filePath = reports_folder + "/student_stats_" + student.get_surname() + "_" + student.get_id() + ".txt";
    ofstream outputFile(filePath);

    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open file " << filePath << endl;
        return;
    }

    outputFile << "Student's " << student.get_surname() << " stats: " << endl << endl;
    outputFile << "----------------------------------------" << endl << endl;

    outputFile << "----------------------------------------" << endl << endl;

    student.show_stats(outputFile);

    outputFile << "----------------------------------------" << endl << endl;

    outputFile.close();
    cout << endl << endl << "student stats saved to file: " << filePath << endl;
}


//print the graduated students
void secretary::show_graduated() const {
    if (graduated.empty()) {
        cout << "No graduates yet." << endl;
    } else {
        for (const auto& ptr : graduated) {
            cout << ptr << endl;
            cout << "----------------------------------------" << endl;
        }
    }
    char exit;
    do{
        cout<<"Enter E to exit to Main menu: ";
        cin>>exit;
    }while(exit != 'E' && exit!= 'e');
}


// Function to trim whitespaces from the beginning and end of a string
string trim(const string& str);

//READ DATA
// STUDENT / PROFESSOR / COURSE
void secretary::read_student_data(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    string name, surname, id;
    int semester;

    while (getline(file, line)) {

        line = trim(line);
        if (line.front() == '#' && line.back() == '#') {
            // Skip lines enclosed with '#'
            continue;
        }
        if (line.find("Name: ") != string::npos) {
            name = line.substr(6);
        } else if (line.find("Surname: ") != string::npos) {
            surname = line.substr(9);
        } else if (line.find("ID: ") != string::npos) {
            id = line.substr(4);
        } else if (line.find("Semester: ") != string::npos) {
            semester = stoi(line.substr(10));

            // Construct a student object and add it to the secretary's svec
            student newStudent(name, surname, id, semester);
            add_student(newStudent);
        }
    }

    file.close();
}

void secretary::read_professor_data(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    string name, surname, id;

    while (getline(file, line)) {

        line = trim(line);
        if (line.front() == '#' && line.back() == '#') {
            // Skip lines enclosed with '#'
            continue;
        }
        if (line.find("Name: ") != string::npos) {
            name = line.substr(6);
        } else if (line.find("Surname: ") != string::npos) {
            surname = line.substr(9);
        } else if (line.find("ID: ") != string::npos) {
            id = line.substr(4);

            // Construct a professor object and add it to the secretary's pvec
            professor newProfessor(name, surname, id);
            add_professor(newProfessor);
        }
    }

    file.close();
}

void secretary::read_course_data(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << filename << endl;
        return;
    }

    string line;
    string name;
    int ects, semester;

    while (getline(file, line)) {
        line = trim(line);
        if (line.front() == '#' && line.back() == '#') {
            // Skip lines enclosed with '#'
            continue;
        }

        if (line.find("Name: ") != string::npos) {
            name = line.substr(6);  // scan the 'name' variable correctly
        } else if (line.find("ECTS: ") != string::npos) { 
            ects = stoi(line.substr(6)); //scan ects points
        } else if (line.find("Semester: ") != string::npos) {
            semester = stoi(line.substr(10)); //scan course semester
        } else if (line.find("Role: 1") != string::npos) {
            course newCourse(name, ects, semester, true);//if mandatory set role true and create object
            add_course(newCourse);
        } else if (line.find("Role: 0") != string::npos) {
            course newCourse(name, ects, semester, false);
            add_course(newCourse);
        }
        } 
        file.close();
    }




//PRINT
// STUDENT / PROFESSOR / COURSE
void secretary::print_students(){
    for(auto& ptr : svec){
        cout<<ptr<<endl;
    }
}

void secretary::print_professors(){
    for(auto& ptr : pvec){
        cout<<ptr<<endl;
    }
}

void secretary::print_courses(){
    for(auto& ptr : cvec){
        cout<<ptr<<endl;
    }
}

//EXAMS
void secretary::random_grades() {
    // Set seed for the random number generator using current time
    std::srand(static_cast<unsigned>(std::time(0)));

    // Loop through each course
    for (auto& current_course : cvec) {
        // Check if a professor is assigned to this course
        if (!current_course.assinged_professor) {
            cout << "Error: No professor assigned for course " << current_course.get_name() << endl;
            continue;
        }

        // Loop through each student and grade if they have selected the current course
        for (auto& current_student : svec) {
            for (const auto& selected_course : current_student.selected_courses) {
                if (selected_course == &current_course) {
                    // Generate a random grade between 0 and 10 for each student
                    double random_grade = static_cast<double>(rand() % 101) / 10.0;

                    course* current_course_ptr = const_cast<course*>(&current_course);
                    current_course.assinged_professor->grade_student(current_course_ptr, &current_student, random_grade);
                    break;
                }
            }
        }
    }
}




void secretary::exams(){
    //check vectors first
    if (svec.empty() && pvec.empty() && cvec.empty()) {
        cout << "Error: No students, professors, or courses found. Add data before performing operations." << endl;
        return;
    } 
    else if (svec.empty()) {
        cout << "Error: No students found. Add students before performing student-related operations." << endl;
        return;
    } 
    else if (pvec.empty()) {
        cout << "Error: No professors found. Add professors before performing professor-related operations." << endl;
        return;
    } 
    else if (cvec.empty()) {
        cout << "Error: No courses found. Add courses before performing course-related operations." << endl;
        return;
    }
    cout << "------------Initiating EXAMS------------" << endl<<endl<<endl;
    cout << "Students participating: " << endl;
    for (const auto& ptr : svec) {
        cout << ptr << endl; // Print out student info
        ptr.print_selected_courses(); // Print out all their selected courses
        cout << endl;
    }
    cout<<endl<<endl;
    cout<<endl<<endl;
    cout << "Professors available: " << endl;
    print_professors();
    cout<<endl<<endl;
    cout<<endl<<endl;
    cout << "Courses available: " << endl;
    print_courses();
    cout<<endl<<endl;
    cout<<endl<<endl;
    

    // User prompt
    cout << "Choose which action you would like to perform:" << endl;
    cout << "1) Randomly grade all students" << endl;
    cout << "2) Manually Grade all students "<<endl;

    int prompt;
    cin >> prompt;

    if (prompt == 1) {
        // Randomly grading students
        random_grades();
    } 
    else if (prompt == 2) {
        // Feature coming soon...
        cout <<endl<< "Feature coming soon... Randomly grading students for now)" << endl;
        
        // Proceed with random grading
        random_grades();
    } 
    //now all the grades have been assinged to each student for each course
    cout<<endl<<endl<<"All grades assigned!"<<endl<<endl;

    int continue_button;
    cout<<"Press 1 to print grades: ";
    cin>>continue_button;
    if(continue_button == 1) cout<< "Printing Grades..."<<endl<<endl;
    else cout<<endl<<"Wrong Input. Enter 1 to continue: ";

    system("clear");

    // Print all student grades for each course
    cout<<"Printing All Grades: "<<endl<<endl;
    for (const auto& course : cvec) {
        show_all_grades(course);
        cout << "----------------------------------------" << endl<<endl;
    }

    // Print all students who passed each course
    cout<<"Printing Students That Passed Each Course: "<<endl<<endl;
    for (const auto& course : cvec) {
        show_who_passed(course);
        cout << "----------------------------------------" << endl<<endl;
    }

    // Now that all the grades have been printed, let's check who graduated
    // Print all graduating students
    cout << endl << endl;
    cout << "Graduating students:" << endl;

    show_graduates();

    cout << "----------------------------------------" << endl;

    // Prompt the user to continue to statistics
    char cont;
    cout<<"Enter any key to continue to statistics: ";
    cin>>cont;
    int choice;

    do {
        system("clear");
        cout << "----------- STATS MENU -----------" << endl;
        cout << "1. Show Professor Stats" << endl;
        cout << "2. Show Student Stats" << endl;
        cout << "3. Show Graduates" << endl;
        cout << "4. Exit" << endl;
        cout << "---------------------------" << endl;
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Show Professor Stats
                for (const auto& professor : pvec) {
                    cout << endl<<professor<<endl<<endl;
                    cout<<"Student that selected professor's "<<professor.get_surname()<<" course: "<<endl;
                    for(const auto& assinged_course : professor.assinged_courses){
                        professor.show_stats(assinged_course); // Show courses assigned to the professor
                        cout<<"----------------------------------------"<<endl; 
                        write_professor_report(professor);
                    }
                }
                {char cont;
                cout<<"Enter any key to continue to statistics: ";
                cin>>cont;}
                break;
            case 2:
                // Show Student Stats
                for (const auto& student : svec) {
                    cout << endl<<student<<endl<<endl;
                    cout<<"Courses Selected: "<<endl;
                    student.show_stats(); // Show all grades of the student
                    cout<<"----------------------------------------"<<endl;
                    write_student_report(student);
                }
                {char cont;
                cout<<"Enter any key to continue to statistics: ";
                cin>>cont;}
                break;
            case 3:
                // Show Graduates
                cout<<endl;
                show_graduates();
                cout<<"----------------------------------------"<<endl;
                {char cont;
                cout<<"Enter any key to continue to statistics: ";
                cin>>cont;}
                break;
            case 4:
                // Exit the menu
                cout << "Exiting the menu." << endl;
                break;
            default:
                // Invalid choice
                cout << "Invalid choice. Please enter a number between 1 and 4." << endl;
        }
    } while (choice != 4);
    
    


    char gonext;
    do{
        cout<<"Enter N to finish exams and enter next semester: ";
        cin>>gonext;
        //all procedures are done now update student info
        cout<<endl<<endl<<"All students are entering next semester!"<<endl;
        cout<<"All selected courses are removed from the students' exam course list!"<<endl<<endl;
        for(auto& student : svec) {
            // Increment semester for all students
            student.s_semester++;
            // Clear the selected courses vector to be ready for next semester
            student.selected_courses.clear();
            // Clear the grades vector to be ready for the next semester
            student.grades.clear();
        }
    }while(gonext != 'N' && gonext != 'n');

    char exit;
    //randomly grading students
    do {
        cout << "Press 'E' to end exams sequence ";
        cin >> exit;
    } while (exit != 'E' && exit != 'e');
}


// ADD / EDIT / DELETE 
// STUDENT / PROFESSOR / COURSE

void secretary::add_student() {
    char add;
    do {
        student s;
        cin >> s; // Enter student data
        svec.push_back(s); // Push student back in the vector
        cout << "Student " << s.get_name() << " is added to the system" << endl;

        cout << "Press 1 to continue adding students or any other key to return to the Add/Edit/Delete Menu: ";
        cin >> add;

        if (add != '1') {
            break;
        }

    } while (add == '1');
}

//overload for auto data downlaod
void secretary::add_student(const student& s) {
    svec.push_back(s);
}

student* secretary::edit_student(){
    //temporary val
    string temp_id;
    
    //temporary pointer
    student* temp_student_ptr=nullptr;

    //found val
    bool found=false;

    //switch/case val
    int choice;

    cout<<"Enter Student ID: ";
    cin>>temp_id;
    for(auto& temp_student : svec){
        if(temp_id==temp_student.get_id()){
            found=true;
            temp_student_ptr = &temp_student;
            break;
        }
    }

    if(found){
        cout<<"Student with ID: "<<temp_id<<" found."<<endl;
        cout<<*temp_student_ptr;
        while(true){
            cout<<endl<<"Choose what changes you would like to make: "<<endl;
            cout<<"1) Change Name \n2) Change Surname \n3) Change ID\n4) Save and Exit"<<endl;
            cout<<"Enter Choice: ";
            cin>>choice;

            switch(choice){
                case 1:{
                string new_name;
                cout<<"Enter new name: ";
                cin>>new_name;
                temp_student_ptr->name=new_name;
                cout<<endl<<"Name updated"<<endl;
                break;
                }
                case 2:{
                string new_surname;
                cout<<"Enter new surname: ";
                cin>>new_surname;
                temp_student_ptr->surname=new_surname;
                cout<<endl<<"Surname updated"<<endl;
                break;
                }
                case 3:{
                string new_id;
                cout<<"Enter new ID: ";
                cin>>new_id;
                temp_student_ptr->id=new_id;
                cout<<endl<<"ID updated"<<endl;
                break;
                }
                case 4:{
                cout<<"Saving..."<<endl;
                cout<<"Exiting..."<<endl;
                return nullptr;
                }
                default:
                cout<<"Wrong Input, please try again"<<endl;
                break;
            }
        }
        return temp_student_ptr;
    }

    if(!found){
        cout<<"There is no student with ID: "<<temp_id<<endl;
        return nullptr;
    }
    return nullptr;
}

void secretary::delete_student(/*student& student_name*/){
    //temp val
    string temp_id;

    //temporary class
    student temp_student;
    
    cout<<"Enter Student ID: ";
    cin>>temp_id;

    auto found = find_if(svec.begin(), svec.end(), [&temp_id](const student& s){
                                                            return s.get_id() == temp_id;}); 
    //source for this method cppreference.com
    //find_if(x, y, z) is called with a lambda function [&temp_id](const student& s) compares the id of each person with the temp_id
    //the lambda function returns true if its condition is satisfied and then the search stops
    //when the search stops the find_if function returns a pointer to the first element that satisfied the lambda function
    //or else svec.end() if no such element is found 

    if(found!=svec.end()){
        svec.erase(found); //delete the element "found" is pointing
        cout<<"Student with ID: "<<temp_id<<" found and removed from system"<<endl;
    }
    else cout<<"Student with ID: "<<temp_id<<" not found"<<endl;
}


void secretary::add_professor() {
    char add;
    do {
        professor p;
        cin >> p; // Enter professor data
        pvec.push_back(p); // Push professor back in the vector
        cout << "professor " << p.get_name() << " is added to the system" << endl;

        cout << "Press 1 to continue adding professors or any other key to return to the Add/Edit/Delete Menu: ";
        cin >> add;

        if (add != '1') {
            break;
        }

    } while (add == '1');
}

//overload for auto data downlaod
void secretary::add_professor(const professor& p) {
    pvec.push_back(p);
}

professor* secretary::edit_professor(){
    //temporary val
    string temp_id;
    
    //temporary pointer
    professor* temp_professor_ptr;

    //found val
    bool found=false;

    //switch/case val
    int choice;


    cout<<"Enter Professor ID: ";
    cin>>temp_id;
    for(auto& temp_professor : pvec){
        if(temp_id==temp_professor.get_id()){
            found=true;
            temp_professor_ptr=&temp_professor;
            break;
        }
    }

    if(found){
        cout<<"Professor with ID: "<<temp_id<<" found."<<endl;
        cout<<*temp_professor_ptr;
        while(true){
            cout<<endl<<"Choose what changes you would like to make: "<<endl;
            cout<<"1) Change Name \n2) Change Surname \n3) Change ID\n4) Save and Exit"<<endl;
            cout<<"Enter Choice: ";
            cin>>choice;

            switch(choice){
                case 1:{
                string new_name;
                cout<<"Enter new name: ";
                cin>>new_name;
                temp_professor_ptr->name=new_name;
                cout<<endl<<"Name updated"<<endl;
                break;
                }
                case 2:{
                string new_surname;
                cout<<"Enter new surname: ";
                cin>>new_surname;
                temp_professor_ptr->surname=new_surname;
                cout<<endl<<"Surname updated"<<endl;
                break;
                }
                case 3:{
                string new_id;
                cout<<"Enter new ID: ";
                cin>>new_id;
                temp_professor_ptr->id=new_id;
                cout<<endl<<"ID updated"<<endl;
                break;
                }
                case 4:{
                cout<<"Saving..."<<endl;
                cout<<"Exiting..."<<endl;
                return 0;
                }
                default:
                cout<<"Wrong Input, please try again"<<endl;
                break;
            }
        }
        return temp_professor_ptr;
    }

    if(!found){
        cout<<"There is no professor with ID: "<<temp_id<<endl;
        return nullptr;
    }
    return nullptr;
}

void secretary::delete_professor(/*professor& professor_name*/){
    //temp val
    string temp_id;

    //temporary class
    professor temp_professor;
    
    cout<<"Enter Professor ID: ";
    cin>>temp_id;

    auto found = find_if(pvec.begin(), pvec.end(), [&temp_id](const professor& t){
                                                            return t.get_id() == temp_id;}); 
    //source for this method cppreference.com
    //find_if(x, y, z) is called with a lambda function [&temp_id](const professor& t) compares the id of each person with the temp_id
    //the lambda function returns true if its condition is satisfied and then the search stops
    //when the search stops the find_if function returns a pointer to the first element that satisfied the lambda function
    //or else svec.end() if no such element is found 

    if(found!=pvec.end()){
        pvec.erase(found); //delete the element "found" is pointing
        cout<<"Professor with ID: "<<temp_id<<" found and removed from system"<<endl;
    }
    else cout<<"Professor with ID: "<<temp_id<<" not found"<<endl;
}

void secretary::add_course() {
    char add;
    do {
        course c;
        cin >> c; // Enter course data
        cvec.push_back(c); // Push course back in the vector
        cout << "course " << c.get_name() << " is added to the system" << endl;

        cout << "Press 1 to continue adding courses or any other key to return to the Add/Edit/Delete Menu: ";
        cin >> add;

        if (add != '1') {
            break;
        }

    } while (add == '1');
}

void secretary::add_course(const course& c) {
    cvec.push_back(c);
}

course* secretary::edit_course(){
    //temporary val
    string temp_course_name;
    
    //temporary pointer
    course* temp_course_ptr;

    //found val
    bool found=false;

    //switch/case val
    int choice;


    cout<<"Enter course name ";
    cin>>temp_course_name;
    for(auto& temp_course : cvec){
        if(temp_course_name==temp_course.get_name()){
            found=true;
            temp_course_ptr=&temp_course;
            break;
        }
    }

    if(found){
        cout<<"course with name: "<<temp_course_name<<" found."<<endl;
        cout<<*temp_course_ptr;
        while(true){
            cout<<endl<<"Choose what changes you would like to make: "<<endl;
            cout<<"1) Change Course Name \n2) Change ECTS \n3) Change Course Semester \n4) Change Mandatory Role \n5) Save and Exit"<<endl;
            cout<<"Enter Choice: ";
            cin>>choice;

            switch(choice){
                case 1:{
                string new_name;
                cout<<"Enter new course name: ";
                cin>>new_name;
                temp_course_ptr->course_name=new_name;
                cout<<endl<<"Name updated"<<endl;
                break;
                }
                case 2:
                int new_ects;
                cout<<"Enter new ECTS: ";
                cin>>new_ects;
                temp_course_ptr->ects=new_ects;
                cout<<endl<<"ECTS updated"<<endl;
                break;

                case 3:{
                int new_c_semester;
                cout<<"Enter new course semester: ";
                cin>>new_c_semester;
                temp_course_ptr->c_semester=new_c_semester;
                cout<<endl<<"Course Semester updated"<<endl;
                break;
                }
                case 4:{
                int mandatoryrole;
                while(true){
                    cout<<"Enter 1 if course is mandatory or 0 if non-mandatory: "<<endl;
                    cin>>mandatoryrole;
                    if(mandatoryrole==1){
                        temp_course_ptr->role = true;
                        return 0;
                    }
                    else if(mandatoryrole==0){
                        temp_course_ptr->role = false;
                        return 0;
                    }
                    else cout<<"Wrong Input"<<endl;
                }
                }
                case 5:{
                cout<<"Saving..."<<endl;
                cout<<"Exiting..."<<endl;
                return 0;
                }
                default:
                cout<<"Wrong Input, please try again"<<endl;
                break;
            }
        }
        return temp_course_ptr;
    }

    if(!found){
        cout<<"There is no course with name: "<<temp_course_name<<endl;
        return nullptr;
    }
    return nullptr;
}

void secretary::delete_course(/*course& course_name*/){
    //temp val
    string temp_course_name;

    //temporary class
    professor temp_course;
    
    cout<<"Enter Course Name: ";
    cin>>temp_course_name;

    auto found = find_if(cvec.begin(), cvec.end(), [&temp_course_name](const course& c){
                                                            return c.get_name() == temp_course_name;});
    //source for this method cppreference.com
    //find_if(x, y, z) is called with a lambda function [&temp_id](const professor& s) compares the id of each person with the temp_id
    //the lambda function returns true if its condition is satisfied and then the search stops
    //when the search stops the find_if function returns a pointer to the first element that satisfied the lambda function
    //or else svec.end() if no such element is found 

    if(found!=cvec.end()){
        cvec.erase(found); //delete the element "found" is pointing
        cout<<"Course with Name: "<<temp_course_name<<" found and removed from system"<<endl;
    }
    else cout<<"Course with Name: "<<temp_course_name<<" not found"<<endl;
}


string trim(const string& str) {
    auto start = str.begin();
    while (start != str.end() && isspace(*start)) {
        ++start;
    }

    auto end = str.end();
    while (end != start && isspace(*(end - 1))) {
        --end;
    }

    return string(start, end);
}


void secretary::reset_data(const string& student_filename, const string& professor_filename, const string& course_filename) {
    // Delete existing data files
    remove(student_filename.c_str());
    remove(professor_filename.c_str());
    remove(course_filename.c_str());

    // Write new data to files
    ofstream student_file(student_filename);
    ofstream professor_file(professor_filename);
    ofstream course_file(course_filename);

    if (!student_file.is_open() || !professor_file.is_open() || !course_file.is_open()) {
        cerr << "Error: Unable to open files for writing." << endl;
        return;
    }

    // Write students' data
    for (const auto& student : svec) {
        student_file << "Name: " << student.get_first_name() << endl;
        student_file << "Surname: " << student.get_surname() << endl;
        student_file << "ID: " << student.get_id() << endl;
        student_file << "Semester: "<<student.get_semester() <<endl;
        student_file << endl;
    }

    // Write professors' data
    for (const auto& professor : pvec) {
        professor_file << "Name: " << professor.get_first_name() << endl;
        professor_file << "Surname: " << professor.get_surname() << endl;
        professor_file << "ID: " << professor.get_id() << endl;
        professor_file << endl;
    }

    // Write courses' data
    for (const auto& course : cvec) {
        course_file << "Name: " << course.get_name() << endl;
        course_file << "ECTS: " << course.get_ects() << endl;
        course_file << "Semester: " << course.get_semester() << endl;
        if(course.get_role()) course_file << "Role: 1"<<endl;
        else course_file<< "Role: 0"<<endl;
        course_file << endl;
    }

    // Close the files
    student_file.close();
    professor_file.close();
    course_file.close();

    cout << "Data files reset successfully." << endl;
}

//auto - assing professors to courses ( those from the database ) and auto - select courses for students ( also those from the database )
//in the database files the professors and the courses have been entered in such way so the first professor profile is assinged to the first course profile and so on
//if one of those data files is changed, the scenario() function wont work properly so we wont use it 
void secretary::scenario() {
    if (pvec.size() != cvec.size()) {
        std::cerr << "Error: Professor and Course vectors must have the same size for the scenario to run.\n";
        return;
    }

    size_t size = std::min(pvec.size(), cvec.size());

    for (size_t i = 0; i < size; ++i) {
        professor* p_professor = &pvec[i];  // create a temporary pointer
        pvec[i].add_course(&cvec[i]);       // add course to professors assigned courses vector
        cvec[i].assing_professor(p_professor);  // assign professor to course
    }

    for(auto& student : svec){ //for every student in the database
        for(auto& course : cvec){ //select every course ( those that the students are eligible to select)
            student.select_course(&course);
        }
    }
}