//Assignment No - 03
//Roll No - 23356
/*PROBLEM STATEMENT - Consider a student database of SEIT class (at least 15 records). Database
contains different fields of every student like Roll No, Name and SGPA.
(array of structure)
a) Design a roll call list, arrange list of students according to roll
numbers in ascending order (Use Bubble Sort)
b) Arrange a list of students alphabetically. (Use Insertion sort)
c) Arrange a list of students to find out the first ten toppers from a class.
(Use Quick sort)
d) Search for students according to SGPA. If more than one student has
the same SGPA, then print a list of all students having the same SGPA.
e) Search for a particular student according to name using binary search
without recursion. (all the student records having the presence of search
key should be displayed)*/

#include<iostream>
#include<cstring>
using namespace std;

//Structure to define student
struct student{
    int roll;
    string name;
    float sgpa;
};

//Function to display the details
void display(student stu[],int n){
    for(int i=0;i<n;i++){
        cout<<"Name: "<<stu[i].name<<"||"<<"Roll No: "<<stu[i].roll<<"||"<<"SGPA: "<<stu[i].sgpa<<endl;
    }
}

//Function to take input of the student details
void input(student stu[],int n){
    for(int i=0;i<n;i++){
        cout<<"Enter the name of the student: ";
        cin>>stu[i].name;
        cout<<"Enter the roll no of the student: ";
        cin>>stu[i].roll;
        cout<<"Enter the sgpa of the student: ";
        cin>>stu[i].sgpa;
        cout<<endl;
    }

}

//Function to find a student with given sgpa using linear search
void linearSearch(student stu[],int n){
    float key;
    cout<<"Enter the sgpa to find: ";
    cin>>key;

    int i=0,flag=0;
    while(i<n){
        if(stu[i].sgpa==key){
            cout<<"Name: "<<stu[i].name<<"||"<<"Roll No: "<<stu[i].roll<<endl;
            flag=1;
        }
        i++;
    }
    if(flag==0){
        cout<<"No match found!"<<endl;
    }
}

//Function to arrange list in ascending order according using bubble sort
void bubbleSort(student stu[],int n){
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-i-1;j++){
            if(stu[j].roll>stu[j+1].roll){
                swap(stu[j],stu[j+1]);
            }
        }
    }
}

//Function to arrange the list of students alphabetically according to thier name using insertion sort
void insertionSort(student stu[],int n){
    for(int i=1;i<n;i++){
        student key=stu[i];
        int j=i-1;
        while(j>=0 && (stu[j].name>key.name)){
            stu[j+1]=stu[j];
            j--;
        }
        stu[j+1]=key;
    }
}

//Function to find a student with of particular name given using binary search
void binarySearch(student stu[],int n){
    insertionSort(stu,n);

    string k;
    cout<<"Enter the name of student: ";
    cin>>k;

    int l=0,h=n-1;
    while(l<=h){
        int mid=(l+h)/2;

        if(stu[mid].name==k){
            cout<<"Found!"<<endl;
            cout <<"Name: "<<stu[mid].name<<" || "<<"Roll No: "<<stu[mid].roll<<" || "<<"SGPA: "<<stu[mid].sgpa<<endl;
            return;
        }else if(k<stu[mid].name){
            h=mid-1;
        }else{
            l=mid+1;
        }
    }
    cout<<"Not found"<< endl;
}

//Function to make two parts of given list for quick sort
int partition(student stu[],int l,int h){
    float pivot=stu[l].sgpa;
    int i=l;
    int j=h;

    while(i<=j){
        while(i<=j && stu[i].sgpa>=pivot) i++;
        while(i<=j && stu[i].sgpa<=pivot) j--;
        if(i<j){
            swap(stu[i],stu[j]);
        }
    }
    swap(stu[l],stu[j]);
    return j;
}

//Function to arrange the list of students in descending order according to sgpa using quick sort
void quickSort(student stu[],int l,int h){
    if(l<h){
        int p=partition(stu,l,h);
        quickSort(stu,l,p-1);
        quickSort(stu,p+1,h);
    }
}

int main(){
    int n;
    cout<<"Enter the number of students: ";
    cin>>n;
    student s[n];

    input(s,n);

    char c;
    
    do{
        int a;
        cout<<"MENU:"<<endl;
        cout<<"1.To display details"<<endl;
        cout<<"2.Arrange list of students according to roll no in ascending order"<<endl;
        cout<<"3.Arrange a list of students alphabetically"<<endl;
        // cout<<"4.Arrange a list of students to find out the first ten toppers from a class"<<endl;
        cout<<"4.Search for students according to SGPA"<<endl;
        cout<<"5.Search for a particular student according to name"<<endl;
        cout<<"6.To display the list in descending order of sgpa"<<endl;
        cout<<"Enter your choice: ";
        cin>>a;

        int k;
        //Using switch case to make the program menu driven
        switch(a){
            case 1:
                display(s,n);
                break;

            case 2:
                bubbleSort(s,n);
                display(s,n);
                break;

            case 3:
                insertionSort(s,n);
                display(s,n);
                break;
                
            case 4:
                linearSearch(s,n); 
                break;

            case 5:
                binarySearch(s,n);
                break;

            case 6:
                quickSort(s,0,n-1);
                display(s,n);
                break;
        }
        
        cout<<"Do you want to continue(y/n): "<<endl;
        cin>>c;
    }while(c=='y'||c=='Y');
    
    cout<<"Program Ended"<<endl;

    return 0;
}

/*OUTPUT:

Enter the number of students: 4
Enter the name of the student: Arpita
Enter the roll no of the student: 2
Enter the sgpa of the student: 10

Enter the name of the student: Ameya
Enter the roll no of the student: 1
Enter the sgpa of the student: 9.9

Enter the name of the student: Varad
Enter the roll no of the student: 4
Enter the sgpa of the student: 8

Enter the name of the student: Priya
Enter the roll no of the student: 3
Enter the sgpa of the student: 9.5

MENU:
1.To display details
2.Arrange list of students according to roll no in ascending order
3.Arrange a list of students alphabetically
4.Search for students according to SGPA
5.Search for a particular student according to name
6.To display the list in descending order of sgpa
Enter your choice: 2
Name: Ameya||Roll No: 1||SGPA: 9.9
Name: Arpita||Roll No: 2||SGPA: 10
Name: Priya||Roll No: 3||SGPA: 9.5
Name: Varad||Roll No: 4||SGPA: 8
Do you want to continue(y/n): 
y
MENU:
1.To display details
2.Arrange list of students according to roll no in ascending order
3.Arrange a list of students alphabetically
4.Search for students according to SGPA
5.Search for a particular student according to name
6.To display the list in descending order of sgpa
Enter your choice: 3
Name: Ameya||Roll No: 1||SGPA: 9.9
Name: Arpita||Roll No: 2||SGPA: 10
Name: Priya||Roll No: 3||SGPA: 9.5
Name: Varad||Roll No: 4||SGPA: 8
Do you want to continue(y/n): 
y
MENU:
1.To display details
2.Arrange list of students according to roll no in ascending order
3.Arrange a list of students alphabetically
4.Search for students according to SGPA
5.Search for a particular student according to name
6.To display the list in descending order of sgpa
Enter your choice: 4
Enter the sgpa to find: 9.9
Name: Ameya||Roll No: 1
Do you want to continue(y/n): 
y
MENU:
1.To display details
2.Arrange list of students according to roll no in ascending order
3.Arrange a list of students alphabetically
4.Search for students according to SGPA
5.Search for a particular student according to name
6.To display the list in descending order of sgpa
Enter your choice: 5
Enter the name of student: Priya
Found!
Name: Priya || Roll No: 3 || SGPA: 9.5
Do you want to continue(y/n): 
y
MENU:
1.To display details
2.Arrange list of students according to roll no in ascending order
3.Arrange a list of students alphabetically
4.Search for students according to SGPA
5.Search for a particular student according to name
6.To display the list in descending order of sgpa
Enter your choice: 6
Name: Arpita||Roll No: 2||SGPA: 10
Name: Ameya||Roll No: 1||SGPA: 9.9
Name: Priya||Roll No: 3||SGPA: 9.5
Name: Varad||Roll No: 4||SGPA: 8
Do you want to continue(y/n): 
n
Program Ended
*/
