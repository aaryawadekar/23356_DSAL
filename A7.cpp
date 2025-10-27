//Assignment No - 07
//Roll No - 23356
/*Problem Statement - 
Department maintains student database. The file contains roll number, name, division and address. Implement a CPP program to -
1. Create a sequential file to store and maintain student data.
2. It should allow the user to add and delete information of students.
3. Display information of particular student.
i. If the student record does not exist an appropriate message is displayed.
ii. If student record is found it should display the student details.
*/
#include<iostream>
#include<fstream>
using namespace std;

class student{
public:
    int roll;
    string name;
    float marks;
};

class studentDatabase{
public:
    student s;

    //Function to take input 
    void input(){
        ofstream outfile("student.txt",ios::app);
        cout<<"Enter the name of the student: ";
        cin>>s.name;
        //To check for same roll no
        do{
            cout<<"Enter the roll no of the student: ";
            cin>>s.roll;
            if(rollExist(s.roll)){
                cout<<"Roll No already exists"<<endl;
            }
        }while(rollExist(s.roll));
        cout<<"Enter the marks of the student: ";
        cin>>s.marks;
        outfile<<s.name<<" "<<s.roll<<" "<<s.marks<<endl;

        outfile.close();
    }

    //Function to check for same roll No
    bool rollExist(int rollNo){
        ifstream infile("student.txt");
        if(!infile){
            cerr<<"Error in opening file"<<endl;
            return false;
        }
        student temp;
        while(infile>>temp.name>>temp.roll>>temp.marks){
            if(temp.roll==rollNo){
                return true;
            }
        }
        infile.close();
        return false;
    }

    //Function to add information in file
    void addInfo(){
        ofstream outfile("student.txt",ios::app);
        if(!outfile){
            cerr<<"Error in opening file"<<endl;
            return;
        }
        if (!outfile.good()) {
            cerr<<"File not writable! It may be open in read-only mode."<<endl;
            return;
        }
        input();
        outfile.close();
    }

    //Function to display all the information from the file
    void display(){
        ifstream infile("student.txt");
        if(!infile){
            cerr<<"Error in opening file"<<endl;
            return;
        }
        string name;
        int roll;
        float marks;
        cout<<"Student information: "<<endl;
        while(infile>>name>>roll>>marks){
            cout<<"Name: "<<name<<"||"<<"Roll No: "<<roll<<"||"<<"Marks: "<<marks<<endl;
        }
        infile.close();
    }

    //Function to search from file
    void search(int rollNo){
        ifstream infile("student.txt");
        if (!infile) {
            cout << "No data found." << endl;
            return;
        }
        student s;
        bool found = false;
        while (infile >> s.name >> s.roll >> s.marks) {
            if (s.roll == rollNo) {
                cout << "Found student:\n";
                cout << "Name: " << s.name << ", Roll: " << s.roll << ", Marks: " << s.marks << endl;
                found = true;
                break;
            }
        }
        if (!found)
            cout << "Student with roll no " << rollNo << " not found." << endl;
        infile.close();
    }

    //Function to modify content in a file
    void modifyFile(int rollNo){
        ifstream infile("student.txt");
        ofstream temp("temp.txt");
        student s;
        bool found = false;
        if (!infile) {
            cout<<"No data found"<<endl;
            return;
        }
        while (infile >> s.name >> s.roll >> s.marks) {
            if (s.roll == rollNo) {
                cout << "Enter new name: ";
                cin >> s.name;
                cout << "Enter new roll no: ";
                cin >> s.roll;
                cout << "Enter new marks: ";
                cin >> s.marks;
                found = true;
            }
            temp << s.name << " " << s.roll << " " << s.marks << endl;
        }
        infile.close();
        temp.close();

        if (found) {
            remove("student.txt");
            rename("temp.txt", "student.txt");
            cout << "Student info updated.\n";
        } else {
            remove("temp.txt");
            cout << "Student with roll no " << rollNo << " not found.\n";
        }
    }

    //Function to delete information from file
    void deleteInfo(int rollNo){
        ifstream infile("student.txt");
        ofstream temp("temp.txt");
        student s;
        bool found = false;
        if (!infile) {
            cout << "No data found." << endl;
            return;
        }
        while (infile >> s.name >> s.roll >> s.marks) {
            if (s.roll == rollNo) {
                found = true; 
            } else {
                temp << s.name << " " << s.roll << " " << s.marks << endl;
            }
        }
        infile.close();
        temp.close();

        if (found) {
            remove("student.txt");
            rename("temp.txt", "student.txt");
            cout << "Student deleted successfully.\n";
        } else {
            remove("temp.txt");
            cout << "Student with roll no " << rollNo << " not found.\n";
        }
    }
};

int main(){
    //To check if the file already exists or not
    ifstream infile("student.txt");
    if(!infile){
        cout<<"File doesnt exist"<<endl;
        cout<<"New file created"<<endl;
    }else{
        cout<<"File exists"<<endl;
        cout<<"File opened successfully"<<endl;
    }
    infile.close();
    
    int choice;
    char ch;
    studentDatabase s;

    //Using do while loop for a menu-driven program
    do{
        cout<<endl;
        cout<<"Menu:"<<endl;
        cout<<"1.Add infomation of student"<<endl;
        cout<<"2.Delete information of student"<<endl;
        cout<<"3.Modify information of student"<<endl;
        cout<<"4.Display information of all students"<<endl;
        cout<<"5.To search for a student"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice){
            case 1:
                s.addInfo();
                break;

            case 2:{
                int rollNo;
                cout<<"Enter the roll No you want to delete: ";
                cin>>rollNo;
                s.deleteInfo(rollNo);
                break;
            }

            case 3:{
                int rollNo;
                cout<<"Enter the roll No which you want to modify: ";
                cin>>rollNo;
                s.modifyFile(rollNo);
                break;
            }

            case 4:
                s.display();
                break;

            case 5:{
                int rollNo;
                cout<<"Enter the roll no you want to search for: ";
                cin>>rollNo;
                s.search(rollNo);
                break;
            }
        }
        cout<<"Do you want to continue(y/n): ";
        cin>>ch;
    }while(ch=='y'||ch=='Y');

    cout<<"Program Terminated"<<endl;

    return 0;
}

/*Output:
File doesnt exist
New file created

Menu:
1.Add infomation of student
2.Delete information of student
3.Modify information of student
4.Display information of all students
5.To search for a student
Enter your choice: 1
Enter the name of the student: Aarya
Enter the roll no of the student: 1
Enter the marks of the student: 100
Do you want to continue(y/n): y

Menu:
1.Add infomation of student
2.Delete information of student
3.Modify information of student
4.Display information of all students
5.To search for a student
Enter your choice: 1
Enter the name of the student: Arpita
Enter the roll no of the student: 2
Enter the marks of the student: 100
Do you want to continue(y/n): y

Menu:
1.Add infomation of student
2.Delete information of student
3.Modify information of student
4.Display information of all students
5.To search for a student
Enter your choice: 1
Enter the name of the student: Ameya
Enter the roll no of the student: 3
Enter the marks of the student: 98
Do you want to continue(y/n): y

Menu:
1.Add infomation of student
2.Delete information of student
3.Modify information of student
4.Display information of all students
5.To search for a student
Enter your choice: 1
Enter the name of the student: Sarvesh
Enter the roll no of the student: 4
Enter the marks of the student: 95
Do you want to continue(y/n): y

Menu:
1.Add infomation of student
2.Delete information of student
3.Modify information of student
4.Display information of all students
5.To search for a student
Enter your choice: 1
Enter the name of the student: Nikhil
Enter the roll no of the student: 5
Enter the marks of the student: 76
Do you want to continue(y/n): y

Menu:
1.Add infomation of student
2.Delete information of student
3.Modify information of student
4.Display information of all students
5.To search for a student
Enter your choice: 1
Enter the name of the student: Abhaya
Enter the roll no of the student: 6
Enter the marks of the student: 91
Do you want to continue(y/n): y

Menu:
1.Add infomation of student
2.Delete information of student
3.Modify information of student
4.Display information of all students
5.To search for a student
Enter your choice: 1
Enter the name of the student: Seema
Enter the roll no of the student: 7
Enter the marks of the student: 100
Do you want to continue(y/n): y

Menu:
1.Add infomation of student
2.Delete information of student
3.Modify information of student
4.Display information of all students
5.To search for a student
Enter your choice: 1
Enter the name of the student: Madhuri
Enter the roll no of the student: 8
Enter the marks of the student: 83
Do you want to continue(y/n): y

Menu:
1.Add infomation of student
2.Delete information of student
3.Modify information of student
4.Display information of all students
5.To search for a student
Enter your choice: 1     
Enter the name of the student: Ojasvi
Enter the roll no of the student: 9
Enter the marks of the student: 88
Do you want to continue(y/n): y

Menu:
1.Add infomation of student
2.Delete information of student
3.Modify information of student
4.Display information of all students
5.To search for a student
Enter your choice: 1
Enter the name of the student: Nandini
Enter the roll no of the student: 9
Roll No already exists
Enter the roll no of the student: 10
Enter the marks of the student: 92
Do you want to continue(y/n): y

Menu:
1.Add infomation of student
2.Delete information of student
3.Modify information of student
4.Display information of all students
5.To search for a student
Enter your choice: 2
Enter the roll No you want to delete: 10
Student deleted successfully.
Do you want to continue(y/n): y

Menu:
1.Add infomation of student
2.Delete information of student
3.Modify information of student
4.Display information of all students
5.To search for a student
Enter your choice: 3
Enter the roll No which you want to modify: 6
Enter new name: Shrawani
Enter new roll no: 6
Enter new marks: 99
Student info updated.
Do you want to continue(y/n): y

Menu:
1.Add infomation of student
2.Delete information of student
3.Modify information of student
4.Display information of all students
5.To search for a student
Enter your choice: 4
Student information: 
Name: Aarya||Roll No: 1||Marks: 100
Name: Arpita||Roll No: 2||Marks: 100
Name: Ameya||Roll No: 3||Marks: 98
Name: Sarvesh||Roll No: 4||Marks: 95
Name: Nikhil||Roll No: 5||Marks: 76
Name: Shrawani||Roll No: 6||Marks: 99
Name: Seema||Roll No: 7||Marks: 100
Name: Madhuri||Roll No: 8||Marks: 83
Name: Ojasvi||Roll No: 9||Marks: 88
Do you want to continue(y/n): y

Menu:
1.Add infomation of student
2.Delete information of student
3.Modify information of student
4.Display information of all students
5.To search for a student
Enter your choice: 5
Enter the roll no you want to search for: 2
Found student:
Name: Arpita, Roll: 2, Marks: 100
Do you want to continue(y/n): y

Menu:
1.Add infomation of student
2.Delete information of student
3.Modify information of student
4.Display information of all students
5.To search for a student
Enter your choice: 5
Enter the roll no you want to search for: 10
Student with roll no 10 not found.
Do you want to continue(y/n): n
Program Terminated
*/