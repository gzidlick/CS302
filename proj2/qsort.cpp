// qsort.cpp

#include "volsort.h"

#include <cstdlib>
#include <array>
#include <iostream>

int qsort_number_compare(const void *a, const void *b){
	Node *a_n = *((Node**) a);
	Node *b_n = *((Node**) b);
	if(a_n->number < b_n->number){
		return -1;
	}
	else{
		return 1;
	}
};

int qsort_string_compare(const void *a, const void *b){
	Node *a_n = *((Node**) a);
	Node *b_n = *((Node**) b);
	int tmp = a_n->string.compare(b_n->string);
	if(tmp < 0){
        return -1;
	}
	else{
		return 1;
	}
};



void qsort_sort(List &l, bool numeric) {
    Node* current = l.head;
	Node* array[l.size];
	for(unsigned int i = 0;i<l.size;i++){
		array[i] = current;
		current = current->next;
	}
    if(numeric){
		qsort(array, l.size,sizeof(Node*),qsort_number_compare);
	}
    else{
		qsort(array, l.size,sizeof(Node*),qsort_string_compare);
	}
	for(unsigned int i = 0;i<l.size-1;i++){
		array[i]->next = array[i+1];
	}
	array[l.size-1]->next = NULL;
	l.head = array[0];
}
