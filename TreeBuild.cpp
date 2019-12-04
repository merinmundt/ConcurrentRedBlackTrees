#include <pthread.h>

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
        Node root;
    public:
        //This is the constructor
        TreeBuild(){
            root.data = NULL;
        }
        


    //Method to insert node in parameter into tree
    Node* insertNode(Node *node, int data1){
        if(root.data == NULL){
            root = *node;
            root.color = Black;
            return;
        }
        else{
            int num = node->data;        
            //percolating node down to its position
            if(data1 < num){
                node->left = insertNode(node->left, data1); 
                node->left->parent = node;
            }
            else if(data1 > num){
                node->right = insertNode(node->right, data1);
                node->right->parent = node;
            }
        }
        
        return node;

    }
    //method to make sure the tree follows all Red Black Tree Properties
    Node* refactorTree(Node *node, Node *node2){
        Node *parent_ = NULL;
        Node *grandparent = NULL;

        //while there is still fixing to be done within the tree
        while((node2->color != Black) && (node2 != node) && (node2->parent->color != Black)){



        }
    }



};

int main(char *file_ptr){
        TreeBuild Tree;
        
}