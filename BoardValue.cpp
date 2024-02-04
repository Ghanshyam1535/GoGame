//
//  Name:- Ghanshyam Savaliya
//  Student ID:- 200486455
//

#include <cassert>

#include "BoardValue.h"

bool isBoardValueValid (char value_in)
{
	switch(value_in)
	{
	case BOARD_VALUE_EMPTY:
	case BOARD_VALUE_BLACK:
	case BOARD_VALUE_WHITE:
	case BOARD_VALUE_MARKED:
		return true;
	default:
		return false;
	}
}

bool isBoardValuePlayer (char value_in)
{
	switch(value_in)
	{
	case BOARD_VALUE_BLACK:
	case BOARD_VALUE_WHITE:
		return true;
	default:
		return false;
	}
}

char getOtherPlayer (char player_value_in)
{
	assert(isBoardValuePlayer(player_value_in));

	switch(player_value_in)
	{
	case BOARD_VALUE_BLACK:
		return BOARD_VALUE_WHITE;
	case BOARD_VALUE_WHITE:
		return BOARD_VALUE_BLACK;
	default:
		return BOARD_VALUE_MARKED;  // should never happen
	}
}
