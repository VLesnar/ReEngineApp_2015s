#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Veronica Lesnar E12"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	//Initialize positions
	m_v3O1 = vector3(-2.5f, 0.0f, 0.0f);
	m_v3O2 = vector3(2.5f, 0.0f, 0.0f);

	//Load Models
	m_pMeshMngr->LoadModel("Minecraft\\Steve.obj", "Steve");
	m_pMeshMngr->LoadModel("Minecraft\\Creeper.obj", "Creeper");

	//// Steve
	std::vector<vector3> vertexList = m_pMeshMngr->GetVertexList("Steve");
	sphere1 = new MyBoundingSphereClass(vertexList);

	m_pSphere1 = new PrimitiveClass();
	m_pSphere1->GenerateSphere(sphere1->GetRadius(), 10, REWHITE);


	//// Creeper
	vertexList = m_pMeshMngr->GetVertexList("Creeper");
	sphere2 = new MyBoundingSphereClass(vertexList);
	
	m_pSphere2 = new PrimitiveClass();
	m_pSphere2->GenerateSphere(sphere2->GetRadius(), 10, REWHITE);

	// Unused code from In-Class example
	//uint nVertexCount = vertexList.size();

	//vector3 v3Min;	// Initialized as 0
	//vector3 v3Max;	// Initialized as 0

	//if (nVertexCount > 0)
	//{
	//	v3Min = vertexList[0];
	//	v3Max = vertexList[0];
	//}

	//// Checks for max and min
	//for (uint i = 0; i < nVertexCount; i++) {
	//	if (vertexList[i].x > v3Max.x) {
	//		v3Max.x = vertexList[i].x;
	//	}
	//	else if (vertexList[i].x < v3Min.x) {	// else if cuts some calculations
	//		v3Min.x = vertexList[i].x;
	//	}

	//	if (vertexList[i].y > v3Max.y) {
	//		v3Max.y = vertexList[i].y;
	//	}
	//	else if (vertexList[i].y < v3Min.y) {
	//		v3Min.y = vertexList[i].y;
	//	}

	//	if (vertexList[i].z > v3Max.z) {
	//		v3Max.z = vertexList[i].z;
	//	}
	//	else if (vertexList[i].z < v3Min.z) {
	//		v3Min.z = vertexList[i].z;
	//	}
	//}

	//m_v3Center1 = (v3Max + v3Min) / 2.0f;
	//m_fRadius1 = glm::distance(m_v3Center1, v3Max);	// Can use v3Max or v3Min for the second argument
	
	//vertexList = m_pMeshMngr->GetVertexList("Creeper");
	//nVertexCount = vertexList.size();

	//if (nVertexCount > 0)
	//{
	//	v3Min = vertexList[0];
	//	v3Max = vertexList[0];
	//}

	//// Checks for max and min
	//for (uint i = 0; i < nVertexCount; i++) {
	//	if (vertexList[i].x > v3Max.x) {
	//		v3Max.x = vertexList[i].x;
	//	}
	//	else if (vertexList[i].x < v3Min.x) {	// else if cuts some calculations
	//		v3Min.x = vertexList[i].x;
	//	}

	//	if (vertexList[i].y > v3Max.y) {
	//		v3Max.y = vertexList[i].y;
	//	}
	//	else if (vertexList[i].y < v3Min.y) {
	//		v3Min.y = vertexList[i].y;
	//	}

	//	if (vertexList[i].z > v3Max.z) {
	//		v3Max.z = vertexList[i].z;
	//	}
	//	else if (vertexList[i].z < v3Min.z) {
	//		v3Min.z = vertexList[i].z;
	//	}
	//}

	//m_v3Center2 = (v3Max + v3Min) / 2.0f;
	//m_fRadius2 = glm::distance(m_v3Center2, v3Max);	// Can use v3Max or v3Min for the second argument

	//m_pSphere2 = new PrimitiveClass();
	//m_pSphere2->GenerateSphere(m_fRadius2, 10, REPURPLE);
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

	ArcBall();

	//Set the model matrices for both objects and Bounding Spheres
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O1) * ToMatrix4(m_qArcBall), "Steve");
	m_pMeshMngr->SetModelMatrix(glm::translate(m_v3O2), "Creeper");
	sphere1->SetModelMatrix(m4Model1);
	sphere2->SetModelMatrix(m4Model2);

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	bool bAreColliding = false;
	
	// Collision Checking
	m_pMeshMngr->PrintLine("x: " + std::to_string(m_v3Center1.x) + " y: " + std::to_string(m_v3Center1.y) + " z: " + std::to_string(m_v3Center1.z), REBLACK);
	float sumRadius = (sphere1->GetRadius() + sphere2->GetRadius()) * 2.0f;
	std::cout << "sphere1 radius: " << sphere1->GetRadius() << std::endl;
	std::cout << "sphere2 radius: " << sphere2->GetRadius() << std::endl;
	std::cout << "sumRadius: " << sumRadius << std::endl;
	float distX = sphere1->GetCenter().x - sphere2->GetCenter().x;
	float distY = sphere1->GetCenter().y - sphere2->GetCenter().y;
	float distZ = sphere1->GetCenter().z - sphere2->GetCenter().z;
	float sphereDistance = sqrt((distX * distX) + (distY * distY) + (distZ * distZ));
	std::cout << "sphereDistance: " << sphereDistance << std::endl;
	if (sumRadius > sphereDistance) {
		bAreColliding = true;

		m_pSphere1->GenerateSphere(sphere1->GetRadius(), 10, RERED);
		m_pSphere2->GenerateSphere(sphere2->GetRadius(), 10, RERED);
	}
	else {
		bAreColliding = false;

		m_pSphere1->GenerateSphere(sphere1->GetRadius(), 10, REWHITE);
		m_pSphere2->GenerateSphere(sphere2->GetRadius(), 10, REWHITE);
	}

	//print info into the console
	printf("FPS: %d            \r", nFPS);//print the Frames per Second
	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);

	if (bAreColliding) {
		m_pMeshMngr->PrintLine("They are colliding! :I", RERED);
	}
	else {
		m_pMeshMngr->PrintLine("They are not colliding! :D", REGREEN);
	}

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
	default: //Perspective
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY); //renders the XY grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToQueue(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}

	// Steve
	m4Model1 = m_pMeshMngr->GetModelMatrix("Steve") * glm::scale(vector3(sphere1->GetRadius() * 2.0f));	// Sets this to Steve's location
	matrix4 m4View = m_pCameraMngr->GetViewMatrix();
	matrix4 m4Projection = m_pCameraMngr->GetProjectionMatrix();
	m_pSphere1->Render(m4Projection, m4View, m4Model1);

	// Creeper
	m4Model2 = m_pMeshMngr->GetModelMatrix("Creeper") * glm::scale(vector3(sphere1->GetRadius() * 2.0f));;
	m_pSphere2->Render(m4Projection, m4View, m4Model2);

	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers

	// Unused code from In-Class example
	//m_pSphere1->Render(m4Projection, m4View, m4Model);
	//m_pMeshMngr->AddSphereToQueue(m4Model, RERED, WIRE);

	//m4Model = m_pMeshMngr->GetModelMatrix("Creeper") * glm::translate(m_v3Center2) * glm::scale(vector3(m_fRadius2 * 2.0f));

	//m_pSphere2->Render(m4Projection, m4View, m4Model);
	//m_pMeshMngr->AddSphereToQueue(m4Model, RERED, WIRE);
}

void AppClass::Release(void)
{
	if (m_pSphere1 != nullptr) {
		delete m_pSphere1;
		m_pSphere1 = nullptr;
	}

	if (m_pSphere2 != nullptr) {
		delete m_pSphere2;
		m_pSphere2 = nullptr;
	}

	if (sphere1 != nullptr) {
		delete sphere1;
		sphere1 = nullptr;
	}

	if (sphere2 != nullptr) {
		delete sphere2;
		sphere2 = nullptr;
	}
	super::Release(); //release the memory of the inherited fields
}