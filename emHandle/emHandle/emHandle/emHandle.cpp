#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include "string.h"
#include "emHandle.h"
#include <fstream>
using namespace std;

// Implementation of emHandle member functions
emHandle::emHandle(int max)
{
	// initialize member variables
	maxEmail = max;
	numOfEmail = 0;
	AllEmail = new cppEmail[max];
}
emHandle::~emHandle()
{
	// release the memories and set all member variables to 0;
	delete[] AllEmail;
	maxEmail = 0;
	numOfEmail = 0;
	AllEmail = 0;
}
void emHandle::sort()
{
	// assign every email an index to determine the order of printing.
	// for example, suppose we have two names henry and blue, this function will first assign 0 to blue and 1 to henry, then blue will be printed out first
	unsigned int* index = new unsigned int[numOfEmail];
	for (int i = 0; i < numOfEmail; i++)
	{
		index[i] = 0;
		for (int j = 0; j < numOfEmail; j++)
		{
			if (strcmp(AllEmail[i].getName(), AllEmail[j].getName()) == 1)
				index[i] += 1;
		}
	}
	for (int i = 0; i < numOfEmail; i++)
	{
		for (int j = 0; j < numOfEmail; j++)
		{
			if (index[j] == i && AllEmail[j].getTF() == 'F') // we ignore sent-to-receiver message
			{
				cout << "Name: " << AllEmail[j].getName() << " Subject: " << AllEmail[j].getSubject() << " Date: ";
				// Date is printed differently because the date might be 000101, or 080808, when the number is directly printed, user will see 101 and 80808, so we need to add '0' in the front accordingly
				for (int k = 3; k <= 5; k++)
				{
					if (AllEmail[j].getDate() < AllEmail[j].power(10, k))
					{
						for (int s = 0; s < 6 - k; s++)
							cout << "0";
						break;
					}
				}
				cout << AllEmail[j].getDate() << endl;
			}
		}
	}
}
void emHandle::AddEmail()
{
	// As the sie of the array is assumed big enough, I do not check it here.
	AllEmail[numOfEmail].writemail();
	numOfEmail++;
}
void emHandle::ListAll()
{
	// this function is to list all the emails in the databse
	for (int i = 0; i < numOfEmail; i++)
	{
		AllEmail[i].reademail();
	}
}
void emHandle::writefile(char* filename)
{
	// the format of storing this output file is set to make the read of the file to heap easier, but not for user read.
	ofstream fout(filename); // open the file with truncated mode since all the information are read and stored in the database
	for (int i = 0; i < numOfEmail; i++)
	{
		fout << AllEmail[i].getName() << endl;
		fout << AllEmail[i].getaddress() << endl;
		fout << AllEmail[i].getTF() << endl;
		fout << AllEmail[i].getSubject() << endl;
		fout << AllEmail[i].getCCname() << endl;
		fout << AllEmail[i].getCCaddress() << endl;
		fout << AllEmail[i].getDate() << endl;
		for (int l = 0; l <= AllEmail[i].Getline(); l++)
		{
			if (strcmp(AllEmail[i].getmessage(l), "\0") == 0)
				fout << AllEmail[i].getmessage(l); // leave no space for the last line of message and "message ends"
			else
				fout << AllEmail[i].getmessage(l) << endl;
		}
		fout << "message ends" << endl;
	}
	fout << "end of database" << endl; // an indicator when reading from file (when to end reading)
	fout.close();
}
void emHandle::readfile(char* filename)
{
	// This function will read all the emails stored in the file into heap 
	ifstream fin(filename);
	// Only when the file exists, the following operations will be performed.
	if (fin)
	{
		char b[80]; // to store the input from the file
		int i = 0; // the number of emails
		while (true)
		{
			fin.getline(b, 80);
			if (strcmp(b, "end of database") == 0)// detect whether it is the end of database, if it is, break
			{
				numOfEmail = i;
				break;
			}
			AllEmail[i].setTo_from1(b);
			fin.getline(b, 80);
			AllEmail[i].setTo_from2(b);
			fin.getline(b, 80);
			AllEmail[i].setTo_from3(b);
			fin.getline(b, 80);
			AllEmail[i].setemsubject(b);
			fin.getline(b, 80);
			AllEmail[i].setemCC1(b);
			fin.getline(b, 80);
			AllEmail[i].setemCC2(b);
			fin.getline(b, 80);
			AllEmail[i].setDate(b);
			int n = 0;
			while (true)
			{
				fin.getline(b, 80);
				if (strcmp(b, "message ends") == 0) // detect whether it is the end of message, if it is, break
				{
					char m[] = "\0"; // to mannually stop the reading of uninitiated strings when using function listall and writefile
					AllEmail[i].setMessage(m, n);
					AllEmail[i].setline(n);
					break;
				}
				else
				{
					AllEmail[i].setMessage(b, n);
					n++;
				}
			}
			i++;
		}
	}
	fin.close();
}