#ifndef GENQUEUE_H
#define GENQUEUE_H
#include "ListNode.h"
#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;

template <typename T>
class GenQueue { //queue class based on listnodes 

	public:

		GenQueue();
		~GenQueue();

		void insert(T item);
		T remove();
		T peek();
		bool isEmpty();

		int size;
		ListNode<T>* head; //make a pointer to front and back of the queue
		ListNode<T>* tail;
};

template <typename T>
GenQueue<T>::GenQueue() {

	size = 0; //start size == 0 and head/tail null because there is not two nodes yet 
	head = NULL;
	tail = NULL;

}

template <typename T>
GenQueue<T>::~GenQueue(){

	ListNode<T>* temp = head;
	while (head != 0) { //go through each node and delete/set pointers to null
		temp = head;
		head->prev->next = NULL;
		head = head->prev;
		delete temp;
	}

}

template <typename T>
void GenQueue<T>::insert(T item) {

	ListNode<T>* newNode = new ListNode<T>(item); //make a new node to insert
	if (isEmpty()) {
		head = tail = newNode; //check if it is the first node
	}
	else {
		newNode->next = tail; //set pointers for the new node 
		tail->prev = newNode;
		newNode->prev = NULL;
		tail = newNode; //make the tail = the new node 
	}
	size++; //increase size 

}

template <typename T>
T GenQueue<T>::remove() {
	ListNode<T>* removed; 
	T temp;
	if (isEmpty()) {
		try {
			throw "The queue is empty."; //throw an exception if the queue is empty 
		}
		catch (const char* message){
			cerr << message << endl;
		}
	}

	if (size == 1) { //if there is only one item left, set both pointers to null
		removed = head;
		temp = head->data;
		head = tail = NULL;
		delete removed;
	}
	else {
		removed = head; //else, move the head back and set appropriate pointers to null
		head->prev->next = NULL;
		temp = head->data;
		head = head->prev;
		delete removed;
	}

	size--; //decrease size 
	return temp; //return the data
}

template <typename T>
bool GenQueue<T>::isEmpty() {
	return (size == 0); //if size = 0, the queue will be empty
}

template <typename T>
T GenQueue<T>::peek() {
	return head->data;
}

#endif