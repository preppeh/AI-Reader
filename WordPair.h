//Amanda Tebo, March 1, 2017
//CS&132
//.h file
#ifndef WordPair_H
#define WordPair_H
#include <string>
#include <iostream>
using namespace std;
class WordPair
{
public:
	WordPair();
	WordPair(string, char);
	friend ostream& operator<<(ostream& out, const WordPair&);
	bool operator<(const WordPair&) const;
	string first;
	char after;
};


#endif