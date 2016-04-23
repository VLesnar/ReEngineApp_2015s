#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("SLERP - Veronica Lesnar"); // Window Name

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);
}

void AppClass::InitVariables(void)
{
	//Setting the position in which the camera is looking and its interest point
	m_pCameraMngr->SetPositionTargetAndView(vector3(12.12f, 28.52f, 11.34f), ZERO_V3, REAXISY);

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);

	//Loading the models
	m_pMeshMngr->LoadModel("Planets\\00_Sun.obj", "Sun");
	m_pMeshMngr->LoadModel("Planets\\03_Earth.obj", "Earth");
	m_pMeshMngr->LoadModel("Planets\\03A_Moon.obj", "Moon");

	// Set the matrices
	sunMatrix = IDENTITY_M4;
	earthMatrix = IDENTITY_M4;
	moonMatrix = IDENTITY_M4;

	//Setting the days duration
	m_fDay = 1.0f;
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Getting the time between calls
	double fCallTime = m_pSystem->LapClock();
	//Counting the cumulative time
	static float fRunTime = 0.0f;
	fRunTime += fCallTime * 10;

	float fStartTime = 0.0f;
	float fEndTime = 1.0f;
	float fPercent = MapValue(fRunTime, fStartTime, fEndTime, 0.0f, 1.0f);

	//Earth Orbit
	float fEarthHalfOrbTime = 182.5f * m_fDay; //Earths orbit around the sun lasts 365 days / half the time for 2 stops
	float fEarthHalfRevTime = 0.5f * m_fDay; // Move for Half a day
	float fMoonHalfOrbTime = 14.0f * m_fDay; //Moon's orbit is 28 earth days, so half the time for half a route

	// Sun
	sunMatrix = glm::scale(vector3(sunSize, sunSize, sunSize));

	// Earth
	// Calculates the Earth's spin on its own axis
	quaternion earthQuatAxis1 = glm::angleAxis(0.0f, vector3(0.0f, 1.0f, 0.0f));
	quaternion earthQuatAxis2 = glm::angleAxis(fEarthHalfOrbTime * 2, vector3(0.0f, 1.0f, 0.0f));
	
	// Earth matrix - Point Rotate, Translate, Scale
	earthMatrix = glm::rotate(IDENTITY_M4, fRunTime, vector3(0.0f, 1.0f, 0.0f)) * glm::translate(11.0f, 0.0f, 0.0f)* glm::scale(vector3(earthSize, earthSize, earthSize));
	
	// Moon
	// Calculates the Moon's spin on its own axis
	quaternion moonQuatAxis1 = glm::angleAxis(0.0f, vector3(0.0f, 1.0f, 0.0f));
	quaternion moonQuatAxis2 = glm::angleAxis(fMoonHalfOrbTime, vector3(0.0f, 1.0f, 0.0f));
	
	// Moon matrix - Point Rotate, Translate, Scale
	moonMatrix = glm::rotate(earthMatrix, fRunTime * 14.0f, vector3(0.0f, 1.0f, 0.0f)) * glm::translate(2.0f, 0.0f, 0.0f) * glm::scale(vector3(moonSize, moonSize, moonSize));

	// Axis Rotation
	earthMatrix *= glm::mat4_cast(glm::mix(earthQuatAxis2, earthQuatAxis1, fPercent));
	moonMatrix *= glm::mat4_cast(glm::mix(moonQuatAxis2, moonQuatAxis1, fPercent));
	
	//Setting the matrices
	m_pMeshMngr->SetModelMatrix(sunMatrix, "Sun");
	m_pMeshMngr->SetModelMatrix(earthMatrix, "Earth");
	m_pMeshMngr->SetModelMatrix(moonMatrix, "Moon");

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	static int nEarthOrbits = 0;
	static int nEarthRevolutions = 0;
	static int nMoonOrbits = 0;

	nEarthRevolutions = floor(fRunTime); // Increments everytime the Earth spins once on its own axis
	nEarthOrbits = floor(fRunTime) / 365;	// Increments everytime the Earth spins once around the Sun
	nMoonOrbits = floor(fRunTime) / 28;	// Increments everytime the Moon spins once around the Earth

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	
	m_pMeshMngr->Print("Time:");
	m_pMeshMngr->PrintLine(std::to_string(fRunTime));

	m_pMeshMngr->Print("Day:");
	m_pMeshMngr->PrintLine(std::to_string(m_fDay));

	m_pMeshMngr->Print("E_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthOrbits));

	m_pMeshMngr->Print("E_Revolutions:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthRevolutions));

	m_pMeshMngr->Print("M_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nMoonOrbits));

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);
}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default:
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
	
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}