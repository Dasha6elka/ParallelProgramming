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
	int getCount();
	bool isEmpty();
	Node* Next(Node*);
	Node* Prev(Node*);
	Node* getLast();
	Node* Add(int, Node*);
	void Clear();
};