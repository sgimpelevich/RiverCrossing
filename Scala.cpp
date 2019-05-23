// River Crossing : Defines the entry point for the console application.

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	//approach: 
	// read file, parse and store only time-to-cross as a vector of integers
	// sort vector from smallest to largest time interval
	// calculate total time to cross is: a+d; a+c; a+b
	const string fileName = "InputFile.txt";
	ifstream inFile(fileName);
	if (!inFile)
	{
		cout << "Cannot find " << fileName << " . Exiting . . ." << endl;
		return 1;
	}

	vector<int> timeToCross; // parse line and collect time intervals
	string delimiter = ":";
	if (inFile.is_open())
	{
		string line;
		while (getline(inFile, line))
		{
			// parse line and get time interval
			auto pos = line.find(delimiter);
			string sTime = line.substr(pos+1);
			//cout << "line=[" << line << "]" << endl;
			//cout << "time=[" << sTime << "]" << endl;
			timeToCross.push_back(atoi(sTime.c_str()));
		}
		inFile.close();
	}

	sort(timeToCross.begin(), timeToCross.end());

	int totalTime = 0;			// time accumulated for the all to cross the river
	int fastestTreveler = timeToCross[0];

	// to move from one bank to the other in pairs smallest with the largest
	// round trip cost: smallest time + largest time
	// leave slowest on the other bank; fastest returns back to the starting bank
	// for the next crossing repeat fastest with the next slowest time
	for (auto iter = timeToCross.rbegin(); iter < timeToCross.rend() - 1; iter++)
	{
		// a round trip time for a pairs: a pair crosses the river and a single traveler returns with the torch
		totalTime += (*iter) + fastestTreveler;
		//cout << "adding:" << (*iter) << "+" << fastestTreveler << "=" << totalTime << endl;
	}

	cout << "It took " << totalTime << " min for all to cross the river." << endl;

	return 0;
}

