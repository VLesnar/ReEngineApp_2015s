/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/06
----------------------------------------------*/
#ifndef __MyOctant_H_
#define __MyOctant_H_

#include "RE\ReEng.h"
#include "MyBOManager.h"

namespace ReEng
{
//System Class
class MyOctant
{
	vector3 m_v3Position;
	MeshManagerSingleton* m_pMeshMngr = nullptr;
	float m_fSize;
	int m_nChildCount;
	MyBOManager* m_pBOMngr = nullptr;
	
public:
	static bool m_bHead;
	MyOctant* m_pChildren = nullptr;
	/*
	Method: MyOctant
	Usage: Constructor
	Arguments: ---
	Output: class object
	*/
	MyOctant(void);
	MyOctant(float a_fSize);
	/*
	Method: MyOctant
	Usage: Copy Constructor
	Arguments: class object to copy
	Output: class object instance
	*/
	MyOctant(MyOctant const& other);
	/*
	Method: operator=
	Usage: Copy Assignment Operator
	Arguments: class object to copy
	Output: ---
	*/
	MyOctant& operator=(MyOctant const& other);
	/*
	Method: ~MyOctant
	Usage: Destructor
	Arguments: ---
	Output: ---
	*/
	~MyOctant(void);

	/*
	Method: Swap
	Usage: Changes object contents for other object's
	Arguments:
	other -> object to swap content from
	Output: ---
	*/
	void Swap(MyOctant& other);
	void Display(void);
	void Subdivide(void);
	void ReleaseChildren(void);

	/*
	Method:
	Usage:
	Arguments: ---
	Output:
	*/
	int GetData(void);
	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetData(int a_nData = 1);
	/* Property */
	//__declspec(property(get = GetData, put = SetData)) int Data;

	/*
	Method:
	Usage:
	Arguments:
	Output: ---
	*/
	void SetDataOnVector(int a_nData);
	/*
	Method:
	Usage:
	Arguments:
	Output:
	*/
	int& GetDataOnVector(int a_nIndex);
private:
	/*
	Method: Release
	Usage: Deallocates member fields
	Arguments: ---
	Output: ---
	*/
	void Release(void);
	/*
	Method: Init
	Usage: Allocates member fields
	Arguments: ---
	Output: ---
	*/
	void Init(void);
};

EXPIMP_TEMPLATE template class ReEngDLL std::vector<MyOctant>;
EXPIMP_TEMPLATE template class ReEngDLL std::vector<MyOctant*>;

}

#endif //__MyOctant_H__