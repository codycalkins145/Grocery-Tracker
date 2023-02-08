#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <cctype>
#include <conio.h>
#include <fstream>
#include <iomanip>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}


void main()
{
	char selection = '0'; // Variable used for option selection

	while (selection != '4') { // Loop runs as long as user doesn't choose to exit program
		// Following loop is used for the menu design
		for (int i = 0; i <= 60; i++) { 
			cout << "=";
		}
		cout << endl;

		cout << "What would you like to do today?" << endl;
		
		for (int i = 0; i <= 60; i++) { // Menu design
			cout << "-";
		}
		cout << endl;

		cout << "1: Get a list of each item and their purchase frequency" << endl;
		cout << "2: Get the amount purchased of a specific item" << endl;
		cout << "3: Get a histogram of each item and their purchase frequency" << endl;
		cout << "4: Exit program" << endl;

		for (int i = 0; i <= 60; i++) { // Menu design
			cout << "-";
		}
		cout << endl;

		cout << "Please type option 1, 2, 3, or 4." << endl;

		for (int i = 0; i <= 60; i++) { // Menu design
			cout << "=";
		}
		cout << endl;

		cin >> selection; // Receiving user input for menu selection
		cout << endl;

		if (selection == '1') {	// If user chooses option 1	
			cout << "Items Sold Today" << endl;

			for (int i = 0; i <= 20; i++) { // Output design
				cout << "-";
			}
			cout << endl;

			// Calling function from Python to display items and their frequencies
			CallProcedure("ItemsAndFrequency"); 

			for (int i = 0; i <= 20; i++) { // Output design
				cout << "-";
			}
			cout << endl << endl;

			cout << "Press any key to continue..."; 

			// Awaits user input to return to the main menu display
			while (!_kbhit()) { // Loop continues as long as a key has not been pressed
				continue;
			}
			_getch(); // Stores input so that it won't show up in next input request
			cout << endl << endl;
		}

		else if (selection == '2') {
			bool wordCheck = true; // Variable used to decide if input validation loop continues
			char modInput; // Variable used to check for invalid characters in user input
			string itemInput; // Variable used to input name of specific item

			cout << "Enter the name of an item." << endl;

			while (wordCheck == true) { // Loops while the user input needs to be checked
				cin >> itemInput; // User input for specified item
				cout << endl;

				for (int i = 0; i < itemInput.size(); i++) { // Loops through the users input
					// Character at specified position in string, set to lowercase for easier checking
					modInput = tolower(itemInput[i]);

					// Prompts user for correct input if specified character is not a letter a - z
					if (modInput < 'a' || modInput > 'z') { 
						cout << "Please input a valid item." << endl;
						wordCheck = true; // Continues validation loop
					}
					else { // Continues if all characters in user input are letters a - z
						// Sets user input to all lowercase for consistent comparison in Python
						// and for outputting correct case
						if (isupper(itemInput[i])) { 
							itemInput[i] = tolower(itemInput[i]);
						}
						wordCheck = false; // Ends validation loop
					}
				}
			}
			// Checks if item entered by user is in the text file 
			while (wordCheck == false) { 
				// Takes return from Python function if item was not in the text file
				if (callIntFunc("SingleItemFreq", itemInput) == -1) {
					cout << "This item was not sold today or was not entered correctly. "
						 << "Please enter the item again." << endl;
					cin >> itemInput; // User re-enters correct item name
					cout << endl;

					// Sets user input to all lowercase for consistent comparison in Python
					// and for outputting correct case after re-validation
					for (int i = 0; i < itemInput.size(); i++) {
						if (isupper(itemInput[i])) {
							itemInput[i] = tolower(itemInput[i]);
						}
					}
				}
				else {
					for (int i = 0; i <= 40; i++) { // Output design
						cout << "-";
					}
					cout << endl;

					// Calling and returning function from Python to display amount of specified item
					cout << callIntFunc("SingleItemFreq", itemInput) << " " << itemInput
						 << " were purchased today." << endl;

					for (int i = 0; i <= 40; i++) { // Output design
						cout << "-";
					}
					cout << endl << endl;

					cout << "Press any key to continue...";

					while (!_kbhit()) { 
						continue;
					}
					_getch(); 
					cout << endl << endl;

					wordCheck = true; // Ends second validation loop
				}

				
			}
		}

		else if (selection == '3') {
			ifstream inFS; // Input file stream
			string itemName; // Variable storing name of item from frequency.dat
			int itemFreq; // Variable storing frequncy of item from frequency.dat

			// Calls the Python function that reads from CS210_Project_Three_Input_File
			// and creates/writes to frequency.dat
			CallProcedure("ItemHistogram"); 

			inFS.open("frequency.dat"); // Opens frequency.dat for receiving input

			if (!inFS.is_open()) { // Checks if file is opened successfully 
				cout << "Could not open the file containing the item list." << endl << endl;
				continue; // Starts again from main menu
			}

			inFS >> itemName; // Receiving input from frequency.dat for item
			inFS >> itemFreq; // Receiving input from frequency.dat for item frequency

			while (!inFS.fail()) { // Checks if the input was received successfully
				cout << "Today's Histogram" << endl;

				for (int i = 0; i <= 30; i++) { // Output design
					cout << "-";
				}
				cout << endl;

				while (!inFS.eof()) { // Checks if the end of frequency.dat has been reached
					cout << left << setw(13) << itemName;

					for (int i = 0; i < itemFreq; i++) { // Histogram "bars"
						cout << "|";
					}
					cout << endl;

					inFS >> itemName;
					inFS >> itemFreq;
				}

				for (int i = 0; i <= 30; i++) { // Output design
					cout << "-";
				}
				cout << endl << endl;
			}

			if (!inFS.eof()) { // Returns a message if the end of frequency.dat could not be reached
				cout << "Could not reach the end of the item list file." << endl << endl;
			}
			inFS.close(); // Closes frequency.dat

			cout << "Press any key to continue...";

			while (!_kbhit()) { 
				continue;
			}
			_getch(); 
			cout << endl << endl;
		}

		else if (selection == '4') { // Ends loop if user enters 4
			break; 
		}

		else { // Prompts user for valid selection if user enters unavailable option
			cout << "Please enter a valid selection." << endl << endl;
			continue;
		}
	}	

}