/*	Veronica Lesnar
	ICE 03 - Singletons */
#include "MeshManager.h"

// Acts as the constructor and creates the object
MeshManager* MeshManager::GetInstance() {
	if (instance == nullptr) {
		instance = new MeshManager();
	}
	return instance;
}

// Acts as the destructor
void MeshManager::ReleaseInstance() {
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}

void MeshManager::AddModel(string name) {
	objs.push_back(Mesh(name));
}

void MeshManager::PrintContents() {
	cout << "Meshes in list: " << objs.size() << endl;
	for (int i = 0; i < objs.size(); i++) {
		cout << objs[i];
	}
}