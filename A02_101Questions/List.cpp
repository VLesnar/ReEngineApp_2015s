/*	Veronica Lesnar
	HW 02 */

#include "List.h"

List::List() {
	head = NULL;
}

List::~List() {
	while (head != NULL) {
		Node *n = head->next;
		delete head;
		head = n;
	}
}

void List::Add() {
	char value = 'A' + (rand() % 26);
	cout << "Thing " << value << " has been created." << endl;
	Node *n = new Node(value);
	n->next = head;
	head = n;
}