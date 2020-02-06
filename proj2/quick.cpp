// quick.cpp

#include "volsort.h"
#include <string>
#include <iostream>

// Prototypes
void quickSort(Node* arr[], int low, int high);
int partition (Node* arr[], int low, int high);
void quickSort_S(Node* arr[], int low, int high);
int partition_S(Node* arr[], int low, int high);

//Node *qsort(Node *head, bool numeric);
//void  partition(Node *head,Node *&left,Node *&right, bool numeric);
//Node *concatenate(Node *left, Node *right);

// Implementations

void quick_sort(List &l, bool numeric){
	//fill array with Node*
	Node* current = l.head;
	Node* array[l.size];
	for(unsigned int i = 0;i<l.size;i++){
		array[i] = current;
		current = current->next;
	}
	if(numeric){
		quickSort(array,0,l.size-1);
	}
	else{
		quickSort_S(array,0,l.size-1);
	}
	//asssigns array elements into a list
	for(unsigned int i = 0;i<l.size-1;i++){
		array[i]->next = array[i+1];
	}

	array[l.size-1]->next = NULL;
	l.head = array[0];
}
int partition (Node* arr[], int low, int high) {
	int pivot = arr[low]->number;
	int i  = low;
	int j  = high;
	Node *temp;

	while(i < j){
		//gets index of left most element that is less than pivot
		while(i <= high && arr[i]->number <= pivot){
			i++;
		}
		//gets index of right most element that is greater than pivot
		while(j >= low && arr[j]->number > pivot){
			j--;
		}
		//swap the element that is greater than pivot with element that is less than pivot
		//moves lesser elements to the left and greater elements to right
		if(i < j) {
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}

	//swapping pivot with right most element and return its index
	temp = arr[low];
	arr[low] = arr[j];
	arr[j] = temp;
	return j;
}
void quickSort(Node* arr[], int low, int high){
	if (low < high){
		//"divide" the array by splitting into smaller arrays
		int pivot = partition(arr, low, high);
		//"conquer" by recursing left and right partition
		quickSort(arr, low, pivot - 1);
		quickSort(arr, pivot + 1, high);
	}
}
int partition_S(Node* arr[], int low, int high) {
	string pivot = arr[low]->string;
	int i  = low;
	int j  = high;
	Node *temp;

	while(i < j){
		while(i <= high && arr[i]->string.compare(pivot) <= 0) i++;
		while(j >= low && arr[j]->string.compare(pivot) > 0) j--;

		if(i < j) {
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
		}
	}

	temp = arr[low];
	arr[low] = arr[j];
	arr[j] = temp;
	return j;
}
void quickSort_S(Node* arr[], int low, int high){
	if (low < high){
		int pivot = partition_S(arr, low, high);
		quickSort_S(arr, low, pivot - 1);
		quickSort_S(arr, pivot + 1, high);
	}
}

/*Node *qsort(Node *head, bool numeric) {

  }

  Node *partition(List *l, List *left, List *right, bool numeric) {

  }
  Node *concatenate(Node *left, Node *right) {

  }*/


