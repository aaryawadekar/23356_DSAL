//Assignment No - 02
//Roll No - 23356
/*Problem Statement - Undo/Redo Functionality (Stack): Implementing an undo/redo feature in text editors or
design software using a last-in, first-out (LIFO) approach.*/

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

//Class to define stack
class myStack{
public:
    node* top;
    myStack(){top=nullptr;}
    void push(string l);
    void pop();
    void peep();
    bool isEmpty();
};

//Function to push an element in the stack
void myStack::push(string k){
    node* newNode=new node(k);
    newNode->next=top;
    top=newNode;
}

//Function to pop the top element
void myStack::pop(){
    if(isEmpty()){
        cout<<"Empty stack!"<<endl;
        return;
    }
    node* temp=top;
    top=top->next;
    delete temp;
}

//Function to peep(display) the top element
void myStack::peep(){
    if(isEmpty()){
        cout<<"Empty stack!"<<endl;
        return;
    }
    cout<<"The top element is: "<<top->st<<endl;
}

//Function to check if the stack is empty
bool myStack::isEmpty(){
    if(top==NULL){
        return true;
    }else{
        return false;
    }
}

int main(){
    myStack undoStack,redoStack;
    
    char c;
    do{
        int choice;
        cout<<"Menu:"<<endl;
        cout<<"1.To enter a string"<<endl;
        cout<<"2.To undo"<<endl;
        cout<<"3.To redo"<<endl;
        cout<<"4.To peep the top element"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice){
            case 1:{
                string k;
                cout<<"Enter the string to be pushed: ";
                cin.ignore();
                getline(cin,k);
                undoStack.push(k);
                break;
            }

            //To undo a task
            case 2:{
                if(undoStack.isEmpty()){
                    cout<<"No function to undo"<<endl;
                }else{
                    string s=undoStack.top->st;
                    redoStack.push(s);
                    undoStack.pop();
                }
                break;
            }

            //To redo a task
            case 3:{
                if(redoStack.isEmpty()){
                    cout<<"No function to redo"<<endl;
                }else{
                    string n=redoStack.top->st;
                    undoStack.push(n);
                    redoStack.pop();
                }
                break;
            }

            //To display the top element
            case 4:
                undoStack.peep();
                break;

            default:
                cout<<"Wrong input!"<<endl;
        }
        cout<<"Do you want to continue(y/n)?"<<endl;
        cin>>c;
    }while(c=='y' || c=='Y');

    return 0;
}

/*Output - 
Menu:
1.To enter a string
2.To undo
3.To redo
4.To peep the top element
Enter your choice: 1
Enter the string to be pushed: Hello
Do you want to continue(y/n)?
y
Menu:
1.To enter a string
2.To undo
3.To redo
4.To peep the top element
Enter your choice: 4
The top element is: Hello
Do you want to continue(y/n)?
y
Menu:
1.To enter a string
2.To undo
3.To redo
4.To peep the top element
Enter your choice: 1
Enter the string to be pushed: l1
Do you want to continue(y/n)?
y
Menu:
1.To enter a string
2.To undo
3.To redo
4.To peep the top element
Enter your choice: 1
Enter the string to be pushed: l2
Do you want to continue(y/n)?
y
Menu:
1.To enter a string
2.To undo
3.To redo
4.To peep the top element
Enter your choice: 1
Enter the string to be pushed: l3
Do you want to continue(y/n)?
y
Menu:
1.To enter a string
2.To undo
3.To redo
4.To peep the top element
Enter your choice: 4
The top element is: l3
Do you want to continue(y/n)?
y
Menu:
1.To enter a string
2.To undo
3.To redo
4.To peep the top element
Enter your choice: 2
Do you want to continue(y/n)?
y
Menu:
1.To enter a string
2.To undo
3.To redo
4.To peep the top element
Enter your choice: 4
The top element is: l2
Do you want to continue(y/n)?
y
Menu:
1.To enter a string
2.To undo
3.To redo
4.To peep the top element
Enter your choice: 3
Do you want to continue(y/n)?
n
*/