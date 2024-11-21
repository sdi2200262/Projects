#include<iostream>
#include<string>
#include <limits>
#include<cstdlib>
#include<cctype>
#include"classes.hpp"

using namespace std;

const string studentfilepath = "database/students.txt";
const string professorfilepath = "database/professors.txt";
const string coursefilepath = "database/courses.txt";

void displayfirtmenu(){
    system("clear");
    cout << "Select which action you would like to perform:" << endl;
    cout<<endl;
    cout<<"1) Add Data Manually"<<endl;
    cout<<"2) Download Data from Database"<<endl;
}

void displaymainmenu() {
    system("clear");
    cout << "-----------MENU-----------" << endl;
    cout << "Select which action you would like to perform:" << endl;
    cout << endl;
    cout << "1) Add/Edit/Delete a Student/Professor/Course" << endl;
    cout << "2) Print All Students/Professors/Courses" << endl;
    cout << "3) Assign Professor to a Course" << endl;
    cout << "4) Select a Course for a Student" << endl;
    cout << "5) Initiate EXAMS sequence" << endl;
    cout << "6) Save and Exit" << endl;
}

void displayaddeditdeletemenu() {
    system("clear");
    cout << "-----------MENU-----------" << endl;
    cout << "Select which action you would like to perform:" << endl;
    cout << endl;
    cout << "1) Add" << endl;
    cout << "2) Edit" << endl;
    cout << "3) Delete" << endl;
    cout << "4) Return to Main MENU" << endl;
}

void displayaddmenu() {
    system("clear");
    cout << "-----------MENU-----------" << endl;
    cout << "Select which item you would like to add:" << endl;
    cout << endl;
    cout << "1) Student" << endl;
    cout << "2) Professor" << endl;
    cout << "3) Course" << endl;
    cout << "4) Return to Add/Edit/Delete MENU" << endl;
}

void displayeditmenu() {
    system("clear");
    cout << "-----------MENU-----------" << endl;
    cout << "Select which item you would like to edit:" << endl;
    cout << endl;
    cout << "1) Student" << endl;
    cout << "2) Professor" << endl;
    cout << "3) Course" << endl;
    cout << "4) Return to Add/Edit/Delete MENU" << endl;
}

void displaydeletemenu() {
    system("clear");
    cout << "-----------MENU-----------" << endl;
    cout << "Select which item you would like to delete:" << endl;
    cout << endl;
    cout << "1) Student" << endl;
    cout << "2) Professor" << endl;
    cout << "3) Course" << endl;
    cout << "4) Return to Add/Edit/Delete MENU" << endl;
}

void displayprintallmenu() {
    system("clear");
    cout << "-----------MENU-----------" << endl;
    cout << "Select which items you would like to print:" << endl;
    cout << endl;
    cout << "1) Students" << endl;
    cout << "2) Professors" << endl;
    cout << "3) Courses" << endl;
    cout << "4) Return to Print MENU" << endl;
}

int main(){
    cout<<"Program Starting..."<<endl;
    secretary s;
    
    //read the input
    s.read_student_data(studentfilepath);
    s.read_professor_data(professorfilepath);
    s.read_course_data(coursefilepath);

    //starting scenario
    s.scenario();

    int choice;
    do{
        displaymainmenu();
        cin>>choice;
        switch(choice){

            case 1:
            int choice_1;
            do{
                displayaddeditdeletemenu();
                cin>> choice_1;
                switch(choice_1){

                    case 1://user selected add
                    int choice_1_1;
                    do{
                        displayaddmenu();
                        cin>>choice_1_1;
                        switch(choice_1_1){

                        case 1:{//student
                            cout<<"Selected Student"<<endl;
                            s.add_student();
                            break;
                        }

                        case 2:{//professor
                            cout<<"Selected Professor"<<endl;
                            s.add_professor();
                            break;
                            }

                        case 3:{//course
                            cout<<"Selected Course"<<endl;
                            s.add_course();
                            break;
                            }
                            
                        case 4://return
                            cout<<"Going Back to Add/Edit/Delete MENU"<<endl;
                            break;  

                        default:
                            cout<<"Invalid choice. Please enter a valid option."<<endl;
                        }
                    }while(choice_1_1 != 4);
                    break;


                    case 2://user selected edit
                    if(choice_1_1 == 4) {//check for return choice
                        choice_1_1=0;//reset choice
                        break;
                    }
                    int choice_1_2;
                    do{
                        displayeditmenu();
                        cin>>choice_1_2;
                        switch(choice_1_2){

                        case 1:{//student
                            cout<<"Selected Student"<<endl;
                            s.edit_student();
                            break;
                            }

                        case 2:{//professor
                            cout<<"Selected Professor"<<endl;
                            s.edit_professor();
                            break;
                            }

                        case 3:{//course
                            cout<<"Selected Course"<<endl;
                            s.edit_course();
                            break;
                            }
                            
                        case 4://return
                            cout<<"Going Back to Add/Edit/Delete MENU"<<endl;
                            break;  

                        default:
                            cout<<"Invalid choice. Please enter a valid option."<<endl;
                        }
                    }while(choice_1_2 != 4);
                    break;

                    case 3://user selected delete
                    if(choice_1_1 == 4) {//check for return choice
                        choice_1_1=0;//reset choice
                        break;
                    }
                    if(choice_1_2 == 4) {//check for return choice
                        choice_1_2=0;//reset choice
                        break;
                    }
                    int choice_1_3;
                    do{
                        displaydeletemenu();
                        cin>>choice_1_3;
                        switch(choice_1_3){

                        case 1:{//student
                            cout<<"Selected Student"<<endl;
                            s.delete_student();
                            break;
                            }

                        case 2:{//professor
                            cout<<"Selected Professor"<<endl;
                            s.delete_professor();
                            break;
                            }

                        case 3:{//course
                            cout<<"Selected Course"<<endl;
                            s.delete_course();
                            break;
                            }
                            
                        case 4://return
                            cout<<"Going Back to Add/Edit/Delete MENU"<<endl;
                            break;  

                        default:
                            cout<<"Invalid choice. Please enter a valid option."<<endl;
                        } 
                    }while(choice_1_3 !=4);
                    break;

                    case 4://user selected return to add/edit/delete menu
                    cout<<"Going back to Main MENU"<<endl;
                    break;

                    default:
                    cout<<"Invalid choice. Please enter a valid option."<<endl;
                }
            }while(choice_1 != 4);
            break;

            case 2:
            int choice_2;
            do{
                displayprintallmenu();
                cin>>choice_2;
                switch(choice_2){
                    case 1:{//student
                    cout<<"Selected Student"<<endl;
                    s.print_students();
                    
                    char exit;
                    cout<<endl<<"Press E to Exit to Print MENU: ";
                    cin>>exit;
                    if(exit=='E')break;
                    break;
                    }

                    case 2:{//professor
                    cout<<"Selected Professor"<<endl;
                    s.print_professors();
                    
                    char exit;
                    cout<<endl<<"Press E to Exit to Print MENU: ";
                    cin>>exit;
                    if(exit=='E')break;
                    break;
                    }

                    case 3:{//course
                    cout<<"Selected Course"<<endl;
                    s.print_courses();

                    char exit;
                    cout<<endl<<"Press E to Exit to Print MENU: ";
                    cin>>exit;
                    if(exit=='E')break;
                    break;
                    }
                    
                    case 4://return
                    cout<<"Going Back to Add/Edit/Delete MENU"<<endl;
                    break;  

                    default:
                    cout<<"Invalid choice. Please enter a valid option."<<endl;
                }
            }while(choice_2 != 4);
            break;

            case 3:
            s.assing_professor();
            break;
            
            case 4:
            s.select_course_for_student();
            break;
            
            case 5:
            s.exams();
            break;
            
            case 6:
            s.reset_data(studentfilepath, professorfilepath, coursefilepath);
            break;
            
            default:
            break;
        }
    } while(choice != 6);       
    
    return 0;
}


