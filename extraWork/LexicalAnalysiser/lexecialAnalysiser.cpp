#include <iostream>
#include <conio.h>
#include "../../resourseFiles/transactionTable.h"
#include "../../resourseFiles/fileManager.h"
#include "../../resourseFiles/linkedList.h"

using namespace std;

class LexecialAnalysiser
{
    LinkedList tokenList;
    char lexem[50];
    int state, dataIndex, lexIndex;
    void tokenize();
    void retractState();
    void buildLexem(char);
public:
    LexecialAnalysiser();
    ~LexecialAnalysiser();
    LinkedList getTokenList(char*);
    void getTokens();
};
LexecialAnalysiser::LexecialAnalysiser()
{
//    tokenList = NULL;
    lexem[0] = '\0';
    state = dataIndex = lexIndex = 0;
}
LexecialAnalysiser::~LexecialAnalysiser()
{
    tokenList.deleteList();
}
void LexecialAnalysiser::tokenize()
{
    tokenList.insertNode(lexem,TT[state][TOK]);
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
        break;
    default:
        lexem[lexIndex++] = temp;
        break;
    }
}
LinkedList LexecialAnalysiser::getTokenList(char data[])
{
    cout << data << endl;
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
    tokenList.treavarseList();
}

int main()
{
    LinkedList TL;
    char data[200] = {'\0'};
    FileManager dataFile("../../dataFiles/data.txt");
    dataFile.readLine(data);
    LexecialAnalysiser lexAnalysis;
    TL = lexAnalysis.getTokenList(data);
    lexAnalysis.getTokens();

    getch();
    return 0;
}
/*
void tokenize(char lex[],int state)
{
    switch(TT[state][TOK])
    {
    case ID:
        cout << "<" << lex << "," << "ID>" << endl;
        break;
    case NUM:
        cout << "<" << lex << "," << "NUM>" << endl;
        break;
    case STR:
        cout << "<" << lex << "," << "STR>" << endl;
        break;
    case PUN:
        cout << "<" << lex << "," << "PUN>" << endl;
        break;
    case ERR:
        cout << "<" << lex << "," << "UNDEFINE>" << endl;
        break;
    case OP:
        cout << "<" << lex << "," << "OP>" << endl;
        break;
    default:
        cout << "..." << endl;
        break;
    }
}

string removeBlankSpace(string str){
    for(int i=0,j=0;str[i];i++){
        switch(str[i])
        {
        case (char)(32):
        case '\n':
            str[i] = '\0';
            break;
        default:
            //str[j++]=str[i];
            break;
        }
    }
    return str;
}
int main(){

    FileManager dataFile("../dataFiles/data.txt");
    char temp,lex[20],data[100] = {"table.select(_id,name,45,30.5)$\0"};
    int state = 0;
    int lexInd = 0;
    dataFile.readLine(data,';');
    cout << data << endl;
    for(int i=0;data[i]!='\0';i++)
    {
        temp = data[i];
        state = TT[state][temp];
        //cout << temp << " state : " << state << " Accept : " << TT[state][ACP] << " Retract : " << TT[state][RCT] << " Token : " << TT[state][TOK] << endl;
        if(TT[state][(states)(ACP)])
        {
                lex[lexInd] = '\0';
                tokenize(lex,state);
                if(TT[state][TOK] == STR)
                    i++;
        }
        if(TT[state][RCT])
        {
            state = 0;
            lexInd = 0;
            i--;
        }
        else
        {
            switch(temp)
            {
            case'\'':
            case'\"':
            case'\n':
            case'$':
                break;
            //case'/':
                //i--;
                //break;
            default:
                lex[lexInd++] = temp;
            }
        }
    }

}

*/
