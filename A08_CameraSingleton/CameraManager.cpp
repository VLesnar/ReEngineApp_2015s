#include "CameraManager.h"

CameraManager* CameraManager::GetInstance() {
	if (instance == nullptr) {
		instance = new CameraManager();
	}
	return instance;
}

void CameraManager::ReleaseInstance() {
	if (instance != nullptr) {
		delete instance;
		instance = nullptr;
	}
}
matrix4 CameraManager::GetView(void) {
	return viewMatrix = glm::lookAt(v3Position, v3Target, v3Up);
}

matrix4 CameraManager::GetProjection(bool bOrthographic) {
	if (bOrthographic) {
		return projectMatrix = glm::ortho(-7.5f, 7.5f, -7.5f, 7.5f, 0.01f, 1000.0f);
	}
	else {
		return projectMatrix = glm::perspective(45.0f, 1080.0f / 768.0f, 0.01f, 1000.0f);
	}
}

void CameraManager::SetPosition(vector3 v3Pos) {
	v3Position = v3Pos;
}

void CameraManager::SetTarget(vector3 v3Targ) {
	v3Forward = v3Targ - v3Position;
	glm::normalize(v3Forward);
	v3Target = v3Position + v3Forward;
}

void CameraManager::SetUp(vector3 v3U) {
	v3Up = glm::normalize(v3U);
}

void CameraManager::MoveForward(float fIncrement) {
	SetPosition(vector3(v3Position.x, v3Position.y, v3Position.z + fIncrement));
	SetTarget(vector3(v3Target.x, v3Target.y, v3Target.z + fIncrement));
}

void CameraManager::MoveSideways(float fIncrement) {
	SetPosition(vector3(v3Position.x + fIncrement, v3Position.y, v3Position.z));
	SetTarget(vector3(v3Target.x + fIncrement, v3Target.y, v3Target.z));
}

void CameraManager::MoveVertical(float fIncrement) {
	SetPosition(vector3(v3Position.x, v3Position.y + fIncrement, v3Position.z));
	SetTarget(vector3(v3Target.x, v3Target.y + fIncrement, v3Target.z));
}

void CameraManager::ChangePitch(float fIncrement) {
	SetTarget(vector3(v3Target.x, v3Target.y + fIncrement, v3Target.z + fIncrement));
	SetUp(vector3(v3Up.x, v3Up.y + fIncrement, v3Up.z + fIncrement));
	//cout << "v3Forward: (" << v3Forward.x << ", " << v3Forward.y << ", " << v3Forward.z << ")" << endl;
	//cout << "v3Target: (" << v3Target.x << ", " << v3Target.y << ", " << v3Target.z << ")" << endl;
	//cout << "v3Position: (" << v3Position.x << ", " << v3Position.y << ", " << v3Position.z << ")" << endl;
	//cout << "v3Up: (" << v3Up.x << ", " << v3Up.y << ", " << v3Up.z << ")" << endl;
}

void CameraManager::ChangeRoll(float fIncrement) {

	//SetUp(vector3(v3Up.x + cos(glm::radians(fIncrement)), v3Up.y + sin(glm::radians(fIncrement)), v3Up.z) * quat);
	SetUp(vector3(v3Up.x + fIncrement, v3Up.y + fIncrement, v3Up.z));
	//cout << "v3Forward: (" << v3Forward.x << ", " << v3Forward.y << ", " << v3Forward.z << ")" << endl;
	//cout << "v3Target: (" << v3Target.x << ", " << v3Target.y << ", " << v3Target.z << ")" << endl;
	//cout << "v3Position: (" << v3Position.x << ", " << v3Position.y << ", " << v3Position.z << ")" << endl;
	//cout << "v3Up: (" << v3Up.x << ", " << v3Up.y << ", " << v3Up.z << ")" << endl;
}

void CameraManager::ChangeYaw(float fIncrement) {
	SetTarget(vector3(v3Target.x + fIncrement, 0.0f, v3Target.z + fIncrement));
	//cout << "v3Forward: (" << v3Forward.x << ", " << v3Forward.y << ", " << v3Forward.z << ")" << endl;
	//cout << "v3Target: (" << v3Target.x << ", " << v3Target.y << ", " << v3Target.z << ")" << endl;
	//cout << "v3Position: (" << v3Position.x << ", " << v3Position.y << ", " << v3Position.z << ")" << endl;
	//cout << "v3Up: (" << v3Up.x << ", " << v3Up.y << ", " << v3Up.z << ")" << endl;
}