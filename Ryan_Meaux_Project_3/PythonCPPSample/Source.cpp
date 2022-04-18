#include <Python.h>
#include <iostream>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("CS210_Starter_PY_Code");
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
	pName = PyUnicode_FromString((char*)"CS210_Starter_PY_Code");
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
	pName = PyUnicode_FromString((char*)"CS210_Starter_PY_Code");
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

/* Creates and Displays the Interface*/
void DisplayUI() {
	cout << "Make a Number Selection" << endl<<endl;
	cout << "1: Display All Item Occurance's" << endl;
	cout << "2: Display Specific Item's Occurances" << endl;
	cout << "3: Display Histogram" << endl;
	cout << "4: Exit" << endl << endl;
}


/*
Gets the number of times a specific item occurs
*/
void GetItemOccurances() {
//Get the desired item
		string word;
		cout << "Enter An Item: ";
		cin >> word;
		
// Check to see if the item exists
		int isWordInList = callIntFunc("CheckForWord", word);

// If it does diplay the items data
		if (isWordInList == 1) {
			int occurrences = callIntFunc("CountOccuranceOfWord", word);
			cout << word << ": " << occurrences << endl << endl;
		}
		else {
			cout << "Item Does Not Exist Please Try Again" << endl << endl;
			 
		}


	
}

string GetStringItem(string word) {

	int i = 0;
	int position = word.find(":");
	string item = "";
	while (i < position) {
		char letter = word.at(i);
		item = item + letter;
		++i;
	}
	return(item);
}

//Gets the number of occurances of every word in the file
void GetAllOccurances() {
	CallProcedure("CountAllWords");

}

// Prints the Stars in the histogram
void PrintStars(int numberOfStars) {
	for (int pos = 0; pos <= numberOfStars; ++pos) {
		if (pos == numberOfStars) {
			cout << endl;
		}

		if (pos < numberOfStars) {
			cout << "*";
		}
	}
}

//Draws the histogram
void CreateHistogram() {

	//Read File 
	CallProcedure("WriteToFile");

	string line;
	string newNumber = "";
	
	//Opens file
	ifstream myfile("frequency.dat");
	
	//If the file doesn't exist print not found
	if (!myfile) {
		cout << "Not Found" << endl;
	}


	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{

			// Get the first line in the file
			string item = GetStringItem(line);

			//Get the last character from the line 
			char number = line.at(line.length() - 1);

			//Cast the char to an int
			newNumber = number;
			int newNumb = stoi(newNumber);

			//Print the item and the number of stars
			cout << item;
			PrintStars(newNumb);

		}

		// Close file
		myfile.close();
	}
	
}

int main()
{
	int input = 0;

	//Loop stays alive input == 3 
	while (input != 4 || input == 0) {

		//Displays the UI
		DisplayUI();

		//Captures user selection
		cin >> input;

		while (1) {
			//If the input fails clear it and print an error line and redisplace UI
			if (cin.fail()) {

				cin.clear();
				cin.ignore();
				cout << "Please make a good selection" << endl;
				DisplayUI();
				cin >> input;
			}

			//If the selected input isnt 1,2,3,4 start over
			if (!cin.fail()) {
				if (input != 1 && input != 2 && input != 3 && input != 4) {
					cin.clear();
					cin.ignore();
					cout << "Please make a good selection" << endl;
					DisplayUI();
					cin >> input;
				}
				else {
					break;
				}
				
			}

		}
			//Get all list occurances
			if (input == 1) {

				GetAllOccurances();
			}

			//Gets the number of occurences for an item
			if (input == 2) {
				GetItemOccurances();
			}

			//Create the histogram
			if (input == 3) {
				CreateHistogram();
			}

			// break and exit
			if (input == 4) {
				break;
			}
		
	}
	return 0;
	}