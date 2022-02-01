#include <iostream>
#include <conio.h>
#include <cstring>
#include "../../resourseFiles/Tree.h"
#include "Translater.h"

using namespace std;

int main()
{
    char name[50];
    strcpy(name,"STMT\0");
    Tree tree(name);
    strcpy(name,"table\0");
    tree.addChild(name);
    strcpy(name,".\0");
    tree.addChild(name);
    strcpy(name,"OPTR\0");
    tree.addChild(name);
    tree.changeDir(name);
    strcpy(name,"READ\0");
    tree.addChild(name);
    tree.changeDir(name);
    strcpy(name,"read\0");
    tree.addChild(name);
    strcpy(name,"(\0");
    tree.addChild(name);
    strcpy(name,"R_ATTR\0");
    tree.addChild(name);
    tree.changeDir(name);
    strcpy(name,"id\0");
    tree.addChild(name);
    strcpy(name,"R_ATTR_LIST\0");
    tree.addChild(name);
    tree.previousDir();
    strcpy(name,")\0");
    tree.addChild(name);
    tree.previousDir();
    tree.previousDir();
    strcpy(name,";\0");
    tree.addChild(name);
    strcpy(name,"OPTR");
    tree.addChild(name);
    tree.treversePreOrder();
    Translater t(&tree);
    char Statmnt[300];
    strcpy(Statmnt,t.STMT());
//    cout << "4";
    cout << Statmnt;
    getch();
    return 1;
}
