#pragma once

#include "Node.h";

class List {
private:
	Node* head;
	int count = 0;

public:
	List() {
		head = nullptr;
	}
	int getValue(Node*);
	void setValue(Node*, int);
	int getCount();
	bool isEmpty();
	Node* Next(Node*);
	Node* Prev(Node*);
	Node* getFirst();
	Node* getLast();
	Node* Add(int, Node*);
	Node* Delete(Node*);
	void Clear();
};