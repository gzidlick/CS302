// stl.cpp

#include "volsort.h"

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void stl_sort(List &l, bool numeric) {
	vector<Node*> s;
	Node* current = l.head;
	while(current != NULL){
		s.push_back(current);
		current = current->next;
	}
	if(numeric){
		sort(s.begin(), s.end(),node_number_compare);
	}
	else{
		sort(s.begin(), s.end(),node_string_compare);	
	}
	for(unsigned int i = 0;i<s.size()-1;i++){
		s.at(i)->next = s.at(i+1);
	}
	int tmp = s.size()-1;
	s.at(tmp)->next = NULL;
	l.head = s.at(0);
}

