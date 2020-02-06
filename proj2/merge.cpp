// merge.cpp

#include "volsort.h"

#include <iostream>
// Prototypes

Node *msort(Node *head, bool numeric);
void  split(Node *head, Node *&left, Node *&right);
Node *merge(Node *left, Node *right,Node *sorting,bool numeric);

// Implementations

void merge_sort(List &l, bool numeric) {

}

Node *msort(Node *head, bool numeric) {
	if((head == NULL) || (head->next = NULL)){
		return head;
	}
	Node *l,*r, *newNode; 
	split(head,l,r);
	cout << "sorting" << endl;
	l = msort(l,numeric);
	r = msort(r,numeric);
	cout << "exiting msort" << endl;
	return merge(l,r,newNode,numeric);
}

void split(Node *head, Node *&left, Node *&right) {
	Node *tortoise;
	Node *hare;
	tortoise = head;
	hare = head->next;

	while(hare != NULL){
		hare = hare->next;
		if(hare != NULL){
			tortoise = tortoise->next;
			hare = hare->next;
		}
	}

	left = head;
	right = tortoise->next;
	tortoise->next = NULL;

}

Node *merge(Node *left, Node *right,Node *sorting,bool numeric) {
	Node *newHead = NULL;
	if(left == NULL) return left;
	if(right == NULL) return right;
	if(left && right){
		if(left->number <= right->number){
			sorting = left;
			left = sorting->next;
		}
		else{
			sorting = right;
			right = sorting->next;
		}
		newHead = sorting;
	}
	while(left && right){
		if(left->number <= right->number){
			sorting->next = left;
			sorting = left;
			left = sorting->next;
		}
		else{
			sorting->next = right;
			sorting = right;
			right = sorting->next;
		}
	}
	if(left == NULL) sorting->next = right;
	if(right == NULL) sorting->next = left;
	cout << "exit merge" << endl;
	return newHead;
}

