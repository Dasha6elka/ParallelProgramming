#pragma once

class LinkedList {
	// Struct inside the class LinkedList
	// This is one node which is not needed by the caller. It is just
	// for internal work.
	struct Node {
		int x;
		Node *next;
	};

	// public member
public:
	// constructor
	LinkedList() {
		head = nullptr; // set head to NULL
	}

	// destructor
	~LinkedList() {
		Clear();
	}

	// This prepends a new value at the beginning of the list
	void Add(int val) {
		Node *n = new Node();   // create new Node
		n->x = val;             // set value
		n->next = head;         // make the node point to the next node
		head = n;               // last but not least, make the head point at the new node.
		count++;
	}

	// returns the first element in the list and deletes the Node.
	// caution, no error-checking here!
	int Pop() {
		Node *n = head;
		int ret = n->x;
		head = head->next;
		delete n;
		count--;
		return ret;
	}

	int Count() {
		return count;
	}

	void Clear() {
		Node *next = head;

		while (next) {              // iterate over all elements
			Node *delete_me = next;
			next = next->next;     // save pointer to the next element
			delete delete_me;       // delete the current entry
		}

		count = 0;
	}

	// private member
private:
	Node *head; // this is the private member variable. It is just a pointer to the first Node

	int count;
};