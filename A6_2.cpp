//Assignment No - 06
//Roll No - 23356
/*Pronblem Statement - 
Develop a hashing-based system for securely storing user credentials, where usernames act as keys
and hashed passwords as values. Implement and demonstrate collision handling using:
• Open Addressing (Linear or Quadratic Probing without chaining)
*/

#include<iostream>
#include<string>
#include<functional>
using namespace std;

struct node{
    string name,pass;
    bool isOccupied;

    node(){
        name="";
        pass="";
        isOccupied=false;
    }
};

class hashTable{
    int SIZE;
    node table[100];

public:
    //Constructor
    hashTable(int size){
        SIZE=size;
        for(int i=0;i<SIZE;i++){
            table[i].isOccupied=false;
        }
    }

    int hashFunc(string key){
        hash<string> str_hash;
        return str_hash(key) % SIZE;
    }

    void insert(string username, string password) {
        int index = hashFunc(username);
        string hashedPass = to_string(hash<string>{}(password)); // hash the password

        int startIndex = index; // to detect full table

        while (table[index].isOccupied) {
            index = (index + 1) % SIZE; // linear probing
            if (index == startIndex) {
                cout << "Hash table is full! Cannot insert.\n";
                return;
            }
        }

        table[index].name = username;
        table[index].pass = hashedPass;
        table[index].isOccupied = true;

        cout << "Inserted: " << username << endl;
    }

    void search(string username) {
        int index = hashFunc(username);
        int startIndex = index;

        while (table[index].isOccupied) {
            if (table[index].name == username) {
                cout << "User found! Hashed password: " << table[index].pass.substr(0, 8) << "...\n";
                return;
            }
            index = (index + 1) % SIZE;
            if (index == startIndex)
                break;
        }
        cout << "User not found.\n";
    }

    void display() {
        cout << "\n--- Hash Table ---\n";
        for (int i = 0; i < SIZE; i++) {
            cout << i << ": ";
            if (table[i].isOccupied)
                cout << "[" << table[i].name << "]\n";
            else
                cout << "EMPTY\n";
        }
    }
};

int main(){
    int size;
    cout<<"Enter the size of the hashtable: ";
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
                string name,password;
                cout<<"Enter the name of the user: ";
                cin>>name;
                cout<<"Enter the password: ";
                cin>>password;
                h.insert(name,password);
                break;
            }

            case 2:{
                h.display();
                break;
            }

            case 3:{
                string nameToSearch;
                cout<<"Enter the name of user to search: ";
                cin>>nameToSearch;
                h.search(nameToSearch);
                break;
            }

            case 0:{
                cout<<"Exiting Program"<<endl;
                break;
            }

            default:{
                cout<<"Invalid Choice"<<endl;
                break;
            }
        }

    }while(choice!=0);
    return 0;
}

/*Output - 
Enter the size of the hashtable: 4

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
Enter the name of the user: 
Arpita
Enter the password: 456
Inserted: Arpita

MENU:
1.To enter new user
2.To display information of all users
3.To search for a user
0.To exit from the program
Enter your choice: 1
Enter the name of the user: Tanvi
Enter the password: 891
Inserted: Tanvi

MENU:
1.To enter new user
2.To display information of all users
3.To search for a user
0.To exit from the program
Enter your choice: 1
Enter the name of the user: Diya
Enter the password: 345
Inserted: Diya

MENU:
1.To enter new user
2.To display information of all users
3.To search for a user
0.To exit from the program
Enter your choice: 2

--- Hash Table ---
0: [Arpita]
1: [Diya]
2: [Tanvi]
3: [Aarya]

MENU:
1.To enter new user
2.To display information of all users
3.To search for a user
0.To exit from the program
Enter your choice: 1
Enter the name of the user: Ojaswi
Enter the password: 567
Hash table is full! Cannot insert.

MENU:
1.To enter new user
2.To display information of all users
3.To search for a user
0.To exit from the program
Enter your choice: 3
Enter the name of user to search: Arpita
User found! Hashed password: 11313523...

MENU:
1.To enter new user
2.To display information of all users
3.To search for a user
0.To exit from the program
Enter your choice: 0
Exiting Program
*/
