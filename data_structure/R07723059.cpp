#include <iostream>
#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <conio.h>
#include<vector>
#include<fstream>
#include<string>
#include <sstream>
#include <functional>
#include <algorithm>

using namespace std;

class Node
{
	public:
		int Key;
		Node* Left;
		Node* Right;
		Node* Parent;
};
 
class BST
{
	private:
		Node* root;
		Node* Insert(Node* node, int key);
		vector <int> Y;
		vector <int> X;
		int level;
		ofstream fout;
	public:
		BST();
		~BST();
		Node* show_root();
		void Insert_Public(int key);
		void tree_Preorder(Node* node);
		void tree_Inorder(Node* node);
		void level_initial();
		void print_tree(int row);
		void destructor_BST(Node* node);
		void output_setting(const char* path,int row);
};
BST::BST(){
	root = NULL;	
}
BST::~BST(){
	destructor_BST(root);
	root = NULL;
//	cout<< "BST_clear";
}

void BST::destructor_BST(Node* node){
	if (node != NULL)
	{
		if (node->Left!=NULL) destructor_BST(node->Left);
		if (node->Right!=NULL) destructor_BST(node->Right);
//		cout <<"delete" << node->Key;
		delete node;	
	}

}

void BST::Insert_Public(int key){
	root = Insert(root,key);
}

Node* BST::show_root(){
	return root;
};



Node* BST::Insert(Node* node, int key){
	if (node == NULL) //new node
	{		
		delete node;
		node = new Node;
		node->Key = key;
		node-> Left = NULL;
		node-> Right = NULL;
		node->Parent = NULL;
	}
	
	else if (node->Key < key )
	{
		node->Right = Insert(node->Right,key);
		node->Right->Parent = node;
	}
	else if (node->Key ==key)
	{
		cout << "we have this node!!!";
	}
	else
	{
		node->Left = Insert(node->Left,key);
		node->Left->Parent = node;
	}
	return node;
}


void BST::tree_Preorder(Node* node){
	
	if (node != NULL)
	{
		fout << node->Key;

		if(!(node->Left==NULL && node->Right==NULL))
		{
			fout << "(";
			tree_Preorder(node->Left);
			fout << " ";
			tree_Preorder(node->Right);
			fout<< ")";		
		}		
	}
	else 
	{
		fout<<"-";
	}
};


void BST::level_initial()
{
	level = 0;
};

void BST::tree_Inorder(Node* node){
	if (node!=NULL)
	{
		level++;
		tree_Inorder(node->Left);
		level=level-1;
		
		X.push_back(node->Key);
		Y.push_back(level);
//		cout<<"level:"<<level;
		level++;
		tree_Inorder(node->Right);
		level=level-1;		
//		cout<< "node-key"<<"treeinoder";	
	}
}

void BST::print_tree(int row){
	int get_length(int x);
	const char* path;
//	for (int i=0;i<X.size();i++) cout<< X[i] <<"_" ;
//	cout<<endl;
//	for (int i=0;i<Y.size();i++) cout<< Y[i] <<"_" ;
//	cout<<endl;
	
	// BTree
 
//	cout<< "-----test1213123132";
	path = "BTree.txt";
	fout.close();
	
	if (row == 1)
	{
		fout.open(path, ios::trunc);
	} 
	else
	{
		fout.close();
		fout.open(path, ios::app);
//		fout<< endl;		
	}
	
	int maxValue = *max_element(Y.begin(),Y.end()); // include algorithm
	
	for (int i=0;i<=maxValue;i++)
	{
		
		for (int j=0;j<X.size();j++)
		{
			if (Y[j]==i)
			{
				
				fout <<X[j];
				for(int space=0;space<3-get_length(X[j]);space++) fout <<" ";
				
			}
			else fout << "   ";
		}	
		fout << "\n";
	}
	
	// boundary
	path = "BTree_boundary.txt";
	fout.close();
	if (row == 1) fout.open(path, ios::trunc);
	else
	{
		fout.close();
		fout.open(path, ios::app);
		fout<< endl;		
	}
	for (int i=0;i<=maxValue;i++)
	{
		for (int j=0;j<X.size();j++)
		{
			if (Y[j]==i)
			{
				fout <<X[j]<<" ";;
				break;
			}
		}	
	}

	X.clear();
	Y.clear();
	
}

int get_length(int x)
{
	int length;
	while(x)
	{
		x/=10;
		length++;
	}
	return length;
}

void BST::output_setting(const char* path,int row)
{
	if (row == 1) fout.open(path, ios::trunc);
	else
	{
		fout.close();
		fout.open(path, ios::app);
		fout<< endl;		
	}

}

//------------------

struct TreeNode
{
    int key;
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int key)
    {
        this -> key = key;
        this -> parent = NULL;
        this -> left = NULL;
        this -> right = NULL;
    }
};

class SplayTree
{
    TreeNode *root;
    
    void zig(TreeNode*);
    void zig_zig(TreeNode*);
    void zig_zag(TreeNode*);
    vector <int> Y;
	vector <int> X;
    void splay(TreeNode*);
    ofstream fout;
    
public:
    SplayTree();
    ~SplayTree();
    SplayTree(TreeNode*);
    TreeNode* find(int);
    void insert(int);
    void Delete(int);
    void inOrderPrint(bool);
    void tree_Preorder(TreeNode* node);
    TreeNode* show_root();
    void destructor_splay(TreeNode* node);
    void output_setting(const char* path,int row);
    void tree_Inorder(TreeNode* node,int level);
    void print_tree(int row);
    
};

void SplayTree::zig(TreeNode *x)
{
    TreeNode *p = x -> parent;
    if (p -> left == x)
    {
        TreeNode *A = x -> left;
        TreeNode *B = x -> right;
        TreeNode *C = p -> right;
        
        x -> parent = NULL;
        x -> right = p;
        
        p -> parent = x;
        p -> left = B;
        
        if (B != NULL) B -> parent = p;
    }
    else
    {
        TreeNode *A = p -> left;
        TreeNode *B = x -> left;
        TreeNode *C = x -> right;
        
        x -> parent = NULL;
        x -> left = p;
        
        p -> parent = x;
        p -> right = B;
        
        if (B != NULL) B -> parent = p;
    }
}

SplayTree::~SplayTree(){
	destructor_splay(root);
	root = NULL;
//	cout<< endl<<"spaclear";
}

void SplayTree::destructor_splay(TreeNode* node){
	if (node != NULL)
	{
		if (node->left!=NULL) destructor_splay(node->left);
		if (node->right!=NULL) destructor_splay(node->right);
//		cout <<"delete" << node->key;
		delete node;		
	}
}

void SplayTree::zig_zig(TreeNode *x)
{
    TreeNode *p = x -> parent;
    TreeNode *g = p -> parent;
    if (p -> left == x)
    {
        TreeNode *A = x -> left;
        TreeNode *B = x -> right;
        TreeNode *C = p -> right;
        TreeNode *D = g -> right;
        
        x -> parent = g -> parent;
        x -> right = p;
        
        p -> parent = x;
        p -> left = B;
        p -> right = g;
        
        g -> parent = p;
        g -> left = C;
        
        
        if (x -> parent != NULL)
        {
            if (x -> parent -> left == g) x -> parent -> left = x;
            else x -> parent -> right = x;
        }
        
        if (B != NULL) B -> parent = p;
        
        if (C != NULL) C -> parent = g;
    }
    else
    {
        TreeNode *A = g -> left;
        TreeNode *B = p -> left;
        TreeNode *C = x -> left;
        TreeNode *D = x -> right;
        
        x -> parent = g -> parent;
        x -> left = p;
        
        p -> parent = x;
        p -> left = g;
        p -> right = C;
        
        g -> parent = p;
        g -> right = B;
        
        if (x -> parent != NULL)
        {
            if (x -> parent -> left == g) x -> parent -> left = x;
            else x -> parent -> right = x;
        }
        
        if (B != NULL) B -> parent = g;
        
        if (C != NULL) C -> parent = p;
    }
}

void SplayTree::zig_zag(TreeNode *x)
{
    TreeNode *p = x -> parent;
    TreeNode *g = p -> parent;
    if (p -> right == x)
    {
        TreeNode *A = p -> left;
        TreeNode *B = x -> left;
        TreeNode *C = x -> right;
        TreeNode *D = g -> right;
        
        x -> parent = g -> parent;
        x -> left = p;
        x -> right = g;
        
        p -> parent = x;
        p -> right = B;
        
        g -> parent = x;
        g -> left = C;
        
        if (x -> parent != NULL)
        {
            if (x -> parent -> left == g) x -> parent -> left = x;
            else x -> parent -> right = x;
        }
        
        if (B != NULL) B -> parent = p;
        
        if (C != NULL) C -> parent = g;
    }
    else
    {
        TreeNode *A = g -> left;
        TreeNode *B = x -> left;
        TreeNode *C = x -> right;
        TreeNode *D = p -> right;
        
        x -> parent = g -> parent;
        x -> left = g;
        x -> right = p;
        
        p -> parent = x;
        p -> left = C;
        
        g -> parent = x;
        g -> right = B;
        
        if (x -> parent != NULL)
        {
            if (x -> parent -> left == g) x -> parent -> left = x;
            else x -> parent -> right = x;
        }
        
        if (B != NULL) B -> parent = g;
        
        if (C != NULL) C -> parent = p;
    }
}

void SplayTree::splay(TreeNode *x)
{
    while (x -> parent != NULL)
    {
        TreeNode *p = x -> parent;
        TreeNode *g = p -> parent;
        if (g == NULL) zig(x);
        else if (g -> left == p && p -> left == x) zig_zig(x);
        else if (g -> right == p && p -> right == x) zig_zig(x);
        else zig_zag(x);
    }
    this -> root = x;
}

SplayTree::SplayTree()
{
    this -> root = NULL;
}

SplayTree::SplayTree(TreeNode *rt)
{
    this -> root = rt;
}

TreeNode* SplayTree::find(int x)
{
    TreeNode *ret = NULL;
    TreeNode *curr = this -> root;
    TreeNode *prev = NULL;
    while (curr != NULL)
    {
        prev = curr;
        if (x < curr -> key) curr = curr -> left;
        else if (x > curr -> key) curr = curr -> right;
        else
        {
            ret = curr;
            break;
        }
    }
    if (ret != NULL) splay(ret);
    else if (prev != NULL) splay(prev);
    return ret;
}

void SplayTree::insert(int x)
{
    if (root == NULL)
    {
        root = new TreeNode(x);
        return;
    }
    TreeNode *curr = this -> root;
    while (curr != NULL)
    {
        if (x < curr -> key)
        {
            if (curr -> left == NULL)
            {
                TreeNode *newNode = new TreeNode(x);
                curr -> left = newNode;
                newNode -> parent = curr;
                splay(newNode);
                return;
            }
            else curr = curr -> left;
        }
        else if (x > curr -> key)
        {
            if (curr -> right == NULL)
            {
                TreeNode *newNode = new TreeNode(x);
                curr -> right = newNode;
                newNode -> parent = curr;
                splay(newNode);
                return;
            }
            else curr = curr -> right;
        }
        else
        {
            splay(curr);
            return;
        }
    }
}

TreeNode* subtree_max(TreeNode *subRoot)
{
    TreeNode *curr = subRoot;
    while (curr -> right != NULL) curr = curr -> right;
    return curr;
}

TreeNode* subtree_min(TreeNode *subRoot)
{
    TreeNode *curr = subRoot;
    while (curr -> left != NULL) curr = curr -> left;
    return curr;
}

void SplayTree::Delete(int x)
{
    TreeNode *del = find(x);
    if (del == NULL)
    {
        return;
    }
    TreeNode *L = del -> left;
    TreeNode *R = del -> right;
    if (L == NULL && R == NULL)
    {
        this -> root = NULL;
    }
    else if (L == NULL)
    {
        TreeNode *M = subtree_min(R);
        splay(M);
    }
    else if (R == NULL)
    {
        TreeNode *M = subtree_max(L);
        splay(M);
    }
    else
    {
        TreeNode *M = subtree_max(L);
        splay(M);
        M -> right = R;
        R -> parent = M;
    }
    delete del;
}

void printTree(TreeNode *root, bool brackets)
{
    if (root == NULL)
    {
        if (brackets) printf("{}");
        return;
    }
    if (brackets) printf("{");
    if (root -> left != NULL) printTree(root -> left, brackets);
    if (root != NULL) printf(" %c ", root -> key);
    if (root -> right != NULL) printTree(root -> right, brackets);
    if (brackets) printf("}");
}

void SplayTree::inOrderPrint(bool brackets)
{
    printTree(this -> root, brackets);
}



void SplayTree::tree_Preorder(TreeNode* node){
	
	if (node != NULL)
	{
		fout << node->key;

		if(!(node->left==NULL && node->right==NULL))
		{
			fout << "(";
			tree_Preorder(node->left);
			fout << " ";
			tree_Preorder(node->right);
			fout<< ")";		
		}		
	}
	else 
	{
		fout<<"-";
	}
};

TreeNode* SplayTree::show_root(){
	return root;
};

void SplayTree::output_setting(const char* path,int row)
{
	if (row == 1) fout.open(path, ios::trunc);
	else
	{
		fout.close();
		fout.open(path, ios::app);
		fout<< endl;		
	}

}

void SplayTree::tree_Inorder(TreeNode* node,int level){
	if (node!=NULL)
	{
		level++;
		tree_Inorder(node->left,level);
		level=level-1;
		
		X.push_back(node->key);
		Y.push_back(level);
		
		level++;
		tree_Inorder(node->right,level);
		level=level-1;			
	}
}
void SplayTree::print_tree(int row){
	int get_length(int x);
	const char* path;	
	path = "STree.txt";
	fout.close();
	if (row == 1) fout.open(path, ios::trunc);
	else
	{
		fout.close();
		fout.open(path, ios::app);
//		fout<< endl;		
	}
	int maxValue = *max_element(Y.begin(),Y.end()); // include algorithm
	for (int i=0;i<=maxValue;i++)
	{
		for (int j=0;j<X.size();j++)
		{
			if (Y[j]==i)
			{
				
				fout <<X[j];
				for(int space=0;space<3-get_length(X[j]);space++) fout <<" ";
				
			}
			else fout << "   ";
		}	
		fout << "\n";
	}
	// boundary
	path = "STree_boundary.txt";
	fout.close();
	if (row == 1) fout.open(path, ios::trunc);
	else
	{
		fout.close();
		fout.open(path, ios::app);
		fout<< endl;		
	}
	for (int i=0;i<=maxValue;i++)
	{
		for (int j=0;j<X.size();j++)
		{
			if (Y[j]==i)
			{
				fout <<X[j]<<" ";;
				break;
			}
		}	
	}
	X.clear();
	Y.clear();
}

//---------------------------------

int main(){
	std::ifstream infile;
	infile.open("input.txt");	
	int num ;
	vector <int> vec;
	const char* path;
	const char* path_s;
	int level=0;
	int row = 0;

//	ofstream file;
//	file.open("BTree_PRep.txt",ios::trunc);
//	file.close();
	while(infile >> num)
	{		

		vec.push_back(num);
		char get = infile.get();
//		cout <<"."<< num << "-"<< (get=='\n') <<infile.eof() << "..";
		if ((get=='\n') || infile.eof())
		{
//			cout<<"in if-";
			row++;
			BST* binary_tree = new BST();
			SplayTree* splay_tree = new SplayTree();
			
			
			
//			cout<< "oookkk";
//			cout <<"vec:" <<vec.size();
			for(int i=0;i<vec.size();i++)
			{
//				cout<< "iiinnn";
				binary_tree->Insert_Public(vec[i]);
				splay_tree->insert(vec[i]);
			}

			Node* root = binary_tree->show_root();
//			cout <<"show key root:"<< root->Key << endl;
			path = "BTree_PRep.txt";
			path_s = "STree_PRep.txt";
			binary_tree->output_setting(path,row);
			binary_tree->tree_Preorder(root);
			
			TreeNode* splay_root = splay_tree->show_root();
			splay_tree->output_setting(path_s,row);
			splay_tree->tree_Preorder(splay_root);
			level=0;
			binary_tree->level_initial();
			binary_tree->tree_Inorder(root);
			binary_tree->print_tree(row);
			splay_tree->tree_Inorder(splay_root,level);
			splay_tree->print_tree(row);

			
			
			binary_tree->~BST();
			
			splay_tree->~SplayTree();
			
			vec.clear();
//			cout <<endl <<"vectorclr";
			
			
		}
		
	}
	infile.close();	
	system("pause");
	return 0;
}


