#pragma once
#include "cppEmail.h"
class emHandle
{
public:
	emHandle(int max = 1000);
	~emHandle();
	void sort();
	void AddEmail();
	void ListAll();
	void writefile(char* filename);
	void readfile(char* filename);
private:
	cppEmail* AllEmail; // Pointer pointing to an array of cppEmail objects in the heap
	int maxEmail; // Size of array of cppEmail objects
	int numOfEmail; // Number of valid cppEmail objects
};
