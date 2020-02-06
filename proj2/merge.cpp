// merge.cpp

#include "volsort.h"

#include <iostream>
// Prototypes

void mergesort(Node* arr[],int low,int high);
void merge(Node* arr[],int low,int middle,int high);
void mergesort_S(Node* arr[],int low,int high);
void merge_S(Node* arr[],int low,int middle,int high);

//Node *msort(Node *head, bool numeric);
//void  split(Node *head, Node *&left, Node *&right);
//Node *merge(Node *left, Node *right,Node *sorting,bool numeric);

// Implementations

void merge_sort(List &l, bool numeric) {
	Node* current = l.head;
	Node* array[l.size];
	for(unsigned int i = 0;i<l.size;i++){
		array[i] = current;
		current = current->next;
	}
	if(numeric){
		mergesort(array,0,l.size-1);
	}
	else{
		mergesort_S(array,0,l.size-1);
	}
	for(unsigned int i = 0;i<l.size-1;i++){
		array[i]->next = array[i+1];
	}

	array[l.size-1]->next = NULL;
	l.head = array[0];

}
void mergesort(Node *arr[],int low, int high){	
	if(high > low){
		int middle = (low+high)/2;
		//recur on left side
		mergesort(arr,low,middle);
		//recur on right side
		mergesort(arr,middle+1,high);
		merge(arr,low,middle,high);
	}
}
//"conquer" portion - create a temp array that adds the elements in order
//by comparing the left side with the right side and placing the smaller one to the left
void merge(Node *arr[],int low,int middle,int high){
	int i = low,j = middle+1,k = 0;
	Node *t[high-low+1];

	//iterate through left and right side of array checking for lesser element
	while(i<=middle && j<=high){
		//lesser element goes to the left, greater element goes to the right
		//k keeps track of index in temp array while i and j keeps track of index
		//in their respective side of the array
		if(arr[i]->number <= arr[j]->number){
			t[k] = arr[i];
			k++;
			i++;
		}
		else{
			t[k] = arr[j];
			k++;
			j++;
		}
	}
	//if there are any more elements in the left side add them to 
	//temp array
	while(i <= middle){
		t[k] = arr[i];
		k++;
		i++;
	}
	//if there are any more elements in the right side add them to
	//temp array
	while(j <= high){
		t[k] = arr[j];
		k++;
		j++;
	}
	//copy temp array to orginal array
	for(i = low;i<=high;i++){
		arr[i] = t[i-low];
	}


}
//"_S" functions work the same they just compare strings instead of ints
void mergesort_S(Node *arr[],int low, int high){	
	if(high > low){
		int middle = (low+high)/2;
		mergesort_S(arr,low,middle);
		mergesort_S(arr,middle+1,high);
		merge_S(arr,low,middle,high);
	}
}
void merge_S(Node *arr[],int low,int middle,int high){
	int i = low,j = middle+1,k = 0;
	Node *t[high-low+1];

	while(i<=middle && j<=high){
		if(arr[i]->string.compare(arr[j]->string) <= 0){
			t[k] = arr[i];
			k++;
			i++;
		}
		else{
			t[k] = arr[j];
			k++;
			j++;
		}
	}
	while(i <= middle){
		t[k] = arr[i];
		k++;
		i++;
	}
	while(j <= high){
		t[k] = arr[j];
		k++;
		j++;
	}
	for(i = low;i<=high;i++){
		arr[i] = t[i-low];
	}


}

/*
   Node *msort(Node *head, bool numeric) {

   }

   void split(Node *head, Node *&left, Node *&right) {
   }

   Node *merge(Node *left, Node *right,Node *sorting,bool numeric) {

   }*/

