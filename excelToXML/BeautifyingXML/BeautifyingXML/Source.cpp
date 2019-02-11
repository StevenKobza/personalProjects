#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

void bootifulXML(string &);
void insertBreak(string &, int &, int &);

int main()
{
	string line = "";
	string inputFileName = "";
	ifstream myFile;
	cout << "Enter your file name to open: ";
	getline(cin, inputFileName);
	//myFile.open("..\\..\\text.html");
	myFile.open(inputFileName);
	if (myFile.is_open())
	{
		if (getline(myFile, line))
		{
			bootifulXML(line);
		}
		myFile.close();
	}
	string outputFileName = "";
	cout << "Enter the file name to save to: ";
	getline(cin, outputFileName);
	ofstream outputXML;
	//outputXML.open("..\\..\\bootiful.html");
	outputXML.open(outputFileName);
	if (outputXML.is_open())
	{
		outputXML << line;
	}
	return 0;
}

void bootifulXML(string &inp)
{
	vector<int> lastFound(0);
	int numFound = -1;
	int lastCloseFound = 0;
	int lastEndFound = 0;
	string tempStr = "";
	unsigned found, tabDown;
	unsigned len = inp.length();
	int tabCount = 0;
	for (int i = 0; i < len; i++)
	{
		found = inp.find('>', lastCloseFound);
		if (found != string::npos)
		{
			if (inp[found + 1] == '<' && inp[found + 2] != '/')
			{
				tabCount += 1;
			}
			if (numFound > -1)
			{
				int tempInt = (found + 1 - lastFound[numFound]);
				tempStr = inp.substr(lastFound[numFound], tempInt);
				unsigned find = tempStr.find('/', 0);
				if (find != string::npos)
				{
					tabCount -= 1;
				}
			}
			lastCloseFound = found + 1;
			insertBreak(inp, lastCloseFound, tabCount);
			lastFound.push_back(lastCloseFound);
			numFound += 1;
		}
	}
}

void insertBreak(string &inp, int &found, int &tabCount)
{
	if (inp[found] == '<')
	{
		inp.insert(found, "\n");
		found += 1;
		for (int i = 0; i < tabCount; i++)
		{
			inp.insert(found, "\t");
			found += 1;
		}
	}
}