//Amanda Tebo, March 1, 2017
//CS&132
//.cpp file for WordPair class
#include "WordPair.h"
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;
WordPair::WordPair()//default constructor
{
	first = "";
	after = ' ';
}
WordPair::WordPair(string newFirst, char newAfter)//constructor for word pairs
{
	first = newFirst;
	after = newAfter;
}
bool WordPair::operator<(const WordPair& right) const//compare operator to allow sort
{
	return first < right.first;
}
ostream& operator<<(ostream& out, const WordPair& right)//cout operator
{
	out << "(" << right.first << " , " << right.after << ")" << endl;
	return out;
}
