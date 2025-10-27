//Assignment - 01
//Roll No - 23356
/*Problem Statement - Write a program for library management system using doubly linked list*/

#include<iostream>
#include<string>
#include<cctype>
using namespace std;

class node{
public:
    string name;
    string issueDate;
    node* next;
    node* back;

    node(string n,string i){
        name=n;
        issueDate=i;
        next=nullptr;
        back=nullptr;
    }
};

//Function to check if name is valid(letters and spaces only)
bool isValidName(string name){
    for(char c:name){
        if(!isalpha(c) && c!=' ')
            return false;
    }
    return !name.empty();
}

//Function to check if date is in dd/mm/yyyy format(basic check)
bool isValidDate(string date){
    if(date.size()!= 10) return false;
    if(date[2]!='/' || date[5]!='/') return false;

    string dd=date.substr(0,2);
    string mm=date.substr(3,2);
    string yyyy=date.substr(6,4);

    for(char c:dd+mm+yyyy){
        if(!isdigit(c)) return false;
    }
    return true;
}

//Function to take book name with validation
string getBookName(){
    string name;
    do{
        cout<<"Enter the name of the book: ";
        cin.ignore();
        getline(cin,name);
        if(!isValidName(name)) cout<<"Invalid! Only letters and spaces allowed.\n";
    } while(!isValidName(name));
    return name;
}

//Function to take date with validation
string getIssueDate(){
    string date;
    do{
        cout<<"Enter the issue date (dd/mm/yyyy): ";
        getline(cin,date);
        if(!isValidDate(date)) cout<<"Invalid date format!\n";
    } while(!isValidDate(date));
    return date;
}

//Function to Insert at end
node* insertAtEnd(node* head){
    string name=getBookName();
    string date=getIssueDate();

    node* newNode=new node(name,date);
    if(head==nullptr) return newNode;

    node* temp=head;
    while (temp->next!=nullptr) temp=temp->next;
    temp->next=newNode;
    newNode->back=temp;
    return head;
}

// Insert at beginning
node* insertAtBeginning(node* head){
    string name=getBookName();
    string date=getIssueDate();

    node* newNode = new node(name,date);
    if (head!=nullptr) {
        newNode->next=head;
        head->back=newNode;
    }
    return newNode;
}

// Insert at nth position
node* insertAtNth(node* head,int pos){
    if (pos <= 1) return insertAtBeginning(head);

    string name=getBookName();
    string date=getIssueDate();

    node* newNode=new node(name,date);
    node* temp=head;
    int count=1;

    while(temp!=nullptr && count<pos-1){
        temp=temp->next;
        count++;
    }

    if (temp==nullptr) return insertAtEnd(head);

    newNode->next=temp->next;
    if(temp->next!=nullptr) temp->next->back=newNode;
    temp->next=newNode;
    newNode->back=temp;
    return head;
}

// Delete at beginning
node* deleteAtBeginning(node* head){
    if(head==nullptr) {
        cout<<"List empty\n";
        return nullptr;
    }
    node* temp=head;
    head=head->next;
    if(head!=nullptr) head->back=nullptr;
    delete temp;
    cout<<"Deleted first book.\n";
    return head;
}

// Delete at end
node* deleteAtEnd(node* head){
    if(head==nullptr){
        cout<<"List empty\n";
        return nullptr;
    }
    if(head->next==nullptr){
        delete head;
        return nullptr;
    }
    node* temp=head;
    while (temp->next!=nullptr) temp=temp->next;
    temp->back->next=nullptr;
    delete temp;
    cout<<"Deleted last book.\n";
    return head;
}

// Delete at nth position
node* deleteAtNth(node* head,int pos) {
    if(pos <= 1) return deleteAtBeginning(head);

    node* temp=head;
    int count=1;
    while(temp!=nullptr && count<pos){
        temp=temp->next;
        count++;
    }
    if(temp==nullptr){
        cout<<"Position out of range.\n";
        return head;
    }
    if(temp->next!=nullptr) temp->next->back=temp->back;
    if(temp->back != nullptr) temp->back->next=temp->next;
    delete temp;
    cout<<"Deleted book at position "<<pos<<".\n";
    return head;
}

// Search book
void searchBook(node* head){
    if(head==nullptr){
        cout<<"List empty\n";
        return;
    }
    string name;
    cout<<"Enter the name of the book to search: ";
    cin.ignore();
    getline(cin,name);

    node* temp=head;
    bool found=false;
    while(temp!=nullptr){
        if(temp->name==name){
            cout<<"Book found!\n";
            cout<<"Name: "<<temp->name<<"\nDate: "<<temp->issueDate<<"\n";
            found=true;
        }
        temp=temp->next;
    }
    if(!found) cout<<"Book not found.\n";
}

// Display list
void display(node* head){
    if(head==nullptr){
        cout<<"List empty\n";
        return;
    }
    node* temp=head;
    while(temp!=nullptr){
        cout<<"Name: "<<temp->name<<"\nDate: "<<temp->issueDate<<"\n\n";
        temp=temp->next;
    }
}

int main(){
    node* head=nullptr;
    char ch;
    do{
        int choice;
        cout<<"\nMENU\n";
        cout<<"1. Insert at End\n";
        cout<<"2. Display\n";
        cout<<"3. Insert at Beginning\n";
        cout<<"4. Delete at Beginning\n";
        cout<<"5. Delete at End\n";
        cout<<"6. Insert at Nth Position\n";
        cout<<"7. Delete at Nth Position\n";
        cout<<"8. Search Book\n";
        cout<<"Enter choice: ";
        cin>>choice;

        switch(choice){
            case 1:
                head=insertAtEnd(head); 
                break;
            case 2:
                display(head);
                break;
            case 3:
                head=insertAtBeginning(head);
                break;
            case 4:
                head=deleteAtBeginning(head);
                break;
            case 5:
                head=deleteAtEnd(head);
                break;
            case 6:{
                int pos;
                cout<<"Enter position: ";
                cin>>pos;
                head=insertAtNth(head,pos);
                break;
            }
            case 7:{
                int pos;
                cout<<"Enter position: ";
                cin>>pos;
                head=deleteAtNth(head,pos);
                break;
            }
            case 8:
                searchBook(head); 
                break;
            default: 
                cout<<"Invalid choice\n";
        }

        cout<<"Do you want to continue?(y/n): ";
        cin>>ch;
    } while(ch == 'y' || ch == 'Y');
    return 0;
}

/*Output - 
MENU
1. Insert at End
2. Display
3. Insert at Beginning
4. Delete at Beginning
5. Delete at End
6. Insert at Nth Position
7. Delete at Nth Position
8. Search Book
Enter choice: 1
Enter the name of the book: C Programming
Enter the issue date (dd/mm/yyyy): 12/02/2002
Do you want to continue?(y/n): y

MENU
1. Insert at End
2. Display
3. Insert at Beginning
4. Delete at Beginning
5. Delete at End
6. Insert at Nth Position
7. Delete at Nth Position
8. Search Book
Enter choice: 3
Enter the name of the book: Python Programming
Enter the issue date (dd/mm/yyyy): 30/09/2001
Do you want to continue?(y/n): y

MENU
1. Insert at End
2. Display
3. Insert at Beginning
4. Delete at Beginning
5. Delete at End
6. Insert at Nth Position
7. Delete at Nth Position
8. Search Book
Enter choice: 2
Name: Python Programming
Date: 30/09/2001

Name: C Programming
Date: 12/02/2002

Do you want to continue?(y/n): y

MENU
1. Insert at End
2. Display
3. Insert at Beginning
4. Delete at Beginning
5. Delete at End
6. Insert at Nth Position
7. Delete at Nth Position
8. Search Book
Enter choice: 4
Deleted first book.
Do you want to continue?(y/n): y

MENU
1. Insert at End
2. Display
3. Insert at Beginning
4. Delete at Beginning
5. Delete at End
6. Insert at Nth Position
7. Delete at Nth Position
8. Search Book
Enter choice: 5
Do you want to continue?(y/n): y

MENU
1. Insert at End
2. Display
3. Insert at Beginning
4. Delete at Beginning
5. Delete at End
6. Insert at Nth Position
7. Delete at Nth Position
8. Search Book
Enter choice: 6
Enter position: 1
Enter the name of the book: Java Programming
Enter the issue date (dd/mm/yyyy): 22/06/2003
Do you want to continue?(y/n): y

MENU
1. Insert at End
2. Display
3. Insert at Beginning
4. Delete at Beginning
5. Delete at End
6. Insert at Nth Position
7. Delete at Nth Position
8. Search Book
Enter choice: 1
Enter the name of the book: Javascript Programming
Enter the issue date (dd/mm/yyyy): 21/02/2004
Do you want to continue?(y/n): y

MENU
1. Insert at End
2. Display
3. Insert at Beginning
4. Delete at Beginning
5. Delete at End
6. Insert at Nth Position
7. Delete at Nth Position
8. Search Book
Enter choice: 8
Enter the name of the book to search: Java Programming
Book found!
Name: Java Programming
Date: 22/06/2003
Do you want to continue?(y/n): y

MENU
1. Insert at End
2. Display
3. Insert at Beginning
4. Delete at Beginning
5. Delete at End
6. Insert at Nth Position
7. Delete at Nth Position
8. Search Book
Enter choice: 7
Enter position: 1
Deleted first book.
Do you want to continue?(y/n): y

MENU
1. Insert at End
2. Display
3. Insert at Beginning
4. Delete at Beginning
5. Delete at End
6. Insert at Nth Position
7. Delete at Nth Position
8. Search Book
Enter choice: 2
Name: Javascript Programming
Date: 21/02/2004

Do you want to continue?(y/n): n
*/