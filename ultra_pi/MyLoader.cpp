//implements MyLoader class

#include "stdafx.h"
#include <wchar.h>
#include "MyLoader.h"

const int NUM_CALC_TIME = 8;
const int MAX_CHAR = 50;
const char * FILENAME = "calc_t.dat";

CString calc_time[NUM_CALC_TIME];
int num = 0;


MyLoader::MyLoader()
{
}

MyLoader::~MyLoader()
{
}

//loades the file containing calculation times
bool MyLoader::load_all()
{
	num = 0;							// set num back to start position;
	FILE * stream;
	wchar_t buffer[MAX_CHAR];
	int i = 0;

	if(!fopen_s(&stream, FILENAME, "r"))
	{
		while((feof(stream) == 0) && (i < NUM_CALC_TIME))
		{
			fgetws(buffer, MAX_CHAR - 1, stream);
			calc_time[i] = buffer;
			calc_time[i].Replace(L"\n", L"");
			i++;
		}

		fclose(stream);
		return true;
	}
	return false;
}

//saves the calculation times in a specified file
bool MyLoader::save_all()
{
	FILE * stream;

	if(!fopen_s(&stream, FILENAME, "w"))
	{
		for(int i = 0; i < NUM_CALC_TIME; i++)
		{
			fwprintf_s(stream, _T("%s\n"), calc_time[i]);
		}

		fclose(stream);
		return true;
	}
	return false;
}

//it returns on evern call the time needed to calculate the specified number of digits
//and goes to the next saved time, if existing
CString MyLoader::getNextCalcTime()
{
	if(num < NUM_CALC_TIME)
	{
		num++;
		return calc_time[num - 1];
	}
	return NULL;
}

void MyLoader::setCalcTime(int position, CString time)
{
	if(position >= 0 && position < NUM_CALC_TIME)
	{
		double a, b;
		a = _wtof(calc_time[position]);
		b = _wtof(time);
		if((a > b) || (a <= 0.0))						// is the new value lower than the old one?
			calc_time[position] = time;
	}
}

void MyLoader::init()
{
	for(int i = 0; i < NUM_CALC_TIME; i++)
		calc_time[i] = L"Not yet calculated";
}