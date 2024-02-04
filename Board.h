//
//  Name:- Ghanshyam Savaliya
//  Student ID:- 200486455
//

#pragma once

#include <string>

#include "BoardValue.h"



const int BOARD_SIZE_MIN     =  1;
const int BOARD_SIZE_MAX     = 24;
const int BOARD_SIZE_DEFAULT = 19;
const int STAR_POINT_SPACING =  6;

struct StonesRemoved
{
	int us;
	int them;
};



//
//  Board
//
//  A class to represent the complete position of the game
//    board.  This is which colour of stone (if any) is at each
//    point.
//
//  Class Invariant:
//    <1> board_size >= BOARD_SIZE_MIN
//    <2> board_size <= BOARD_SIZE_MAX
//    <3> place_count == board_size * board_size
//    <4> p_places != nullptr
//    <5> isBoardValueValid(p_places[i])
//                                    WHERE 0 <= i < place_count
//
class Board
{
public:
//
//  Default Constructor
//
//  Purpose: To create an empty Board of the default size.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: A new Board is initialized with a size of
//               BOARD_SIZE_DEFAULT.  Every place is set to
//               BOARD_VALUE_EMPTY.
//
	Board ();

//
//  Size Constructor
//
//  Purpose: To create an empty Board of the specified size.
//  Parameter(s):
//    <1> size_in: The size for the new Board
//  Precondition(s):
//    <1> size_in >= BOARD_SIZE_MIN
//    <2> size_in <= BOARD_SIZE_MAX
//  Returns: N/A
//  Side Effect: A new Board is initialized with a size of
//               size_in.  Every place is set to
//               BOARD_VALUE_EMPTY.
//
	Board (int size_in);

	Board (const Board& board_in);
	~Board ();
	Board& operator= (const Board& board_in);
  bool operator== (const Board& board_in) const;

//
//  getSize
//
//  Purpose: The determine the size of the board.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: The board size.
//  Side Effect: N/A
//
	int getSize () const;

//
//  isOnBoard
//
//  Purpose: The determine whether a place is on this Board.
//  Parameter(s):
//    <1> row_in: The row of the plce to check
//    <2> column_in: The column of the place to check
//  Precondition(s): N/A
//  Returns: Whether place (row_in, column_in) is on the board.
//  Side Effect: N/A
//
	bool isOnBoard (int row_in, int column_in) const;

//
//  getAt
//
//  Purpose: To determine the board value at one place.
//  Parameter(s):
//    <1> row_in: The row of the place to check
//    <2> column_in: The column of the place to check
//  Precondition(s):
//    <1> isOnBoard(row_in, column_in)
//  Returns: The board value at place (row_in, column_in).
//  Side Effect: N/A
//
	char getAt (int row_in, int column_in) const;

//
//  print
//
//  Purpose: To display the board.
//  Parameter(s): N/A
//  Precondition(s): N/A
//  Returns: N/A
//  Side Effect: The current board position (state) is printed
//               to standard output (cout).  This includes the
//               row numbers, column letters, and any empty star
//               points.
//
	void print () const;

//
//  countWithValue
//
//  Purpose: To determine the number of places on the board with
//           the specified value.  This function can be used to
//           count a player's stones.  To determine the player's
//           score, use calculateScore.
//  Parameter(s):
//    <1> value_in: The board value to count
//  Precondition(s):
//    <1> isBoardValueValid(us_value_in)
//  Returns: The number of places on the board that have value
//           value_in.
//  Side Effect: N/A
//
	int countWithValue (char value_in) const;

//
//  calculateScore
//
//  Purpose: To determine the score for a player.  The function
//           considers controlled territory.
//  Parameter(s):
//    <1> us_value_in: The board value for the player
//  Precondition(s):
//    <1> isBoardValuePlayer(us_value_in)
//  Returns: The score for the player playing stones with value
//           us_value_in.
//  Side Effect: N/A
//
	int calculateScore (char us_value_in) const;

//
//  setAt
//
//  Purpose: To set the board value at one place.  This function
//           does not detect captured stones.
//  Parameter(s):
//    <1> row_in: The row of the place to change
//    <2> column_in: The column of the place to change
//    <3> value_in: The new board value
//  Precondition(s):
//    <1> isOnBoard(row_in, column_in)
//    <2> isBoardValueValid(us_value_in)
//  Returns: N/A
//  Side Effect: Board place (row_in, column_in) is set to value
//               value_in.
//
	void setAt (int row_in, int column_in,
	            char value_in);

//
//  load
//
//  Purpose: To load a board position (state) from a file.
//  Parameter(s):
//    <1> filename_in: The name of the file to load from,
//                     including the file extension
//  Precondition(s):
//    <1> filename_in != ""
//  Returns: N/A
//  Side Effect: The contents of this Board are replaced with
//               the board position in file filename_in.  If
//               anything goes wrong, an error message is
//               printed and this Board is left in a
//               consistant state.  It may be unchanged, or it
//               may have a mix of data from the file and
//               BOARD_VALUE_EMPTY values.
//
	void load (const std::string& filename_in);

//
//  playStone
//
//  Purpose: To play a stone and remove any captured stones.
//  Parameter(s):
//    <1> row_in: The row to play the stone at
//    <2> column_in: The column to play the stone at
//    <3> us_value_in: The board value of the stone played
//  Precondition(s):
//    <1> isOnBoard(row_in, column_in)
//    <2> getAt(row_in, column_in) == BOARD_VALUE_EMPTY
//    <3> isBoardValuePlayer(us_value_in)
//  Returns: How many stones of each color were captured.
//  Side Effect: Board place (row_in, column_in) is set to value
//               value_in.  Any stones of either color that are
//               captured are removed.
//
	StonesRemoved playStone (int row_in, int column_in,
	                         char us_value_in);

//
//  replaceAll
//
//  Purpose: To replace all instances of one value on this
//           Board with another value.
//  Parameter(s):
//    <1> old_value_in: The value to replace
//    <2> new_value_in: The replacement value
//  Precondition(s):
//    <1> isBoardValueValid(old_value_in)
//    <2> isBoardValueValid(new_value_in)
//  Returns: N/A
//  Side Effect: Every place on this Board that has value
//               old_value_in is set to have value new_value_in.
//
	void replaceAll (char old_value_in,
	                 char new_value_in);

//
//  fillConnected
//
//  Purpose: To replace all instances of one value on this
//           Board that are connected to another value with a
//           third value.  Place A is connected to place B if
//    <1> A is next to B.
//    <2> A is next to a place of the same type that fulfills
//        either of these conditions.  Note that this allows
//        arbitrarily long connection chains.
//  Parameter(s):
//    <1> old_value_in: The value to replace
//    <2> new_value_in: The replacement value
//    <3> neighbour_value_in: The value old_value_in must be
//                            connected to
//  Precondition(s):
//    <1> isBoardValueValid(old_value_in)
//    <2> isBoardValueValid(new_value_in)
//    <3> isBoardValueValid(neighbour_value_in)
//  Returns: N/A
//  Side Effect: Every place on this Board that has value
//               old_value_in and is connected to at least one
//               place with value neighbour_value_in is set to
//               have value new_value_in.
//  Warning: This function is slow.
//
	void fillConnected (char old_value_in,
	                    char new_value_in,
	                    char neighbour_value_in);

//
//  isANeighbourWithValue
//
//  Purpose: To determine if a place has a neighbour with the
//           specified board value.  This function correctly
//           handles the edge of the board.
//  Parameter(s):
//    <1> row_in: The row of the place to check
//    <2> column_in: The column of the place to check
//    <3> value_in: The board value to check for
//  Precondition(s):
//    <1> isOnBoard(row_in, column_in)
//    <2> isBoardValueValid(value_in)
//  Returns: Whether any of the four neighbours of board place
//           (row_in, column_in) have value value_in.  Note that
//           a place is NOT its own neighbour.
//  Side Effect: N/A
//
	bool isANeighbourWithValue (int row_in, int column_in,
	                            char value_in) const;

private:
	int toIndex (int row_in, int column_in) const;
	int calculatePlaceCount () const;
	bool isAlignedForStarPoint (int index_in) const;
	void printRowNumber (int row_in) const;
	void printColumnLetters () const;
	int capturePlayer (char player_value_in);
	void copyData (const Board& board_in);
	void destroyData ();
	bool isInvariantTrue () const;

private:
	int board_size;
	int place_count;
	char* p_places;
};



