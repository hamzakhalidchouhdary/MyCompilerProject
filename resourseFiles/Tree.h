#include <iostream>
#include <conio.h>
#include <cstring>
#include <windows.h>

using namespace std;

struct Dir
{
    char name[50]; // contains directory name
    Dir* childList = NULL; // contains child directory
    Dir* nextDir = NULL; // contains next directory link to maintain child list
    Dir(char t[])
    {
        strcpy(name,t);
        childList = NULL;
        nextDir = NULL;
    }
    Dir()
    {
        strcpy(name,"ROOT");
        childList = NULL;
        nextDir = NULL;
    }

};

struct StackNode{
    Dir* data;
    StackNode* next;
    StackNode()
    {
        data = NULL;
        next = NULL;
    }
    StackNode(StackNode* t)
    {
        this->data = t->data;
        this->next = t;
    }
    StackNode(Dir* t, StackNode* n)
    {
        data = t;
        next = n;
    }
};

class Stack
{
    StackNode* head;
public:
    Stack();
    void push(Dir*);
    Dir* pop();
    void treverseStack();
    void freeStack();
};
Stack::Stack()
{
    head = NULL; // initialize head of stack
}
void Stack::treverseStack()
{
    StackNode* t = head;
    while(t)
    {
        cout << t->data->name << " ";
        t = t->next;
    }
    cout << endl;
}
void Stack::push(Dir* t)
{
    head = new StackNode(t,head); // add a new node
}
void Stack::freeStack()
{
    StackNode* t; // temp container
    while(head) // loop until head is NULL
    {
        t = head; // copy head
        head = head->next; // obtain lower node of stack in head
        delete t; // free top node (head)
    }
}
Dir* Stack::pop()
{
    if(head) // stack not empty
    {
        StackNode t = new StackNode(head);// copy head data
        head = head->next; // obtain lower node of stack in head
        delete t.next; // delete head
        return t.data; // return head data
    }
    else // stack empty
    {
        return NULL;
    }
}

class Tree
{
    Stack S;
    void treversePreOrder(Dir*);
    void treversePostOrder(Dir*);
    void treverseInOrder(Dir*);
    Dir* deleteDir(Dir*);
    Dir* getDir(char[]);
protected:
    Dir* root;
    Dir* curDir;
public:
    Tree();
    ~Tree();
    Tree(char[]);
    char* readData();
    int addChild(char[]);
    int deleteDir(char[]);
    int deleteCurDir();
    int changeDir(char[]);
    void moveToFirst();
    int moveDir(char[],char[]);
    void sortChild();
    bool previousDir();
    void treverseCurDir();
    void treversePreOrder();
    void treversePostOrder();
    void treverseInOrder();
    void destroyTree();

};
Tree::Tree()
{
    curDir = root = new Dir(); // create root
}
Tree::Tree(char t[])
{
    curDir = root = new Dir(t); // create root
}
Tree::~Tree()
{
    destroyTree(); // free tree from memory
    delete root; // delete root dir
}
char* Tree::readData()
{
    char data[50];
    if(curDir)
    {
        strcpy(data,curDir->name);
    }
    else
    {
        strcpy(data,"\0");
    }
    return data;
}
void Tree::moveToFirst()
{
    Dir* first = curDir->childList;
    changeDir(first->name);
}
void Tree::destroyTree()
{
    curDir = root; // move to root dir
    deleteCurDir(); // delete current dir (root)
    S.freeStack(); // empty stack
}
Dir* Tree::getDir(char t[])
{
    Dir* temp = curDir->childList; // obtain current directory
    while(temp && (strcmp(temp->name,t))) // terminate as desire directory is found
    {
        temp = temp->nextDir; // move to next node
    }
    return temp;

}
int Tree::addChild(char t[])
{
    int status = -1; // status code for fuzzy logic
    if(!curDir->childList) // no child exists
    {
        curDir->childList = new Dir(t); // insert first child node
        status = 1; // set status to 1 (successfully inserted)
    }
    else // child exists
    {
        Dir* temp = curDir->childList; // obtain current directory
        do
        {
            if(!strcmp(temp->name,t)) // if same name directory already exists
            {
                status = 0; // set status to 0 (already exists)
                temp = NULL; // set temp to NULL to terminate loop
            }
            else if(!temp->nextDir) // if current node is last in list
            {
                temp->nextDir = new Dir(t); // add a new directory
                status = 1; // set status to 1 (successfully inserted)
                temp = NULL; // set temp to NULL to terminate loop
            }
            else // default case
            {
                temp = temp->nextDir; // move to next node
            }
        }while(temp); // loop until temp is not NULL
    }
    return status;
}
int Tree::changeDir(char t[])
{
    Dir* temp = getDir(t);
    int status = -1; // status code for fuzzy logic
    if(!temp) // no found
    {
        status = 0 ;
    }
    else
    {
        S.push(curDir); // stack current directory
        curDir = temp; // change current directory
        status = 1;
    }
    return status;

}
Dir* Tree::deleteDir(Dir* dir)
{
    if(dir && dir->childList) // child exists
    {
        Dir* nextNode; // temp identifier to store next child
        Dir* curNode;// temp temp identifier to store current child
        while(dir->childList) // loop until child exists
        {
            curNode = dir->childList;
            dir->childList = deleteDir(dir->childList); // delete first child and store next child
        }
        nextNode = dir->nextDir; // obtain next child before deletion
        delete curNode; // delete child
        return nextNode; // return next child
    }
    else
    {
        return NULL;
    }

}
int Tree::deleteDir(char t[])
{
    Dir* t1 = getDir(t); // t1 is pointing current dir
    //cout << t1 << endl;
    //cout << t1->name;
//    cout << t1->childList << endl;
//    treverseCurDir();
    if(t1)
    {
//        cout << t1 << endl;
//       // t1->childList = 0;
//        cout << t1->childList << endl;
        deleteDir(t1);
//        cout << t1 << endl;
        Dir* t2;
        t2 = curDir->childList; // t2 is pointing child list of current dir
//        cout << t2 << endl;
        if(t2 == t1) // first node is to be deleted
            curDir->childList = t1->nextDir; // copy list directly to current dir
        else // first node is not to be deleted
        {
            while(t2->nextDir != t1) // find t1 in t2 list
                t2 = t2->nextDir;
            t2->nextDir = t1->nextDir;// get next nodes of t1 to t2
        }
        delete t1;
    }

}
int Tree::deleteCurDir()
{
//    cout << "~DIR..." << endl; // break point statement
    Dir *t1;
    t1 = curDir;
    deleteDir(t1);
//    cout << "~DIR_1..." << endl; // break point statement
//    treverseCurDir();  // break point statement
//    cout << curDir << endl; // break point statement
    if(curDir != root)
    {
        Dir *t2;
//        S.treverseStack(); // break point statement
        previousDir();
        t2 = curDir->childList; // t2 is pointing child list of current dir
//        cout << "~DIR_2..." << endl; // break point statement
//        treverseCurDir(); // break point statement
//        cout << curDir  << endl << t2 << endl; // break point statement

        if(t2 == t1) // first node is to be deleted
            curDir->childList = t1->nextDir; // copy list directly to current dir
        else // first node is not to be deleted
        {
            while(t2->nextDir && t2->nextDir != t1 ) // find t1 in t2 list until end of list
                t2 = t2->nextDir;
            t2->nextDir = t1->nextDir;// get next nodes of t1 to t2
        }
//        cout << "~DIR_3" << endl; // break point statement
        delete t1;
    }
//    cout << "~DIR" << endl; // break point statement
}
bool Tree::previousDir()
{
    Dir* t = S.pop(); // obtain previous dir
    if(t) // stack not empty
    {
        curDir = t; // move to previous dir
        return 1;
    }

    else // stack empty
    {
        curDir = root; // move to root dir
        return 0;
    }

}
void Tree::treverseCurDir()
{
    Dir* temp = curDir->childList;
    cout << curDir->name << ":";
    while(temp)
    {
        cout << temp->name << " ";
        temp = temp->nextDir;
    }
    cout << endl;
}
void Tree::treversePreOrder(Dir* t)
{
        if(t)
        {
            cout << t->name << " ";
            treversePreOrder(t->childList);
            treversePreOrder(t->nextDir);
        }
}
void Tree::treversePostOrder(Dir* t)
{
        if(t)
        {
            treversePostOrder(t->nextDir);
            treversePostOrder(t->childList);
            cout << t->name << " ";

        }
}
void Tree::treverseInOrder(Dir* t)
{
        if(t)
        {
            treverseInOrder(t->childList);
            cout << t->name << " ";
            treverseInOrder(t->nextDir);
        }
}
void Tree::treversePreOrder()
{
    treversePreOrder(root);
    cout << endl;
}
void Tree::treversePostOrder()
{
    treversePostOrder(root);
    cout << endl;
}
void Tree::treverseInOrder()
{
    treverseInOrder(root);
    cout << endl;
}
