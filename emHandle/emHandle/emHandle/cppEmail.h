#pragma once
#include <string.h>
class cppEmail
{
public:
	void writemail();
	void reademail();
	//---------------------------these functions are to view and write an email object------------------------------------------------------
	void setTo_from1(char* a) { strcpy(To_from[0], a); }
	void setTo_from2(char* b) { strcpy(To_from[1], b); }
	void setTo_from3(char* c) { strcpy(To_from[2], c); }
	void setemsubject(char* n);
	void setemCC1(char* a) { strcpy(emCC[0], a); }
	void setemCC2(char* b) { strcpy(emCC[1], b); }
	void setMessage(char* a, int m);
	void setDate(char* a);
	void setline(int a) { line = a; }
	//------------------------------these functions are to set all the information from an email object------------------------------------------------
	int power(int a, int b);
	bool addcheck(char*);
	//------------------------------these functions are for helping the memberfunction to be built------------------------------------------------
	char getTF() { return To_from[2][0]; }
	char* getName() { return To_from[0]; }
	char* getCCname() { return emCC[0]; }
	char* getaddress() { return To_from[1]; }
	char* getCCaddress() { return emCC[1]; }
	unsigned int getDate() { return emDate; }
	char* getSubject() { return emSubject; }
	int Getline() { return line; }
	char* getmessage(int j) { return emMessage[j]; }
	//------------------------------these functions are to get all the information from an email object------------------------------------------------
private:
	char To_from[3][80];
	char emSubject[80];
	char emCC[2][80];
	char emMessage[100][80];
	unsigned int emDate;
	int line; // how many lines in the message
};