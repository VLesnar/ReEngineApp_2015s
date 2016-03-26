/*	Veronica Lesnar
	HW 02 */

#ifndef _NODE_H
#define _NODE_H

#endif
struct Node
{
public:
	int name; // Holds the name of the Thing
	Node *next; // Points to the next item in the list
	Node(char let);	// Constructor
	~Node();	// Destructor
};