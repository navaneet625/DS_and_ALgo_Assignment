#include<bits/stdc++.h>
using namespace std;
template<class X>
class Node
{
    public:
    Node <X>*pre;
    X data;
    Node <X>*next;
};
template<class X>
class DQUEUE
{
  private:
  Node<X> *front;
  Node<X> *back;
  int size;
  public:
  DQUEUE()
  {
    front=NULL;
    back=NULL;
    size=0;
  }
  void Push_front(X );//1
  void Pop_front();//2
  void Push_back(X );//3
  void Pop_back();//4                5....deque
  void AssignVal(int ,X);//6   ............
  X Front();//7
  X Back();//8
  string Empty();//9
  int Size();//10
  void ReSize(int,X);//11     ...............
  void Erase();//12
  X Nth_element(int );//13
  void Display();//14
};
template<class X>
void DQUEUE<X>::Push_front(X data)
{
    Node<X> * p = new Node<X>;
    if(p==NULL)
      cout<<"dequeue overflow\n";
    else
    {
        p->data=data;
        p->next=NULL;
        p->pre=NULL;
      if(front==NULL)
      {
        front=p;
        back=p;
      }
      else
      {
        p->next=front;
        front->pre=p;
        front=p;
      }
     size++; 
    }
}
template<class X>
void DQUEUE<X>::Push_back(X data)
{
    Node<X> * p= new Node<X>;
    if(p==NULL)
      cout<<"dequeue overflow\n";
    else
    {
        p->data=data;
        p->next=NULL;
        p->pre=NULL;
      if(back== NULL )
      {
        front=p;
        back=p;
      }
      else
      {  
          p->pre=back;
          back->next=p;
          back=p;
      }
     size++; 
    }
}
template<class X>
void DQUEUE<X>::Pop_front()
{
  if(front==NULL)
      cout<<"Dqueue underflow\n";
  else
  {
    Node<X> *p=new Node<X>;
    p=front;
    front=front->next;
    if(front==NULL)
      back=NULL;
    else
      front->pre=NULL;
    free(p);
    size--;
  }
}
template<class X>
void DQUEUE<X>::Pop_back()
{
  if(back==NULL)
      cout<<"Dqueue underflow\n";
  else
  {
    Node<X> *p=new Node<X>;
    p=back;
    back=back->pre;
    if(back==NULL)
     front=NULL;  
    else
     back->next=NULL;
    free(p);
   size--; 
  }
}
template<class X>
X DQUEUE<X>::Front()
{
  if(front==NULL)
     {
     cout<<"This time Dque is empty : ";   
     return -1;
     }
   else 
     return front->data;
}
template<class X>
X DQUEUE<X>::Back()
{
  if(back==NULL)
    {
    cout<<"This time dque is empty:";  
    return -1;
    }
  else
     return back->data;
}
template<class X>
string  DQUEUE<X>::Empty()
{
  if(front == NULL)
    return "true";
  else
     return "false";
}
template<class X>
int DQUEUE<X>::Size()
{
  return size;
}
template<class X>
void DQUEUE<X>::Erase()
{
  back=NULL;
  while(front!=NULL)
  {
    Node<X> *p=new Node<X> ;
    p=front;
    front=front->next;
    free(p);
  }
  size=0; 
}
template<class X>
X DQUEUE<X>::Nth_element(int a)
{
  Node<X> *p=new Node<X>;
  p=front;
  int count=0;
   if(front==NULL){
    cout<<"Dque size is <="<<a<<"...";
    return -1;
    }
   if(a<0)
   {
     cout<<"invalid input ";
      return -1;
   }
    while(p->next!=NULL && count!=a)
   {
     p=p->next;
     count++;
   }
   if(count==a)
    return p->data;
   else
    {
      cout<<"Invalid input ";
      return -1;
    }
}
template<class X>
void DQUEUE<X>::AssignVal(int n, X x)
{
  Node<X> *p= new Node<X>;
  p=front;
  while(n--)
   DQUEUE<X>::Push_back(x);
}
template<class X>
void DQUEUE<X>::ReSize(int n,X d)
{
  int m= DQUEUE<X>::Size();
  if(n==m)
  return ;
  else if(m>n)
  {
    n=m-n;
    while(n--)
      DQUEUE<X>::Pop_back();
  }
  else
  {
    n=n-m;
    while(n--)
     DQUEUE<X>::Push_back(d);
  }
}
template<class X>
void DQUEUE<X>::Display()
{
  if(front==NULL)
  {
    cout<<"not a one data in present in Dque";
   return;
  }
  else
  {
      Node<X> *p= new Node<X>;
      p=front;
      while(p!=NULL)
      {
        cout<<p->data<<" ";
        p=p->next;
      }
  }
}
int main()
{
 DQUEUE<X> dq;
 X q;
 cin>>q;
 while(q--)
 {
   int a;
   cin>>a;
  if(a==1){
      int x;
      cin>>x;
      dq.Push_front(x);
      dq.Display();
      cout<<endl;
    }
  else if(a==2){
      dq.Pop_front();
      dq.Display();
      cout<<endl;
    }
  else if(a==3){
      int x;
      cin>>x;
      dq.Push_back(x);
      dq.Display();
      cout<<endl;
    }
  else if(a==4){
      dq.Pop_back();
      dq.Display();
      cout<<endl;
     }
  else if(a==5)
      DQUEUE<int> *dq =new DQUEUE<int>;
  else if(a==6){      
      DQUEUE<int> *dq =new DQUEUE<int>;
      int x,y;
      cin>>x>>y;
      dq->AssignVal(x,y);
      dq->Display();
      cout<<endl; 
    } 
  else if(a==7)
      cout<<dq.Front()<<endl;
  else if(a==8)
      cout<<dq.Back()<<endl;
  else if(a==9)
      cout<<dq.Empty()<<endl;
  else if(a==10)
      cout<<dq.Size()<<endl;
  else if(a==11){
      int x,d;
      cin>>x>>d;
      dq.ReSize(x,d);
      dq.Display();
      cout<<endl;
    }           
  else if(a==12)
      dq.Erase();
  else if(a==13){
      int n;
      cin>>n;
      cout<<dq.Nth_element(n)<<endl;
    }
  else if(a==14){
      dq.Display();
      cout<<endl;
      }      
  else
      cout<<"enter correct value in between 1-14\n";   
 }
dq.Erase();
return 0;
}