//Assignment No - 02
//Roll No - 23356
/*Problem Statement - Task Scheduling System (Queue): Managing tasks in a first-in, first-out (FIFO) order, such
as print job scheduling or process management in an operating system.*/

#include<iostream>
using namespace std;

//Class to define node
class node{
public:
    node* next;
    string st;
    
    node(node* n,string st1){
        next=n;
        st=st1;
    }
    
    node(string st1){
        st=st1;
        next=nullptr;
    }
};

//Class to define a queue
class myQueue{
public:
    node* front;
    node* rear;
    myQueue(){front=nullptr , rear=nullptr;}
    
    //Function to enqueue elements
    void enqueue(string v){
        node* newNode=new node(v);
        if(rear==NULL){
            cout<<"Entering the task to execute "<<v<<endl;
            front=rear=newNode;
            return;
        }
        cout<<"Entering the task to execute "<<v<<endl;
        rear->next=newNode;
        rear=newNode;
    }

    //Function to dequeue elements
    void dequeue(){
        if(front==NULL){
            cout<<"No task to execute"<<endl;
            return;
        }
        node* temp=front;
        front=front->next;
        delete temp;
    }

    //Function to display all the elements
    void display(){
        node* temp=front;
        int cnt=0;
        if(temp==NULL){
            cout<<"No task to execute"<<endl;
            return;
        }
        cout<<"The tasks to be executed are: "<<endl;
        while(temp!=NULL){
            cout<<"Task: "<<temp->st<<endl;
            temp=temp->next;
            cnt++;
        }
        cout<<"There are "<<cnt<<" tasks to be executed"<<endl;
    }

    //Function to peep the top element
    void peep(){
        node* temp=front;
        if(temp==NULL){
            cout<<"No task to execute"<<endl;
            return;
        }
        cout<<"The current task is: "<<temp->st<<endl;
    }
};

int main(){
    string s;
    int n;
    myQueue q;
    char c;
    do{
        cout<<"Menu: "<<endl;
        cout<<"1.To enter a new task(Enter)"<<endl;
        cout<<"2.To execute given task(Execute)"<<endl;
        cout<<"3.To skip the current task(Skip)"<<endl;
        cout<<"4.To show the current status(Show)"<<endl;
        cout<<"5.To display all the tasks to be executed(Display)"<<endl;
        cout<<"Enter yout task: ";
        cin>>s;

        if(s=="Enter"||s=="enter") {n=1;}
        else if(s=="Execute"||s=="execute"){n=2;}
        else if(s=="Skip"||s=="skip") {n=3;}
        else if(s=="Show"||s=="show") {n=4;}
        else if(s=="Display"||s=="display") {n=5;}
        else{cout<<"Wrong choice"<<endl;}
    
        switch(n){
            case  1:{
                string a;
                cout<<"Enter the task to execute: ";
                cin.ignore();
                getline(cin,a);
                q.enqueue(a);
                break;
            }

            case 2:{
                if(q.front==NULL){
                    cout<<"No task to execute"<<endl;
                }else{
                    cout<<"Executing the task: "<<q.front->st<<endl;
                    q.dequeue();
                }
                break;
            }

            case 3:{
                if(q.front==NULL){
                    cout<<"No task to skip"<<endl;
                }else{
                    cout<<"Skipping the task "<<q.front->st<<endl;
                    q.dequeue();
                }
                break;
            }

            case 4:
                q.peep();
                break;

            case 5:
                q.display();
                break;
        }
        cout<<"Do you want to continue(y/n)?";
        cin>>c;
    }while(c=='y'||c=='Y');

    return 0;
/*Output -

Menu:
1.To enter a new task(Enter)
2.To execute given task(Execute)
3.To skip the current task(Skip)
4.To show the current status(Show)
5.To display all the tasks to be executed(Display)
Enter your task: Enter
Enter the task to execute: Clean Desk
Entering the task to execute Clean Desk
Do you want to continue(y/n)?y

Menu:
1.To enter a new task(Enter)
2.To execute given task(Execute)
3.To skip the current task(Skip)
4.To show the current status(Show)
5.To display all the tasks to be executed(Display)
Enter your task: Enter
Enter the task to execute: Update Software
Entering the task to execute Update Software
Do you want to continue(y/n)?y

Menu:
1.To enter a new task(Enter)
2.To execute given task(Execute)
3.To skip the current task(Skip)
4.To show the current status(Show)
5.To display all the tasks to be executed(Display)
Enter your task: Enter
Enter the task to execute: Backup Files
Entering the task to execute Backup Files
Do you want to continue(y/n)?y

Menu:
...
Enter your task: Display
The tasks to be executed are:
Task: Clean Desk
Task: Update Software
Task: Backup Files
There are 3 tasks to be executed
Do you want to continue(y/n)?y

Menu:
...
Enter your task: Execute
Executing the task: Clean Desk
Do you want to continue(y/n)?y

Menu:
...
Enter your task: Show
The current task is: Update Software
Do you want to continue(y/n)?y

Menu:
...
Enter your task: Skip
Skipping the task Update Software
Do you want to continue(y/n)?y

Menu:
...
Enter your task: Display
The tasks to be executed are:
Task: Backup Files
There are 1 tasks to be executed
Do you want to continue(y/n)?n

-----------------------------------------------
*/

