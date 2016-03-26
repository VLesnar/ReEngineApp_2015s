/*	Veronica Lesnar
	ICE 03 - Singletons */
#include "Mesh.h"

// Constructor
Mesh::Mesh(string nm) {
	name = nm;
}

// Overloads << so we can print to the console
ostream& operator<<(ostream& os, Mesh& mesh) {
	os << mesh.name << endl;
	return os;
}