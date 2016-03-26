/*	Veronica Lesnar
	ICE 03 - Singletons */
#include "Main.h"

MeshManager* MeshManager::instance = nullptr;
int main() {
	MeshManager* oMeshManager = MeshManager::GetInstance();

	oMeshManager->PrintContents();
	
	oMeshManager->AddModel("Duck.obj");
	oMeshManager->AddModel("Horse.obj");
	oMeshManager->AddModel("Bird.obj");
	oMeshManager->AddModel("Dog.obj");

	oMeshManager->PrintContents();

	cout << "Adding one additional object." << endl;

	oMeshManager->AddModel("Cat.obj");
	oMeshManager->PrintContents();

	cout << "Releasing the MeshManager instance and creating a new one.\n" << endl;

	MeshManager::ReleaseInstance();

	oMeshManager = MeshManager::GetInstance();

	oMeshManager->PrintContents();

	oMeshManager->AddModel("House.obj");
	oMeshManager->AddModel("Train.obj");
	oMeshManager->AddModel("Car.obj");
	oMeshManager->AddModel("Stove.obj");
	
	oMeshManager->PrintContents();
	
	MeshManager::ReleaseInstance();

	getchar();
	return 0;
}