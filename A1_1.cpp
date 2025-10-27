//Assignment - 01
//Roll No - 23356
/*Problem Statement - "Efficient Data Management Using Linked Lists: Implementing Dynamic Operations for
Contact Management System"
Utilize Singly and Doubly Linked Lists to manage a Contact Management System. The system
will support key operations such as:
• Creating a contact list dynamically.
• Adding new contacts efficiently.
• Deleting contacts when no longer needed.
• Searching for specific contacts based on name or number.
• Reversing the contact list for alternate viewing orders.
• Traversing through the list to display all stored contacts.*/

#include<iostream>
#include<string>
using namespace std;

// Structure of contact
struct Contact{
    string name;
    string phone;
    string email;
    string company;
    string dob;
    Contact* next;
};

//Class of contact list
class ContactList{
    Contact* head;

public:
    // Constructor
    ContactList(){
        head = NULL;
    }

    // Destructor
    ~ContactList(){
        Contact* curr=head;
        while(curr!=NULL){
            Contact* temp=curr;
            curr=curr->next;
            delete temp;
        }
    }

    //To check whether the phone no has 10 digits
    bool isValidPhone(string p){
        if(p.size()!=10) return false;
        for(char c:p){
            if(!isdigit(c))
                return false;
        }
        return true;
    }

    //To check whether the email has @
    bool isValidEmail(string e){
        return e.find('@') != string::npos;
    }

    //To check the format of dob
    bool isValidDOB(string d){
        if (d.size() != 10) return false;
        if (!isdigit(d[0]) || !isdigit(d[1]) || d[2] != '/' ||
            !isdigit(d[3]) || !isdigit(d[4]) || d[5] != '/' ||
            !isdigit(d[6]) || !isdigit(d[7]) || !isdigit(d[8]) || !isdigit(d[9]))
            return false;
        return true;
    }

    //Function to take input
    void getNode(string& n,string& p,string& e,string& c,string& d){
        cin.ignore();

         cout<<"Enter name: ";
         getline(cin,n);

        do{
            cout<<"Enter the phone no(10 digits): ";
            cin>>p;
            if(!isValidPhone(p))
                cout<<"Invalid phone no!\n";
        }while(!isValidPhone(p));

        do{
            cout<<"Enter email(should contain '@'): ";
            cin>>e;
            if(!isValidEmail(e))
                cout<<"Invalid email!"<<endl;
        }while(!isValidEmail(e));

        cin.ignore();
        cout<<"Enter the company name: ";
        getline(cin,c);

        do{
            cout<<"Enter DOB(DD/MM/YYYY): ";
            cin>>d;
            if(!isValidDOB(d))
                cout<<"Wrong format!\n";
        }while(!isValidDOB(d));
    }

    //Function to create a new contact
    Contact* create(string n,string p,string e,string c,string d){
        Contact* t=new Contact;
        t->name=n;
        t->phone=p;
        t->email=e;
        t->company=c;
        t->dob=d;
        t->next=NULL;
        return t;
    }

    //Function to insert at beginning
    void insertAtB(string n,string p,string e,string c,string d){
        Contact* t=create(n,p,e,c,d);
        t->next=head;
        head=t;
    }

    //Function to insert at end
    void insertAtE(string n,string p,string e,string c,string d){
        Contact* t=create(n,p,e,c,d);
        if(head==NULL){
            head=t;
        }else{
            Contact* ptr=head;
            while(ptr->next!=NULL){
                ptr=ptr->next;
            }
            ptr->next=t;
        }
    }

    //Function to insert contact after given phone no
    void insertAfterPhone(){
        string findPhone,n,p,e,c,d;
        cout<<"Enter phone after which to insert: ";
        cin>>findPhone;

        Contact* ptr=head;
        while(ptr!=NULL && ptr->phone!=findPhone){
            ptr=ptr->next;
        }

        if(ptr!=NULL){
            getNode(n,p,e,c,d);
            Contact* t=create(n,p,e,c,d);
            t->next=ptr->next;
            ptr->next=t;
            cout<<"Contact added!\n";
        }else{
            cout<<"Phone not found!\n";
        }
    }

    //Function to display the list
    void display(){
        if(head == NULL){
            cout<<"No contacts.\n";
            return;
        }
        Contact* ptr=head;
        while(ptr!=NULL){
            cout<<ptr->name<<" | "<<ptr->phone<<" | "<<ptr->email<<" | "<<ptr->company<<" | "<<ptr->dob<<endl;
            ptr=ptr->next;
        }
        cout<<"NULL\n";
    }

    //Function to search by phone no
    void searchByPhone(string p){
        Contact* ptr=head;
        while(ptr!=NULL){
            if(ptr->phone==p){
                cout<<"Found: "<<ptr->name<<" | "<<ptr->phone<<" | "<<ptr->email<<" | "<<ptr->company<<" | "<<ptr->dob<<endl;
                return;
            }
            ptr=ptr->next;
        }
        cout<<"Not found!\n";
    }

    //Function to delete a particular contact of given phone no
    void deleteByPhone(string p){
        if(head==NULL){
            cout<<"Empty list.\n";
            return;
        }

        if(head->phone == p){
            Contact* t=head;
            head=head->next;
            delete t;
            cout<<"Deleted!\n";
            return;
        }

        Contact* prev=head;
        Contact* curr=head->next;
        while(curr != NULL){
            if(curr->phone==p){
                prev->next=curr->next;
                delete curr;
                cout<<"Deleted!"<<endl;
                return;
            }
            prev=curr;
            curr=curr->next;
        }
        cout<<"Not found!"<<endl;
    }

    //Function to reverse the given contact list
    void reverseList(){
        Contact* prev=NULL;
        Contact* curr=head;
        Contact* nxt=NULL;

        while(curr!=NULL){
            nxt=curr->next;
            curr->next=prev;
            prev=curr;
            curr=nxt;
        }
        head=prev;
        cout<<"List reversed!"<<endl;
    }
};

int main(){
    ContactList cl;
    int ch;
    string n,p,e,c,d;
    char cont;

    do{
        cout<<"\n1. Insert at start\n2. Insert at end\n3. Insert after phone\n4. Display\n"<<"5. Search any contact\n6. Delete any contact\n7. Reverse the list\n8. Exit\nChoice: ";
        cin>>ch;

        switch(ch){
        case 1:
            cl.getNode(n,p,e,c,d);
            cl.insertAtB(n,p,e,c,d);
            break;

        case 2:
            cl.getNode(n,p,e,c,d);
            cl.insertAtE(n,p,e,c,d);
            break;

        case 3:
            cl.insertAfterPhone();
            break;

        case 4:
            cl.display();
            break;

        case 5:
            cout<<"Enter phone: ";
            cin>>p;
            cl.searchByPhone(p);
            break;

        case 6:
            cout<<"Enter phone: ";
            cin>>p;
            cl.deleteByPhone(p);
            break;

        case 7:
            cl.reverseList();
            cl.display();
            break;

        case 8:
            cout<<"Exiting program!"<<endl;
            return 0;

        default:
            cout<<"Invalid!"<<endl;
        }

        cout<<"Do you want to continue?(y/n): ";
        cin>>cont;
    }while(cont=='y' || cont=='Y');

    return 0;
}

/*Output - 
1. Insert at start
2. Insert at end
3. Insert after phone
4. Display
5. Search any contact
6. Delete any contact
7. Reverse the list
8. Exit
Choice: 1
Enter name: Amruta
Enter the phone no(10 digits): 9028271927
Enter email(should contain '@'): amruta@gmail.com
Enter the company name: Mastercard
Enter DOB(DD/MM/YYYY): 12/02/2004
Do you want to continue?(y/n): y

1. Insert at start
2. Insert at end
3. Insert after phone
4. Display
5. Search any contact
6. Delete any contact
7. Reverse the list
8. Exit
Choice: 2
Enter name: Bhumika
Enter the phone no(10 digits): 8363437383
Enter email(should contain '@'): bhumika19@gmail.com
Enter the company name: Arista  
Enter DOB(DD/MM/YYYY): 19/06/2003
Do you want to continue?(y/n): y

1. Insert at start
2. Insert at end
3. Insert after phone
4. Display
5. Search any contact
6. Delete any contact
7. Reverse the list
8. Exit
Choice: 3
Enter phone after which to insert: 8363437383
Enter name: Mrudul
Enter the phone no(10 digits): 7463836393
Enter email(should contain '@'): mrudul@gmail.com
Enter the company name: ZS Technologies
Enter DOB(DD/MM/YYYY): 21/02/2004
Contact added!
Do you want to continue?(y/n): y

1. Insert at start
2. Insert at end
3. Insert after phone
4. Display
5. Search any contact
6. Delete any contact
7. Reverse the list
8. Exit
Choice: 4
Amruta | 9028271927 | amruta@gmail.com | Mastercard | 12/02/2004
Bhumika | 8363437383 | bhumika19@gmail.com | Arista  | 19/06/2003
Mrudul | 7463836393 | mrudul@gmail.com | ZS Technologies | 21/02/2004
NULL
Do you want to continue?(y/n): y

1. Insert at start
2. Insert at end
3. Insert after phone
4. Display
5. Search any contact
6. Delete any contact
7. Reverse the list
8. Exit
Choice: 5
Enter phone: 8363437383
Found: Bhumika | 8363437383 | bhumika19@gmail.com | Arista  | 19/06/2003
Do you want to continue?(y/n): y

1. Insert at start
2. Insert at end
3. Insert after phone
4. Display
5. Search any contact
6. Delete any contact
7. Reverse the list
8. Exit
Choice: 6
Enter phone: 8363437383
Deleted!
Do you want to continue?(y/n): y

1. Insert at start
2. Insert at end
3. Insert after phone
4. Display
5. Search any contact
6. Delete any contact
7. Reverse the list
8. Exit
Choice: 7
List reversed!
Mrudul | 7463836393 | mrudul@gmail.com | ZS Technologies | 21/02/2004
Amruta | 9028271927 | amruta@gmail.com | Mastercard | 12/02/2004
NULL
Do you want to continue?(y/n): y

1. Insert at start
2. Insert at end
3. Insert after phone
4. Display
5. Search any contact
6. Delete any contact
7. Reverse the list
8. Exit
Choice: 8
Exiting program!
*/