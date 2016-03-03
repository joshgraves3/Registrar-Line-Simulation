#ifndef LISTNODE_H
#define LISTNODE_H
#include <iostream>
using namespace std;

template <typename T>
class ListNode {
	public:
		T data;
		ListNode *next;
		ListNode *prev;
		ListNode();
		ListNode(T d);
		~ListNode();
};

//default constructor
template <typename T>
ListNode<T>::ListNode() {}

//constructor to set data and set next and prev pointers initially to null
template <typename T>
ListNode<T>::ListNode(T d) {
	data = d;
	next = NULL;
	prev = NULL;
}

//destructor to set node pointers to null to avoid memory leaks
template <typename T>
ListNode<T>::~ListNode() {
	next = NULL;
	prev = NULL;
}

#endif