#include<iostream>
#include<string>
#include<vector>

//-------------------------------------------------------------------------------
//class person from first stage of the project
//it is a bit modified to match with the requirements of this project

//person
using namespace std;

class person{
    protected:
    string name;
    string surname;
    string id;
    //char role;  not needed
    static int counter;
    

    public:
    person();//constructor + counter
    ~person(); //destructor

    //getters
    string get_name() const;
    string get_first_name() const;
    string get_surname() const;
    string get_id() const;

};

//------------------------------------------------------------------------------------
//classes and structs for the second stage of the project

//forward
class course; 
class professor;

struct course_grade{ //for student
    string course_name;
    int semester;
    double grade;
};

struct diploma_requirements{ //for secretary
    int total_ects_needed;
    int total_mandatory_courses_needed;
};

//student
class student: public person{
    private:
    int s_semester; //semester starting from 1 (hopefully done by 8)
    int total_ects; //to see if the student has enough ects to get the diploma
    int total_mandatory_passed; //total mandatory courses passed to see if the student is able to get the diploma
    vector<const course*> selected_courses; //list of selected courses for current semester exam
    vector<course_grade> grades; //list of course grades of the current semester
    vector<course_grade> passed_courses;//list of the names of passed courses and their grade

    public:
    student(); //constructor
    ~student(); //destructor
    student( string& n,  string& sn,  string& i, int sem);

    void select_course(const course* course_ptr); //add a course to current semester exams
    void print_selected_courses() const; //print selected courses of current semester
    void show_stats() const; //show students stats in selected courses
    void show_stats(ostream& output) const; //for file report

    //getters
    int get_semester() const;
    int get_ects() const;
    int get_passed() const;
    double get_specific_grade(const course* course_ptr) const;
    
    // operators (<<) and (>>) overload
    friend ostream &operator<<(ostream &output, const student &s); 
    friend istream &operator>>( istream  &input, student &s );

    //friend class professor so they can grade the student
    friend class professor;
    //firend class secretary for obv reasons
    friend class secretary;
};


//professor
class professor: public person{
    private:
    vector<const course*> assinged_courses; //a professor can be assinged multiple courses

    public:
    professor(); //constructor
    ~professor(); //destructor
    professor(const string& n, const string& sn, const string& i);

    //getter
    void get_courses() const;

    void add_course(const course* course_ptr); //add course to the vector
    void grade_student(course*& course_ptr, student* student_ptr, double grade); //grade the students of the assinged course
    void show_stats(const course* course_nptr) const; //show statistics of the assinged course
    void show_stats(ostream& output, const course* course_ptr) const; //for reports 

    // operators (<<) and (>>) overload
    friend ostream &operator<<(ostream &output, const professor &p); 
    friend istream &operator>>( istream  &input, professor &p );

    //professor is friendly class with student class and course class
    //also friend class secretary for obv rsns 
    friend class secretary;
};


//course
class course{
    private:
    string course_name; //name of the course
    professor* assinged_professor; //a course can have only one assinged professor
    int ects; //ects points
    int c_semester; //to see if the student can select it for the exams
    bool role; //1(true) = mandatory course while 0(false)=non-mandatory
    vector<const student*> students; //vector with pointers to all the students that selected this course

    public:
    course();//constructor
    ~course();//destructor    
    course(const string& cn, int e, int sem, bool r);

    void assing_professor(professor*& professor_ptr); //assing professor
    void add_student(const student* student_ptr); //add a student

    //getters
    string get_professor() const; 
    string get_name() const;
    int get_ects() const;
    int get_semester() const;
    bool get_role() const;

    // operators (<<) and (>>) overload
    friend ostream &operator<<(ostream &output, const course &c); 
    friend istream &operator>>( istream  &input, course &c );

    //friend class professor so they can show the course's stats
    friend class professor;
    //friend class secretary for obv rsns
    friend class secretary;
};


//secretary
class secretary{
    private:
    vector<student> svec;
    vector<professor> pvec;
    vector<course> cvec;
    vector<student> graduated;
    diploma_requirements reqs;
    
    public:
    secretary(); //constructor
    ~secretary();  //destructor

    friend ostream& operator<<(ostream& out , const secretary& ob); //output overload
    friend istream& operator>>(istream& out ,  secretary& ob);  //input overload

    void assing_professor(/*course& course_name, professor& professor_name*/); //assing professor to a course
    void select_course_for_student(); //add a course to the selected_courses of a students vector
    bool do_they_graduate(const student& s); //check if a specific student is able to graduate
    void show_graduates(); //show which students are eligible to get their diploma
    void show_all_grades(const course& selected_course); //show all grades for this course
    void show_who_passed(const course& selected_course); //show which students passed this course
    void write_professor_report(const professor& professor);//show professor's stats 
    void write_student_report(const student& student);//show student's stats 
    void show_graduated() const; //print the graduated list

    void read_student_data(const string& filename); //student data download
    void read_professor_data(const string& filename); //professor data download
    void read_course_data(const string& filename); //course data download

    void print_students();
    void print_professors();
    void print_courses();

    void random_grades(); //randomly grade students (for exams function)
    void exams();

    void add_student();
    void add_student(const student& s);
    student* edit_student(/*student& student_name*/);
    void delete_student(/*student& student_name*/);

    void add_professor();
    void add_professor(const professor& p);
    professor* edit_professor(/*professor& professor_name*/);
    void delete_professor(/*professor& professor_name*/);

    void add_course();
    void add_course(const course& c);
    course* edit_course(/*course& course_name*/);
    void delete_course(/*course& course_name*/);

    void reset_data(const string& student_filename, const string& professor_filename, const string& course_filename);
    
    void scenario(); //function that pre-loads the program so its ready for testing
};