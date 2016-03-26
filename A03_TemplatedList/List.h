/*	Veronica Lesnar
	HW 03 */

#ifndef _LIST_H
#define _LIST_H

#include <iostream>

using namespace std;

template<class T>
class List
{
public:
	// Variables
	T* data = nullptr;	// The data array
	int numEntries;	// The current number of entries in the List

	// Constructor - Allocates one space for the List
	List<T>(T entries) {
		this->data = nullptr;
		numEntries = entries;
		data = new T[numEntries];
	}

	// Copy Constructor - Copies another List into the new List
	List<T>(const List<T> &otherList) {
		List<T> temp(otherList.numEntries);
		memcpy(&temp, &otherList, sizeof(List));
		Swap(temp);
	}
	// Copy Assignment Operator - Reinitializes the List and copies another List's data into the new List
	List<T> &operator=(const List<T> &otherList) {
		if (this != &otherList) {
			Release();
			List<t> temp(otherList.numEntries);
			memcpy(&temp, &otherList, sizeof(List));
			Swap(temp);
		}
		return *this;
	}

	// Destructor - Deallocates the memory of the List
	~List<T>() {
		Release();
	}

	// Push - Adds data to the top of the list and allocates new space if needed
	void Push(T data) {
		this->data[numEntries] = data;
		numEntries++;
	}
	
	// Pop - Removes data from the top of the List
	void Pop() {
		this->data[numEntries] = NULL;
		numEntries--;
	}

	// Print - Writes the contents of the List to the console
	void Print() {
		cout << "Writing the contents of the List..." << endl;
		cout << "Data in List:" << endl;
		if (!IsEmpty()) {
			for (int i = 0; i < numEntries; i++) {
				cout << data[i];
				// Checks if the data is the last in the List
				if (i != (numEntries - 1)) {
					cout << ", ";
				}
			}
			cout << endl;
		}
		else {
			cout << "There are no entries in the list." << endl;
		}
	}
	
	// GetSize - Returns the number of items in the List
	int GetSize() {
		return numEntries;
	}

	// IsEmpty - Returns a boolean that shows whether or not the List has any data inside of it
	bool IsEmpty() {
		return numEntries < 1;
	}

	// Swap - Swaps the information from one List into another List
	void Swap(List<T> &otherList)
	{
		swap(this->numEntries, otherList.numEntries);
		swap(this->data, otherList.data);
	}

	// Release - Deletes the information in the List and resets numEntries to 0
	void Release() {
		if (data != nullptr) {
			delete[] data;
			data = nullptr;
		}
		
		numEntries = 0;
	}
};

#endif