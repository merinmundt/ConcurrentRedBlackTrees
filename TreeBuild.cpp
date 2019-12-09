#include <pthread.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <thread>
#include <queue>
#include <semaphore.h>
#include <chrono> 
//#include <bits/stdc++.h> 

using namespace std;
using namespace std::chrono;
enum COLOR {Red, Black};
const std::string WHITESPACE = " \n\r\t\f\v";
queue <string> readQueue;
queue<string> writeQueue;
sem_t mute;
sem_t wrtieLock;
ofstream myfile;
//TreeBuild Tree;

//initializing the node struct
struct Node
{
    int data;
    bool color;
    Node *left, *right, *parent;

    Node(int k){
        this->data = k;
        this->color = Red;
        right = NULL;
        left = NULL;
        parent = NULL;
    }
};
Node *NIL;
Node *root;
class TreeBuild{    
    private:
        Node *root;
        Node *NIL;
    public:
        //This is the constructor
        TreeBuild(){
            NIL = new Node(0);
            NIL->color = NIL; 
            root = NIL;
            root->parent = NIL;
            root->left = NIL;
            root->right = NIL;

        }

    //method to search for a node
    bool searchNode(int data){
        printf("made it\n");
        Node *curr = root;
        while (curr != NIL) {
            //node is found
            if (curr->data == data) {
                printf("true\n");
                myfile << "true";
                //myfile << this_thread;
                return true;

            }
            if (curr->data < data) {
                curr = curr->right;
                
            }
            if (curr->data > data){
                curr = curr->left;
            }
            
        }
        printf("DNE\n");
        return false;
    }

    Node* searchNodeReturn(int data){
        printf("made it\n");
        Node *curr = root;
        while (curr != NIL) {
            if (curr->data == data) {
                printf("true\n");
                return curr;

            }
            if (curr->data < data) {
                curr = curr->right;
            }
            if (curr->data > data){
                curr = curr->left;
            }
            
        }
        return curr;
    }

    //finding the node to replace the node to be deleted
    Node* replaceNode(Node *rep){
        //if node to be deleted has 2 children
        if(rep->left != NIL && rep->right != NIL){
            Node* temp;
            temp = rep->right;
            while(temp->left != NIL){
                temp = temp->left;
            }
            rep = temp;
            return rep;
        }
        //if node has 2 leaves(NIL) for children
        if(rep->left == NIL && rep->right == NIL){
            return NIL;
        }

        //if node only has one child, and one leaf
        if(rep->left != NIL){
            return rep->left;
        }
        else{
            return rep->right;
        }
    }
    void fixDelete(Node *x){
        Node *temp;
        while((x != root) && (x->color = Black)){
            if(x == x->parent->left){
                temp = x->parent->right;
                if(temp->color == Red){
                    temp->color = Black;
                    x->parent->color = Red;
                    LSwitch(x->parent);
                    temp = x->parent->right;
                }
                if(temp->left->color == Black && temp->right->color == Black){
                    temp->color = Red;
                    x = x->parent;
                }
                if(temp->right->color == Black){
                    temp->left->color = Black;
                    temp->color = Red;
                    RSwitch(temp);
                    temp = x->parent->right;
                }
                else{
                    temp->color = x->parent->color;
                    x->parent->color = Black;
                    temp->right->color = Black;
                    LSwitch(x->parent);
                    x = root;
                }
            }
            else{
                temp = x->parent->left;
                if(temp->color == Red){
                    temp->color = Black;
                    x->parent->color = Red;
                    RSwitch(x->parent);
                    temp = x->parent->left;
                }
                if(temp->right->color == Black && temp->left->color == Black){
                    temp->color = Red;
                    x = x->parent;
                }
                if(temp->left->color == Black){
                    temp->right->color = Black;
                    temp->color = Red;
                    LSwitch(temp);
                    temp = x->parent->left;
                }
                else{
                    temp->color = x->parent->color;
                    x->parent->color = Black;
                    temp->left->color = Black;
                    RSwitch(x->parent);
                    x = root;
                }
            }
        }

        x->color = Black;
    }

    Node* minimum(Node *x){
          while(x != NIL){
              x = x->left;
          }     
          return x;
    }

    void Transplant(Node *x, Node *y){
        if(x->parent == NIL){
            root = y;
        }
        else if (x == x->parent->left){
            x->parent->left = y;
        }
        else{
            x->parent->right = y;
        }
        if(y != NIL){
            y->parent = x->parent;    
        }
    }

    void deleteNode(int data){
        Node *delNode = searchNodeReturn(data);
        if(delNode == NIL){
            printf("node does not exist\n");
            return;
        }
        Node *dummy = new Node(data);
        //delNode->data = data;
        Node *y = delNode;
        dummy->color = y->color;
        Node *x;

        printf("heee\n");
        std::cout << root->right << "\n";
        if(delNode->left == NIL){
            printf("yes\n");
            x = delNode->right;
            printf("yes again");
            Transplant(delNode,delNode->right);
        }
        else if(delNode->right == NIL){
            printf("sup\n");
            x = delNode->left;
            Transplant(delNode,delNode->left);
        }
        else{
            printf("mitch\n");
            y = minimum(delNode->right);
            dummy->color = y->color;
            x = y->right;
            if(y->parent == delNode){
                x->parent = y;
            }
            else{
                Transplant(y, y->right);
                y->right = delNode->right;
                y->right->parent = y;
            }
            Transplant(delNode, y);
            y->left = delNode->left;
            y->left->parent = y;
            y->color = delNode->color;

        }
        printf("shock\n");
        if(dummy->color == Black){
            fixDelete(x);
        }
        std::cout << root->right << "\n";
    }


    //method to switch a node to the left to keep Red Back properties
    void LSwitch(Node *node1){
            Node *node = root;
            Node *right = node1->right;
            node1->right = right->left;
            if(node1->right != NIL){
                node1->right->parent = node1;
            }
            //moving up
            right->parent = node1->parent;
            if(node1->parent == NIL){
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
    void RSwitch(Node *node1){
            Node *node = root;
            Node *left = node1->left;
            node1->left = left->right;
            if(node1->left != NIL){
                node1->left->parent = node1;
            }
            //moving up
            left->parent = node1->parent;
            if(node1->parent == NIL){
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
    void insertNode(int data1){
        printf("in here\n");
        //data1 = data1 - 48;
        std::cout << data1 << "\n";
        Node *node = root;
        Node *y = NIL;
        Node *newNode = new Node(data1);
        while(node != NIL){
            y = node;
            if(newNode->data < node->data){
                node = node->left;
            }
            else{
                node = node->right;
            }
        }
        newNode->parent = y;
        if(y == NIL){
            root = newNode;
            root->parent = NIL;
            root->color = Black;

        }
        else if(y->data < newNode->data){
            y->right = newNode;
        }
        else{
            y->left = newNode;
        }
        
        newNode->left = NIL;
        newNode->right = NIL;
        newNode->color = Red;

        //std::cout << root->data << "\n";
        //std::cout << root->color << "\n";
        refactorTree(newNode);
        

    }
    //method to make sure the tree follows all Red Black Tree Properties
    void refactorTree(Node *node2){
        Node *node = root;
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
                            LSwitch(parent_);
                            node2 = parent_;
                            parent_= node2->parent;
                        } 

                        //second case
                        else if(node2 == parent_->left){
                            RSwitch(grandparent);
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
                    if(node4->color == Red && node4 != NIL){
                        node4->color = Black;
                        parent_->color = Black;
                        grandparent->color = Red;
                        node2 = grandparent;
                    }
                    //node 4 is not red
                    else{
                        //first case if node 2 is on the right of its parent
                        if(node2 == parent_->right){
                            LSwitch(grandparent);
                            Node *Dummy;
                            Dummy->color = parent_->color;
                            parent_->color = grandparent->color;
                            grandparent->color = Dummy->color;
                            node2 = parent_;
                        }
                        else if(node2 == parent_->left){
                            RSwitch(parent_);
                            node2 = parent_;
                            parent_ = node2->parent;
                        }
                    }

                }
        }
        node->color = Black;
    }

};

void preOrderPrint(Node *n){
    if(n == NIL){
        myfile << ",f";
    }
    char col ='b';
    if(n->color == Red){
        col = 'r';
    }
    if(n!= root){
        myfile << ",";
    }
    myfile << n->data << col;
    preOrderPrint(n->left);
    preOrderPrint(n->right);

}

TreeBuild Tree;

//method to parse the input file
vector<string> parseInput(string file){
    
    std::vector<string> commands;
    string line;
    //printf("Here\n");
    ifstream inputFile(file);
    if(inputFile.is_open()){
        //printf("herr2\n");
        while(!inputFile.eof()){
            //printf("here3\n");
            getline(inputFile, line);
            commands.push_back(line);
        }
        inputFile.close();
    }

    std:;vector<string> sepComma;
    string token;
    string s;
    char delimeter = ',';
    char delimeter2 = '||';
    std::istringstream tokenstring;
    std::istringstream spaces;
    int count = 0;
    for(int i = 0; i < commands.size(); i++){
        //std::cout << commands[i] << '\n';
        std::istringstream tokenstring(commands[i]);
        std::istringstream spaces(commands[i]);
        if(count == 0){
            while(std::getline(tokenstring, token, delimeter)){
                token.erase(remove(token.begin(), token.end(), ' '), token.end());
                sepComma.push_back(token);
            }
            if(commands[i+1].empty()){
                count++;
                //printf("true\n");
                sepComma.push_back("\n");
            }
        }
        else if(count == 1){
            while(std::getline(tokenstring, token, delimeter)){
                sepComma.push_back(token);
            }
            if(commands[i+1].empty()){
                count++;
                //printf("true\n");
                sepComma.push_back("\n");
            }
        }
        else if(count == 2){
            while(std::getline(tokenstring, token, delimeter2)){
                token.erase(remove(token.begin(), token.end(), ' '), token.end());
                sepComma.push_back(token);
            }
        }
        

    }
    // for(int j = 0; j < sepComma.size(); j++){
    //     std::cout << sepComma[j] << '\n';
    // }
    return sepComma;
}

//method to get number out of command
int getNum(string n){
    int num = n.at(n.length()-3);
    int num2 = n.at(n.length() -2);
    //num.append(num2);
    string s1 = to_string(num);
    string s2 = to_string(num2);
    string s = s1 + s2;
    int c = stoi(s);
    std::cout << c << "\n";
    return c;

}
//method to run write process
void *writeProcess(void *arg){
    int write;
    sem_init(&mute,0,1);
    sem_init(&wrtieLock, 0,1);
    while(!writeQueue.empty()){
        printf("her\n");
        sem_wait(&wrtieLock);
        write++;
        
        if(write > 0 && !readQueue.empty()){
            sem_wait(&mute);
        }
        sem_post(&wrtieLock);
        if(writeQueue.empty()){
            pthread_exit(NULL);
        }
        printf("HIm\n");
        string p = writeQueue.front();
        //string num = p.substr(p.length()-3, p.length()-2); 
        if(p.at(p.length()- 10) == 'i'){
            Tree.insertNode(getNum(p));
        }
        else{
            Tree.deleteNode(getNum(p));
        }
        printf("sup\n");
        writeQueue.pop();
        write--;
        sem_wait(&wrtieLock);

        if(write == 0){
            sem_post(&mute);
        }            
        sem_post(&wrtieLock);
    }
}

//method to run read proccess
void *concurrentThread(void *arg){
        int read;
        sem_init(&mute,0,1);
        sem_init(&wrtieLock, 0,1);
        while(!readQueue.empty()){
            sem_wait(&mute);
            read++;
            //printf("like\n");
            if(read >0){
                sem_wait(&wrtieLock);
            }

            sem_post(&mute);
            if(readQueue.empty()){
                pthread_exit(NULL);
            }
            string s = readQueue.front();
            //string num = s.substr(s.length()-3, s.length()-2);
            printf("like\n");
            Tree.searchNode(getNum(s));
            readQueue.pop();
            read--;
            sem_wait(&mute);

            if(read == 0){
                sem_post(&wrtieLock);
            }
            sem_post(&mute);
        }

        pthread_exit(NULL);


}

//method to run the instructions and the threads
void runInstruction(TreeBuild Tree, string s){
        std::cout << s << "\n";
        char num;
        char col;
        
        vector<string> threadandComs;
        std::string temp;
        char del = ',';
        string split;
        //printf("here\n");
        if(s.at(s.length() -1) == 'b' || s.at(s.length() -1) == 'r' || s.at(s.length() -1) == 'f'){
            if(s.at(s.length() -1) == 'f'){
                return;
            }
            col = s.at(s.length()-1);
            temp = s.substr(0, s.length()-1);
            //num = stoi(temp);
            Tree.insertNode(stoi(temp));
        } 
        else if(s.find(',') != std::string::npos){
            printf("trueeee\n");
            std::istringstream ss(s);
            if(s.at(s.length()-10)== 's'){
                while(std::getline(ss, split, del)){
                    if(split.at(split.length()-1 ==')')){
                        //split.erase(remove(split.begin(), split.end(), ' '), split.end());
                        readQueue.push(split);
                    }
                }
            }
            else{
               while(std::getline(ss, split, del)){
                     if(split.at(split.length()-1 ==')')){
                        //split.erase(remove(split.begin(), split.end(), ' '), split.end());
                        writeQueue.push(split);                   
                    }
                } 
            }

            
        }
        int i;
        int j;
        printf("yoyo\n");
        pthread_t threads[readQueue.size() + writeQueue.size()];   
        for(i = 0; i < readQueue.size(); i++){
            pthread_create(&threads[i], NULL, concurrentThread, NULL);
            printf("got here\n");
        }
        for(j = 0; j < writeQueue.size(); j++){
            printf("hey\n");
            pthread_create(&threads[i+j], NULL, writeProcess, NULL);
        }


}
int main(int i){
        auto start = high_resolution_clock::now();
        TreeBuild Tree;
        vector<string> commands;
        pthread_mutex_t m;
        ofstream myfile;
        myfile.open("output.txt");
        //pthread_mutex_init(m, NULL);
        commands = parseInput("Hello.txt");
        for(int i = 0; i < commands.size(); i++){
            string instruction = commands[i];
            std::cout << instruction << "\n";
            runInstruction(Tree, instruction);
                        
        }   
        
        auto stop = high_resolution_clock::now(); 
        auto duration = duration_cast<microseconds>(stop - start); 
        //duration.count;
        myfile << duration.count();
        return 0;
}