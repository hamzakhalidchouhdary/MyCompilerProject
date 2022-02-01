#include <iostream>
#include <conio.h>
#include <cstring>
#include <windows.h>

using namespace std;

struct Dir
{
    char name[50]; // contains directory name
    Dir* childList; // contains child directory
    Dir* nextDir; // contains next directory link to maintain child list
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
    StackNode* head;  //
public:
    Stack();
    void push(Dir*);
    Dir* pop();
    void treverseStack();
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
Dir* Stack::pop()
{
    if(head)
    {
        StackNode* t = new StackNode(head);
        head = head->next;
        delete t->next;
        return t->data;
    }
    else
    {
        return NULL;
    }
}

class Tree
{
    Dir* root;
    Dir* curDir;
    Stack S;
    void treversePreOrder(Dir*);
    void treversePostOrder(Dir*);
    void treverseInOrder(Dir*);
    Dir* deleteDir(Dir*);
    Dir* getDir(char[]);

public:
    Tree();
    ~Tree();
    Tree(char[]);
    int addChild(char[]);
    int deleteDir(char[]);
    int deleteCurDir();
    int changeDir(char[]);
    int moveDir(char[],char[]);
    void sortChild();
    bool previousDir();
    void treverseCurDir();
    void treversePreOrder();
    void treversePostOrder();
    void treverseInOrder();

};
Tree::Tree()
{
    curDir = root = new Dir();
}
Tree::Tree(char t[])
{
    curDir = root = new Dir(t);
}
Tree::~Tree()
{
    curDir = root;
    deleteCurDir();
    delete root;
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
        S.push(curDir);
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
    if(t1)
    {
        deleteDir(t1);
        Dir* t2;
        t2 = curDir->childList; // t2 is pointing child list of current dir
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
    deleteDir(curDir);
    if(curDir != root)
    {
        Dir *t1,*t2;
        t1 = curDir;
        previousDir();
        t2 = curDir->childList; // t2 is pointing child list of current dir
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
bool Tree::previousDir()
{
    Dir* t = S.pop();
    if(t)
    {
        curDir = t;
        return 1;
    }

    else
    {
        curDir = root;
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

void options()
{
    cout <<  "1 : ADD NODE" << endl
         <<  "2 : CHANGE DIR" << endl
         <<  "3 : DELETE DIR" << endl
         <<  "4 : PREVIOUS DIR" << endl
         <<  "5 : PRE-ORDER" << endl
         <<  "6 : POST-ORDER" << endl
         <<  "7 : IN-ORDER" << endl
         <<  "8 : DELETE CURRENT DIR" << endl
         <<  "0 : Exit" << endl << endl;
    cout << "YOUR OPTION : ";
}

int main()
{
    char name[50];
    //strcpy(name,"A\0");
    //cout << "breakpoint";
    Tree tree;
    int opt = 0;

    do{
        system("cls");
        tree.treverseCurDir();
        options();
        cin >> opt;
        switch(opt)
        {
        case 0:
            //exit(1);
            break;
        case 1:
            system("cls");
            cout << "ENTER DIR NAME : ";
            cin >> name;
            name[strlen(name)] = '\0';
            tree.addChild(name);
            break;
        case 2:
            system("cls");
            cout << "ENTER DIR NAME : ";
            cin >> name;
            name[strlen(name)] = '\0';
            if(!tree.changeDir(name))
                cout << "\a";
            break;
        case 3:
            system("cls");
            cout << "ENTER DIR NAME : ";
            cin >> name;
            name[strlen(name)] = '\0';
            tree.deleteDir(name);
            break;
        case 4:
            if(!tree.previousDir())
                cout << "\a";
            break;
        case 5:
            system("cls");
            tree.treversePreOrder();
            cout << "PRESS ANY KEY TO GO BACK";
            getch();
            break;
        case 6:
            system("cls");
            tree.treversePostOrder();
            cout << "PRESS ANY KEY TO GO BACK";
            getch();
            break;
        case 7:
            system("cls");
            tree.treverseInOrder();
            cout << "PRESS ANY KEY TO GO BACK";
            getch();
            break;
        case 8:
            tree.deleteCurDir();
            break;

        default:
            cout << "\a";
            system("cls");
            break;
        }
    }while(opt);

    getch();
    return 1;
}
