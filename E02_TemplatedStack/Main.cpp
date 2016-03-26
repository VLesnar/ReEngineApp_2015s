#include <iostream>
#include "Main.h"

int main()
{
	int nEntries = 10;
	double temp = 1;

	TypeStack<int> intStack(nEntries);
	TypeStack<double> doubleStack(nEntries);
	TypeStack<char> charStack(nEntries);

	for (int i = 0; i < nEntries; i++)
	{
		intStack.m_Data[i] = i;
		doubleStack.m_Data[i] = i + 0.5;
		charStack.m_Data[i] = i + 97;
	}

	intStack.Print();
	doubleStack.Print();
	charStack.Print();

	getchar();
	return 0;
}
