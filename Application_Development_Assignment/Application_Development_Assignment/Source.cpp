#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include "string.h"
#include "emHandle.h"
#include <fstream>
using namespace std;
bool menu(emHandle*, char*);
char* login();
//function prototypes
int main()
{
	cout << "This is email information holding database\n";
	char sign[20]; // sign is to store the name or "quit" returned by login()
	strcpy(sign, login());
	if (strcmp(sign, "quit") != 0) // if login() returns "quit", the program will end
	{
		// use fileName to store the input and output file name (username.txt)
		char fileName[25];
		strcpy(fileName, sign);
		strcat(fileName, ".txt");
		emHandle* database = new emHandle;
		database->readfile(fileName);// read emails from files
		bool exitflag = false;
		while (!exitflag)
		{
			exitflag = menu(database, fileName);
		}
		delete database;
	}
	return 0;
}

char* login()
{
	// this function is to let the user log in or sign up
	char name[20];
	char passward[20];
	char choice;
	char quit[] = { "quit" };
	cout << "========= Log in ===========\n";
	cout << "Please input your username: \n";
	cout << "Please do not contain space, '\\n', and '\\t' in your username\n";
	cin >> name;
	cin.get();
	cout << "Are you a new user? (y/n) ";
	cin >> choice;
	while (choice != 'y' && choice != 'n')
	{
		cout << "Wrong input! Please input again ";
		cin >> choice;
	}
	if (choice == 'y')
	{
		char name2[20];
		strcpy(name2, name);
		strcat(name2, ".txt");
		ifstream test(name2);
		if (test)
		{
			cout << "Account exists!\n";
			return quit;
		}
		else
		{
			cout << "Please input your password: \n";
			cout << "Please do not contain space, '\\n', and '\\t' in your password\n";
			cin >> passward;
			cin.get();
			ofstream fout("user.txt", ios::app);
			fout << name << " " << passward << endl;
			fout.close();
			cout << "Sign up successfully!\n";
			return name;
		}
		test.close();
	}
	else
	{
		cout << "Please input your password: \n";
		for (int i = 0; i < 3; i++)
		{
			cout << "Now you have " << 3 - i << " chances to enter the password.\n";
			cin >> passward;
			cin.get(); // to clear the '\n' in the buffer
			char user[40];
			strcpy(user, name);
			strcat(user, " ");
			strcat(user, passward);
			char storeUser[40];
			ifstream fin("user.txt");
			while (fin.getline(storeUser, 40))
			{
				if (strcmp(user, storeUser) == 0)
				{
					cout << "Log in successfully!\n";
					return name;
				}
			}
			fin.close();
			if (i < 2)
				cout << "Password wrong! Please re-enter: \n";
		}
	}
	return quit;
}

bool menu(emHandle* database, char* fileName)
{
	// read the information in the stored file to heap first
	char choice;
	cout << "Menu: \n"
		<< "a. Add new emails to the Database\n"
		<< "b. Handle the email Database\n"
		<< "c. Display the database of emails\n"
		<< "q. End the application\n"
		<< "Please enter your choice: ";
	cin >> choice;
	cin.get();
	switch (choice)
	{
	case 'a':
		int num;
		cout << "Input the number of emails you want to add to this database: ";
		cin >> num;
		cin.get();
		for (int i = 0; i < num; i++)
		{
			cout << "Please input the info of the email No." << i + 1 << ": \n";
			database->AddEmail();
		}
		break;
	case 'b':
		database->sort();
		break;
	case 'c':
		database->ListAll();
		break;
	case 'q':
		database->writefile(fileName);
		cout << "Goodbye!\n";
		return true;
	default:
		cout << "Wrong input! Please input again!\n";
	}
	return false;
}