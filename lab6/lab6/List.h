#include "Node.h";

class List {
	Node* head;
	int count = 0;
	Node* Prev(Node *);

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

int List::getValue(Node* node) {
	return node->field;
}

void List::setValue(Node* node, int value) {
	node->field = value;
}

int List::getCount() {
	return count;
}

bool List::isEmpty() {
	return head == nullptr;
}

Node* List::Next(Node* node) {
	if (isEmpty()) {
		return nullptr;
	}

	return node->ptr;
}

Node* List::Prev(Node* node) {
	if (isEmpty() || node == nullptr) {
		return nullptr;
	}
	Node* current = head;
	while (current->ptr != node) {
		current = current->ptr;
	}

	return current;
}

Node* List::getFirst() {
	return head;
}

Node* List::getLast() {
	Node* next = head;
	while (Next(next) != nullptr) {
		next = Next(next);
	}

	return next;
}

Node* List::Add(int value, Node* node = nullptr) {
	Node* element = new Node();
	element->field = value;
	count++;
	if (node == nullptr) {
		if (head == nullptr) {
			element->ptr = node;
		}
		else {
			element->ptr = head;
		}
		head = element;
		return element;
	}
	element->ptr = node->ptr;
	node->ptr = element;

	return element;
}

Node* List::Delete(Node* node) {
	if (node == nullptr) {
		return nullptr;
	}
	count--;
	if (node == head) {
		head = node->ptr;
		delete node;

		return head;
	}
	Node* prev = Prev(node);
	prev->ptr = node->ptr;
	delete node;

	return prev;
}

void List::Clear() {
	class Node* current = head;
	if (current == nullptr) {
		return;
	}
	do {
		Node* next = current;
		current = Next(current);
		delete next;
	} while (current != nullptr);
	count = 0;
	head = nullptr;
}