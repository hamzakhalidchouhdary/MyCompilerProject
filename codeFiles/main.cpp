#include <iostream>
#include <conio.h>
#include "../resourseFiles/fileManager.h"
#include "../resourseFiles/lexecialAnalysiser.h"
#include "../resourseFiles/Grammer.h"
#include "../resourseFiles/Translater.h"
#include <fstream>
#include <windows.h>


using namespace std;

int main()
{
    LinkedList *tokenList; //linked list object to store set of tokens returned by lexecial analysis
    Tree *parseTree = NULL; // tree class object to obtain parse tree from syntax analysis
    char fileAddr[50]; // file address buffer to store address of data file
    strcpy(fileAddr,"../dataFiles/data.txt"); //copy path to file Address buffer
    while(1)
    {
        system("cls");
        FileManager dataFile(fileAddr);  // file manager object to utilize file reading facilities
        while(!dataFile.isOpen()) // repeat until file is not opened
        {
            cout << "Enter file path : "; // display a massage to user
            cin >> fileAddr; // read file path from user
            dataFile.openFile(fileAddr); //FileManager member to open a input file
        }
        LexecialAnalysiser lexAnalysis; // lexecial analysiser object to perform lexecial analysis
        char data[200] = {'\0'}; // data buffer to store context read from file
        Grammer synAnalysis; // Grammer object to verify syntax
        int LineCounter = 1; // line counting variable
        while(!dataFile.fileEnd()) // repeat (loop) body of while until file end
        {
           // cout << "LOOP STARTED\n"; // break point statement
            dataFile.readLine(data); // read a line from input file to data buffer
            cout << "LINE " << LineCounter << ":" << data << endl;
            tokenList=lexAnalysis.getTokenList(data); // perform lexecail analysis to context of data buffer and get set of tokens in tokenList
           // cout << "LEXECAL ANALYSIS END" << endl;
            //lexAnalysis.getTokens(); //call LexecialAnalysiser member to display token set
            //cout << endl; // break line
            //lexAnalysis.destroyList(); // call LexecialAnalysiser member to destroy set of token to free memory
            //lexAnalysis.getTokens(); //call LexecialAnalysiser member to display token set
    //        cout << "TOKEN LIST : " ; // UI statement
    //        tokenList->treavarseList(); //call LinkedList member to display list
    //        cout << endl; // break line statement
    //        cout << "SYNTAX ANALYSIS START " << endl; // break point statement
            synAnalysis.readList(tokenList); // passing tokens to syntax analysis
    //        cout << "PARSE TERR " << endl; // break point statement
            parseTree = synAnalysis.STMT(); // call syntax analysis
    //        cout << "SYNTAX ANALYSIS END " << endl; // break point statement
            if(parseTree)
            {
    //            cout << "NO ERROR IN LINE " << LineCounter << endl;
    //            cout << "PARSE TREE : "; // UI statement
    //            parseTree->treversePreOrder();
                Translater t(parseTree);
                char Statmnt[300];
                strcpy(Statmnt,t.STMT());
                cout << "OUTPUT:" <<  Statmnt << endl;
                parseTree->destroyTree();

            }

            else
                cout << "ERROR IN LINE " << LineCounter << endl;
    //        cout << "DISTROY LIST" << endl; // break point statement
            tokenList->deleteList(); //call LinkedList member to delete list to free memory
            LineCounter++;
            cout << endl; // break line
        }
        cout << "PRESS ANY KEY TO READ FILE AGAIN";
        getch();
    }

//    cout << "LOOP END";  // break point statement

    getch();
    return 0;
}
