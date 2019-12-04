#include <pthread.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
//#include <bits/stdc++.h> 

using namespace std;
enum COLOR {Red, Black};

//initializing the node struct
struct Node
{
    int data;
    bool color;
    Node *left, *right, *parent;

    Node(){
        this->data = data;
        this->color = Red;
        right = NULL;
        left = NULL;
        parent = NULL;
    }
};

class TreeBuild{    
    private:
        Node *root;
    public:
        //This is the constructor
        TreeBuild(){
            root = NULL;
        }

    //method to search for a node
    bool searchNode(int data){
    
        Node *curr = root;
        while (curr != NULL) {
            if (curr->data == data) {
                return true;
            }
            if (curr->data < data) {
                curr = curr->right;
            }
            if (curr->data > data){
                curr = curr->left;
            }
            
        }
        return false;
    }

    //finding the node to replace the node to be deleted
    Node* replaceNode(Node *rep){
        //if node to be deleted has 2 children
        if(rep->left != NULL && rep->right != NULL){
            Node* temp;
            temp = rep->right;
            while(temp->left != NULL){
                temp = temp->left;
            }
            rep = temp;
            return rep;
        }
        //if node has 2 leaves(NIL) for children
        if(rep->left == NULL && rep->right == NULL){
            return NULL;
        }

        //if node only has one child, and one leaf
        if(rep->left != NULL){
            return rep->left;
        }
        else{
            return rep->right;
        }
    }

    //method to delete a node
    Node* deleteNote(int data){
       Node *delNode;
       delNode->data = data;
       
       
        
    }

    //method to switch a node to the left to keep Red Back properties
    void LSwitch(Node *node, Node *node1){
            Node *right = node1->right;
            node1->right = right->left;
            if(node1->right != NULL){
                node1->right->parent = node1;
            }
            //moving up
            right->parent = node1->parent;
            if(node1->parent == NULL){
                node = right;
            }
            else if(node1->parent->left == node1){
                node1->parent->left = right;
            }
            else{
                node1->parent->right = right;
            }
            right->left = node1;
            node1->parent = right;
    }

    //method to switch a node to the right to keep Red Back properties
    void RSwitch(Node *node, Node *node1){
            Node *left = node1->left;
            node1->left = left->right;
            if(node1->left != NULL){
                node1->left->parent = node1;
            }
            //moving up
            left->parent = node1->parent;
            if(node1->parent == NULL){
                node = left;
            }
            else if(node1->parent->right == node1){
                node1->parent->left = left;
            }
            else{
                node1->parent->right = left;
            }
            left->right = node1;
            node1->parent = left;
    }

    //Method to insert Node data1 in parameter into tree
    Node* insertNode(int data1){
        Node *node = root;
        Node *newNode;
        newNode->data = data1;
        if(node == NULL){
            return newNode;
        }
        else{
            int num = node->data;  
            bool insert = false; 
            while(!insert){     
                //percolating node down to its position
                if(data1 < num){
                    node = node->left;
                    if(node == NULL){
                        node->parent->left = newNode;
                    }
                }
                else if(data1 > num){
                    node = node->right;
                    if(node == NULL){
                        node->parent->right = newNode;
                    }
                }
                    
            }
        }

        //might not be right here
        refactorTree(root, node);
        return node;

    }
    //method to make sure the tree follows all Red Black Tree Properties
    Node* refactorTree(Node *node, Node *node2){
        Node *parent_ = NULL;
        Node *grandparent = NULL;

        //while there is still fixing to be done within the tree
        while((node2->color != Black) && (node2 != node) && (node2->parent->color != Black)){

                parent_ = node2->parent;
                grandparent = node2->parent->parent;

                //checking which position the parent is in (left or right)
                if(grandparent->left == parent_){
                    Node *node3 = grandparent->right;
                    
                    //node 3 is Red
                    if((node3->color == Red) && (node3 != NULL)){
                        node3->color = Black;
                        parent_->color = Black;
                        grandparent->color = Red;
                        node2 = grandparent;
                    }

                    else{
                        //first case if uncle is not red
                        if(node2 == parent_->right){
                            LSwitch(node, parent_);
                            node2 = parent_;
                            parent_= node2->parent;
                        } 

                        //second case
                        else if(node2 == parent_->left){
                            RSwitch(node, grandparent);
                            Node *Dummy;
                            Dummy->color = parent_->color;
                            parent_->color = grandparent->color;
                            grandparent->color = Dummy->color;
                            node2 = parent_;
                        }
                    }
                }
                //When the parent of node2 is in the right position of it's parent
                else{
                    Node *node4 = grandparent->left;

                    //node 4 is red
                    if(node4->color == Red && node4 != NULL){
                        node4->color = Black;
                        parent_->color = Black;
                        grandparent->color = Red;
                        node2 = grandparent;
                    }
                    //node 4 is not red
                    else{
                        //first case if node 2 is on the right of its parent
                        if(node2 == parent_->right){
                            LSwitch(node, grandparent);
                            Node *Dummy;
                            Dummy->color = parent_->color;
                            parent_->color = grandparent->color;
                            grandparent->color = Dummy->color;
                            node2 = parent_;
                        }
                        else if(node2 = parent_->left){
                            RSwitch(node, parent_);
                            node2 = parent_;
                            parent_ = node2->parent;
                        }
                    }

                }
        }
        node->color = Black;
    }

    void parseInput(string file){
        std::vector<string> commands;
        string line;
        ifstream inputFile(file);
        if(inputFile.is_open){
            while(!EOF){
                getline(inputFile, line);
                commands.push_back(line);
            }
        }
    }
};

int main(char *file_ptr){
        TreeBuild Tree;
        
        
}