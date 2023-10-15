
#pragma once

#include <string>
#include "string.h"

using namespace std;

enum InfoTypes
{
	INFO_ID = 0,
	INFO_FIRST_NAME = 1,
	INFO_MIDDLE_NAME = 2,
	INFO_LAST_NAME = 3,
	INFO_ROLE = 4,
	INFO_ORGANIZATION = 5,
	INFO_ADDRESS = 6,
	INFO_CITY = 7,
	INFO_COUNTY = 8,
	INFO_STATE = 9,
	INFO_ZIP = 10,
	INFO_PRIMARY_PHONE_NUMBER = 11,
	INFO_SECONDARY_PHONE_NUMBER = 12,
	INFO_EMAIL = 13,
    INFO_NONE = 14
};

//Define a clear function based on OS the code is compiled for since there is no standard way to do this
#ifdef _WIN32
static void clear_console()
{
	system("cls");
}
#elif __linux__
static void clear_console()
{
	system("clear");
}
#endif


static const string lowercase(const string& s)
{
    string temp = s;
    for(auto& x : temp)
        x = tolower(x);
    return temp;
}

//Compare two strings alphabetically; 0 if both are the same, 1 if first is larger, 2 if second is larger
static const int compare_strings(const string& a, const string& b)
{
	//Lowercase so the difference in ASCII for capital and lowercase do not interfere with comparison
	const string ac = lowercase(a);
	const string bc = lowercase(b);

	for (int i = 0; i < ac.size(); ++i)
	{
		//Less in ASCII means higher in alphabet
		if ((int)ac[i] < (int)bc[i])
			return 1;
		else if ((int)ac[i] > (int)bc[i])
			return 2;
	}

    return 0;
}