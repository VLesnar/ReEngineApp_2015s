/*	Veronica Lesnar
	HW 02 */

#ifndef _LIST_H
#define _LIST_H

#include "Node.h"
#include <string>
#include <iostream>
#include <time.h>

using namespace::std;

#endif
class List
{
private:
	Node *head;	// Holds the first node
public:
	List();
	~List();
	void Add();
};

