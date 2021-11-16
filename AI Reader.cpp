//Amanda Tebo, March 1, 2017
//Assignment #6
//Main Program

#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <algorithm>
#include <vector>
#include <ctime>
#include <random>
#include "WordPair.h"
using namespace std;
char isGood(char);
string grabLast(string, int);
void printMe(WordPair);
WordPair chooseRandomNotStart(multiset<WordPair>, string);
WordPair chooseRandom(multiset<WordPair>);
multiset<WordPair> createList(int, string);
string makeSentence(multiset<WordPair>, int);
int main()
{
	srand(unsigned(time(0)));
	int choice;
	string textFile;
	cout << "Please enter the level of search you wish to do: ";
	cin >> choice;
	cout << endl << "Please enter the text you would like to read from: ";
	getline(cin, textFile);
	getline(cin, textFile); //for some reason, you need two getlines for visual studio for it to work
	ifstream inputFile;
	if (textFile.find(".txt") != string::npos)//if inputted string does have .txt inside it
	{
		inputFile.open(textFile);
	}
	//if inputted string doesn't have .txt inside it
	else if (textFile.find(".txt") == string::npos)
	{
		string textFileOpen = textFile + ".txt";
		inputFile.open(textFileOpen);
	}
	multiset<WordPair> listOfWordPair;
	listOfWordPair = createList(choice, textFile);//create the list of word pairs
	string sentence = makeSentence(listOfWordPair, choice);//create sentence based on word pairs
	cout << sentence << endl;
	char round2 = 'n';
	do
	{
		cout << endl << "Would you like to make another sentence? (y or n)" << endl;
		cin >> round2;
		if (round2 == 'y')
		{
			sentence = makeSentence(listOfWordPair, choice);
			cout << sentence << endl;
		}
	} while (round2 == 'y');
	system("pause");
}
void printMe(WordPair x)
{
	cout << x.first << "   " << x.after << endl;
}
multiset<WordPair> createList(int choice, string textFile)
{
	multiset<WordPair> listOfWP;
	ifstream inputFile;
	if (textFile.find(".txt") != string::npos)
	{
		inputFile.open(textFile);
	}
	//if inputted string doesn't have .txt inside it
	else if (textFile.find(".txt") == string::npos)
	{
		string textFileOpen = textFile + ".txt";
		inputFile.open(textFileOpen);
	}
	string start = "";//starting string
	char first;
	while (inputFile >> noskipws >> first)//while there's an input, assign each character to first
	{
		first = isGood(first);
		// make wordpair and add to set
		if (first != '~')
		{
			WordPair pair;
			pair.first = start;
			pair.after = first;
			listOfWP.insert(pair);
			start = start + first;
		}
		if (start == " ") start = "";
		if (start.size() > choice) start = start.substr(1);
		if (first == '.')//when you reach a period, restart sentence
		{
			start = "";
		}
	}
	return listOfWP;
}
string makeSentence(multiset<WordPair> listOfWP, int choice)
{
	string start = "";
	while (start.find(".") == std::string::npos)
	{
		string addOn = grabLast(start, choice);//grab the last characters depending on user choice depth of level
		WordPair pair1 = chooseRandomNotStart(listOfWP, addOn);
		start = start + pair1.after;
	}
	return start;
}
char isGood(char x)
{
	if (x > 255 || x < 0) return '~';
	if (isprint(x)) return x;
	if (iscntrl(x)) return ' ';
	return x;
}
string grabLast(string x, int choice)
{
	string last;
	if (x.size() < choice) last = x;//if string is shorter than search level
	else last = x.substr(x.size() - choice, choice);//else grab the last choice number of characters
	return last;
}
WordPair chooseRandomNotStart(multiset<WordPair> x, string addOn)
{
	vector<WordPair> sentenceEnding;
	for (WordPair pair : x)
	{
		if (addOn == pair.first) sentenceEnding.push_back(pair);
	}
	random_shuffle(sentenceEnding.begin(), sentenceEnding.end());//shuffle vector
	if (sentenceEnding.size() == 0)
	{
		addOn = addOn.substr(1);
		for (WordPair pair : x)
		{
			if (addOn == pair.first) sentenceEnding.push_back(pair);
		}
	}
	return sentenceEnding[0];//return first pair in the vector
}