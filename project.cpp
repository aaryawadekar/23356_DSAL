//DSA Mini Project - SplitSmart+
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

struct Friend {
    string name;
    double balance = 0.0;
};

struct Expense {
    string desc;
    double amount;
    int paidBy;
    vector<pair<int,double>> shares; // (friendIndex, shareAmount)
};

vector<Friend> friendsList;
vector<Expense> expenses;

void saveData();
void loadData();

//Function to add friends
void addFriend() {
    cout << "Enter friend name: ";
    cin.ignore();
    string name;
    getline(cin, name);

    for (auto &f : friendsList)
        if (f.name == name) { cout << "Friend already exists!\n"; return; }

    friendsList.push_back({name, 0});
    saveData();
    cout << "Friend added!\n";
}

//Function to list friends
void listFriends() {
    cout << "\n--- Friends ---\n";
    if (friendsList.empty()) { cout << "No friends added yet.\n"; return; }
    for (int i = 0; i < friendsList.size(); i++)
        cout << i+1 << ") " << friendsList[i].name << endl;
}

//Function to serach for friends
void searchFriend() {
    cout << "Enter friend name: ";
    cin.ignore();
    string name;
    getline(cin, name);

    for (auto &f : friendsList)
        if (f.name == name) { cout << name << " exists!\n"; return; }

    cout << "Friend not found.\n";
}

//Function to add expenses
void addExpense() {
    if (friendsList.empty()) { cout << "Add friends first!\n"; return; }

    Expense e;
    cout << "Enter description: ";
    cin.ignore();
    getline(cin, e.desc);

    cout << "Enter total amount: ";
    cin >> e.amount;

    listFriends();
    cout << "Who paid? (enter number): ";
    cin >> e.paidBy;
    e.paidBy--;

    cout << "\nSelect Split Method:\n";
    cout << "1) Equal Split\n2) Unequal Split\nChoice: ";
    int type; cin >> type;

    cout << "How many people shared? ";
    int n; cin >> n;

    double sumShares = 0;

    if (type == 1) {
        double share = e.amount / n;
        cout << "Enter their numbers: ";
        for (int i = 0; i < n; i++) {
            int x; cin >> x;
            e.shares.push_back({x-1, share});
        }
    } 
    else {
        cout << "Enter friend number & share amount:\n";
        for (int i = 0; i < n; i++) {
            int x; double sh;
            cin >> x >> sh;
            e.shares.push_back({x-1, sh});
            sumShares += sh;
        }
        if (sumShares != e.amount) {
            cout << "Error! Total shares != bill amount\n";
            return;
        }
    }

    expenses.push_back(e);

    // Balance updates
    for (auto &p : e.shares)
        friendsList[p.first].balance -= p.second;
    friendsList[e.paidBy].balance += e.amount;

    saveData();
    cout << "Expense added!\n";
}

//Function for manual payment
void manualPayment() {
    listFriends();
    cout << "Enter payer friend number: ";
    int payer, receiver;
    cin >> payer;
    payer--;

    cout << "Enter receiver friend number: ";
    cin >> receiver;
    receiver--;

    cout << "Enter amount paid: ";
    double amt; cin >> amt;

    friendsList[payer].balance -= amt;
    friendsList[receiver].balance += amt;

    cout << friendsList[payer].name << " paid " << friendsList[receiver].name 
         << " Rs " << fixed << setprecision(2) << amt << endl;

    saveData();
}

//Function to show balances
void showBalances() {
    cout << "\n--- Balances ---\n";
    for (auto &f : friendsList)
        cout << setw(12) << left << f.name << " : " 
             << fixed << setprecision(2) << f.balance << endl;
}

//Function to show history
void showHistory() {
    if (expenses.empty()) { cout << "No history.\n"; return; }

    cout << "\n--- Expense History ---\n";
    for (auto &e : expenses) {
        cout << e.desc << " | Amount: " << e.amount 
             << " | Paid by: " << friendsList[e.paidBy].name
             << " | Split:\n";
        for (auto &p : e.shares)
            cout << "   " << friendsList[p.first].name << " -> " << p.second << endl;
        cout << endl;
    }
}

//Function to settle up all expenses
void settleUp() {
    cout << "\n--- Settlements ---\n";
    int n = friendsList.size();

    while (true) {
        int maxCred=-1, maxDebt=-1;
        double mxC=0, mxD=0;

        for (int i=0;i<n;i++) {
            if (friendsList[i].balance > mxC) { mxC = friendsList[i].balance; maxCred = i; }
            if (friendsList[i].balance < mxD) { mxD = friendsList[i].balance; maxDebt = i; }
        }

        if (maxCred == -1 || maxDebt == -1) break;

        double settled = min(mxC, -mxD);
        friendsList[maxCred].balance -= settled;
        friendsList[maxDebt].balance += settled;

        cout << friendsList[maxDebt].name << " pays "
             << friendsList[maxCred].name << " "
             << fixed << setprecision(2) << settled << endl;
    }
    saveData();
}

//Function to save the data
void saveData() {
    ofstream f("friends.txt");
    for (auto &fr : friendsList)
        f << fr.name << "\n" << fr.balance << "\n";
    f.close();

    ofstream e("expenses.txt");
    for (auto &ex : expenses) {
        e << ex.desc << "\n" << ex.amount << " " << ex.paidBy << " " << ex.shares.size();
        for (auto &pr : ex.shares) e << " " << pr.first << " " << pr.second;
        e << "\n";
    }
    e.close();
}

void loadData() {
    ifstream f("friends.txt");
    string name; double balance;
    while (getline(f, name)) {
        f >> balance; f.ignore();
        friendsList.push_back({name, balance});
    }
    f.close();

    ifstream e("expenses.txt");
    while (true) {
        Expense ex; int count;
        if (!getline(e, ex.desc)) break;
        e >> ex.amount >> ex.paidBy >> count;
        for (int i=0;i<count;i++) {
            int id; double sh;
            e >> id >> sh;
            ex.shares.push_back({id, sh});
        }
        e.ignore();
        expenses.push_back(ex);
    }
    e.close();
}

//Main file
int main() {
    loadData();
    int choice;

    while (true) {
        cout << "\n====== SplitSmart+ ======\n";
        cout << "1. Add Friend\n2. List Friends\n3. Add Expense\n4. Show Balances\n5. Show History\n6. Search Friend\n7. Settle Up\n8. Manual Payment\n0. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1: addFriend(); break;
            case 2: listFriends(); break;
            case 3: addExpense(); break;
            case 4: showBalances(); break;
            case 5: showHistory(); break;
            case 6: searchFriend(); break;
            case 7: settleUp(); break;
            case 8: manualPayment(); break;
            case 0: saveData(); return 0;
            default: cout << "Invalid choice!\n";
        }
    }
}

/*Output - 
====== SplitSmart+ ======
1. Add Friend
2. List Friends
3. Add Expense
4. Show Balances
5. Show History
6. Search Friend
7. Settle Up
8. Manual Payment
0. Exit
Choice: 1
Enter friend name: Aarya 
Friend added!

====== SplitSmart+ ======
1. Add Friend
2. List Friends
3. Add Expense
4. Show Balances
5. Show History
6. Search Friend
7. Settle Up
8. Manual Payment
0. Exit
Choice: 1
Enter friend name: Arpita
Friend added!

====== SplitSmart+ ======
1. Add Friend
2. List Friends
3. Add Expense
4. Show Balances
5. Show History
6. Search Friend
7. Settle Up
8. Manual Payment
0. Exit
Choice: 1
Enter friend name: Ojasvi
Friend added!

====== SplitSmart+ ======
1. Add Friend
2. List Friends
3. Add Expense
4. Show Balances
5. Show History
6. Search Friend
7. Settle Up
8. Manual Payment
0. Exit
Choice: 2

--- Friends ---
1) Aarya
2) Arpita
3) Ojasvi

====== SplitSmart+ ======
1. Add Friend
2. List Friends
3. Add Expense
4. Show Balances
5. Show History
6. Search Friend
7. Settle Up
8. Manual Payment
0. Exit
Choice: 3
Enter description: Lunch
Enter total amount: 2000

--- Friends ---
1) Aarya
2) Arpita
3) Ojasvi
Who paid? (enter number): 1

Select Split Method:
1) Equal Split
2) Unequal Split
Choice: 1
How many people shared? 3
Enter their numbers: 1 2 3
Expense added!

====== SplitSmart+ ======
1. Add Friend
2. List Friends
3. Add Expense
4. Show Balances
5. Show History
6. Search Friend
7. Settle Up
8. Manual Payment
0. Exit
Choice: 3
Enter description: Coffee
Enter total amount: 300

--- Friends ---
1) Aarya
2) Arpita
3) Ojasvi
Who paid? (enter number): 2

Select Split Method:
1) Equal Split
2) Unequal Split
Choice: 2
How many people shared? 2
Enter friend number & share amount:
1 200
2 100
Expense added!

====== SplitSmart+ ======
1. Add Friend
2. List Friends
3. Add Expense
4. Show Balances
5. Show History
6. Search Friend
7. Settle Up
8. Manual Payment
0. Exit
Choice: 4

--- Balances ---
Aarya        : 1133.33
Arpita       : -466.67
Ojasvi       : -666.67

====== SplitSmart+ ======
1. Add Friend
2. List Friends
3. Add Expense
4. Show Balances
5. Show History
6. Search Friend
7. Settle Up
8. Manual Payment
0. Exit
Choice: 5

--- Expense History ---
Lunch | Amount: 2000.00 | Paid by: Aarya | Split:
   Aarya -> 666.67
   Arpita -> 666.67
   Ojasvi -> 666.67

Coffee | Amount: 300.00 | Paid by: Arpita | Split:
   Aarya -> 200.00
   Arpita -> 100.00


====== SplitSmart+ ======
1. Add Friend
2. List Friends
3. Add Expense
4. Show Balances
5. Show History
6. Search Friend
7. Settle Up
8. Manual Payment
0. Exit
Choice: 6
Enter friend name: Aarya
Aarya exists!

====== SplitSmart+ ======
1. Add Friend
2. List Friends
3. Add Expense
4. Show Balances
5. Show History
6. Search Friend
7. Settle Up
8. Manual Payment
0. Exit
Choice: 6
Enter friend name: Ria
Friend not found.

====== SplitSmart+ ======
1. Add Friend
2. List Friends
3. Add Expense
4. Show Balances
5. Show History
6. Search Friend
7. Settle Up
8. Manual Payment
0. Exit
Choice: 7

--- Settlements ---
Ojasvi pays Aarya 666.67
Arpita pays Aarya 466.67

====== SplitSmart+ ======
1. Add Friend
2. List Friends
3. Add Expense
4. Show Balances
5. Show History
6. Search Friend
7. Settle Up
8. Manual Payment
0. Exit
Choice: 3
Enter description: Dinner
Enter total amount: 3000

--- Friends ---
1) Aarya
2) Arpita
3) Ojasvi
Who paid? (enter number): 3

Select Split Method:
1) Equal Split
2) Unequal Split
Choice: 1
How many people shared? 3
Enter their numbers: 1 2 3
Expense added!

====== SplitSmart+ ======
1. Add Friend
2. List Friends
3. Add Expense
4. Show Balances
5. Show History
6. Search Friend
7. Settle Up
8. Manual Payment
0. Exit
Choice: 8

--- Friends ---
1) Aarya
2) Arpita
3) Ojasvi
Enter payer friend number: 3
Enter receiver friend number: 2
Enter amount paid: 1000
Ojasvi paid Arpita Rs 1000.00

====== SplitSmart+ ======
1. Add Friend
2. List Friends
3. Add Expense
4. Show Balances
5. Show History
6. Search Friend
7. Settle Up
8. Manual Payment
0. Exit
Choice: 4

--- Balances ---
Aarya        : -1000.00
Arpita       : 0.00
Ojasvi       : 1000.00

====== SplitSmart+ ======
1. Add Friend
2. List Friends
3. Add Expense
4. Show Balances
5. Show History
6. Search Friend
7. Settle Up
8. Manual Payment
0. Exit
Choice: 8

--- Friends ---
1) Aarya
2) Arpita
3) Ojasvi
Enter payer friend number: 1
Enter receiver friend number: 3
Enter amount paid: 1000
Aarya paid Ojasvi Rs 1000.00

====== SplitSmart+ ======
1. Add Friend
2. List Friends
3. Add Expense
4. Show Balances
5. Show History
6. Search Friend
7. Settle Up
8. Manual Payment
0. Exit
Choice: 4

--- Balances ---
Aarya        : -2000.00
Arpita       : 0.00
Ojasvi       : 2000.00

====== SplitSmart+ ======
1. Add Friend
2. List Friends
3. Add Expense
4. Show Balances
5. Show History
6. Search Friend
7. Settle Up
8. Manual Payment
0. Exit
Choice: 7

--- Settlements ---
Aarya pays Ojasvi 2000.00

====== SplitSmart+ ======
1. Add Friend
2. List Friends
3. Add Expense
4. Show Balances
5. Show History
6. Search Friend
7. Settle Up
8. Manual Payment
0. Exit
Choice: 0
*/
