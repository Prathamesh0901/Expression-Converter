#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <math.h>
using namespace std;

#define MAX 50

template<class T>
class stack{
    private:
        int top = -1;
        T arr[MAX];
    
    public:
        void push(T t){
            if( isFull() ){
                cout << "Stack is full!" << endl;
            }
            arr[++top] = t;
        }

        T pop(){
            if( isEmpty() ) {
                cout << " Stack is empty! " << endl;
            }
            return arr[top--];
        }

        bool isEmpty() {
            if( top < 0) {
                return true;
            }
            return false;
        }

        bool isFull() {
            if( top > MAX) {
                return true;
            }
            return false;
        }

        T topOfStack() {
            return arr[top];
        }
};

class stack2{
    private:
        string arr[MAX];
        int top = -1;

    public:
        void push(string t){
            arr[++top] = t;
        }

        string pop(){
            if( isEmpty() ) {
                cout << " Stack is empty! " << endl;
            }
            return arr[top--];
        }

        bool isEmpty() {
            if( top < 0) {
                return true;
            }
            return false;
        }

        string topOfStack() {
            return arr[top];
        }
};

int precedence(char symbol) {
    switch (symbol) {
        case '^':
            return 3;
        case '/':
        case '*':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}

void selectExpression(string& expression, vector<string>& expressions){
    for(int i=0;i<expressions.size();i++){
        cout<<i+1<<"."<<expressions[i]<<endl;
    }
    int x;
    cin>>x;
    if(x > expressions.size() || x == 0){
        cout<<"Enter valid number!"<<endl;
    }
    else{
        expression = expressions[x-1];
    }
}

bool isOperator(char x) {
    if(x == '+' || x == '-' || x == '*' || x == '/' || x == '^') {
        return true;
    }
    return false;
}

bool isOperand(char ch){
    if(isalpha(ch) || isdigit(ch)){
        return true;
    }
    return false;
}

class Postfix {

protected:
    string infixExpression;
    stack<char> s;
    stack<float> p;

    void map(vector<float>& m) {
        for(int i=0; i<infixExpression.length(); i++){
            char ch = infixExpression[i];
            int x;
            if( isOperand(ch) ){
                cout<<"Enter value of "<<ch<<": ";
                cin>>x;
                m[ch - 'a'] = x;
            }
        }
    }

public:
    Postfix(string e){
        infixExpression = e;
    }

    string convertToPostfix(){
        string ans;
        int j = 0;
        char symbol, next;
        for (int i = 0; i < infixExpression.length(); i++) {
            symbol = infixExpression[i];
            if (!isspace(symbol)) {
                switch (symbol) {
                    case '(':
                        s.push(symbol);
                        break;
                    case ')':
                        while ((next = s.pop()) != '(')
                            ans += next;
                        break;
                    case '+':
                    case '-':
                    case '*':
                    case '/':
                    case '^':
                        while (!s.isEmpty() && precedence(s.topOfStack()) >= precedence(symbol))
                            ans += s.pop();
                        s.push(symbol);
                        break;
                    default:
                        ans += symbol;
                }
            }
        }
        while (!s.isEmpty())
            ans += s.pop();

        return ans;
    }

    float evaluatePostfix(string& e) {
        vector<float> m(26, 0);
        map(m);
        for(int i=0; i<e.length(); i++) {
            char ch = e[i];
            if( isOperator(ch) ){
                int a = p.pop();
                int b = p.pop();
                if(ch == '+') {
                    p.push(a+b);
                }
                else if(ch == '-') {
                    p.push(a-b);
                } 
                else if(ch == '*') {
                    p.push(a*b);
                } 
                else if(ch == '/') {
                    p.push(a/b);
                } 
                else if(ch == '^') {
                    p.push(pow(a, b));
                } 
            }
            else if( isOperand(ch) ) {
                p.push(m[ch - 'a']);
            }
        }
        return p.pop();
    }

    string postfixToInfix(string postfixExpression) {
        stack2 p;
        for(int i=0;i<postfixExpression.length();i++){
            char ch = postfixExpression[i];
            if(isOperand(ch)){
                string str(1, ch);
                p.push(str);
            }
            else if( isOperator(ch)){
                string s2 = p.pop(), s1 = p.pop();
                string s3 = "(" + s1 + ch + s2 + ")";
                p.push(s3);
            }
        }
        string answer = p.pop();
        return answer;
    }

    ~Postfix(){}
};

class Prefix: protected Postfix{

private:
    void changePar(string& str){
        for(int i=0;i<str.length();i++){
            if(str[i] == '('){
                str[i]=')';
            }
            else if(str[i] == ')'){
                str[i]='(';
            }
        }
    }

    void reverse(string& str){
        int i=0, j=str.length()-1;
        while(i<=j){
            swap(str[i], str[j]);
            i++;
            j--;
        }
    }

    public:
        Prefix(string e): Postfix(e){}

        string convertToPrefix(){
            string ans;
            reverse(infixExpression);
            changePar(infixExpression);

            ans = convertToPostfix();

            reverse(ans);
            return ans;
        }

        float evaluatePrefix(string& e){
            vector<float> m(26, 0);
            map(m);
            for(int i=e.length()-1; i>=0; i--) {
                char ch = e[i];
                if( isOperator(ch) ){
                    int a = p.pop();
                    int b = p.pop();
                    if(ch == '+') {
                        p.push(a+b);
                    }
                    else if(ch == '-') {
                        p.push(a-b);
                    } 
                    else if(ch == '*') {
                        p.push(a*b);
                    } 
                    else if(ch == '/') {
                        p.push(a/b);
                    } 
                    else if(ch == '^') {
                        p.push(pow(a, b));
                    } 
                }
                else if( isOperand(ch) ) {
                    p.push(m[ch - 'a']);
                }
            }
            return p.pop();
        }

        string prefixToInfix(string prefixExpression){
            reverse(prefixExpression);
            string answer = postfixToInfix(prefixExpression);
            reverse(answer);
            changePar(answer);
            return answer;
        }

        ~Prefix(){}
};

void menu() {
    cout << "********* MENU **********" << endl;
    cout << "1.Enter a new expression" <<endl
         << "2.Select an expression" <<endl
         << "3.Postfix Calculations" <<endl
         << "4.Prefix Calculations" <<endl
         << "5.EXIT" << endl;
    cout << "*************************" << endl;
}

bool alreadyExists(string& exp, vector<string>& expressions) {
    for(int i=0;i<expressions.size();i++) {
        if(exp == expressions[i]) {
            return true;
        }
    }
    return false;
}

int main() {

    int x;
    vector<string> infixExpressions = {"a+b","(a+b)*(c+d)"};
    vector<string> prefixExpressions = {"+ab", "*+ab+cd"};
    vector<string> postfixExpressions = {"ab+", "ab+cd+*"};
    string infixExpression = infixExpressions[0];
    string postfixExpression = postfixExpressions[0];
    string prefixExpression = prefixExpressions[0];

    do {
        menu();
        cin >> x;

        switch (x) {
            case 1: {
                string exp;
                cout << "Enter a new expression: ";
                cin.ignore();
                getline(cin, exp);
                if(alreadyExists(exp, infixExpressions)) {
                    cout<<"Expression already exists!" <<endl;
                }
                else{
                    infixExpression = exp;
                    infixExpressions.push_back(exp);
                }
                break;
            }

            case 2: {
                selectExpression(infixExpression, infixExpressions);
                break;
            }

            case 3: {
                if(infixExpression == ""){
                    cout << "WARNING: No expression selected! Select an expression first!" <<endl;
                    break;
                }
                int q;
                cout<<"****** POSTFIX MENU *****" << endl
                    <<"1.Convert to postfix" << endl
                    << "2.Evaluate postfix expression" << endl
                    << "3.Postfix to infix conversion" << endl
                    <<"*************************" << endl;
                cin>>q;
                Postfix p1(infixExpression);
                string answer = p1.convertToPostfix();
                postfixExpressions.push_back(answer);
                postfixExpression = answer;
                switch(q) {
                    case 1: {
                        cout<<"Performing postfix operation on expression: "<<infixExpression<<endl;
                        cout << "Postfix expression: " << answer << endl;
                        break;
                    }
                    case 2: {
                        cout<<"Evaluating postfix expression: "<<answer<<endl;
                        float x = p1.evaluatePostfix(answer);
                        cout << "Evaluation answer: " << x <<endl;
                        break;
                    }
                    case 3: {
                        int z;
                        cout<< "****************************" <<endl;
                        cout<<"1. Convert expression :" << postfixExpression << endl;
                        cout<<"2. Select other postfix expression " <<endl;
                        cout<< "****************************" <<endl;
                        cin>>z;
                        switch(z) {
                            case 1: {
                                cout<<"Infix Expression: " << p1.postfixToInfix(postfixExpression) <<endl;
                                break;
                            }
                            case 2: {
                                selectExpression(postfixExpression, postfixExpressions);
                                cout<<"Converting postfix expression: " << postfixExpression << endl;
                                cout<<"Infix Expression: " << p1.postfixToInfix(postfixExpression) <<endl;
                                break;
                            }
                        }
                        break;
                    }
                }
                break;
            }
            
            case 4: {
                if(infixExpression == ""){
                    cout << "WARNING: No expression selected! Select an expression first!" <<endl;
                    break;
                }
                int q;
                cout<<"****** PREFIX MENU ******" << endl
                    <<"1.Convert to prefix" << endl
                    << "2.Evaluate prefix expression" << endl
                    << "3.Prefix to infix conversion" << endl
                    <<"*************************" << endl;
                cin>>q;
                Prefix p2(infixExpression);
                string answer = p2.convertToPrefix();
                prefixExpressions.push_back(answer);
                prefixExpression = answer;
                switch(q) {
                    case 1: {
                        cout<<"Performing prefix operation on expression: "<<infixExpression<<endl;
                        cout << "Prefix expression: " << answer << endl;
                        break;
                    }
                    case 2: {
                        cout<<"Evaluating prefix expression: "<<answer<<endl;
                        int x = p2.evaluatePrefix(answer);
                        cout << "Evaluation answer: " << x <<endl;
                        break;
                    }
                    case 3: {
                        int z;
                        cout<< "****************************" <<endl;
                        cout << "1. Convert expression: "<< prefixExpression << endl;
                        cout << "2. Select new prefix expression: " << endl;
                        cout<< "****************************" <<endl;
                        cin>>z;
                        switch(z) {
                            case 1: {
                                cout<<"Infix Expression: " << p2.prefixToInfix(prefixExpression) <<endl;
                                break;
                            }
                            case 2: {
                                selectExpression(prefixExpression, prefixExpressions);
                                cout<<"Converting prefix expression: " << prefixExpression << endl;
                                cout<<"Infix Expression: " << p2.prefixToInfix(prefixExpression) <<endl;
                                break;
                            }
                        }
                        
                        break;
                    }
                }
                break;
            }

            default: {
                if( x != 5){
                    cout << "Invalid choice!" <<endl;
                    break;
                }
            }
        }

    } while (x != 5);

    return 0;
}