//Assignment No - 05
//Roll No - 23356
/*Problem Statement - 
Implementation of a Priority Queue
• Develop a priority queue where elements are dequeued based on priority rather than insertion order.
• Support operations such as insertion, deletion, and display.
Implementation of a Double-Ended Queue (Deque)
• Implement a double-ended queue where insertion and deletion can happen from both ends.
• Support operations such as enqueue front, enqueue rear, deque front, dequeue rear.
*/
#include<iostream>
using namespace std;

//Priority Queue Class
class PriorityQueue{
    int arr[50];
    int pr[50];
    int size;

public:
    PriorityQueue(){size=0;}

    void insert(int val,int p){
        arr[size]=val;
        pr[size]=p;
        size++;
        cout<<"Inserted "<<val<<" with priority "<<p<<endl;
    }

    void del(){
        if(size==0){
            cout<<"Queue is empty"<<endl;
            return;
        }
        int highestprio=0;
        for(int i = 1; i < size; i++) {
            if(pr[i]<pr[highestprio]){
                highestprio=i;
            }
        }

        cout<<"Deleted: "<<arr[highestprio]<<" with priority: "<<pr[highestprio]<<endl;

        for (int i = highestprio; i < size - 1; i++) {
            arr[i] = arr[i + 1];
            pr[i]=pr[i+1];
        }
        size--;
    }

    void display(){
        if(size==0){
            cout<<"Queue is empty"<<endl;
            return;
        }
        cout<<"Priority Queue elements:"<<endl;
        for(int i=0;i<size;i++){
            cout<<"Value: "<<arr[i]<<" Priority: "<<pr[i]<<endl;
        }
    }
};

//Deque Class
class Deque{
    int arr[50];
    int front,rear,size;

public:
    Deque(){front=-1;rear=-1;size=50;}

    void enqueueFront(int x){
        if((front==0 && rear==size-1)||(front==rear+1)){
            cout<<"Deque is full"<<endl;
            return;
        }
        if(front==-1){front=rear=0;}
        else if(front==0) front=size-1;
        else front--;
        arr[front]=x;
        cout<<"Inserted "<<x<<" at front"<<endl;
    }

    void enqueueRear(int x){
        if((front==0 && rear==size-1)||(front==rear+1)){
            cout<<"Deque is full"<<endl;
            return;
        }
        if(front==-1){front=rear=0;}
        else if(rear==size-1) rear=0;
        else rear++;
        arr[rear]=x;
        cout<<"Inserted "<<x<<" at rear"<<endl;
    }

    void dequeueFront(){
        if(front==-1){
            cout<<"Deque is empty"<<endl;
            return;
        }
        cout<<"Deleted "<<arr[front]<<" from front"<<endl;
        if(front==rear) front=rear=-1;
        else if(front==size-1) front=0;
        else front++;
    }

    void dequeueRear(){
        if(front==-1){
            cout<<"Deque is empty"<<endl;
            return;
        }
        cout<<"Deleted "<<arr[rear]<<" from rear"<<endl;
        if(front==rear) front=rear=-1;
        else if(rear==0) rear=size-1;
        else rear--;
    }

    void display(){
        if(front==-1){
            cout<<"Deque is empty"<<endl;
            return;
        }
        cout<<"Deque elements: ";
        int i=front;
        while(true){
            cout<<arr[i]<<" ";
            if(i==rear) break;
            i=(i+1)%size;
        }
        cout<<endl;
    }
};

int main(){
    PriorityQueue pq;
    Deque dq;
    int mainChoice,ch,v,p;
    char c;
    do{
        cout<<"Main Menu:"<<endl;
        cout<<"1.Priority Queue"<<endl;
        cout<<"2.Deque"<<endl;
        cout<<"Enter your choice: ";
        cin>>mainChoice;
        switch(mainChoice){
            case 1:
                do{
                    cout<<"Priority Queue Menu:"<<endl;
                    cout<<"1.Insert"<<endl;
                    cout<<"2.Delete"<<endl;
                    cout<<"3.Display"<<endl;
                    cout<<"Enter your choice: ";
                    cin>>ch;
                    switch(ch){
                        case 1:
                            cout<<"Enter value and priority: ";
                            cin>>v>>p;
                            pq.insert(v,p);
                            break;

                        case 2:
                            pq.del();
                            break;

                        case 3:
                            pq.display();
                            break;

                        default:
                            cout<<"Wrong choice"<<endl;
                    }
                    cout<<"Continue with Priority Queue(y/n)? ";
                    cin>>c;
                    cout<<endl;
                }while(c=='y'||c=='Y');
                break;

            case 2:
                do{
                    cout<<"Deque Menu:"<<endl;
                    cout<<"1.Enqueue Front"<<endl;
                    cout<<"2.Enqueue Rear"<<endl;
                    cout<<"3.Dequeue Front"<<endl;
                    cout<<"4.Dequeue Rear"<<endl;
                    cout<<"5.Display"<<endl;
                    cout<<"Enter your choice: ";
                    cin>>ch;
                    switch(ch){
                        case 1:
                            cout<<"Enter value: ";
                            cin>>v;
                            dq.enqueueFront(v);
                            break;

                        case 2:
                            cout<<"Enter value: ";
                            cin>>v;
                            dq.enqueueRear(v);
                            break;

                        case 3:
                            dq.dequeueFront();
                            break;

                        case 4:
                            dq.dequeueRear();
                            break;

                        case 5:
                            dq.display();
                            break;

                        default:
                            cout<<"Wrong choice"<<endl;
                    }
                    cout<<"Continue with Deque(y/n)? ";
                    cin>>c;
                    cout<<endl;
                }while(c=='y'||c=='Y');
                break;
            default:
                cout<<"Wrong choice"<<endl;
        }
        cout<<"Do you want to go back to Main Menu(y/n)? ";
        cin>>c;
        cout<<endl;
    }while(c=='y'||c=='Y');
    cout<<"Program ended"<<endl;
    return 0;
}

/*Output - 
Main Menu:
1.Priority Queue
2.Deque
Enter your choice: 1
Priority Queue Menu:
1.Insert
2.Delete
3.Display
Enter your choice: 1
Enter value and priority: 1 1
Inserted 1 with priority 1
Continue with Priority Queue(y/n)? y
Priority Queue Menu:
1.Insert
2.Delete
3.Display
Enter your choice: 1
Enter value and priority: 2 2
Inserted 2 with priority 2
Continue with Priority Queue(y/n)? y
Priority Queue Menu:
1.Insert
2.Delete
3.Display
Enter your choice: 3
Priority Queue elements:
Value: 1 Priority: 1
Value: 2 Priority: 2
Continue with Priority Queue(y/n)? y
Priority Queue Menu:
1.Insert
2.Delete
3.Display
Enter your choice: 2
Deleted 1 with priority 1
Continue with Priority Queue(y/n)? y
Priority Queue Menu:
1.Insert
2.Delete
3.Display
Enter your choice: 3
Priority Queue elements:
Value: 2 Priority: 2
Continue with Priority Queue(y/n)? n
Do you want to go back to Main Menu(y/n)? y
Main Menu:
1.Priority Queue
2.Deque
Enter your choice: 2
Deque Menu:
1.Enqueue Front
2.Enqueue Rear
3.Dequeue Front
4.Dequeue Rear
5.Display
Enter your choice: 1
Enter value: 1
Inserted 1 at front
Continue with Deque(y/n)? y
Deque Menu:
1.Enqueue Front
2.Enqueue Rear
3.Dequeue Front
4.Dequeue Rear
5.Display
Enter your choice: 2
Enter value: 2
Inserted 2 at rear
Continue with Deque(y/n)? y
Deque Menu:
1.Enqueue Front
2.Enqueue Rear
3.Dequeue Front
4.Dequeue Rear
5.Display
Enter your choice: 5
Deque elements: 1 2 
Continue with Deque(y/n)? y
Deque Menu:
1.Enqueue Front
2.Enqueue Rear
3.Dequeue Front
4.Dequeue Rear
5.Display
Enter your choice: 3
Deleted 1 from front
Continue with Deque(y/n)? y
Deque Menu:
1.Enqueue Front
2.Enqueue Rear
3.Dequeue Front
4.Dequeue Rear
5.Display
Enter your choice: 5
Enter your choice: 5
Deque elements: 2
Continue with Deque(y/n)? y
Deque elements: 2
Continue with Deque(y/n)? y
Deque Menu:
1.Enqueue Front
Continue with Deque(y/n)? y
Deque Menu:
1.Enqueue Front
2.Enqueue Rear
3.Dequeue Front
Deque Menu:
1.Enqueue Front
2.Enqueue Rear
3.Dequeue Front
4.Dequeue Rear
5.Display
4.Dequeue Rear
5.Display
Enter your choice: 4
5.Display
Enter your choice: 4
Deleted 2 from rear
Enter your choice: 4
Deleted 2 from rear
Continue with Deque(y/n)? y
Deleted 2 from rear
Continue with Deque(y/n)? y
Deque Menu:
Continue with Deque(y/n)? y
Deque Menu:
1.Enqueue Front
Deque Menu:
1.Enqueue Front
2.Enqueue Rear
3.Dequeue Front
4.Dequeue Rear
5.Display
Enter your choice: 5
Deque is empty
Continue with Deque(y/n)? n
Do you want to go back to Main Menu(y/n)? n
Program
*/