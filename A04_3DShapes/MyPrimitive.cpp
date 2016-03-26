#include "MyPrimitive.h"
MyPrimitive::MyPrimitive() { }
MyPrimitive::MyPrimitive(const MyPrimitive& other) { }
MyPrimitive& MyPrimitive::operator=(const MyPrimitive& other) { return *this; }
MyPrimitive::~MyPrimitive(void) { super::Release(); }
void MyPrimitive::CompileObject(vector3 a_v3Color)
{
	m_uVertexCount = static_cast<int> (m_lVertexPos.size());
	for (uint i = 0; i < m_uVertexCount; i++)
	{
		AddVertexColor(a_v3Color);
	}

	CompleteTriangleInfo(true);
	CompileOpenGL3X();

}
//C--D
//|\ |
//| \|
//A--B
//This will make the triang A->B->C and then the triang C->B->D
void MyPrimitive::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
void MyPrimitive::GeneratePlane(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;

	vector3 pointA(-fValue, -fValue, 0.0f); //0
	vector3 pointB(fValue, -fValue, 0.0f); //1
	vector3 pointC(fValue, fValue, 0.0f); //2
	vector3 pointD(-fValue, fValue, 0.0f); //3

	vector3 pointE(fValue, -fValue, -0.001f); //1
	vector3 pointF(-fValue, -fValue, -0.001f); //0
	vector3 pointG(fValue, fValue, -0.001f); //2
	vector3 pointH(-fValue, fValue, -0.001f); //3

											  //F
	AddQuad(pointA, pointB, pointD, pointC);
	//Double sided
	AddQuad(pointE, pointF, pointG, pointH);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

											  //F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;

	float angle = 360.0f;
	float angleDegree = angle / a_nSubdivisions;
	float rad = (float)PI / 180.0f;

	// Top
	for (int i = 0; i < a_nSubdivisions; i++) {
		float x = a_fRadius * cos(angle * rad);
		float z = a_fRadius * sin(angle * rad);
		float y = a_fHeight;

		AddVertexPosition(vector3(x, 0.0f, z));

		angle -= angleDegree;

		x = a_fRadius * cos(angle * rad);
		z = a_fRadius * sin(angle * rad);
		y = a_fHeight;

		AddVertexPosition(vector3(x, 0.0f, z));
		AddVertexPosition(vector3(0.0f, y, 0.0f));
	}

	// Base
	for (int i = 0; i < a_nSubdivisions; i++) {
		float x = a_fRadius * cos(angle * rad);
		float z = a_fRadius * sin(angle * rad);
		float y = a_fHeight;

		AddVertexPosition(vector3(x, 0.0f, z));

		angle += angleDegree;

		x = a_fRadius * cos(angle * rad);
		z = a_fRadius * sin(angle * rad);
		y = a_fHeight;

		AddVertexPosition(vector3(x, 0.0f, z));
		AddVertexPosition(vector3(0.0f, 0.0f, 0.0f));
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;

	float angle = 360.0f;
	float angleDegree = angle / a_nSubdivisions;
	float rad = (float)PI / 180.0f;

	// Body
	for (int i = 0; i < a_nSubdivisions; i++) {
		float x = a_fRadius * cos(angle * rad);
		float z = a_fRadius * sin(angle * rad);
		float y = a_fHeight;

		vector3 point1 = vector3(x, 0.0f, z);
		vector3 point3 = vector3(x, y, z);

		angle -= angleDegree;

		x = a_fRadius * cos(angle * rad);
		z = a_fRadius * sin(angle * rad);
		y = a_fHeight;

		vector3 point2 = vector3(x, 0.0f, z);
		vector3 point4 = vector3(x, y, z);

		AddQuad(point1, point2, point3, point4);
	}

	// Top
	for (int i = 0; i < a_nSubdivisions; i++) {
		float x = a_fRadius * cos(angle * rad);
		float z = a_fRadius * sin(angle * rad);
		float y = a_fHeight;

		AddVertexPosition(vector3(x, y, z));

		angle -= angleDegree;

		x = a_fRadius * cos(angle * rad);
		z = a_fRadius * sin(angle * rad);
		y = a_fHeight;

		AddVertexPosition(vector3(x, y, z));
		AddVertexPosition(vector3(0.0f, y, 0.0f));
	}

	// Base
	for (int i = 0; i < a_nSubdivisions; i++) {
		float x = a_fRadius * cos(angle * rad);
		float z = a_fRadius * sin(angle * rad);
		float y = a_fHeight;

		AddVertexPosition(vector3(x, 0.0f, z));

		angle += angleDegree;

		x = a_fRadius * cos(angle * rad);
		z = a_fRadius * sin(angle * rad);
		y = a_fHeight;

		AddVertexPosition(vector3(x, 0.0f, z));
		AddVertexPosition(vector3(0.0f, 0.0f, 0.0f));
	}

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;

	float angle = 360.0f;
	float angleDegree = angle / a_nSubdivisions;
	float rad = (float)PI / 180.0f;

	// Outer Body
	for (int i = 0; i < a_nSubdivisions; i++) {
		float x = a_fOuterRadius * cos(angle * rad);
		float z = a_fOuterRadius * sin(angle * rad);
		float y = a_fHeight;

		vector3 point1 = vector3(x, 0.0f, z);
		vector3 point3 = vector3(x, y, z);

		angle -= angleDegree;

		x = a_fOuterRadius * cos(angle * rad);
		z = a_fOuterRadius * sin(angle * rad);
		y = a_fHeight;

		vector3 point2 = vector3(x, 0.0f, z);
		vector3 point4 = vector3(x, y, z);

		AddQuad(point1, point2, point3, point4);
	}

	// Inner Body
	for (int i = 0; i < a_nSubdivisions; i++) {
		float x = a_fInnerRadius * cos(angle * rad);
		float z = a_fInnerRadius * sin(angle * rad);
		float y = a_fHeight;

		vector3 point1 = vector3(x, 0.0f, z);
		vector3 point3 = vector3(x, y, z);

		angle += angleDegree;

		x = a_fInnerRadius * cos(angle * rad);
		z = a_fInnerRadius * sin(angle * rad);
		y = a_fHeight;

		vector3 point2 = vector3(x, 0.0f, z);
		vector3 point4 = vector3(x, y, z);

		AddQuad(point1, point2, point3, point4);
	}

	// Top
	for (int i = 0; i < a_nSubdivisions; i++) {
		float x = a_fOuterRadius * cos(angle * rad);
		float z = a_fOuterRadius * sin(angle * rad);
		float y = a_fHeight;

		vector3 point1 = vector3(x, y, z);

		x = a_fInnerRadius * cos(angle * rad);
		z = a_fInnerRadius * sin(angle * rad);
		y = a_fHeight;

		vector3 point2 = vector3(x, y, z);

		angle += angleDegree;

		x = a_fOuterRadius * cos(angle * rad);
		z = a_fOuterRadius * sin(angle * rad);
		y = a_fHeight;

		vector3 point3 = vector3(x, y, z);

		x = a_fInnerRadius * cos(angle * rad);
		z = a_fInnerRadius * sin(angle * rad);
		y = a_fHeight;

		vector3 point4 = vector3(x, y, z);

		AddQuad(point1, point2, point3, point4);
	}

	// Base
	for (int i = 0; i < a_nSubdivisions; i++) {
		float x = a_fOuterRadius * cos(angle * rad);
		float z = a_fOuterRadius * sin(angle * rad);
		float y = a_fHeight;

		vector3 point1 = vector3(x, 0.0f, z);

		x = a_fInnerRadius * cos(angle * rad);
		z = a_fInnerRadius * sin(angle * rad);
		y = a_fHeight;

		vector3 point2 = vector3(x, 0.0f, z);

		angle -= angleDegree;

		x = a_fOuterRadius * cos(angle * rad);
		z = a_fOuterRadius * sin(angle * rad);
		y = a_fHeight;

		vector3 point3 = vector3(x, 0.0f, z);

		x = a_fInnerRadius * cos(angle * rad);
		z = a_fInnerRadius * sin(angle * rad);
		y = a_fHeight;

		vector3 point4 = vector3(x, 0.0f, z);

		AddQuad(point1, point2, point3, point4);
	}


	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius <= a_fInnerRadius + 0.1f)
		return;

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 25)
		a_nSubdivisionsA = 25;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 25)
		a_nSubdivisionsB = 25;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	AddQuad(point0, point1, point3, point2);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;

	float angle = 360.0f;
	float angleDegree = 360.0f / a_nSubdivisions;
	float rad = (float)PI / 180.0f;
	float height = 180.0f;
	float angleHeight = 180.0f / a_nSubdivisions;
	float depth = 270.0f;
	float angleDepth = 180.0f / a_nSubdivisions;

	for (int i = 0; i < a_nSubdivisions; i++) {
		for (int j = 0; j < a_nSubdivisions; j++) {
			vector3 point1;
			vector3 point2;
			vector3 point3;
			vector3 point4;

			float x = a_fRadius * cos(angle * rad) * cos(depth * rad);
			float z = a_fRadius * sin(angle * rad) * cos(depth * rad);
			float y = a_fRadius * cos(height * rad);

			point1 = vector3(x, y, z);

			x = a_fRadius * cos(angle * rad) * cos((depth + angleDepth) * rad);
			z = a_fRadius * sin(angle * rad) * cos((depth + angleDepth) * rad);
			y = a_fRadius * cos((height + angleHeight) * rad);

			point3 = vector3(x, y, z);

			angle -= angleDegree;

			x = a_fRadius * cos(angle * rad) * cos((depth)* rad);
			z = a_fRadius * sin(angle * rad) * cos((depth)* rad);
			y = a_fRadius * cos((height)* rad);

			point2 = vector3(x, y, z);

			x = a_fRadius * cos(angle * rad) * cos((depth + angleDepth) * rad);
			z = a_fRadius * sin(angle * rad) * cos((depth + angleDepth) * rad);
			y = a_fRadius * cos((height + angleHeight) * rad);

			point4 = vector3(x, y, z);

			AddQuad(point1, point2, point3, point4);
		}
		depth += angleDepth;
		height += angleHeight;
	}

	//Your code ends here
	CompileObject(a_v3Color);
}