#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

void readFile(vector<string> &, const int &);
void toLowerCase(vector<string> &);
void input(vector<char> &, int &);
void reduceVec(vector<string> &, const int &);
void calcWords(vector<string> &, vector<string> &, vector<char> &, int &);
bool illegalWord(string &);
bool contains(string &, char &);

int main()
{
	vector<string> words(0);
	vector<char> letters(0);
	vector<string> outputWords(0);
	int numLetters = 0;


	input(letters, numLetters);
	readFile(words, numLetters);
	toLowerCase(words);
	reduceVec(words, numLetters);
	calcWords(outputWords, words, letters, numLetters);
	for (unsigned i = 0; i < outputWords.size(); i++)
	{
		cout << outputWords[i] << ", ";
	}

	system("pause");
	return 0;
}

void readFile(vector<string> &words, const int &length)
{
	string temp = "";
	fstream fileToRead("10kWords.txt");
	if (fileToRead.is_open())
	{
		while (getline(fileToRead, temp))
		{
			if (!illegalWord(temp) && temp.size() == length)
			{
				words.push_back(temp);
				temp = "";
			}
		}
	}
}

void toLowerCase(vector<string> &words)
{
	string temp;
	for (unsigned i = 0; i < words.size(); i++)
	{
		temp = words[i];
		for (unsigned y = 0; y < temp.size(); y++)
		{
			temp[y] = tolower(temp[y]);
		}
		words[i] = temp;
	}
}

void input(vector<char> &letters, int &numLetters)
{
	string tempStrLength = "";
	string tempStrNum = "";
	char tempLetter = ' ';
	int tempLength = 0;
	int tempNum = 0;
	cout << "How long is the word? ";
	getline(cin, tempStrLength);
	tempLength = stoi(tempStrLength);
	cout << "How many letters do you have to choose from? ";
	getline(cin, tempStrNum);
	tempNum = stoi(tempStrNum);
	for (int i = 0; i < tempNum; i++)
	{
		cout << "Letter #" << i + 1 << ": ";
		cin >> tempLetter;
		letters.push_back(tolower(tempLetter));
	}
	numLetters = tempLength;
}

void reduceVec(vector<string> &words, const int &numLetters)
{
	vector<string> temp(0);
	for (unsigned i = 0; i < words.size(); i++)
	{
		if (words[i].size() == numLetters)
		{
			temp.push_back(words[i]);
		}
	}
	words = temp;
}



bool illegalWord(string &testWord)
{
	bool illResult = false;
	bool result = false;
	bool vowResult = true;
	string illegalCharacters = "1234567890'-\\/&+";
	string vowels = "aeiou";
	for (unsigned i = 0; i < illegalCharacters.size(); i++)
	{
		illResult = contains(testWord, illegalCharacters[i]);
		if (illResult == true)
			break;
	}
	return result;
}

bool contains(string &testWord, char &testPhrase)
{
	bool result = false;
	if (testWord.find(testPhrase) != string::npos)
	{
		result = true;
	}
	return result;
}

void calcWords(vector<string> &outputWords, vector<string> &words, vector<char> &letters, int &length)
{
	int lettersSize = letters.size();
	vector<char> tempLetters(0);
	vector<string> tempWords(0);
	bool *result = nullptr;
	for (int x = 0; x < lettersSize; x++)
	{
		for (unsigned i = 0; i < words.size(); i++)
		{
			if (words[i].find_first_of(letters[x]) == words[i].find_last_of(letters[x]) && words[i].find(letters[x]) != string::npos)
			{
				tempWords.push_back(words[i]);
			}
		}
	}
	for (unsigned i = 0; i < tempWords.size(); i++)
	{
		result = new bool[lettersSize];
		for (int y = 0; y < lettersSize; y++)
		{
			result[y] = false;
		}
		for (int x = 0; x < lettersSize; x++)
		{
			if (tempWords[i].find(letters[x]) != string::npos)
			{
				result[x] = true;
			}
		}
		bool tempTotalResult = true;
		int tempCounter = 1;
		for (int y = 0; y < lettersSize; y++)
		{
			if (result[y] == true)
				tempCounter++;
			if (tempCounter >= length)
			{
				tempCounter = 1;
				tempTotalResult = true;
				break;
			}
		}
		bool tempResultAgain = false;
		bool duplicate = false;
		for (int y = 0; y < words.size(); y++)
		{

			if (words[y] == tempWords[i])
				tempResultAgain = true;
		}
		for (int y = 0; y < tempWords[i].size(); y++)
		{
			for (int x = 0; x < lettersSize; x++)
			{
				if (tempWords[i].at(y) == letters[x])
				{
					break;
				}
				else if (x == lettersSize - 1)
				{
					tempResultAgain = false;
					//break;
				}
			}
			if (tempResultAgain == false)
				break;
		}
		if (tempTotalResult == true && tempResultAgain == true)
		{
			for (unsigned x = 0; x < outputWords.size(); x++)
			{
				if (outputWords[x] == tempWords[i])
					duplicate = true;
			}
			if (!duplicate)
			{
				outputWords.push_back(tempWords[i]);
			}
		}
	}
}