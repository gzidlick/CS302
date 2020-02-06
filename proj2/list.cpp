#include "volsort.h"


List::List() {
	head = NULL;
}

List::~List() {
	Node* current = head;
	Node* nxt;

	while(current != NULL){
		nxt = current->next;
		delete current;
		current = nxt;
	}
}
