#include <bits/stdc++.h>
#define table_size 5
#define ll long long 
using namespace std;
template <class K, class V>
class unorderedMap
{
  public:
    ll prime_num = 31;
    ll siZe = 5;
    class node
    {
      public:
        K key;
        V value;
        node *next;
    };
    node *hash_table[table_size];//assigning space for map 
    unorderedMap()//initislising index with null
    {
        for (ll i = 0; i < table_size; i++)
            hash_table[i] = NULL;
    }
   //rolling hash function
    ll covert_HashValue(K key)
    {
        string str(key);
        ll hash_val = 0;
        ll mul = 1;
        for (ll i = 0; i < str.size(); i++)
        {
            hash_val += ((str[i]-'0'+1) * mul);
            hash_val %= siZe;
            mul *= prime_num;
        }
        return hash_val;
    }
    node *createNode(K key, V value)
    {
        node *p = new node;
        p->key = key;
        p->value = value;
        p->next = NULL;
        return p;
    }
    void insert(K key, V value)
    {
        ll index = covert_HashValue(key);
        node *head = hash_table[index];
        if(head == NULL)
        {
            node *newNode = createNode(key, value);
            hash_table[index] = newNode;
            return;
        }
        else if(head->next == NULL)
        {
            if(head->key == key)
                return;
            else
            {
                node *newNode = createNode(key, value);
                head->next = newNode;
                return;
            }
        }
        else
        {
            node *p = head;
            while (p->next != NULL)
            {
                if (p->key == key) return;
                else p = p->next;
               
            }
            if (p->key == key)
            {
                return;
            }
            node *newNode = createNode(key, value);
            p->next = newNode;
            return;
        }
    }
    void map_key_val(K key,V value)
    {
        ll index = covert_HashValue(key);
        node *head = hash_table[index];
        if(head == NULL)
        {
            node *newNode = createNode(key,value);
            head->next=newNode;
            return ;
        }
        else if(head->next!=NULL)
        {
            if(head->key == key)
            {
                head->value=value;
                return;
            }
            else
            {
                node *newNode=createNode(key,value);
                head->next=newNode;
            }
        }
        else
        {
            node *p=head;
            while(p->next != NULL)
            {
                if(p->key==key)
                {
                    p->value=value;
                    return;
                }
                else
                  p=p->next;
            }
            if(p->key==key)
            {
                p->value=value;
                return;
            }
            node *newNode = createNode(key,value);
            p->next=newNode;
            return;
        }
        
    }
    void find(K key)
    {
        ll index = covert_HashValue(key);
        node *head = hash_table[index];
        if (head == NULL)
        {
         cout<<"false"<<endl;
            return ;
        }
        else
        {
            node *p = head;
            while (p != NULL)
            {
                if (p->key == key)
                {
                
                  cout<<"true"<<endl;
                    return ;
                }
                else
                {
                    p = p->next;
                }
            }
       
            cout<<"false"<<endl;
            return ;
        }
    }
    void map_Key(K key)
    {
        ll index = covert_HashValue(key);
        node *head = hash_table[index];
        if(head==NULL)
        {
          cout<<"No value for this key"<<endl;
          return ;
        }
        else
        {
            node* p = head;
            while(p!=NULL)
            {
             if(p->key == key)
             {
                cout<<p->value<<endl;
                return ;
             }
             else
                p=p->next;
            } 
           cout<<"No value for this key"<<endl; 
           return ;
        }
    }
    void erase_key(K key)
    {
        ll index = covert_HashValue(key);
        node *head = hash_table[index];
        node *p = head, *q = NULL;
        if (head == NULL)
        {
            cout << "No Data Found Related with key." << endl;
            return;
        }
        else
        {
            if (head->key == key)
            {
                p = head;
                head = head->next;
                hash_table[index] = head;
                free(p);
                return;
            }
            while (p->next != NULL && p->key != key)
            {
                q = p;
                p = p->next;
            }
            if (p->next == NULL && p->key != key)
            {
                cout << "No Data Found Related with key." << endl;
                return;
            }
            else
            {
                q->next = p->next;
                free(p);
            }
        }
        return;
    }
    void print_all_key_val()
    {
        for (ll i = 0; i < table_size; i++)
        {
            cout << endl
                 << i << " : ";
            node *p = hash_table[i];
            while (p != NULL)
            {
                cout << "=>[" << p->key << "=" << p->value << "]";
                p = p->next;
            }
            cout << endl;
        }
    }
};
int main()
{
    string key;
    string value;
    unorderedMap<string, string> a;
    int c;
    while(1)
    {
        cin>>c;
        if(c==1)
           {
            cin>>key>>value;
            a.insert(key,value);
           }
        else if(c==2)
        {
            cin>>key;
           a.erase_key(key);
        }
        else if(c==3)
        {
            cin>>key;
            a.find(key);
        }
        else if(c==4)
        {
            cin>>key;
           a.map_Key(key);
        }   
        else if(c==5)
           {
               cin>>key>>value;
               a.map_key_val(key,value);
           }
        else
           cout<<"Invalid input\n";
       a.print_all_key_val();
       cout<<endl;       
    } 
}