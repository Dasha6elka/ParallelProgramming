#include "List.h";

int List::getValue(Node* node) {
	return node->field;
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
		if (current->ptr == nullptr) {
			return nullptr;
		}
		current = current->ptr;
	}

	return current;
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