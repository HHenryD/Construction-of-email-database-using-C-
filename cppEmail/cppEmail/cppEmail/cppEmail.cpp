#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include "string.h"
#include "cppEmail.h"
#include <fstream>
using namespace std;

// Implementation of cppEmail member functions
void cppEmail::writemail()
{
	cout << "Enter the name of sender or receiver: ";
	cin.getline(To_from[0], 80);
	char b[80];
	cout << "Enter the email address of sender or receiver: ";
	cin.getline(b, 80);
	while (addcheck(b) == 0)
	{
		cout << "Invalid email address, please enter again: ";
		cin.getline(b, 80);
	}
	To_from[1][0] = '[';
	for (int i = 0; i < strlen(b); i++)
		To_from[1][i + 1] = b[i];
	To_from[1][strlen(b) + 1] = ']';
	To_from[1][strlen(b) + 2] = '\0';// to store the whole string that user enters and add a pair of square bracket at both sides
	char a;
	cout << "Is this email sent or received?\n";
	do
	{
		cout << "If it is sent, enter 'T', otherwise, enter 'F': ";
		cin >> a;
		cin.get(); // to clear the buffer by throwing one \n remaining in
	} while (a != 'T' && a != 'F');// if user don't enter T or F at the time, prompt user to re-enter the function
	To_from[2][0] = a;
	To_from[2][1] = '\0';
	cout << "Enter the email subject: ";
	cin.getline(emSubject, 80);
	cout << "Does this email have a CC?(y/n): ";
	char aaa;
	cin >> aaa; cin.get();
	while (aaa != 'y' && aaa != 'n')
	{
		cout << "Wrong input! Please input again ";
		cin >> aaa;
	}
	if (aaa == 'y') // if the user have a CC person
	{
		cout << "Enter the name of CC: ";
		cin.getline(emCC[0], 80);
		cout << "Enter the email address of CC: ";
		char k[80];
		cin.getline(k, 80);
		while (addcheck(k) == 0)
		{
			cout << "Invalid email address, please enter again: ";
			cin.getline(k, 80);
		}
		emCC[1][0] = '[';
		for (int i = 0; i < strlen(k); i++)
			emCC[1][i + 1] = k[i];
		emCC[1][strlen(k) + 1] = ']';
		emCC[1][strlen(k) + 2] = '\0';
	}
	else // if the user do not have a CC person
	{
		strcpy(emCC[0], "\0");
		strcpy(emCC[1], "\0");
	}
	cout << "Enter your message\n";
	cout << "Note: each line is less than 80 words\n";
	cout << "You need to manually press enter key to get to the next line\n";
	cout << "Enter 'quit' to stop writing\n";
	for (int i = 0; i < 500; i++)
	{
		cin.getline(emMessage[i], 80);
		if (strcmp(emMessage[i], "quit") == 0) // when the user enter quit the email writing function ends
			break;
		line = i;
	}
	cout << "Input the date in the following formula\n";
	cout << "e.g. 9 November 2019 can be represented by the integer 191109\n";// tell user the formula
	cout << "Please input the value:";
	cin >> emDate;
	cin.get(); // to clear the buffer by throwing one \n remaining in
}
void cppEmail::reademail()
{
	// give all the information of the email
	cout << "To_From: " << To_from[0] << " " << To_from[1] << " " << To_from[2] << endl;
	cout << "Subject: " << emSubject << endl;
	if (strcmp(emCC[0], "\0") == 0) // if there is no CC person
		cout << "No CC" << endl;
	else
		cout << "CC: " << emCC[0] << " " << emCC[1] << endl;
	// Date is printed differently because the date might be 000101, or 080808, when the number is directly printed, user will see 101 and 80808, so we need to add '0' in the front accordingly
	cout << "Date: ";
	for (int i = 3; i <= 5; i++)
	{
		if (emDate < power(10, i))
		{
			for (int j = 0; j < 6 - i; j++)
				cout << "0";
			break;
		}
	}
	cout << emDate << endl;
	cout << "Messages: \n";
	for (int i = 0; i < line + 1; i++)
	{
		if (strcmp(getmessage(i), "\0") == 0)
			cout << getmessage(i); // leave no space for the last line of message and "message ends"
		else
			cout << getmessage(i) << endl;
	}
}

void cppEmail::setemsubject(char* n)
{
	strcpy(emSubject, n);
}
void cppEmail::setMessage(char* a, int m)
{
	strcpy(emMessage[m], a);
}
int cppEmail::power(int a, int b)
{
	// this function is to return the value of a^b
	int m = 1;
	for (int i = 0; i < b; i++)
		m = m * a;
	return m;
}
void cppEmail::setDate(char* a)
{
	// In this step we transfer a string to unsgined int and store in emDate.
	// We do this transformation because when we use fin.getline() to get the date from the stored file (username.txt), what we have is a string but not a number
	unsigned int m = 0;
	for (int i = 0; i < strlen(a); i++)
	{
		switch (a[i])
		{
		case '0': m = m + 0 * power(10, strlen(a) - 1 - i); break;
		case '1': m = m + 1 * power(10, strlen(a) - 1 - i); break;
		case '2': m = m + 2 * power(10, strlen(a) - 1 - i); break;
		case '3': m = m + 3 * power(10, strlen(a) - 1 - i); break;
		case '4': m = m + 4 * power(10, strlen(a) - 1 - i); break;
		case '5': m = m + 5 * power(10, strlen(a) - 1 - i); break;
		case '6': m = m + 6 * power(10, strlen(a) - 1 - i); break;
		case '7': m = m + 7 * power(10, strlen(a) - 1 - i); break;
		case '8': m = m + 8 * power(10, strlen(a) - 1 - i); break;
		case '9': m = m + 9 * power(10, strlen(a) - 1 - i); break;
			// to transfer the string into a number
		}
	}
	emDate = m;
}
bool cppEmail::addcheck(char* rat)
{
	// This function is to used to check the format of email address
	if (rat[0] == '@')
		return false; //@ cannot be the first one
	if (rat[strlen(rat) - 1] == '@')
		return false;//@ cannot be the last one
	int o = 0; // how many @ in the string
	for (int i = 0; i < strlen(rat); i++)
	{
		if (rat[i] == '@')
			o++;
	}
	if (o == 1)// there is only one @
		return true;
	else
		return false; // there is no @ in the address or there are more than one @ in address
}