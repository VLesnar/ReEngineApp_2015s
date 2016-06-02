#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Assignment  06 - LERP"); // Window Name
}

void AppClass::InitVariables(void)
{
	m_pCameraMngr->SetPositionTargetAndView(vector3(0.0f, 0.0f, 15.0f), ZERO_V3, REAXISY);

	// Color of the screen
	m_v4ClearColor = vector4(REBLACK, 1); // Set the clear color to black

	m_pMeshMngr->LoadModel("Sorted\\WallEye.bto", "WallEye");

	fDuration = 1.0f;

	// Holds the positions of the spheres and of WallEye's movement
	positions.push_back(vector3(-4.0f, -2.0f, 5.0f));
	positions.push_back(vector3(1.0f, -2.0f, 5.0f));
	positions.push_back(vector3(-3.0f, -1.0f, 3.0f));
	positions.push_back(vector3(2.0f, -1.0f, 3.0f));
	positions.push_back(vector3(-2.0f, 0.0f, 0.0f));
	positions.push_back(vector3(3.0f, 0.0f, 0.0f));
	positions.push_back(vector3(-1.0f, 1.0f, -3.0f));
	positions.push_back(vector3(4.0f, 1.0f, -3.0f));
	positions.push_back(vector3(0.0f, 2.0f, -5.0f));
	positions.push_back(vector3(5.0f, 2.0f, -5.0f));
	positions.push_back(vector3(1.0f, 3.0f, -5.0f));

	count = 0; // How many times WallEye LERPS, or goes from one point to the next 
	start = 0; // The starting point of WallEye's LERP
	end = 1; // The ending point of WallEye's LERP
}

void AppClass::Update(void)
{
#pragma region Does not change anything here
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();
#pragma region

#pragma region Does not need changes but feel free to change anything here
	//Lets us know how much time has passed since the last call
	double fTimeSpan = m_pSystem->LapClock(); //Delta time (between frame calls)

	//cumulative time
	static double fRunTime = 0.0f; //How much time has passed since the program started
	fRunTime += fTimeSpan; 
#pragma endregion

#pragma region Your Code goes here
	// Adds the spheres by translating their position to the index in the vector list then scaling them
	for (int i = 0; i < positions.size(); i++) {
		m_pMeshMngr->AddSphereToQueue(glm::translate(positions[i]) * glm::scale(vector3(0.1f, 0.1f, 0.1f)), vector3(1.0f, 0.0f, 0.0f), 3);
	}

	// Checks to make sure the indices don't go out of bounds for start and end
	if (end >= 11) {
		end = 0.0f;
	}
	if (start >= 11) {
		start = 0.0f;
		fRunTime = 0.0f;
		count = 0.0f;
	}
	// Set the position of WallEye using a lerp between the beginning point and the end point and a vector between 0.0-1.0
	m_pMeshMngr->SetModelMatrix(glm::translate(glm::lerp(positions[start], positions[end], vector3(fRunTime - count, fRunTime - count, fRunTime - count))), "WallEye");
	start = floor(fRunTime); // Based on fRunTime rounded down to give the index
	end = floor(fRunTime + 1);	// Based on fRunTime rounded down + 1 to give the next index
	count = floor(fRunTime);	// Counts how many LERPS have passed



#pragma endregion

#pragma region Does not need changes but feel free to change anything here
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("count:");
	m_pMeshMngr->Print(std::to_string(count), REWHITE);
	m_pMeshMngr->Print("\nfTimeSpan:");
	m_pMeshMngr->Print(std::to_string(fTimeSpan), REWHITE);
	m_pMeshMngr->Print("\nfRunTime:");
	m_pMeshMngr->Print(std::to_string(fRunTime), REWHITE);
	m_pMeshMngr->Print("\nFPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();
	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToRenderListBasedOnCamera(m_pCameraMngr->GetCameraMode());
	m_pMeshMngr->Render(); //renders the render list
	m_pMeshMngr->ClearRenderList(); //Reset the Render list after render
	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}