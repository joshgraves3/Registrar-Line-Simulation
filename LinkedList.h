#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "ListNode.h"
using namespace std;

template <typename T>
class LinkedList {
	
	public:
		int size;
		ListNode<T>* front;
		ListNode<T>* back;
		LinkedList(T d);
		~LinkedList();
		void insertBack(T d);
		void insertFront(T d);
		T removeBack();
		T removeFront();
		T remove(T d);
		int search(T d);
};

template <typename T>
LinkedList<T>::LinkedList(T d) {
	
	ListNode<T>* firstNode = new ListNode<T>(d); //make a new node when you instantiate the list 
	size = 1;
	front = firstNode; //the first node will be both front and back 
	back = firstNode;
}

template <typename T>
LinkedList<T>::~LinkedList() {
	
	ListNode<T>* temp = front; //go through each node and delete it 
	while (front != NULL) {
		temp = front;
		front->next->prev = NULL;
		front = front->next;
		delete temp;
	}
}

template <typename T>
void LinkedList<T>::insertBack(T d) {
	
	ListNode<T>* newNode = new ListNode<T>(d); //make a new node to insert 
	back->next = newNode; //back next will now be the "new" back 
	newNode->prev = back; //new node back = current back 
	back = newNode; //make the new node the back of the list and increase size 
	size++;
}

template <typename T>
void LinkedList<T>::insertFront(T d) {

	ListNode<T>* newNode = new ListNode<T>(d); //same as insert back, but opposite ways for the pointers 
	front->prev = newNode;
	newNode->next = front;
	front = newNode;
	size++;

}

template <typename T>
T LinkedList<T>::removeBack() {

	T returnVal = back->data;
	ListNode<T>* temp = back;
	back = back->prev;
	back->next = NULL;
	delete temp;
	size--;
	return returnVal;

}

template <typename T>
T LinkedList<T>::removeFront() {

	T returnVal = front->data;
	ListNode<T>* temp = front;
	front = front->next;
	front->prev = NULL;
	delete temp;
	size--;
	return returnVal;

}

template <typename T>
T LinkedList<T>::remove(T d) {

	ListNode<T>* current = front;
	while (current->data != d) { //go through each node to find the data 
		current = current->next;
		if (current == NULL) //if you don't find it return -1
			return -1;
	}

	if (current == front) { //if you find the data at the front, move front to the one after it 
		front = current->next;
	}
	else {
		current->prev->next = current->next; //else, move the pointer to the node to the one in front of it
	}

	if (current == back) { //if you find the data at the back, move back to the one behind it 
		back = current->prev;
	}
	else {
		current->next->prev = current->prev; //else, set the pointer to it from the front to the one behind it 
	}

	current->next = NULL; //set the node to be deleted pointers to null then delete it and decrease the size 
	current->prev = NULL;
	size--;
	return current->data;

}

template <typename T>
int LinkedList<T>::search(T d) {

	ListNode<T>* current = front; //start at the front of the list 
	int index = -1;

	while (current != NULL) {
		if (current->data == d) //check if data = what the user gave
			return ++index; //if it is at the front, it will return 0
		else {
			current = current->next; //if not, move to next node
			++index; //increase index
		}
	}

	return -1; //if it isn't found, return -1
}
#endif






