#include<bits/stdc++.h>
#include<string>
#include<iostream>
#include<cmath> 
using namespace std; 
class Node
 {
    public:
    float data;
    Node * next;
};
class STACK
{
  private:
  Node *top;
  public:
  STACK()
  {
      top=NULL;
  }
  void push(float data);
  void pop();
  float Top();
};
float STACK::Top()
{
  if(top==NULL)
  {
    cout<<"stack is empty";
    exit (1);
  }
  else
  {
    float y= top->data;
    return y;
  }
 }
void STACK::push(float data)
{
  Node * p= new Node;
  if(p==NULL)
    {
      cout<<"stack overflow"<<endl;
      exit(1);
    }
    else
    {
       p->next=top;
       p->data=data;
       top=p;
    }
}
void STACK::pop()
{
   if(top==NULL)
     {
         cout<<"stack underflow";
        exit (1);
     }
     else
     {
       struct  Node * p = top;
        top = top->next;
        free(p);
     }
}
int precedence(char op){ 
    if(op == '+'|| op == '-') 
    return 1; 
    if(op == '*'||op == '/'|| op=='%') 
     return 2; 
  return 0; 
} 
int isdigit(char c)
{
    if(c>='0' && c<='9')
     return 1;
    if(c == '.')
     return 2; 
    else
    return 0;
}
double Operation(double a, double b, char c){ 
    if(c=='+')
     return b+a;
    else if(c=='-')
     return b-a;
    else if(c=='*')
     return b*a;
    else if( c=='%' && a!=0)
     return fmod(b,a);
    else if(c=='/' && a!=0)
     return b/a;
    else
      exit(1);
} 
float expresion_evalution(string s){ 
    int i; 
    //stack <float> st_int; 
    //stack <char> st_char;
    STACK st_int;
    STACK st_char;
    st_char.push('$') ;
    int l=s.length();
   for(i = 0; i < l; i++){ 
        if(s[i] == ' ') 
            continue; 
        else if(s[i] == '('){ 
            st_char.push(s[i]); 
        } 
       else if(isdigit(s[i])){ 
               float val = 0.0,v=0.0;
               int count=0; 
           while( i < l && (isdigit(s[i])==1 || isdigit(s[i])==2))
            { 
                count=1;
                if(isdigit(s[i]) == 2){
                    int j=-1; 
                  while(isdigit(s[i+1])){
                    v+=(pow(10,j)*(s[++i]-'0'));
                  //  cout<<"j :"<<j<<" decimal value : "<<v<<endl;
                    j--;
                  }
                  // cout<<v<<" "<<val<<endl;
                   i++;
                }
                else if(isdigit(s[i]))
                {
                val =(val*10) + (s[i]-'0'); 
             //   cout<<val<<endl;
                i++; 
                }
            } 
             if(count)
               i--;
          //  cout<<val<<endl;   
            val=val + v; 
         //   cout<<val<<endl;  
            st_int.push(val); 
          //  cout<<st_int.top()<<endl;
        } 
       else if(s[i] == ')') 
        { 
            while(st_char.Top()!='$' && st_char.Top() != '(') 
            { 
                float a = st_int.Top(); 
                   st_int.pop(); 
                float b = st_int.Top(); 
                   st_int.pop(); 
                char op = st_char.Top(); 
                    st_char.pop(); 
                 st_int.push(Operation(a, b, op)); 
              //  cout<<st_int.top()<<endl; 
            } 
            if(st_char.Top()!='$') 
               st_char.pop(); 
        } 
        else
        {
            while(st_char.Top()!='$' && precedence(st_char.Top()) >= precedence(s[i])){ 
                float a = st_int.Top(); 
                   st_int.pop(); 
                float b = st_int.Top(); 
                   st_int.pop(); 
                char op = st_char.Top(); 
                    st_char.pop(); 
                st_int.push(Operation(a, b, op)); 
            //  cout<<st_int.Top()<<endl;  
            } 
           st_char.push(s[i]); 
        } 
    } 
    while(st_char.Top()!='$'){ 
        float a = st_int.Top(); 
          st_int.pop(); 
        float b = st_int.Top(); 
          st_int.pop(); 
        char op = st_char.Top(); 
           st_char.pop(); 
        st_int.push(Operation(a, b, op)); 
    } 
   // cout<<values.Top()<<endl;
 //  double x=st_int.Top();
   
    return st_int.Top(); 
} 
int main() { 
    string s;
    cin>>s;
    cout<<fixed<<setprecision(5)<<expresion_evalution(s)<<endl;
    return 0; 
} 
  