#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <stdlib.h>
/*
Program			:	Linked List Data Structure
Author			:	Hamza Khalid Chouhdary
Starting Date	:	15 DEC 2019
*/
#include<ostream>
//linked list node data type
struct Node {
	int data;
	Node* link;
	Node()
	{
	    data = 0;
	    link = NULL;
	}
};
//linked list data structure
class LinkedList {
protected:
	Node *head; // linked list header
public:
	LinkedList() { // consturctor
		head = NULL;
	}
	~LinkedList() { //desturctuor
		deleteList();
		//treavarseList();
	}
	bool isEmpty() { // will return 1 if head is null other wise 0; to check either LL exisits or not
		if (head == NULL)
			return 1;
		else
			return 0;
	}
	bool insertNode(int val) { // add a new node at the end of LL and return 1 if inserted else 0
		Node *New = new Node();
		bool isInserted = false;
		New->data = val;
		New->link = NULL;
		if (head == NULL) {
			head = New;
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
	bool deleteList() { // distory entire LL and return 1 if distoried other wise 0
		Node *t = NULL;
		while (head != NULL) {
			t = head;
			head = head->link;
			delete t;
		}
		return isEmpty();
	}
	bool insertNode(int pos, int val) { // insert a node between the LL take a position node and insert new node next to that. if inserted return 1 else 0
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
	}
	bool deleteNode(int val) { // delete a specific node
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
	}
	void treavarseList() { // display entire LL
		Node *t = head;
		if (isEmpty())
			std::cout << "List is empty";
		else
			while (t != NULL) {
				std::cout << t->data << " ";
				t = t->link;
			}
	}

};
//stack data sturcture
class Stack : private LinkedList {
public:
	bool push(int val) {
		bool isInserted = false;
		Node *n = new Node;
		n->data = val;
		n->link = NULL;
		if (isEmpty()) {
			head = n;
			isInserted = true;
		}
		else {
			n->link = head;
			head = n;
			isInserted = true;
		}
		return isInserted;
	}
	void pop() {
		Node *t = head;
		head = head->link;
		delete t;
	}
	int top() {
		return head->data;
	}
	void treverseStack() {
		Node *t = head;
		if (isEmpty())
			std::cout << "Stack is empty";
		else
			while (t != NULL) {
				std::cout << t->data << " ";
				t = t->link;
			}
	}
	bool isEmpty() {
		if (head == NULL)
			return 1;
		else
			return 0;
	}
};

int main()
{
	Stack S;
	char ch = '\0';
	int val, pos;
	/*while (ch != (char)(27))
	{
		system("cls");
		std::cout << "List Value : ";
		S.treverseStack();
		std::cout << std::endl;
		std::cout << "1\t:\tPush\n";
		if (!S.isEmpty()) {
			std::cout << "2\t:\tPop" << std::endl
				<< "3\t:\tTop" << std::endl;
		}
		ch = _getch();
		switch (ch)
		{
		case '1':
			std::cout << "Enter Value : ";
			std::cin >> val;
			S.push(val);
			break;
		case '2':
			if (!S.isEmpty())
				S.pop();
			else
				std::cout << "\a";
			break;
		case '3':
			if (!S.isEmpty())
				std::cout << S.top();
			else
				std::cout << "\a";
			break;
		case (char)(27) :
				break;
		default:
			std::cout << "\a";
			break;
		}

	}*/


	LinkedList LL;
	while (ch != (char)(27))
	{
		system("cls");
		std::cout << "List Value : ";
		LL.treavarseList();
		std::cout << std::endl;
		std::cout << "1\t:\tInsert Node\n";
		if (!LL.isEmpty()) {
			std::cout << "2\t:\tInsert Node Between" << std::endl
				<< "3\t:\tDelete A Node" << std::endl
				<< "4\t:\tDelete List" << std::endl;
		}
		std::cout << "Esc\t:\tExit";
		ch = _getch();
		system("cls");
		switch (ch) {
		case '1':
			std::cout << "Enter a value : ";
			std::cin >> val;
			LL.insertNode(val);
			break;
		case '2':
			if (LL.isEmpty()) std::cout << "\a";
			else {
				LL.treavarseList();
				std::cout << std::endl;
				std::cout << "Enter position value : ";
				std::cin >> pos;
				std::cout << "Enter new value : ";
				std::cin >> val;
				LL.insertNode(pos, val);
				//_getch();
			}
			break;
		case '3':
			if (LL.isEmpty()) std::cout << "\a";
			else {
				LL.treavarseList();
				std::cout << std::endl;
				std::cout << "Enter a value : ";
				std::cin >> val;
				LL.deleteNode(val);
			}
			break;
		case '4':
			if (LL.isEmpty()) std::cout << "\a";
			else {
				LL.deleteList();

			}
			break;
		case (char)(27):
			break;
		default:
			std::cout << "\a";
			break;
		}
	}




}
