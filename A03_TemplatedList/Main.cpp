/*	Veronica Lesnar
	HW 03 */

#include "Main.h"

int main() {
	typedef int myType;
	
	int numEntries = 10;

	List<myType> list(numEntries);
	List<myType> anotherList(0);
	List<double> doubleList(numEntries);
	List<char> charList(numEntries);

	for (int i = 0; i < (numEntries); i++)
	{
		list.data[i] = static_cast<myType>(i);
		doubleList.data[i] = i + 0.5;
		charList.data[i] = i + 97;
	}

	list.Print();
	cout << "The size of this list is: " << list.GetSize() << endl;

	list.Push(11);
	list.Push(12);
	list.Push(13);

	list.Print();
	cout << "The size of this list is: " << list.GetSize() << endl;

	list.Pop();
	list.Pop();
	list.Pop();
	list.Pop();
	list.Pop();
	list.Pop();

	list.Print();
	cout << "The size of this list is: " << list.GetSize() << endl;

	anotherList.Print();

	charList.Print();
	charList.Pop();
	charList.Pop();
	charList.Print();
	
	doubleList.Print();
	doubleList.Pop();
	doubleList.Pop();
	doubleList.Print();

	getchar();
	return 0;
}