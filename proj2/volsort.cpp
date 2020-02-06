#include "volsort.h"
#include <string>
#include <iostream>
using namespace std;

//return true if less
bool node_number_compare(const Node *a, const Node *b){
	if(a->number <= b->number){
		return true;
	}
	else{
		return false;
	}
};
//return true if false
bool node_string_compare(const Node *a, const Node *b){
	int tmp = a->string.compare(b->string);
	//string is shorter or first non-match char is lower
	if(tmp < 0){
		return true;
	}
	else{
		return false;
	}
};
void dump_node(Node *n){
	Node *temp = n;
	while(temp != NULL){
//		cout << "String: " << temp->string << endl;
		cout << "Number: " << temp->number << endl;
		temp = temp->next;
	}
};
void List::push_front(const string &s){
	int new_int;
	try{
		new_int = stoi(s);
	}
	catch(exception& e){
		new_int = 0;
	}
	if(!head){
		head = new Node;
		head->string = s;
		head->number = new_int;
		head->next = NULL;
		size++;
	}
	else{
		Node *temp = new Node;
		temp->next = head;
		temp->string = s;
		temp->number = new_int;
		head = temp;
		size++;
	}
};
