/*	Veronica Lesnar
	ICE 03 - Singletons */
#ifndef  _MESHMANAGER_H
#define _MESHMANAGER_H

#include <vector>
#include "Mesh.h"

using namespace std;

#endif // _MESHMANAGER_H
class MeshManager {
	static MeshManager* instance;
private:
	MeshManager() {};
	MeshManager(MeshManager const& other);
	MeshManager& operator=(MeshManager const& other) {};
	vector<Mesh> objs; 
public:
	static MeshManager* GetInstance();
	static void ReleaseInstance();
	void PrintContents();
	void AddModel(string name);
};