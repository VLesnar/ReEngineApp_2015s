#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Veronica Lesnar"); // Window Name
	m_pSystem->SetWindowWidth(720); //Set window dimensions
	m_pSystem->SetWindowHeight(720);
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);//Set clear color
}
void AppClass::InitVariables(void)
{
	//Set the camera position
	m_pCameraMngr->SetPosition(vector3(0.0f, 0.0f, 18.0f));
	//Load the model
	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve");
}
void AppClass::Update(void)
{
#pragma region DOES NOT NEED CHANGES
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Call the arcball method
	ArcBall();
#pragma endregion
#pragma region Your code goes here
	//Calculate delta and total times
	static double dTotalTime = 0.0; //Total time of the simulation
	double dDeltaTime = m_pSystem->LapClock(); //time difference between function calls
	dTotalTime += dDeltaTime; //Incrementing the time differences 

	float fStartTime = 0.0f; //start of simulation
	float fEndTime = 5.0f; //end of simulation

	//float fStartAngle = 0.0f;
	//float fEndAngle = 720.0f;

	float fPercent = MapValue(static_cast<float>(dTotalTime), fStartTime, fEndTime * 2.0f, 0.0f, 1.0f);
	
	//float fCurrentAngle = glm::lerp(fStartAngle, fEndAngle, fPercent);

	//m_m4Steve = glm::rotate(IDENTITY_M4, fCurrentAngle, vector3(0.0f, 0.0f, 1.0f));

	//glm::quat qQuaternion1;	// glm library contains quaternions
	quaternion qQuaternion1;	// Identity
	glm::quat qQuaternion2 = glm::angleAxis(90.0f, vector3(0.0f, 0.0f, 1.0f));	// Allows you to initialize a quaternion without "weird" results
	glm::quat qQuaternion3 = glm::angleAxis(180.0f, vector3(0.0f, 0.0f, 1.0f));	// The first value changes the time it takes to rotate in this case

	//m_m4Steve = glm::mat4_cast(qQuaternion1); // Casts to a matrix4
	//m_m4Steve = ToMatrix4(qQuaternion1 * qQuaternion3);
	m_m4Steve = glm::mat4_cast(glm::mix(qQuaternion1, qQuaternion3, fPercent)); // Performs a slerp, don't use slerp

	// Rotation - Action you perform on an object
	// Orientation - The state in which that object is facing
	// Quaternions work with orientation not rotation

	/*static float fStartHeight = 0.0f;
	static float fEndHeight = 5.0f;

	float fHeight = glm::lerp(fStartHeight, fEndHeight, fPercent);

	m_m4Steve = m_m4Steve * glm::translate(vector3(0.0f, fHeight, 0.0f));

	// Lerp is done
	if (fPercent > 1.0f) {
		//float temp = fStartHeight;
		//fStartHeight = fEndHeight;
		//fEndHeight = temp;

		std::swap(fStartHeight, fEndHeight);
		dTotalTime = 0.0;
	}*/
#pragma endregion
#pragma region DOES NOT NEED CHANGES
	//Set the model matrix
	m_pMeshMngr->SetModelMatrix(m_m4Steve, "Steve");
	
	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	m_pMeshMngr->Print("Seconds:");
	m_pMeshMngr->PrintLine(std::to_string(dTotalTime), RERED);
	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
#pragma endregion
}
void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
	
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}
void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}