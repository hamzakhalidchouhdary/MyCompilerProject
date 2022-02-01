#include <cstring>
//#include <iostream>

using namespace std;

struct Node {
    char lexem[50];
	int lexicalUnit;
	Node* link;
	Node()
	{
	    strcpy(lexem,"EMPTY\0");
	    lexicalUnit = 0;
	    link = NULL;
	}
};
//linked list data structure
class LinkedList {
	 // linked list header
	 Node *head;
protected:
	 Node *curNode;
public:
	LinkedList();
	~LinkedList();
	bool isEmpty();
	bool isEnd();
	bool insertNode(char*,int);
	bool deleteList();
	void nextNode(void);
	char* getCurLexem(void);
	int getCurLexUnit(void);
	//bool deleteNode(int);
	//bool insertNode(int, int);
	void treavarseList();
};
void LinkedList::nextNode(void)
{
    curNode = curNode->link;
}
bool LinkedList::isEnd(void)
{
    if(curNode == NULL)
        return 1;
    else
        return 0;
}
char* LinkedList::getCurLexem(void)
{
    return curNode->lexem;
}
int LinkedList::getCurLexUnit(void)
{
    return curNode->lexicalUnit;
}
LinkedList::LinkedList() { // consturctor
    curNode = head = NULL;
}
LinkedList::~LinkedList() { //desturctuor
    deleteList();
    //treavarseList();
}
bool LinkedList::isEmpty() { // will return 1 if head is null other wise 0; to check either LL exisits or not
    if (head == NULL)
        return 1;
    else
        return 0;
}
bool LinkedList::insertNode(char lex[],int lexUnit){ // add a new node at the end of LL and return 1 if inserted else 0
    Node *New = new Node();
    bool isInserted = false;
    //cout <<"<" << lex << ",Lex>";
    strcpy(New->lexem,lex);
    //cout <<"<" << lex << ",New->lexem>" << endl;
    New->lexicalUnit = lexUnit;
    New->link = NULL;
    if (head == NULL) {
        curNode = head = New;
        isInserted = true;
    }
    else {
        Node *t = head;
        while (t->link != NULL) {
            t = t->link;
        }
        t->link = New;
        isInserted = true;
    }
    return isInserted;
}
bool LinkedList::deleteList() { // distory entire LL and return 1 if distoried other wise 0
    Node *t = NULL;
    while (head != NULL) {
        t = head;
        head = head->link;
        delete t;
    }
    curNode = head;
    return isEmpty();
}
/*bool LinkedList::insertNode(int pos, int val) { // insert a node between the LL take a position node and insert new node next to that. if inserted return 1 else 0
    Node *t = head, *n = NULL;
    while (t != NULL) {
        if (t->data == pos)
            break;
        else
            t = t->link;
    }
    if (t == NULL)
        return 0;
    else {
        n = new Node;
        n->data = val;
        n->link = t->link;
        t->link = n;
        return 1;
    }
}*/
/*bool LinkedList::deleteNode(int val) { // delete a specific node
    Node *t = head, *p = NULL;
    while (t != NULL) {
        if (t->data == val)
            break;
        else
        {
            p = t;
            t = t->link;
        }

    }
    if (t != NULL)
        if (t == head) {
            head = t->link;
            delete t;
            return 1;
        }
        else {
            p->link = t->link;
            delete t;
            return 1;
        }
    else
        return 0;
}*/
void LinkedList::treavarseList() { // display entire LL
    Node *t = head;
    if (isEmpty())
        std::cout << "<NO TOKEN FOUND>";
    else
        while (t != NULL) {
                //cout << t->lexem;
                cout << "<" << t->lexem << ",";
            switch(t->lexicalUnit)
            {
            case id:
                cout << "ID>";
                break;
            case num:
                cout << "NUM>";
                break;
            case str:
                cout << "STR>";
                break;
            case pun:
                cout << "PUN>";
                break;
            case err:
                cout << "UNDEFINE>";
                break;
            case op:
                cout << "OP>";
                break;
            case kw:
                cout << "KW>";
                break;
            default:
                cout << "...";
                break;
            }
            t = t->link;
        }
}
