#include<bits/stdc++.h>
using namespace std;
template <typename X, typename Y>
class Node
{
public:
	X key;
    Y value;
	Node *left;
	Node *right;
	int height;
};
template <typename X, typename Y>
class Ordered_map
{
public:
	int height(Node<X ,Y> *n)//...................
	{
		if (n == NULL)
			return 0;
		return n->height;
	}
	int max(int a, int b)//.........................
	{
		return (a > b) ? a : b;
	}
	Node<X,Y> *newnode(X key,Y value)//.....................
	{
		Node<X,Y>* p = new Node<X,Y>();
		p->key = key;
        p->value = value;
		p->left = NULL;
		p->right = NULL;
		p->height = 1;
		return p;
	}
	Node<X,Y> *rotateRight(Node<X,Y> *p)//...................
	{
		Node<X,Y> *q = p->left;
		Node<X,Y> *r = q->right;
		//right rotate
		q->right = p;
		p->left = r;
		//height of updated node p and q
		p->height = max(height(p->left), height(p->right)) + 1;
		q->height = max(height(q->left), height(q->right)) + 1;
		return q;
	}
	Node<X,Y> *rotateLeft(Node<X,Y> *p)//...................
	{
		Node<X,Y> *q = p->right;
		Node<X,Y> *r = q->left;
		//left rotate
		q->left = p;
		p->right = r;
		//height of updated node p and q
		p->height = max(height(p->left), height(p->right)) + 1;
		q->height = max(height(q->left), height(q->right)) + 1;
		return q;
	}
	int getBalance(Node<X,Y> *n)//..................
	{
		if (n == NULL)
			return 0;
		return height(n->left) - height(n->right);
	}
	Node<X,Y> *insert(Node<X,Y> *node, X key ,Y value) //O(logn).....................
	{
		if (node == NULL)
			return newnode(key,value);
		if (key < node->key)
			node->left = insert(node->left, key , value);
		else if (key > node->key)
			node->right = insert(node->right, key, value);
		else
		    node->value=value;
        node->height = 1 + max(height(node->left), height(node->right));
		int balance = getBalance(node);
		//left left case
		if (balance > 1 && key < node->left->key)
			return rotateRight(node);
		//right right case
		if (balance < -1 && key > node->right->key)
			return rotateLeft(node);
		//left right case
		if (balance > 1 && key > node->left->key)
		{
			node->left = rotateLeft(node->left);
			return rotateRight(node);
		}
		//right left case
		if (balance < -1 && key < node->right->key)
		{
			node->right = rotateRight(node->right);
			return rotateLeft(node);
		}
	  return node;
	}
	void showMapData(Node<X,Y> *root)//O(n).
	{
		if (root != NULL)
		{
			showMapData(root->left);
		    cout <<"["<<root->key<< ","<<root->value<<"]";
			showMapData(root->right);
		}
	}
	Node<X,Y> *minValueNode(Node<X,Y>* node)//......................
	{
		Node<X,Y> *p = node;
		while (p->left != NULL)
			p = p->left;
		return p;
	}
	Node<X,Y> *eraseKey(Node<X,Y> * root, X key) //logn.........................
	{
		//if root is pointing to null
		if (root == NULL)
			return root;
		//if data less than root then go left
		if (key < root->key)
			root->left = eraseKey(root->left, key);
		//if data more than root then go right
		else if (key > root->key)
			root->right = eraseKey(root->right, key);
		//if data is equal to root data then delete root data
		else
		{
			    //node 0 or 1 child
				if ((root->left == NULL) || (root->right == NULL))
				{
					Node<X,Y> *temp;
					if (root->left != NULL)
						temp = root->left;
					else
						temp = root->right;
					if (temp == NULL) //0 child
					{
						temp = root;
						root = NULL;
					}
					else//1 child
						*root = *temp;
					free(temp);
				}
				else//node have 2 child
				{
					Node<X,Y>* temp = minValueNode(root->right);
					root->key = temp->key;
                    root->value = temp->value;
					root->right = eraseKey(root->right, temp->key);
				}
		}
		if ( root == NULL)
			return root;
		root->height = 1 + max(height(root->left), height(root->right));
		int balance = getBalance(root);
		//left left case
		if (balance > 1 && key < root->left->key)
			return rotateRight(root);
		//right right case
		if (balance < -1 && key > root->right->key)
			return rotateLeft(root);
		//left right case
		if (balance > 1 && key > root->left->key)
		{
			root->left = rotateLeft(root->left);
			return rotateRight(root);
		}
		//right left case
		if (balance < -1 && key < root->right->key)
		{
			root->right = rotateRight(root->right);
			return rotateLeft(root);
		}
		return root;
	}
	void findKey(Node<X,Y> *root, X key) //logn
	{
		if(root == NULL)
        {
            cout<<"false\n";
			return ;
        }    
		if(key == root->key)
        { 
            cout<<"true\n";
			return ;
        }    
		else if (key < root->key)
			return findKey(root->left, key);
		else
			return findKey(root->right, key);
		//return false;
	}
	int mapSize(Node<X,Y> *root)//O(logn)....................
	{
		if (root == NULL)
			return 0;
		else return 1 + mapSize(root->left) + mapSize(root->right);
	}
    void mapKeyVal(Node<X,Y> *root,X key)//...................
    {
        if(root ==NULL)
        {
            cout<<"No value are there for this key\n";
            return;
        }
        if(key == root->key)
         {
             cout<<root->value<<endl;
             return;
         }
        else if(key < root->key)
         return mapKeyVal(root->left,key);
        else
         return mapKeyVal(root->right,key); 
    }
    void clear(Node<X,Y>*root)
     {
       if(root == NULL)
          return ;
       clear(root->left);
       clear(root->right); 
        delete root; 
        // root=NULL;
     }
};
int main()
{
	Node<int ,int> *root = NULL;
    Ordered_map<int ,int> a;
	 int c;
     int  key;
     int  value;
    while(1)
    {
        cin>>c;
        if(c==1)
           {
            cin>>key>>value;
            root=a.insert(root,key,value);
           }
        else if(c==2)
        {
            cin>>key;
           root=a.eraseKey(root,key);
        }
        else if(c==3)
        {
            cin>>key;
            a.findKey(root,key);
        }
        else if(c==4)
        {
            cin>>key;
           a.mapKeyVal(root,key);
        }   
        else if(c==5)
           {
               cin>>key>>value;
               root=a.insert(root,key,value);
           }
        else if(c==6)
              cout<<a.mapSize(root)<<endl;
        else if(c==7)
               a.clear(root);
        else
           cout<<"Invalid input\n";
	  if(c!=7)	   
       a.showMapData(root);
       cout<<endl;       
    } 
}
