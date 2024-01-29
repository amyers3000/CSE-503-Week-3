//
//  tree.cpp
//  CSE 503 Week 3
//
//  Created by Alex Myers on 1/28/24.
//

#include <iostream>
#include <cstddef>

using std::cout;
using std::endl;

class Node {
    int value;
public:
    Node* left;       // left child
    Node* right;      // right child
    Node* p;          // parent
    Node(int data) {
        value = data;
        left = NULL;
        right = NULL;
        p  = NULL;
    }
    ~Node() {
    }
    int d() {
        return value;
    }
    void print() {
        std::cout << value << std::endl;
        
    }
    void setValue(int newValue) {
        value = newValue;
    }
    
};

void insert(Node *insert_node, Node * &tree_root);
void traverseTree(Node *t);
void delete_node(int value, Node * &tree_root);
Node * findMin(Node *t);
bool search(int value, Node *tree_root);


int main(int argc, const char * argv[])
{
    Node* root = nullptr;
    
    insert(new Node(3), root);
    insert(new Node(2), root);
    insert(new Node(5), root);
    insert(new Node(6), root);
    insert(new Node(10), root);
    insert(new Node(4), root);
    insert(new Node(7), root);
    insert(new Node(8), root);
    insert(new Node(11), root);
    insert(new Node(15), root);
    insert(new Node(13), root);

    std::cout << "Binary Search Tree after insertion" << endl;
    traverseTree(root);
    
    delete_node(5, root);
    delete_node(8, root);
    
    std::cout << "Binary Search Tree after insertion" << endl;
    traverseTree(root);
    
    std::cout << "Binary Search Tree contains 7: " << (search(7, root) ? "true": "false")<< endl;
    std::cout << "Binary Search Tree contains 5: " << (search(5, root) ? "true": "false") << endl;
    
}

void insert(Node *insert_node, Node *&tree_root) {
    if (tree_root == nullptr)
        tree_root = insert_node;
    else if (insert_node->d() < tree_root->d())
        if (tree_root->left)
            insert(insert_node, tree_root->left);
        else {
            tree_root->left = insert_node;
            insert_node->p = tree_root;
        }
    else if (insert_node->d() > tree_root->d())
        if (tree_root->right)
            insert(insert_node, tree_root->right);
        else {
            tree_root->right = insert_node;
            insert_node->p = tree_root;
        }
    else
        ;
}

void traverseTree(Node *t){
    if( t != NULL)
    {
        t->print();
        traverseTree(t->left);
        traverseTree(t->right);
    }
}

Node * findMin(Node *t){
    if(t == nullptr)
        return NULL;
    if(t->left == nullptr)
        return t;
    return findMin(t->left);
}


void delete_node(int value, Node *&tree_root) {
    if (tree_root == nullptr)
        return;

    if (value < tree_root->d())
        delete_node(value, tree_root->left);
    else if (value > tree_root->d())
        delete_node(value, tree_root->right);
    else {
        if (tree_root->left != nullptr && tree_root->right != nullptr) {
            tree_root->setValue(findMin(tree_root->right)->d());
            delete_node(tree_root->d(), tree_root->right);
        } else {
            Node *oldNode = tree_root;
            tree_root = (tree_root->left != nullptr) ? tree_root->left : tree_root->right;

            if (tree_root != nullptr) {
                tree_root->p = oldNode->p;
            }

            delete oldNode;
        }
    }
}

bool search(int value, Node *tree_root){
    if(tree_root == nullptr)
        return false;
    else if(value < tree_root->d())
        return search(value, tree_root->left);
    else if(value > tree_root->d())
        return search(value, tree_root->right);
    else
        return true;
}
