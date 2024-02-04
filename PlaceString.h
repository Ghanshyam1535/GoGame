//
//  Name:- Ghanshyam Savaliya
//  Student ID:- 200486455
//

#pragma once

#include <string>

using namespace std;



//
//  A place-string is a short string the player enters to choose
//    where to play a stone.  It is composed of an uppercase
//    letter representing a column followed by a non-negative
//    number representing a row.  The row numbers are
//    nonnegative integers (i.e. 0, 1, 2, ...).  A column letter
//    can be any upper case letter from 'A' to 'Z', except 'I'
//    or 'O'.  Thus, some valid place-strings are "A0", "H7",
//    "B18", "N12", and "U7".  A place-string with the correct
//    format is termed well-formed, and one without it
//    (e.g. "Q", "7G", "I6", "corner") is termed ill-formed.  A
//    place-string is well-formed even if it specifies a place
//    outside the 19x19 board (e.g. "A333", "Z9").
//
//  For reference:
//     A  B  C  D  E  F  G  H  J  K
//     0  1  2  3  4  5  6  7  8  9
//
//     L  M  N  P  Q  R  S  R  U  V
//    10 11 12 13 14 15 16 17 18 19
//
//     W  X  Y  Z
//    20 21 22 23
//


//
//  INVALID_COORDINATE
//
//  A constant returned when a place-string cannot be parsed.
//
const int INVALID_COORDINATE = -1;


//
//  stringToInteger
//
//  Purpose: To convert the specified string of digits to a
//           non-negative integer.
//  Parameter(s):
//    <1> str_in: The string to convert
//  Precondition(s): N/A
//  Returns: str_in, expressed as an integer.  If str_in is the
//           empty string or contains any non-digit characters,
//           INVALID_COORDINATE is returned.
//  Side Effect: N/A
//
int stringToInteger (const string& str_in);

//
//  placeStringToColumn
//
//  Purpose: To determine the column for a board place from the
//           specified place-string.  This depends on the first
//           character of the place-string.
//  Parameter(s):
//    <1> place_string_in: The place-string
//  Precondition(s): N/A
//  Returns: The column, expressed as an integer.  If
//           place_string does not contain a valid column,
//           INVALID_COORDINATE is returned.
//  Side Effect: N/A
//
int placeStringToColumn (const string& place_string_in);

//
//  placeStringToRow
//
//  Purpose: To determine the row for a board place from the
//           specified place-string.  This depends on the second
//           and following characters of the place-string.
//  Parameter(s):
//    <1> place_string_in: The place-string
//  Precondition(s): N/A
//  Returns: The row, expressed as an integer.  If place_string
//           does not contain a valid row, INVALID_COORDINATE is
//           returned.
//  Side Effect: N/A
//
int placeStringToRow (const string& place_string_in);

//
//  isPlaceStringWellFormed
//
//  Purpose: To determine if a place-string is well-formed.
//           This is equivilent to whether it contains both a
//           valid row and a valid column.
//  Parameter(s):
//    <1> place_string_in: The place-string
//  Precondition(s): N/A
//  Returns: Whether place_string is well-formed.
//  Side Effect: N/A
//
bool isPlaceStringWellFormed (const string& place_string_in);


