//
//  Name:- Ghanshyam Savaliya
//  Student ID:- 200486455
//

#pragma once

#include "Move.h"
#include "Board.h"

class Game;



struct MoveResult
{
	bool is_legal;
	float net_score;
};



//
//  ArtificialIntelligence
//
//  A class to choose moves for the computer player.  Client
//    code should create an ArtificialIntelligence object and
//    then call chooseMove repeatedly.
//
//  Class Invariant:
//    <1> isBoardValuePlayer(us_value)
//
class ArtificialIntelligence
{
public:
//
//  Constructor
//
//  Purpose: To initialize an ArtificialIntelligence to play
//           stones with the specified board value.
//  Parameter(s):
//    <1> us_value_in: Which player to choose moves for
//  Precondition(s):
//    <1> isBoardValuePlayer(us_value_in)
//  Returns: N/A
//  Side Effect: This ArtificialIntelligence is set to play
//               stones with color us_value_in.
//
	ArtificialIntelligence (char us_value_in);

//
//  chooseMove
//
//  Purpose: To choose the next move for the controlled player.
//  Parameter(s):
//    <1> board_in: The current board position
//  Precondition(s): N/A
//  Returns: Which move to make.
//  Side Effect: N/A
//
	Move chooseMove (const Game& game_in) const;

private:
	float calculateNetScore (const Board& board_in) const;
	MoveResult getPlayResult (const Game& game_in,
	                          int row_in, int column_in) const;
	bool isInvariantTrue () const;

private:
	char us_value;
};
