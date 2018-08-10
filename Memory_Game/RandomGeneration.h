/*
Memory Game

Name : Mansi Patel (200351242)
Ramandeep Kaur (200353584)
*/

#pragma once


#include<time.h>
#include<iostream>
#include<conio.h>

using namespace std;

class RandomGeneration
{
	int Low, High;

public:
	RandomGeneration();
	int DrawRandomNumber();
	int GetHigh();
	int GetLow();

	~RandomGeneration();

};

RandomGeneration::RandomGeneration()
{
	Low = 1;
	High = 100;
}
RandomGeneration::~RandomGeneration()
{
}


// Return the Random Number
// Interval : Self explanatory - Get the differece between the high and low values
// RandomOfSet = using the rand() function to generate random numbers from 0 to Interval -1
// RandomNumber = Add the RandomOfSet to the lowest number;

int RandomGeneration::DrawRandomNumber()
{
	int Interval = GetHigh() - GetLow() + 1;
	int RandomOfSet = rand() % Interval;
	int RandomNumber = GetLow() + RandomOfSet;

	//cout << RandomNumber;
	return RandomNumber;
}

// Standard Inpectors - Return High & Low values

int RandomGeneration::GetHigh()
{
	return High;
}

int RandomGeneration::GetLow()
{
	return Low;
}