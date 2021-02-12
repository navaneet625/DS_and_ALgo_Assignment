#include<bits/stdc++.h>
using namespace std;
#define ll long long int 
#define MAX 10000
int arr[10000];
bool issmall(string s1,string s2)
{
    int sz1=s1.length();
    int sz2=s2.length();
    if(sz1>sz2)
     return false;
    else if(sz1<sz2)
     return true;
    else
    {
        for(int i=0;i<sz1;i++)
        {
            if(s1[i]<s2[i])
              return true;
            else if(s1[i]>s2[i])
              return false;
        }
        return false;
    }
}
string strsub(string s1,string s2)
{
    int sz1=s1.length();
    int sz2=s2.length();
    int borrow=0;
    reverse(s1.begin(),s1.end());
    reverse(s2.begin(),s2.end());
    string str="";
    for(int i=0;i<sz2;i++)
    {
         int sub=((s1[i]-'0')-(s2[i]-'0')-borrow);
          if(sub<0)
          {
              sub=sub + 10;
              borrow=1; 
          }
          else
             borrow=0;
     str.push_back(sub + '0');       
   }
    for(int i=sz2;i<sz1;i++)
    {
        int sub=(s1[i]-'0'-borrow);
        if(sub<0)
        {
            sub = sub + 10;
            borrow=1;
        }
        else
           borrow=0;
        str.push_back(sub +'0');
    }
      int len=str.length()-1;
      while (str[len]=='0')
      {
        str.pop_back();
        len--;
      }
    reverse(str.begin(),str.end());
  return str;   
}
string Gcd(string s1,string s2)
{
    if(issmall(s1,s2))
      swap(s1,s2);
     s1=strsub(s1,s2);
    //cout<<s1<<" ";
    if(!s1.empty()  && s1!="1")
     return Gcd(s1,s2);
    else if (s1=="1")
     return "1";
    else
      return s2;
}
ll gcd(ll b,ll x)
{
    if(b==0)
     return x;
    else if(x==0)
      return b;
    else return gcd(x,b%x);   
}
ll Mod(string a,ll b)
{
    ll size=a.length();
    ll res=0;
    for(ll i=0;i<size;i++){
        res=((res*10) + (a[i]-'0'))%b;
      // cout<<res<<endl;
    }
//  cout<<res<<"  ......."<<endl;  
    return res;
}
int  fact(int n)
{
  int num=1,l=1,i,a;
    arr[0]=1;
    while(num<=n){
        i=0;
        a=0;
      while(i<l){
        arr[i]*=num;
        arr[i]+=a;
        a=arr[i]/10;
        arr[i]%=10;
        i++;
      }
      while(a!=0){
      arr[l]=a%10;
      a/=10;
      l++;
      }
     num++; 
    }
    l--;
  return l;  
}
string  multyply(string num1, string num2)
{
   int len1=num1.length();
   int len2=num2.length();
   if(len1==0 || len2 ==0)
     return "0";
  // int arr[len1 + len2 ]={0};
   vector<int> arr1(len1+len2,0);
   int n1=0,n2=0;
   for(int i=len1-1;i>=0;i--)
     {
         int carry=0;
         n2=0;
        int sn1=num1[i] -'0';
         for(int j=len2-1;j>=0;j--)
         {
           int sn2=num2[j]-'0';
             int res= sn1 * sn2 + arr1[n1+n2] + carry;
             carry =res/10;
             arr1[n1+n2]=res%10;
            n2++; 
         }
         if(carry>0)
             arr1[n1+n2]+=carry;
         n1++;
     }
    //int arrSize = sizeof(arr)/sizeof(arr[0]);
    int arrSize=arr1.size()-1;
    while(arrSize>=0 && arr1[arrSize]==0)
      arrSize--;
    if(arrSize==-1)
     return "0";
    string s="";
    while(arrSize>=0)
      s+=to_string(arr1[arrSize--]);
      
 return s;      
}
string power(string str,int n)
{
   string res="1";
   while (n>0)
   {
      if(n&1)
        res=multyply(str,res);
 //  cout<<res<<endl;
      str=multyply(str,str);
      n=n>>1;
   }
  //cout<<res<<endl; 
  return res; 
}
int main(){
  int q;
  cin>>q;
  while(q--)
  {
    int t;
    cin>>t;
        if(t==3)
          {
             int n;
             cin>>n;
             int q = fact(n);
             for(int i=q;i>=0;i--)
             cout<<arr[i];
          } 
        else if(t==1)
          {
             string a;
             int N;
             cin>>a>>N;
             cout<<power(a,N)<<endl;
          }
        else if(t==2)
          {
             string s1;
             string s2;
             cin>>s1>>s2;
             int len1=s1.length();
             int len2=s2.length();
             ll x,ans;
            if(len1<=18)
            {
              ll res=stoll(s1);
              x=Mod(s2,res);
              ans=gcd(res,x);
             cout<<ans<<endl; 
            }
            else if(len2<=18)
            {
              ll res=stoll(s2);
              x=Mod(s1,res);
              ans=gcd(res,x);
             cout<<ans<<endl;  
            }
            else
              cout<<Gcd(s1,s2)<<endl;
          }  
      else
       cout<<"invalid input"<<endl;
           
  }
return 0; 
}