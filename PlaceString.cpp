//
//  Name:- Ghanshyam Savaliya
//  Student ID:- 200486455
//

#include "PlaceString.h"

#include <string>

using namespace std;

int stringToInteger (const string& str_in)
{
	if(str_in == "")
		return INVALID_COORDINATE;

	int result = 0;
	for(int i = 0; i < (int)(str_in.length()); i++)
	{
		if(str_in[i] < '0' || str_in[i] > '9')
			return INVALID_COORDINATE;

		result *= 10;
		result += str_in[i] - '0';
	}
	return result;
}

int placeStringToColumn (const string& place_string_in)
{
	if(place_string_in.length() < 1)
		return INVALID_COORDINATE;

	char column_char = place_string_in[0];
	if(column_char >= 'A' && column_char <= 'H')
		return column_char - 'A';
	else if(column_char >= 'J' && column_char <= 'N')
		return column_char - 'A' - 1;
	else if(column_char >= 'P' && column_char <= 'Z')
		return column_char - 'A' - 2;
	else
		return INVALID_COORDINATE;
}

int placeStringToRow (const string& place_string_in)
{
	if(place_string_in.length() < 2)
		return INVALID_COORDINATE;

	string row_str = place_string_in.substr(1);
	return stringToInteger(row_str);
}

bool isPlaceStringWellFormed (const string& place_string_in)
{
	if(placeStringToColumn(place_string_in) == INVALID_COORDINATE)
		return false;
	if(placeStringToRow(place_string_in) == INVALID_COORDINATE)
		return false;
	return true;
}

