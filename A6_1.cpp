//Assignment No - 06
//Roll No - 23356
/*Pronblem Statement - 
Develop a hashing-based system for securely storing user credentials, where usernames act as keys
and hashed passwords as values. Implement and demonstrate collision handling using:
• Chaining (Array-based collision resolution)
*/

#include<iostream>
#include<string>
#include<functional>
using namespace std;

struct node{
    string name;
    string pass;
    node* next;

    node(string n,string p){
        name=n;
        pass=p;
        next=NULL;
    }
};

class hashTable{
    int SIZE;
    node* table[100];

public:
    //Constructor
    hashTable(int size){
        SIZE=size;
        for(int i=0;i<SIZE;i++){
            table[i]=NULL;
        }
    }

    int hashFunc(string key){
        hash<string> str_hash;
        return str_hash(key) % SIZE;
    }

    void insert(string username,string password){
        int index = hashFunc(username);
        string hashedPass = to_string(hash<string>{}(password)); 

        node* newNode = new node(username, hashedPass);

        if (table[index] == NULL) {
            table[index] = newNode;
        } else {
            node* temp = table[index];
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = newNode;
        }

        cout << "Inserted: " << username << endl;
    }

    void search(string username) {
        int index = hashFunc(username);
        node* temp = table[index];
        while (temp != NULL) {
            if (temp->name == username) {
                cout << "User found! Hashed password: " << temp->pass.substr(0, 8) << "...\n";
                return;
            }
            temp = temp->next;
        }
        cout << "User not found.\n";
    }

    void display() {
        cout << "\n--- Hash Table ---\n";
        for (int i = 0; i < SIZE; i++) {
            cout << i << ": ";
            node* temp = table[i];
            while (temp != NULL) {
                cout << "[" << temp->name << "] -> ";
                temp = temp->next;
            }
            cout << "NULL\n";
        }
    }
};

int main(){
    int size;
    cout<<"Enter the size of the hashtable:";
    cin>>size;
    hashTable h(size);

    int choice;

    do{
        cout<<endl;
        cout<<"MENU:"<<endl;
        cout<<"1.To enter new user"<<endl;
        cout<<"2.To display information of all users"<<endl;
        cout<<"3.To search for a user"<<endl;
        cout<<"0.To exit from the program"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice){
            case 1:{
                string name;
                string pass;
                cout<<"Enter the name of the user: ";
                cin>>name;
                cout<<"Enter the password: ";
                cin>>pass;
                h.insert(name,pass);
                break;
            }

            case 2:{
                h.display();
                break;
            }

            case 3:{
                string nameToSearch;
                cout<<"Enter the name of the user: ";
                cin>>nameToSearch;
                h.search(nameToSearch);
                break;
            }

            case 0:{
                cout<<"Program Terminated!"<<endl;
                break;
            }

            default:{
                cout<<"Invalid choice"<<endl;
                break;
            }
        }
    }while(choice!=0);

    return 0;
}

/*OUTPUT -
Enter the size of the hashtable:4

MENU:
1.To enter new user
2.To display information of all users
3.To search for a user
0.To exit from the program
Enter your choice: 1
Enter the name of the user: Aarya
Enter the password: 123
Inserted: Aarya

MENU:
1.To enter new user
2.To display information of all users
3.To search for a user
0.To exit from the program
Enter your choice: 1
Enter the name of the user: Arpita
Enter the password: 456
Inserted: Arpita

MENU:
1.To enter new user
2.To display information of all users
3.To search for a user
0.To exit from the program
Enter your choice: 1
Enter the name of the user: Tanvi
Enter the password: 678
Inserted: Tanvi

MENU:
1.To enter new user
2.To display information of all users
3.To search for a user
0.To exit from the program
Enter your choice: 1
Enter the name of the user: Srushti
Enter the password: 891
Inserted: Srushti

MENU:
1.To enter new user
2.To display information of all users
3.To search for a user
0.To exit from the program
Enter your choice: 2

--- Hash Table ---
0: NULL
1: NULL
2: [Tanvi] -> NULL
3: [Aarya] -> [Arpita] -> [Srushti] -> NULL

MENU:
1.To enter new user
2.To display information of all users
3.To search for a user
0.To exit from the program
Enter your choice: 1
Enter the name of the user: Diya
Enter the password: 456
Inserted: Diya

MENU:
1.To enter new user
2.To display information of all users
3.To search for a user
0.To exit from the program
Enter your choice: 2

--- Hash Table ---
0: [Diya] -> NULL
1: NULL
2: [Tanvi] -> NULL
3: [Aarya] -> [Arpita] -> [Srushti] -> NULL

MENU:
1.To enter new user
2.To display information of all users
3.To search for a user
0.To exit from the program
Enter your choice: 3
Enter the name of the user: Arpita
User found! Hashed password: 11313523...

MENU:
1.To enter new user
2.To display information of all users
3.To search for a user
0.To exit from the program
Enter your choice: 0
Program Terminated!
*/