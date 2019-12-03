#include <pthread.h>

using namespace std;
enum COLOR {Red, Black};
class TreeBuild{

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
    




    int main(char *file_ptr){
        
        
    }

};