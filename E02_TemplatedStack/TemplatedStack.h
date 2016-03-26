/*--------------------------------------------------------------------------------------------------
Created by Alberto Bobadilla (labigm@rit.edu) in 2014
Modified: 08/29/2015 labigm
--------------------------------------------------------------------------------------------------*/
#ifndef __TEMPLATEDSTACK_H_
#define __TEMPLATEDSTACK_H_

#include <iostream>

template<class T>
class TypeStack
{
public:
	//Data in the stack
	T* m_Data;
	//Size of the stack
	T m_nEntries;
	//constructor
	TypeStack(T a_nEntries) : m_Data(nullptr)
	{
		m_nEntries = a_nEntries;
		m_Data = new T[m_nEntries];
	}
	//Copy Constructor
	TypeStack(const TypeStack& other)
	{
		TypeStack temp(other.m_nEntries);
		Swap(temp);
	}
	//Copy Assignment Operator
	TypeStack& operator=(const TypeStack& other)
	{
		if (this != &other)
		{
			Release();
			TypeStack temp(other.m_nEntries);
			Swap(temp);
		}
	}
	//Destructor
	~TypeStack()
	{
		Release();
	}
	//Releases stack
	void Release()
	{
		if (m_Data != nullptr)
		{
			delete[] m_Data;
			m_Data = nullptr;
		}
	}
	//Swaps information from other stack
	void Swap(TypeStack& other)
	{
		std::swap(this->m_Data, other.m_Data);
	}
	//Prints all the elements in the stack
	void Print()
	{
		std::cout << m_nEntries << " Entries in the stack:" << std::endl;
		for (int i = 0; i < m_nEntries; i++)
		{
			std::cout << m_Data[i];
			std::cout << ", ";
		}
		std::cout << "\n";
	}
};

#endif //__TEMPLATEDSTACK_H
