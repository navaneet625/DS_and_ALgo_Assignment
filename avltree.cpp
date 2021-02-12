#include<bits/stdc++.h>
using namespace std;
template <typename key>
class Node
{
public:
	key data;
	Node<key> *left;
	Node<key> *right;
	int height;
	int duplicate;
};
template <typename key>
class avl
{
	Node<key> *ub, *lb;
public:
	int height(Node<key> *n)
	{
		if (n == NULL)
			return 0;
		return n->height;
	}
	int max(int a, int b)
	{
		return (a > b) ? a : b;
	}
	Node<key> *newnode(key data)
	{
        Node<key>* p = new Node<key>();
		p->data = data;
		p->left = NULL;
		p->right = NULL;
		p->height = 1;
		p->duplicate = 1;
		return p;
	}
	Node<key> *rotateRight(Node<key> *p)
	{
		Node<key> *q = p->left;
		Node<key> *r = q->right;
		//right rotate
		q->right = p;
		p->left = r;
		//height of updated node p and q
		p->height = max(height(p->left), height(p->right)) + 1;
		q->height = max(height(q->left), height(q->right)) + 1;
		return q;
	}
	Node<key> *rotateLeft(Node<key> *p)
	{
		Node<key> *q = p->right;
		Node<key> *r = q->left;
		//left rotate
		q->left = p;
		p->right = r;
		//height of updated node p and q
		p->height = max(height(p->left), height(p->right)) + 1;
		q->height = max(height(q->left), height(q->right)) + 1;
		return q;
	}
	int getBalance(Node<key> *n)
	{
		if (n == NULL)
			return 0;
		return height(n->left) - height(n->right);
	}
	Node<key> *insert(Node<key> *node, key data) //O(logn)
	{
		if (node == NULL)
			return newnode(data);
		if (data < node->data)
			node->left = insert(node->left, data);
		else if (data > node->data)
			node->right = insert(node->right, data);
		else
		{
			if (node->data == data)
				node->duplicate += 1;
			// cout<<node->data<<" "<<node->duplicate<<endl;
		}
		node->height = 1 + max(height(node->left), height(node->right));
		int balance = getBalance(node);
		//left left case
		if (balance > 1 && data < node->left->data)
			return rotateRight(node);
		//right right case
		if (balance < -1 && data > node->right->data)
			return rotateLeft(node);
		//left right case
		if (balance > 1 && data > node->left->data)
		{
			node->left = rotateLeft(node->left);
			return rotateRight(node);
		}
		//right left case
		if (balance < -1 && data < node->right->data)
		{
			node->right = rotateRight(node->right);
			return rotateLeft(node);
		}
		return node;
	}
	void InOrder(Node<key> *root)//O(n)
	{
		if (root != NULL)
		{
			int x = root->duplicate;
			InOrder(root->left);
			while (x--) {
				cout << root->data << " ";
			}
			InOrder(root->right);
		}
	}
	Node<key> *minValueNode(Node<key>* node)
	{
		Node<key> *p = node;
		while (p->left != NULL)
			p = p->left;
		return p;
	}
	Node<key> *deleteNode(Node<key> * root, key data) //logn
	{
		//if root is pointing to null
		if (root == NULL)
			return root;
		//if data less than root then go left
		if (data < root->data)
			root->left = deleteNode(root->left, data);
		//if data more than root then go right
		else if (data > root->data)
			root->right = deleteNode(root->right, data);
		//if data is equal to root data then delete root data
		else
		{
			if (root->duplicate > 1)
			{
				root->duplicate -= 1;
			}
			else
			{
				//node 0 or 1 child
				if ((root->left == NULL) || (root->right == NULL))
				{
					Node<key> *temp;
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
					Node<key>* temp = minValueNode(root->right);
					root->data = temp->data;
					root->right = deleteNode(root->right, temp->data);
				}
			}
		}
		if ( root == NULL)
			return root;
		root->height = 1 + max(height(root->left), height(root->right));
		int balance = getBalance(root);
		//left left case
		if (balance > 1 && data < root->left->data)
			return rotateRight(root);
		//right right case
		if (balance < -1 && data > root->right->data)
			return rotateLeft(root);
		//left right case
		if (balance > 1 && data > root->left->data)
		{
			root->left = rotateLeft(root->left);
			return rotateRight(root);
		}
		//right left case
		if (balance < -1 && data < root->right->data)
		{
			root->right = rotateRight(root->right);
			return rotateLeft(root);
		}
		return root;
	}
	void searchData(Node<key> *root, key data) //logn
	{
	    if (root == NULL)
		{
			cout<<"false\n";
			return;
		}
		if (data == root->data)
		{
			cout<<"true\n";
			return ;
		}	
		else if (data < root->data)
			return searchData(root->left, data);
		else
			return searchData(root->right, data);
		//return false;
	}
	int countTotalNode(Node<key> *root)//O(logn)
	{
		if (root == NULL)
			return 0;
		else return root->duplicate + countTotalNode(root->left) + countTotalNode(root->right);
	}
	key kth_largest(Node<key> *root, int k) //O(logn)
	{
		key temp = countTotalNode(root->right);
		if (k <= temp + root->duplicate && k > temp)
			return root->data;
		else if (k <= temp) //largest element in right sub tree
			return kth_largest(root->right, k);
		else
			return kth_largest(root->left, (k - temp - root->duplicate));
	}
	int countOccurance(Node<key> *root, key data) //O(logn)
	{
		if (root == NULL)
			return 0;
		if (data == root->data)
			return root->duplicate;
		else if (data < root->data)
			return countOccurance(root->left, data);
		else
			return countOccurance(root->right, data);
    }
	void min_diff(Node<key> *root, key item, int *min_val, int *min_key)
	{
		if (root == NULL)
			return;
		if (root->data == item)
		{
			*min_key = item;
			return ;
		}
		if (*min_val > abs(root->data - item))
		{
			*min_val = abs(root->data - item);
			*min_key = root->data;
		}
		if (item < root->data)
			min_diff(root->left, item, min_val, min_key);
		else
			min_diff(root->right, item, min_val, min_key);
    }
	key closestElement(Node<key> *root, key item) //O(logn)
	{
		key min_val = INT_MAX, min_key = -1;
		min_diff(root, item, &min_val, &min_key);
		return min_key;
	}
	void Generate_upper_bound(Node<key>* root, key data)
	{
		if (root == NULL) {
			return;
		}
		if (root->data > data) 
		{
			ub = root;
			upper_bound(root->left, data);
		} 
		else 
		{
			upper_bound(root->right, data);
		}
	}
	void Generate_lower_bound(Node<key>* root, key data)
	{

		if (root == NULL) {
			return;
		}
		if (root->data >= data) 
		{
			lb = root;
			lower_bound(root->left, data);
		} else 
		{
			lower_bound(root->right, data);
		}
	}
    key lower_bound(Node<key>* root, key data) {
		Generate_lower_bound(root, data);
		return lb->data;
	}
	key upper_bound(Node<key>* root, key data) {
		Generate_upper_bound(root, data);
		return ub->data;
	}
	Node<key>* u_b(Node<key>* root, key data)
	{
		ub = NULL;
		upper_bound(root, data);
		return ub;
	}
	Node<key>* l_b(Node<key> *root , key data)
	{
		lb = NULL;
		lower_bound(root, data);
		return lb;
	}
	int  no_ofEle_in_range(Node<key> *root, key first, key last)
	{
		if (root == NULL)
			return 0;
		if (root->data == last && root->data == first)
			return root->duplicate;
		if (first <= root->data && last >= root->data)
			return root->duplicate + no_ofEle_in_range(root->left, first, last) + no_ofEle_in_range(root->right, first, last);
		else if (first > root->data)
			return no_ofEle_in_range(root->right, first, last);
		else
			return no_ofEle_in_range(root->left, first, last);
	}
};


int main()
{
	Node<int>* root=NULL;
	avl<int> a;
     int c;
	 int  data;
    while(1)
    {
        cin>>c;
        if(c==1)
           {
            cin>>data;
            root=a.insert(root,data);
           }
        else if(c==2)
        {
            cin>>data;
           root=a.deleteNode(root,data);
        }
        else if(c==3)
        {
            cin>>data;
            a.searchData(root,data);
		}
        else if(c==4)
        {
            cin>>data;
          cout<< a.countOccurance(root,data)<<endl;
        }   
        else if(c==5)
           {
			   int lb;
               cin>>lb;
               cout<<a.lower_bound(root,lb)<<endl;
           }
        else if(c==6)
              {
				  int ub;
				  cin>>ub;
				cout<<a.upper_bound(root,ub)<<endl;
			  }	  
        else if(c==7)
               {
				   int val;
				   cin>>val;
				   cout<<a.closestElement(root,val)<<endl;
			   }
		else if(c==8)
		{
			int k;
			cin>>k;
			cout<<a.kth_largest(root,k)<<endl;
		}	   
        else if(c==9)
          cout<< a.countTotalNode(root)<<endl;
		else
		    cout<<"Invalid Input\n";
	 a.InOrder(root);   
  } 
  return 0;
}
