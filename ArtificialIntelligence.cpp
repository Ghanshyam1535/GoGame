//
//  Name:- Ghanshyam Savaliya
//  Student ID:- 200486455
//

#include "ArtificialIntelligence.h"

#include <cassert>
#include <cstdlib>
#include <iostream>

#include "Board.h"
#include "Game.h"
#include "Move.h"
#include "Search.h"

using namespace std;

ArtificialIntelligence ::ArtificialIntelligence(char us_value_in) {
  assert(isBoardValueValid(us_value_in) && isBoardValuePlayer(us_value_in));
  us_value = us_value_in;
  assert(isInvariantTrue());
}

Move ArtificialIntelligence ::chooseMove(const Game &game_in) const {
  int AI_SIZE = (BOARD_SIZE_MAX * BOARD_SIZE_MAX) + 1;
  SortableMove moves[AI_SIZE];
  int total_moves = 0;

  moves[total_moves].is_played = false;
  moves[total_moves].net_score = 0.5 + calculateNetScore(game_in.getBoard());

  total_moves++;
  MoveResult result;

  for (int i = 0; i < game_in.getBoard().getSize(); i++) {
    for (int j = 0; j < game_in.getBoard().getSize(); j++) {
      result = getPlayResult(game_in, i, j);
      // if move is legal run the loop
      if (result.is_legal) {
        moves[total_moves].row = i;
        moves[total_moves].column = j;
        moves[total_moves].is_played = true;
        // Automatically calculate the score and accrement the moves
        moves[total_moves].net_score = result.net_score;
        total_moves++;
      }
    }
  }
  // sort the array of white stone
  mySort(moves, total_moves);
  // find the largest stone place by white
  double highest_score = moves[total_moves].net_score;
  int largest = unsortedFindLargest(moves, total_moves);
  // place of white which will genrate randomlY which will help to score better.
  int index = binarySearchFirst(moves, total_moves, moves[largest]);

  srand(time(NULL));
  // random collection of stones of white for more points
  int range = total_moves - index;
  int random = (rand() % range) + index;

  return moves[random];
}

float ArtificialIntelligence ::calculateNetScore(const Board &board_in) const {
  char them_value = getOtherPlayer(us_value);

  int us_score_play = board_in.calculateScore(us_value);
  int them_score_play = board_in.calculateScore(them_value);
  return (float)(us_score_play - them_score_play);
}

MoveResult ArtificialIntelligence ::getPlayResult(const Game &game_in,
                                                  int row_in,
                                                  int column_in) const {
  Board board_in = game_in.getBoard();
  MoveResult result;

  if (game_in.getBoard().isOnBoard(row_in, column_in) &&
      game_in.getBoard().getAt(row_in, column_in) == BOARD_VALUE_EMPTY) {
    Board copied = game_in.getBoard();
    StonesRemoved removed = copied.playStone(row_in, column_in, us_value);
    if (removed.us > 0) {
      result.is_legal = false;
      return result;
    } else {
      result.is_legal = true;
      result.net_score = calculateNetScore(copied);
    }
  } else {
    result.is_legal = false;
  }
  return result;
}

bool ArtificialIntelligence ::isInvariantTrue() const {
  return isBoardValuePlayer(us_value) && isBoardValueValid(us_value);
}
