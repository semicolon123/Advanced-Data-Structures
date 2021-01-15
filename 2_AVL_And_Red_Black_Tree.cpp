#include<bits/stdc++.h> 
using namespace std; 

class Node 	// An AVL tree node
{ 
	public: 
			int key; 
			Node *left; 
			Node *right; 
			int height; 
}; 

int max(int a, int b); 		// To get maximum of two integers 

int height(Node *N) 		// To get the height of the tree 
{ 
	if (N == NULL) 
		return 0; 
	return N->height; 
} 

int max(int a, int b) 		// to get maximum of two integers 
{ 
	return (a > b)? a : b; 
} 

Node* newNode(int key) 	/* Allocates a new node with the given key and NULL left and right pointers. */
{ 
	Node* node = new Node(); 
	node->key = key; 
	node->left = NULL; 
	node->right = NULL; 
	node->height = 1; // new node is initially added at leaf 
	return(node); 
} 

Node *rightRotate(Node *y) 	// Function to right rotate subtree rooted with y 
{ 
	Node *x = y->left; 
	Node *T2 = x->right; 

	// Perform rotation 
	x->right = y; 
	y->left = T2; 

	// Update heights 
	y->height = max(height(y->left), 
					height(y->right)) + 1; 
	x->height = max(height(x->left), 
					height(x->right)) + 1; 

	// Return new root 
	return x; 
} 

Node *leftRotate(Node *x) 		//Function to left rotate subtree rooted with x 
{ 
	Node *y = x->right; 
	Node *T2 = y->left; 

	// Perform rotation 
	y->left = x; 
	x->right = T2; 

	// Update heights 
	x->height = max(height(x->left),	 
					height(x->right)) + 1; 
	y->height = max(height(y->left), 
					height(y->right)) + 1; 

	// Return new root 
	return y; 
} 

int getBalance(Node *N) 		// Get Balance factor of node N 
{ 
	if (N == NULL) 
		return 0; 
	return height(N->left) - height(N->right); 
} 

Node* insert(Node* node, int key) 	//Recursive function to insert a key in the subtree rooted with node and 
									// returns the new root of the subtree.
{ 
	/* 1. Perform the normal BST insertion */
	if (node == NULL) 
		return(newNode(key)); 

	if (key < node->key) 
		node->left = insert(node->left, key); 
	else if (key > node->key) 
		node->right = insert(node->right, key); 
	else // Equal keys are not allowed in BST 
		return node; 

	/* 2. Update height of this ancestor node */
	node->height = 1 + max(height(node->left), 
						height(node->right)); 

	// 3. Get the balance factor of this ancestor node to check whether this node became unbalanced
	int balance = getBalance(node); 

	// If this node becomes unbalanced, then there are 4 cases 

	// Left Left Case 
	if (balance > 1 && key < node->left->key) 
		return rightRotate(node); 

	// Right Right Case 
	if (balance < -1 && key > node->right->key) 
		return leftRotate(node); 

	// Left Right Case 
	if (balance > 1 && key > node->left->key) 
	{ 
		node->left = leftRotate(node->left); 
		return rightRotate(node); 
	} 
	// Right Left Case 
	if (balance < -1 && key < node->right->key) 
	{ 
		node->right = rightRotate(node->right); 
		return leftRotate(node); 
	} 
	/* return the (unchanged) node pointer */
	return node; 
} 

void printGivenLevel(Node *root, int level) 
{ 
    if (root == NULL) 
        return; 
    if (level == 1) 
        cout << root->key << " "; 
    else if (level > 1) 
    { 
        printGivenLevel(root->left, level-1); 
        printGivenLevel(root->right, level-1); 
    } 
}
void printLevelOrder(Node *root) 
{ 
    int h = height(root); 
    int i; 
    for (i = 1; i <= h; i++) 
        printGivenLevel(root, i); 
} 

enum Color {RED, BLACK}; 

struct NodeRedBlack
{ 
	int data; 
	bool color; 
	NodeRedBlack *left, *right, *parent; 
	NodeRedBlack(int data) 		// Constructor 
	{ 
	this->data = data; 
	left = right = parent = NULL; 
	this->color = RED; 
	} 
}; 

class RBTree 			// Class to represent Red-Black Tree 
{ 
	private: 
		NodeRedBlack *root; 
	protected: 
		void rotateLeft(NodeRedBlack *&, NodeRedBlack *&); 
		void rotateRight(NodeRedBlack *&, NodeRedBlack *&); 
		void fixViolation(NodeRedBlack *&, NodeRedBlack *&); 
	public: 
		// Constructor 
		RBTree() { root = NULL; } 
		void insert(const int &n); 
		void inorder(); 
		void levelOrder(); 
}; 


void inorderHelper(NodeRedBlack *root) 		// Function to do inorder traversal 
{ 
	if (root == NULL) 
		return; 

	inorderHelper(root->left); 
	cout << root->data << " "; 
	inorderHelper(root->right); 
} 

NodeRedBlack* BSTInsert(NodeRedBlack* root, NodeRedBlack *pt)  //function to insert a new node with given key in BST
{ 	
	if (root == NULL) 	//If the tree is empty, return a new node 
	return pt; 

	if (pt->data < root->data)   	//Otherwise, recur down the tree */
	{ 
		root->left = BSTInsert(root->left, pt); 
		root->left->parent = root; 
	} 
	else if (pt->data > root->data) 
	{ 
		root->right = BSTInsert(root->right, pt); 
		root->right->parent = root; 
	} 
	
	return root;    //return the (unchanged) node pointer 
} 

void levelOrderHelper(NodeRedBlack *root) 		//Function to do level order traversal 
{ 
	if (root == NULL) 
		return; 

	std::queue<NodeRedBlack *> q; 
	q.push(root); 

	while (!q.empty()) 
	{ 
		NodeRedBlack *temp = q.front(); 
		cout << temp->data << " "; 
		q.pop(); 

		if (temp->left != NULL) 
			q.push(temp->left); 

		if (temp->right != NULL) 
			q.push(temp->right); 
	} 
} 

void RBTree::rotateLeft(NodeRedBlack *&root, NodeRedBlack *&pt) 
{ 
	NodeRedBlack *pt_right = pt->right; 

	pt->right = pt_right->left; 

	if (pt->right != NULL) 
		pt->right->parent = pt; 

	pt_right->parent = pt->parent; 

	if (pt->parent == NULL) 
		root = pt_right; 

	else if (pt == pt->parent->left) 
		pt->parent->left = pt_right; 

	else
		pt->parent->right = pt_right; 

	pt_right->left = pt; 
	pt->parent = pt_right; 
} 

void RBTree::rotateRight(NodeRedBlack *&root, NodeRedBlack *&pt) 
{ 
	NodeRedBlack *pt_left = pt->left; 

	pt->left = pt_left->right; 

	if (pt->left != NULL) 
		pt->left->parent = pt; 

	pt_left->parent = pt->parent; 

	if (pt->parent == NULL) 
		root = pt_left; 

	else if (pt == pt->parent->left) 
		pt->parent->left = pt_left; 

	else
		pt->parent->right = pt_left; 

	pt_left->right = pt; 
	pt->parent = pt_left; 
} 

// This function fixes violations 
// caused by BST insertion 
void RBTree::fixViolation(NodeRedBlack *&root, NodeRedBlack *&pt) 
{ 
	NodeRedBlack *parent_pt = NULL; 
	NodeRedBlack *grand_parent_pt = NULL; 

	while ((pt != root) && (pt->color != BLACK) && 
		(pt->parent->color == RED)) 
	{ 
		parent_pt = pt->parent; 
		grand_parent_pt = pt->parent->parent; 

		/* Case A: Parent of pt is left child of Grand-parent of pt */
		if (parent_pt == grand_parent_pt->left) 
		{ 

			NodeRedBlack *uncle_pt = grand_parent_pt->right; 

			/* Case A1: The uncle of pt is also red Only Recoloring required */
			if (uncle_pt != NULL && uncle_pt->color == RED) 
			{ 
				grand_parent_pt->color = RED; 
				parent_pt->color = BLACK; 
				uncle_pt->color = BLACK; 
				pt = grand_parent_pt; 
			} 

			else
			{ 
				/* Case A2: Pt is right child of its parent Left-rotation required */
				if (pt == parent_pt->right) 
				{ 
					rotateLeft(root, parent_pt); 
					pt = parent_pt; 
					parent_pt = pt->parent; 
				} 

				/* Case A3: pt is left child of its parent Right-rotation required */
				rotateRight(root, grand_parent_pt); 
				swap(parent_pt->color, grand_parent_pt->color); 
				pt = parent_pt; 
			} 
		} 

		/* Case B: Parent of pt is right child of Grand-parent of pt */
		else
		{ 
			NodeRedBlack *uncle_pt = grand_parent_pt->left; 

			/* Case B1: The uncle of pt is also red only Recoloring required */
			if ((uncle_pt != NULL) && (uncle_pt->color == RED)) 
			{ 
				grand_parent_pt->color = RED; 
				parent_pt->color = BLACK; 
				uncle_pt->color = BLACK; 
				pt = grand_parent_pt; 
			} 
			else
			{ 
				/* Case B2: pt is left child of its parent Right-rotation required */
				if (pt == parent_pt->left) 
				{ 
					rotateRight(root, parent_pt); 
					pt = parent_pt; 
					parent_pt = pt->parent; 
				} 

				/* Case B3: Pt is right child of its parent Left-rotation required */
				rotateLeft(root, grand_parent_pt); 
				swap(parent_pt->color, grand_parent_pt->color); 
				pt = parent_pt; 
			} 
		} 
	} 

	root->color = BLACK; 
} 

void RBTree::insert(const int &data) 	// Function to insert a new node with given data 
{ 
	NodeRedBlack *pt = new NodeRedBlack(data); 
	root = BSTInsert(root, pt); 		// Do a normal BST insert 

	fixViolation(root, pt); 		// fix Red Black Tree violations 
} 

void RBTree::levelOrder() { levelOrderHelper(root); } 

// Driver Code 
int main() 
{ 
	Node *root = NULL; 
	RBTree tree; 
	int n = 0; //number of elements in the tree;

	cout<<"Enter how many elements you want to insert:";
	cin>>n;

	int value = 0;

	for(int i=0;i<n;i++){
		cout<<"Enter value "<<i<<":";
		cin>>value;
		root = insert(root,value);
		tree.insert(value); 
	}
	
	cout << "Level Order Traversal of Created AVL Tree\n"; 
	printLevelOrder(root); 
	
	cout << "\n\nLevel Order Traversal of Created Red Black Tree\n"; 
	tree.levelOrder(); 
	return 0; 
} 