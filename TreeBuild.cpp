#include <pthread.h>

using namespace std;
enum COLOR {Red, Black};

//initializing the node struct
struct Node
{
    int data;
    bool color;
    Node *left, *right, *parent;

    Node(int data){
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
            root = NULL;
        }

    //Method to insert node in parameter into tree
    void insertNode(Node *node){
        if(root == NULL){
            root = node;
            return;
        }
        

    }



    int main(char *file_ptr){
        TreeBuild Tree;
        
    }

};