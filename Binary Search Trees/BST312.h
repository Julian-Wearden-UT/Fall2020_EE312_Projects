
/*  BST312.h
  EE312 Fall 2020

  a simple implementation of a binary search tree


*/

#ifndef BST_312_H
#define BST_312_H

#include <cstdlib>  // Provides size_t
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template<class ItemType>
class BST_312 {
public:

    BST_312();

    //Copy constructor
    BST_312(const BST_312& src);

    ~BST_312();

/****************************
makeEmpty

Function: Removes all the items from the BST.
Preconditions: BST has been initialized
Postconditions: All the items have been removed
*****************************/
    void makeEmpty();

/****************************
isEmpty

Function: Checks to see if there are any items in the BST.
Preconditions: BST has been initialized
Postconditions: Returns true if there are no items in the BST, else false.
*****************************/
    bool isEmpty() const;

/****************************
isFull

Function: Determines if you have any more room to add items to the BST
Preconditions: BST has been initialized
Postconditions: Returns true if there is no more room to add items, else false
*****************************/
    bool isFull() const;

/****************************
insertItem

Function: Adds newItem to the BST.
Preconditions: BST has been initialized and is not full.
Postconditions: newItem is in the proper position for a BST.
*****************************/
    void insertItem(const ItemType&);

/****************************
deleteItem

Function: Removes target from BST.
Preconditions: BST has been initialized.
Postconditions: If found, element has been removed from BST.
*****************************/
    void deleteItem(const ItemType& newItem);

/****************************
countNodes

Function: Counts the number of nodes in the BST
Preconditions: BST has been initialized.
Postconditions: returns the number of nodes in the BST
*****************************/
    int countNodes();

/****************************
preOrderTraversal

Function: Returns the preOrder (Node, Left, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> preOrderTraversal() const;

/****************************
inOrderTraversal

Function: Returns the inOrder (Left, Node, Right) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> inOrderTraversal();

/****************************
postOrderTraversal

Function: returns the postOrder (Left, Right, Node) as a vector of ItemTypes
Preconditions: BST has been initialized.
Postconditions: none
*****************************/
    vector<ItemType> postOrderTraversal();

/********************
 isItemInTree

Function: Determines if a given Item is in tree.
Preconditions: BST has been initialized.
Postconditions: none
*****************************/

    bool isItemInTree(const ItemType& item);

private:
    struct TreeNode {
        ItemType data;
        TreeNode* left;
        TreeNode* right;
    };

    TreeNode* root;


    void insertItem(TreeNode*& t, const ItemType& newItem);
    void inOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    int countNodes(TreeNode* t) const;
    void deleteNode(TreeNode*& node);
    void makeEmpty(TreeNode*& t);
    void deleteItem(TreeNode*& t, const ItemType& newItem);
    void getPredecessor(TreeNode* t, ItemType& data);
    void preOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void postOrderTraversal(TreeNode* t,vector<ItemType>& result) const;
    void copyTree(TreeNode*& copy, const TreeNode* originalTree);
    TreeNode* createNode(const ItemType& newItem);

};

/*******************************
//Function implementations
********************************/


template<class ItemType>
BST_312<ItemType>::BST_312 ()
{
    root = NULL;
}

template<class ItemType>
BST_312<ItemType>::BST_312(const BST_312& src)
{
    copyTree(root, src.root);
}

template<class ItemType>
BST_312<ItemType>::~BST_312()
{
    makeEmpty();
}

template<class ItemType>
void BST_312<ItemType>::copyTree(TreeNode*& copy, const TreeNode* originalTree)
{
    if (originalTree == NULL)
        copy = NULL;
    else
    {
        copy = new TreeNode;
        copy->data = originalTree->data;

        copyTree(copy->left, originalTree->left);
        copyTree(copy->right, originalTree->right);
    }
}

template<class ItemType>
void BST_312 <ItemType>::deleteNode(TreeNode*& t)
{
    ItemType info;
    TreeNode* tempPtr;

    tempPtr = t;

    if (t->left == NULL)
    {
        t = t->right;
        delete tempPtr;
    }
    else if (t->right == NULL)
    {
        t = t->left;
        delete tempPtr;
    }
    else
    {
        getPredecessor(t->left, info);
        t->data = info;
        deleteItem(t->left, info);
    }
}

//find largest in left subtree
template<class ItemType>
void BST_312 <ItemType>::getPredecessor(TreeNode* t, ItemType& data)
{
    while (t->right != NULL)
        t = t->right;
    data = t->data;
}

template<class ItemType>
void BST_312 <ItemType>::deleteItem(TreeNode*& t, const ItemType& newItem)
{
    if (t == NULL)
        return;
    else if (newItem < t->data)
        deleteItem(t->left, newItem);
    else if (newItem > t->data)
        deleteItem(t->right, newItem);
    else
        deleteNode(t);
}

template<class ItemType>
void BST_312 <ItemType>::deleteItem(const ItemType& newItem)
{
    deleteItem(root, newItem);

}

template<class ItemType>
void BST_312 <ItemType>::makeEmpty(TreeNode*& t)
{
    //YOUR CODE GOES HERE
    if(t != NULL){  //While stuff in tree
        makeEmpty(t->left); //Recursively delete left
        makeEmpty(t->right);    //Recursively delete right
        deleteNode(t);
        t = NULL;   //Set to null
    }
}

template<class ItemType>
void BST_312 <ItemType>::makeEmpty()
{
    makeEmpty(root);
    root = NULL;
}

template<class ItemType>
bool BST_312 <ItemType>::isEmpty() const
{
    return root == NULL;
}

template<class ItemType>
bool BST_312 <ItemType>::isFull() const
{
    try
    {
        TreeNode* temp = new TreeNode;
        delete temp;
        return false;
    }
    catch (std::bad_alloc)
    {
        return true;
    }
}

template<class ItemType>
void BST_312 <ItemType>::insertItem(TreeNode*& t, const ItemType& newItem)
{
    //YOUR CODE GOES HERE
    if(isFull()){return;}   //Done
    else {
        if (t != NULL) {
            if (newItem == t->data) { return; } //No duplicates
            else if (newItem < t->data) { insertItem(t->left, newItem); }  //Go left
            else { insertItem(t->right, newItem); }     //Go right
        }
        else{t = createNode(newItem);}  //When t == NULL insert node
    }
}


template<class ItemType>
void BST_312 <ItemType>::insertItem(const ItemType& newItem)
{
    //YOUR CODE GOES HERE
    if (isFull()){return;}
    else{insertItem(root, newItem);}    //Start at root
}

//Creates node for insertItem
//Precondition: Memory must be available
//Postcondition: None
template<class ItemType>
typename BST_312<ItemType>::TreeNode* BST_312<ItemType>::createNode(const ItemType& newItem)
{
    auto* temp = new TreeNode;  //Malloc space
    temp->data = newItem;   //Assign new node with appropriate values
    temp->left = NULL;
    temp->right = NULL;
    return temp;        //Return new node
}

template<class ItemType>
int BST_312 <ItemType>::countNodes(TreeNode* t) const
{
    //YOUR CODE GOES HERE
    vector<ItemType> result;    //Create vector
    result = preOrderTraversal();   //Store preOrderTraversal in vector
    return result.size();   //Return size of vector
}

template<class ItemType>
int BST_312 <ItemType>::countNodes()
{
    //YOUR CODE GOES HERE
    return countNodes(root);
}

template<class ItemType>
void BST_312 <ItemType>::preOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    //YOUR CODE GOES HERE
    if (t == NULL){return;}
    else{
        result.push_back(t->data);  //Store item in vector
        preOrderTraversal(t->left, result);
        preOrderTraversal(t->right, result);
    }

}

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::preOrderTraversal() const
{
    //YOUR CODE GOES HERE
    vector<ItemType> result;    //Create vector
    preOrderTraversal(root, result);    //Start at root node
    return result;

}

template<class ItemType>
void BST_312 <ItemType>::inOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    //YOUR CODE GOES HERE
    if (t == NULL){return;} //Done
    else{
        inOrderTraversal(t->left, result);
        result.push_back(t->data);  //Add item to vector
        inOrderTraversal(t->right, result);
    }

}

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::inOrderTraversal()
{
    //YOUR CODE GOES HERE
    vector<ItemType> result;    //Create vector
    inOrderTraversal(root, result); //Start at root node
    return result;
}

template<class ItemType>
void BST_312 <ItemType>::postOrderTraversal(TreeNode* t,vector<ItemType>& result) const
{
    //YOUR CODE GOES HERE
    if (t == NULL){return;} //Done
    else{
        postOrderTraversal(t->left, result);
        postOrderTraversal(t->right, result);
        result.push_back(t->data);  //Add item to vector
    }
}

template<class ItemType>
vector<ItemType> BST_312 <ItemType>::postOrderTraversal()
{
    //YOUR CODE GOES HERE
    vector<ItemType> result;    //Create vector
    postOrderTraversal(root, result);   //Start at root node
    return result;
}

template<class ItemType>
bool BST_312 <ItemType>::isItemInTree(const ItemType& item)
{
  //YOUR CODE GOES HERE
  vector<ItemType> result;  //Create vector
  result = preOrderTraversal(); //Store vector returned
  return find(result.begin(), result.end(), item) != result.end();  //Iterate through vector to find item

}
#endif

