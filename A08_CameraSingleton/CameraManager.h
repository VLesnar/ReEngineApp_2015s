#pragma once
#include "RE\ReEngAppClass.h"

using namespace ReEng;
using namespace std;

class CameraManager
{
	static CameraManager* instance;
private:
	CameraManager() {};
	CameraManager(CameraManager const& other);
	matrix4 viewMatrix;
	matrix4 projectMatrix;
	matrix4 orthoMatrix;
	vector3 v3Position;
	vector3 v3Target;
	vector3 v3Up;
public:
	static CameraManager* GetInstance();
	static void ReleaseInstance();
	matrix4 GetView(void); // Gets the view matrix
	matrix4 GetProjection(bool bOrthographic); // Gets the projection matrix
	void SetPosition(vector3 v3Pos); // Sets the position of the camera
	void SetTarget(vector3 v3Targ); // Sets the target of the camera
	void SetUp(vector3 v3Up); // Sets the up vector of the camera
	void MoveForward(float fIncrement); // Move the camera forward or backward
	void MoveSideways(float fIncrement); // Move the camera left and right
	void MoveVertical(float fIncrement); // Move the camera up and down
	void ChangePitch(float fIncrement); // Orient the camera, changing its angle in X
	void ChangeRoll(float fIncrement); // Orient the camera, changing its angle in Z
	void ChangeYaw(float fIncrement); // Orient the camera, changing its angle in Y
};

