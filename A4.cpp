//Assignment No - 04
//Roll No - 23356
/*Problem Statement - Implement a program to convert an infix expression to prefix and postfix notation.
• Evaluate both prefix and postfix expressions. Use STL for implementation.*/

#include<iostream>
#include<stack>
#include<string>
#include<cmath>
using namespace std;

//Function to check the precedence
int prec(char c){
    if(c=='^'||c=='$') return 3;
    if(c=='*'||c=='/') return 2;
    if(c=='+'||c=='-') return 1;
    return -1;
}

//Function to check if the character in the string is operand
bool isOperand(char c) {
    if((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
        return true;
    }    
    return false;
}

//Function to check if the character in the string is paranthesis
bool isParanthesis(char c){
    if(c=='('||c==')'||c=='{'||c=='}'){
        return true;
    }else{
        return false;
    }
}

//Function to check whether the given expression has proper paranthesis or not
bool checkParanthesis(string s){
    int cnt=0;
    for(int i=0;i<s.length();i++){
        char c=s[i];

        if(c=='(') cnt++;
        else if(c==')') cnt--;

        if(cnt<0){
            cout<<"Opening parathesis is missing"<<endl;
            return false;
        }
    }
    if(cnt>0){
        cout<<"Closing paranthesis is missing"<<endl;
        return false;
    }
    return true;
}

//Function to convert infix string to postfix
string infixToPostfix(string s){
    stack<char>st;
    string res="";

    for(int i=0;i<s.length();i++){
        char c=s[i];

        if(isOperand(c)){
            res+=c;
        }else if(c=='('){
            st.push(c);
        }else if(c==')'){
            while(!st.empty() && st.top()!='('){
                res+=st.top();
                st.pop();
            }
            if(!st.empty()) st.pop();
        }else{
            while(!st.empty() && prec(s[i])<=prec(st.top())){
                res+=st.top();
                st.pop();
            }
            st.push(c);
        }
    }

    while(!st.empty()){
        res+=st.top();
        st.pop();
    }
    return res;
}

//Function to reverse the given string
string rev(string s){
    int n=s.length();
    for(int i=0;i<n/2;i++){
        char t=s[i];
        s[i]=s[n-i-1];
        s[n-i-1]=t;
    }
    return s;
}

//Function to convert infix string to prefix string
string infixToPrefix(string s){
    s=rev(s);
    for(int i=0;i<s.length();i++){
        if(s[i]=='('){
            s[i]=')';
        }else if(s[i]==')'){
            s[i]='(';
        }
    }
    string post=infixToPostfix(s);
    post=rev(post);
    return post;
}

//Function to evaluate the given postfix string
int postFixEvaluate(string exp){
    stack<int>st;

    for(int i=0;i<exp.length();i++){
        char c=exp[i];
        if(c==' ') continue; //To ignore the unnecessary spaces
        if(isOperand(c)){ //To check if the given exp has vaild operands or not
            st.push(c-'0');
        }else{
            if(st.size()<2){
                cout<<"Stack empty(invalid postfix expression)"<<endl;
                return -1;
            }
            int val2=st.top();
            st.pop();
            int val1=st.top();
            st.pop();

            if(c=='+'){
                st.push(val1 + val2);
            }else if(c=='-'){
                st.push(val1-val2);
            }else if(c=='*'){
                st.push(val1*val2);
            }else if(c=='/'){
                if(val2==0){ //To check valid invalid division
                    cout<<"Division by zero is not allowed"<<endl;
                    return -1;
                }
                st.push(val1/val2);
            }else if(c=='^'){
                st.push(pow(val1,val2));
                break;
            }else{
                cout<<"Unknown operator"<<endl; //To check for an unknown operator
                return -1;
            }
        }
    }

    //To check if the given expression is invalid or not
    if(st.size()!=1){
        cout<<"Invalid postfix expression"<<endl;
        return -1;
    }
    return st.top();
}

int main(){
    char ch;
    
    do{
        string c;
        cout<<"Enter the string: ";
        cin>>c;
        int n;
        cout<<"1.To convert an infix expression into postfix operation"<<endl;
        cout<<"2.To convert an infix expression into prefix operation"<<endl;
        cout<<"3.Evaluation of postfix expression"<<endl;
        cout<<"Enter your choice: ";
        cin>>n;

        switch(n){
            case 1:{
                string s=infixToPostfix(c); //Calling the function
                cout<<"The postfix string is: "<<s<<endl;
                break;
            }

            case 2:{
                string s=infixToPrefix(c); //Calling the function
                cout<<"The prefix string is: "<<s<<endl;
                break;
            }

            case 3:{
                if(!checkParanthesis(c)){ //To check for proper paranthesis
                    break;
                }
                int res=postFixEvaluate(c);
                if(res!=-1){
                    cout<<"The evaluation of the given postfix expression is: "<<res<<endl;
                    break;
                }
            }
        }

        cout<<"Do you want to continue(y/n)? ";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    return 0;
}

/*Output - 
Enter the string: (a+b)*(c-d)
1.To convert an infix expression into postfix operation
2.To convert an infix expression into prefix operation
3.To convert an prefx expression into postfix operation
Enter your choice: 1
The postfix string is: ab+cd-*
Do you want to continue(y/n)? y
Enter the string: (a+b)*(c-d)
1.To convert an infix expression into postfix operation
2.To convert an infix expression into prefix operation
3.To convert an prefx expression into postfix operation
Enter your choice: 2
The prefix string is: *+ab-cd
Do you want to continue(y/n)? y
Enter the string: ((a+b)*c-(d-e))$(f+g)
1.To convert an infix expression into postfix operation
2.To convert an infix expression into prefix operation
3.To convert an prefx expression into postfix operation
Enter your choice: 1
The postfix string is: ab+c*de--fg+$
Do you want to continue(y/n)? y
Enter the string: ((a+b)*c-(d-e))$(f+g)
1.To convert an infix expression into postfix operation
2.To convert an infix expression into prefix operation
3.To convert an prefx expression into postfix operation
Enter your choice: 2
The prefix string is: $-*+abc-de+fg
Do you want to continue(y/n)? y
Enter the string: 23*54*+9-
1.To convert an infix expression into postfix operation
2.To convert an infix expression into prefix operation
3.Evaluation of postfix expression
Enter your choice: 3
The evaluation of the given postfix expression is: 17
Do you want to continue(y/n)? y
Enter the string: 2+
1.To convert an infix expression into postfix operation
2.To convert an infix expression into prefix operation
3.Evaluation of postfix expression
Enter your choice: 3
Stack empty(invalid postfix expression)
Do you want to continue(y/n)? y
Enter the string: (23+5
1.To convert an infix expression into postfix operation
2.To convert an infix expression into prefix operation
3.Evaluation of postfix expression
Enter your choice: 3
Closing paranthesis is missing
Do you want to continue(y/n)? n
*/