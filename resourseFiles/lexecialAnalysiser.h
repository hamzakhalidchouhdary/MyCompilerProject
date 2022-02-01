//#include <iostream>
//#include <conio.h>
#include "../resourseFiles/transactionTable.h"
#include "../resourseFiles/linkedList.h"
#include "../resourseFiles/Hashing.h"

using namespace std;

class LexecialAnalysiser
{
    LinkedList *tokenList;//linked list obj to make token list
    char lexem[50];
    int state, dataIndex, lexIndex;
    void tokenize();
    void retractState();
    void buildLexem(char);
    void initializeDataMembers();
public:
    LexecialAnalysiser();
    ~LexecialAnalysiser();
    LinkedList* getTokenList(char*);
    void destroyList();
    void getTokens();
};
void LexecialAnalysiser::destroyList()
{
    tokenList->deleteList();
}
LexecialAnalysiser::LexecialAnalysiser()
{
    initializeDataMembers();
}
LexecialAnalysiser::~LexecialAnalysiser()
{
    tokenList->deleteList();
}
void LexecialAnalysiser::initializeDataMembers()
{
    //tokenList = NULL;
    lexem[0] = '\0';
    state = dataIndex = lexIndex = 0;
    tokenList = new LinkedList;
}
void LexecialAnalysiser::tokenize()
{
    if(!TT[state][TOK]) // if TT[state][TOK] is 0 (id)
    {
        Hashing obj; //Hashing class obj to use Hash Table
        if(obj.isInTable(lexem)) // if lexem matcH in Hash table
            tokenList->insertNode(lexem,kw); //tokenize as keyword
        else
            tokenList->insertNode(lexem,id); //tokenize as id
    }
    else
        tokenList->insertNode(lexem,TT[state][TOK]); //tokenize as returned from TT
}
void LexecialAnalysiser::retractState()
{
    state = 0;
    lexIndex = 0;
    dataIndex--;

}
void LexecialAnalysiser::buildLexem(char temp)
{
    switch(temp)
    {
    case '\'':
    case '\"':
    case '\n':
    case '$':
    //case (char)(32):// white space ascii
    case '\r':
        break;
    case (char)(32):
        if(state == 17 || state == 12)
        {
            lexem[lexIndex++] = (char)(32);
        }
        break;
    default:
        lexem[lexIndex++] = temp;
        break;
    }
}
LinkedList* LexecialAnalysiser::getTokenList(char data[])
{
    //cout << data << endl;
    initializeDataMembers();
    while(data[dataIndex])
    {

        state = TT[state][data[dataIndex]];
        if(TT[state][ACP])
        {
            lexem[lexIndex] = '\0';
            tokenize();
        }
        if(TT[state][RCT])
        {
            retractState();
        }
        else
        {
            buildLexem(data[dataIndex]);
        }
        dataIndex++;
    }
    return tokenList;
}
void LexecialAnalysiser::getTokens()
{
    tokenList->treavarseList();
}
