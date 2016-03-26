/*	Veronica Lesnar
	HW 02 */

#include "Main.h"

int main() {
	List things = List();
	
	srand(time(NULL));
	things.Add();
	things.Add();
	things.Add();
	things.Add();

	// Ends the program
	cout << "Press enter to finish";
	getchar();
	return 0;
}