/*	Veronica Lesnar
	ICE 03 - Singletons */
#ifndef  _MESH_H
#define _MESH_H

#include <string>
#include <iostream>

using namespace std;

#endif // _MESH_H

class Mesh {
public:
	Mesh(string nm);	// Constructor
	friend ostream& operator<<(ostream& os, Mesh& mesh);	// Operator Overload
private:
	string name;	// Holds the name field of the mesh object
};