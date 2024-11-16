// Acadmey Managment System comprises of 1 Main class Acadmey that runs All functions and classes 
// 1 Admin class that can add and remove students and teachers and also manges fees and salary
// 1 teacher class that can compile results of students and see his salary status
// 1 student class that can view results and their fees status (paid or not)
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// Main Class 
class Academy
{
public:
    void run();  // Function is defined outside the class performs all tasks
};

class Student
 {
    friend class Teacher;
    friend class Admin;
private:
    bool feeStatus;
    string subjects[5] = {"Maths", "Physics", "Chemistry", "English", ""}; // Last subject to be chosen by student
    int marks[5];
public:
    string username;
    string password;
    Student() : feeStatus(false)  // constructor to add subjects marks of students
     {
        for (int i = 0; i < 5; ++i)
         {
            marks[i] = 0;
        }
    }

    bool getFeeStatus() const
     {
        return feeStatus;
    }

    void setFeeStatus(bool status) {
        feeStatus = status;
    }

    void setMarks(int subjectIndex, int newMarks)  // Function to get marks of students
     {
        if (subjectIndex >= 0 && subjectIndex < 5)
         {
            marks[subjectIndex] = newMarks;
        }
    }

    int getMarks(int subjectIndex) const 
    {
        if (subjectIndex >= 0 && subjectIndex < 5) {
            return marks[subjectIndex];
        }
        return 0;
    }

    void setSubjectChoice(const string& choice)  // choose subjects choice
    {
        subjects[4] = choice;
    }

    void viewResults() const   
     {
        cout << "Your marks:\n";
        for (int i = 0; i < 5; ++i) {
            cout << subjects[i] << ": " << marks[i] << endl;
        }
    }

    void viewFeeStatus() const
     {
        cout << "Fee Status: " << (feeStatus ? "Paid" : "Unpaid") << endl;
    }
   // operator overloading to input students name, paswords and fee status and subjects
    friend istream& operator>>(istream& is, Student& student) {
        is >> student.username >> student.password >> student.feeStatus;
        for (int i = 0; i < 5; ++i) {
            is >> student.subjects[i] >> student.marks[i];
        }
        return is;
    }
   // operator overloading to output students name, paswords and fee status and subjects
    friend ostream& operator<<(ostream& os, const Student& student) {
        os << student.username << " " << student.password << " " << student.feeStatus;
        for (int i = 0; i < 5; ++i) {
            os << " " << student.subjects[i] << " " << student.marks[i];
        }
        return os;
    }
};

class Teacher
 {
private:
    bool salaryStatus;
    string subjects[2] = {"", ""}; // Teacher can teach up to two subjects
public:
    string username;
    string password;
    Teacher() : salaryStatus(false) {}
    bool getSalaryStatus() const
     {
        return salaryStatus;
    }
    void setSalaryStatus(bool status) {
        salaryStatus = status;
    }
  // subjects that teacher will teach 
    void setSubjects(const string& subject1, const string& subject2 = "") {
        subjects[0] = subject1;
        subjects[1] = subject2;
    }
// teacher can teach one or 2 subjects
    bool canTeachSubject(const string& subject) const
     {
        return subjects[0] == subject || subjects[1] == subject;
    }

// change marks of subjects which teacher is teaching of his students
    void changeMarks(Student& student, const string& subject, int newMarks)
     {
            int count=0;
        for (int i = 0; i < 5; ++i)
         {
            if (student.subjects[i] == subject)
             {
                student.setMarks(i, newMarks);
                count++;
                break;
            }
        }
        if(count==0)
        cout<<"student Not found ";
    }
// display all students results 
    void compileResults(Student students[], int studentCount) const {
        for (int i = 0; i < studentCount; ++i) {
            cout << students[i].username << ": ";
            for (int j = 0; j < 5; ++j) {
                if (canTeachSubject(students[i].subjects[j])) {
                    cout << students[i].subjects[j] << ": " << students[i].marks[j] << " ";
                }
            }
            cout << endl;
        }
    }
// check salary status
    void SalaryStatus() const
     {
        cout << "Your Salary is: " << (salaryStatus ? "Ready" : "Not Ready") << endl;
    }
   // operator overloading to input teacher name, paswords and salary status and subjects
    friend istream& operator>>(istream& is, Teacher& teacher) {
        is >> teacher.username >> teacher.password >> teacher.subjects[0] >> teacher.subjects[1];
        return is;
    }
   // operator overloading to output teacher name, paswords and salary status and subjects
    friend ostream& operator<<(ostream& os, const Teacher& teacher) 
    {
        os << teacher.username << " " << teacher.password << " " << teacher.subjects[0] << " " << teacher.subjects[1];
        return os;
    }
};

class Admin 
{
    const string adminUsername = "admin";
    const string adminPassword = "admin123";
public:
    bool authenticate(const string &uname, const string &pass) // function to check username and pasword of admin
     {
        return uname == adminUsername && pass == adminPassword; // returns true or false
    }
  // function to add students 
    void addStudent(Student students[], int &studentCount, const string &uname, const string &pass)
     {
        students[studentCount].username = uname;
        students[studentCount].password = pass;
        cout << "Choose an additional subject (Computer/Biology): ";
        string subjectChoice;
        getline(cin, subjectChoice);

        // students can only choose one Computer or Biology
        if (subjectChoice == "Computer" || subjectChoice == "Biology")
         {
            students[studentCount].setSubjectChoice(subjectChoice);
        }
         else 
        // it will set computer if user has entered invlaid choice
        {
            cout << "Invalid choice, defaulting to Computer.\n";
            students[studentCount].setSubjectChoice("Computer");
        }
        studentCount++;
        cout << "Student added successfully!" << endl;
    }
// Function to remove students
    void removeStudent(Student students[], int &studentCount, const string &uname) {
        bool found = false;
        for (int i = 0; i < studentCount; ++i) {
            if (students[i].username == uname) {
                for (int j = i; j < studentCount - 1; ++j) {
                    students[j] = students[j + 1];
                }
                studentCount--;
                found = true;
                cout << "Student " << uname << " removed successfully!" << endl;
                break;
            }
        }
        if (!found) {
            cout << "Student " << uname << " not found!" << endl;
        }
    }

// function to add teacher
    void addTeacher(Teacher teachers[], int &teacherCount, const string &uname, const string &pass, const string &subject1, const string &subject2 = "") {
        teachers[teacherCount].username = uname;
        teachers[teacherCount].password = pass;
        teachers[teacherCount].setSubjects(subject1, subject2);
        teacherCount++;
        cout << "Teacher added successfully!" << endl;
    }
// function to remove teacher
    void removeTeacher(Teacher teachers[], int &teacherCount, const string &uname) {
        bool found = false;
        for (int i = 0; i < teacherCount; ++i) {
            if (teachers[i].username == uname) {
                for (int j = i; j < teacherCount - 1; ++j) {
                    teachers[j] = teachers[j + 1];
                }
                teacherCount--;
                found = true;
                cout << "Teacher " << uname << " removed successfully!" << endl;
                break;
            }
        }
        if (!found) {
            cout << "Teacher " << uname << " not found!" << endl;
        }
    }

// it will change fees status (to paid)
    void manageFees(Student &student, bool status)
     {
        student.setFeeStatus(status);
    }
// it will change salary status (to ready)
    void calculateSalary(Teacher &teacher, bool status) {
        teacher.setSalaryStatus(status);
    }
};

void Academy::run()  // main function that will perform all tasks
 {
    const int MAX_STUDENTS = 100;  
    const int MAX_TEACHERS = 10;

    Student students[MAX_STUDENTS];
    Teacher teachers[MAX_TEACHERS];
    Admin admin;

    int studentCount = 0;
    int teacherCount = 0;
// it will store data in files
    ifstream studentsFile("Students.txt");
    ifstream teachersFile("Teachers.txt");

    if (studentsFile.is_open()) 
    {
        while (studentsFile >> students[studentCount]) {
            studentCount++;
        }
        studentsFile.close();
    }

    if (teachersFile.is_open()) {
        while (teachersFile >> teachers[teacherCount]) {
            teacherCount++;
        }
        teachersFile.close();
    }

    char choice;
    while (true) 
    {
        cout << "                                   Welcome to Academy Management System\n\n";
        cout << "1. Admin login\n2. Teacher login\n3. Student login\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To consume the newline character after choice input
        if (choice == '4')
         {
            system("cls");
            cout << "\nGood Bye" << endl;
            break;
        }
        switch (choice) {
        case '1':  // admin role 
         {
            string uname, pass;
            cout << "Enter admin username: ";
            getline(cin, uname);
            cout << "Enter admin password: ";
            getline(cin, pass);
            if (admin.authenticate(uname, pass))
             {    system("cls");
                int adminChoice;
                while (true) 
                {
                    cout << "1. Add Student\n2. Remove Student\n3. Add Teacher\n4. Remove Teacher\n5. Manage Fees\n6. Manage Salary\n7. Logout\n";
                    cout << "Enter your choice: ";
                    cin >> adminChoice;
                    cin.ignore();

                    if (adminChoice == 1) 
                    {
                        string sname, spass;
                        cout << "Enter student username: ";
                        getline(cin, sname);
                        cout << "Enter student password: ";
                        getline(cin, spass);
                          system("cls");
                        admin.addStudent(students, studentCount, sname, spass);
                    
                     } 
                     else if (adminChoice == 2)
                     {
                        string sname;
                        cout << "Enter student username: ";
                        getline(cin, sname);
                          system("cls");
                        admin.removeStudent(students, studentCount, sname);
                    } 
                    else if (adminChoice == 3)
                     {
                        string tname, tpass, subject1, subject2;
                        cout << "Enter teacher username: ";
                        getline(cin, tname);
                        cout << "Enter teacher password: ";
                        getline(cin, tpass);
                        cout << "Enter subject1: ";
                        getline(cin, subject1);
                        cout << "Enter subject2 (optional): ";
                        getline(cin, subject2);
                          system("cls");
                        admin.addTeacher(teachers, teacherCount, tname, tpass, subject1, subject2);
                    }
                     else if (adminChoice == 4) 
                    {
                        string tname;
                        cout << "Enter teacher username: ";
                        getline(cin, tname);
                        system("cls");
                        admin.removeTeacher(teachers, teacherCount, tname);
                    }
                      else if (adminChoice == 5)
                     {
                          system("cls");
                        string sname;
                        cout << "Enter student username: ";
                        getline(cin, sname);
                        cout<<"Want to Mark Paid(0), Unpaid(1): ";
                        int paid;
                        cin>>paid;
                        if(paid==0)
                        {
                        for (int i = 0; i < studentCount; ++i)
                         {
                            if (students[i].username == sname)
                             {
                                admin.manageFees(students[i], true);
                                cout << "Fee is marked as paid for " << sname << endl;
                                break;
                            }
                        }
                        }
                            if(paid==1)
                        {
                        for (int i = 0; i < studentCount; ++i)
                         {
                            if (students[i].username == sname)
                             {
                                admin.manageFees(students[i], false);
                                cout << "Fee is marked as unpaid for " << sname << endl;
                                break;
                            }
                        }
                        }
                    
                    } 
                    else if (adminChoice == 6)
                     { 
                        system("cls");
                        string tname;
                        cout << "Enter teacher username: ";
                        getline(cin, tname);
                        cout<<"Want to marked ready(0), Unready(1): ";
                        int choice;
                        cin>>choice;
                        if(choice==0)
                        {
                        for (int i = 0; i < teacherCount; ++i) {
                            if (teachers[i].username == tname) {
                                admin.calculateSalary(teachers[i], true);
                                cout << "Salary marked as ready for " << tname << endl;
                                break;
                            }
                        }
                        }
                              if(choice==1)
                        {
                        for (int i = 0; i < teacherCount; ++i)
                         {
                            if (teachers[i].username == tname)
                             {
                                admin.calculateSalary(teachers[i], false);
                                cout << "Salary marked as Unready for " << tname << endl;
                                break;
                            }
                        }
                        }
                    } 
                    else if (adminChoice == 7)
                     {
                        system("cls");
                        break;
                    }
                }
            } 
            else
             { 
                  system("cls");
                cout << "Invalid admin credentials!" << endl;
            }
            break;
        }
        case '2':  // teacher role
         {
            string uname, pass;
            cout << "Enter teacher username: ";
            getline(cin, uname);
            cout << "Enter teacher password: ";
            getline(cin, pass);
              system("cls");
            bool found = false;
            for (int i = 0; i < teacherCount; ++i) {
                if (teachers[i].username == uname && teachers[i].password == pass) {
                    found = true;
                    int teacherChoice;
                    while (true) {
                        cout << "1. Change Student Marks\n2. Compile Results\n3. View Salary Status\n4. Logout\n";
                        cout << "Enter your choice: ";
                        cin >> teacherChoice;
                        cin.ignore();
                          system("cls");

                       // change marks of students

                        if (teacherChoice == 1) 
                        {
                            string sname, subject;
                            int marks;
                            cout << "Enter student username: ";
                            getline(cin, sname);
                            cout << "Enter subject: ";
                            getline(cin, subject);
                            cout << "Enter new marks: ";
                            cin >> marks;
                            cin.ignore();
                              system("cls");
                            if (teachers[i].canTeachSubject(subject))
                             {
                                int count=0;
                                for (int j = 0; j < studentCount; ++j) 
                                {
                                    if (students[j].username == sname)
                                     {
                                        teachers[i].changeMarks(students[j], subject, marks);
                                        cout << "Marks updated for " << sname << " in subject " << subject << endl;
                                        count++;
                                        break;
                                    }
                                }

                                if(count==0)
                                cout<<"Student not found"<<endl;  
                            } else {
                                  system("cls");
                                cout << "You are not authorized to change marks for this subject.\n";
                            }
                        } 
                        else if (teacherChoice == 2) 
                        {   
                              system("cls");
                            teachers[i].compileResults(students, studentCount);
                        } 
                        else if (teacherChoice == 3)
                         { 
                              system("cls");
                            teachers[i].SalaryStatus();
                        }
                         else if (teacherChoice == 4)
                          {
                              system("cls");
                            break;
                        }
                    }
                    break;
                }
            }
            if (!found) {
                  system("cls");
                cout << "Invalid teacher credentials!" << endl;
            }
            break;
        }
        case '3': 
        {  //students role
            string uname, pass;
            cout << "Enter student username: ";
            getline(cin, uname);
            cout << "Enter student password: ";
            getline(cin, pass);
              system("cls");
            bool found = false;
            for (int i = 0; i < studentCount; ++i)
             {
                if (students[i].username == uname && students[i].password == pass) {
                    found = true;
                    int studentChoice;
                    while (true) {
                        cout << "1. View Results\n2. View Fee Status\n3. Logout\n";
                        cout << "Enter your choice: ";
                        cin >> studentChoice;
                        cin.ignore();
                          system("cls");
                        if (studentChoice == 1)
                         {  
                              system("cls");
                            students[i].viewResults();
                        } 
                        else if (studentChoice == 2)
                         {     system("cls");
                            students[i].viewFeeStatus();
                        } 
                        else if (studentChoice == 3) 
                        {      system("cls");
                            break;
                        }
                    }
                    break;
                }
            }
            if (!found)
             {    system("cls");
                cout << "Invalid student credentials!" << endl;
            }
            break;
        }
        default:
        {
              system("cls");
            cout << "Invalid Input" << endl;
            break;
        }
        }
    }
// loads data into file 

    ofstream studentsFileOut("Students.txt");
    for (int i = 0; i < studentCount; ++i) {
        studentsFileOut << students[i] << endl;
    }
    studentsFileOut.close();

    ofstream teachersFileOut("Teachers.txt");
    for (int i = 0; i < teacherCount; ++i)
     {
        teachersFileOut << teachers[i] << endl;
    }
    teachersFileOut.close();
}

int main()
 {
    Academy academy;
    academy.run();
    return 0;
}
