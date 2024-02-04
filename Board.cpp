//
//  Name:- Ghanshyam Savaliya
//  Student ID:- 200486455
//

#include "Board.h"

#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#include "BoardValue.h"

using namespace std;

Board ::Board() {
  board_size = BOARD_SIZE_DEFAULT;
  place_count = calculatePlaceCount(); // board_size must be set
  p_places = new char[place_count];

  // can't use clear because invariant isn't true yet
  for (int i = 0; i < place_count; i++) {
    p_places[i] = BOARD_VALUE_EMPTY;
  }

  assert(isInvariantTrue());
}

Board ::Board(int size_in) {
  assert(size_in >= BOARD_SIZE_MIN);
  assert(size_in <= BOARD_SIZE_MAX);

  board_size = size_in;
  place_count = calculatePlaceCount(); // board_size must be set
  p_places = new char[place_count];

  // can't use clear because invariant isn't true yet
  for (int i = 0; i < place_count; i++) {
    p_places[i] = BOARD_VALUE_EMPTY;
  }

  assert(isInvariantTrue());
}

Board ::Board(const Board &board_in) {
  assert(board_in.isInvariantTrue());

  p_places = nullptr;
  copyData(board_in);

  assert(isInvariantTrue());
}

Board ::~Board() {
  assert(isInvariantTrue());

  destroyData();
}

Board &Board ::operator=(const Board &board_in) {
  assert(isInvariantTrue());
  assert(board_in.isInvariantTrue());

  if (&board_in != this) {
    // from destructor
    destroyData();

    // no parent class to call operator= for

    // from copy constructor
    copyData(board_in);
  }

  assert(isInvariantTrue());
  return *this;
}

int Board ::getSize() const {
  assert(isInvariantTrue());

  return board_size;
}

bool Board ::isOnBoard(int row_in, int column_in) const {
  assert(isInvariantTrue());

  if (row_in < 0)
    return false;
  if (row_in >= board_size)
    return false;
  if (column_in < 0)
    return false;
  if (column_in >= board_size)
    return false;
  return true;
}

char Board ::getAt(int row_in, int column_in) const {
  assert(isInvariantTrue());
  assert(isOnBoard(row_in, column_in));

  int index = toIndex(row_in, column_in);
  assert(index < place_count);
  return p_places[index];
}

void Board ::print() const {
  assert(isInvariantTrue());

  printColumnLetters();

  for (int r = 0; r < board_size; r++) {
    printRowNumber(r);
    cout << " ";

    for (int c = 0; c < board_size; c++) {
      char value_here = getAt(r, c);
      if (value_here == BOARD_VALUE_EMPTY && isAlignedForStarPoint(r) &&
          isAlignedForStarPoint(c)) {
        cout << "*";
      } else
        cout << value_here;
      cout << " ";
    }

    printRowNumber(r);
    cout << endl;
  }

  printColumnLetters();
}

int Board ::countWithValue(char value_in) const {
  assert(isBoardValueValid(value_in));

  int count = 0;
  /*
          // from Assignments 3 and 4
          for(int r = 0; r < BOARD_SIZE; r++)
          {
                  for(int c = 0; c < BOARD_SIZE; c++)
                  {
                          if(getAt(r, c) == value_in)
                                  count++;
                  }
          }
  */
  // does the same thing, but runs faster
  for (int i = 0; i < place_count; i++) {
    if (p_places[i] == value_in)
      count++;
  }
  return count;
}

int Board ::calculateScore(char us_value_in) const {
  assert(isInvariantTrue());
  assert(isBoardValuePlayer(us_value_in));

  Board copy = *this;
  char them_value = getOtherPlayer(us_value_in);
  copy.fillConnected(BOARD_VALUE_EMPTY, them_value, them_value);
  copy.fillConnected(BOARD_VALUE_EMPTY, us_value_in, us_value_in);
  return copy.countWithValue(us_value_in);
}

void Board ::setAt(int row_in, int column_in, char value_in) {
  assert(isInvariantTrue());
  assert(isOnBoard(row_in, column_in));
  assert(isBoardValueValid(value_in));

  int index = toIndex(row_in, column_in);
  assert(index < place_count);
  p_places[index] = value_in;

  assert(isInvariantTrue());
}

void Board ::load(const string &filename_in) {
  assert(isInvariantTrue());
  assert(filename_in != "");

  // open file with name filename_in
  // fin will read from that file
  // use fin like you use cin
  ifstream fin(filename_in);

  if (!fin) {
    cout << "Error: Could not open file \"" << filename_in << "\"" << endl;
    return; // end function immediately
  }

  // read in the board size
  string line;
  int board_size_read;
  fin >> board_size_read;
  if (!fin) {
    cout << "Error: File \"" << filename_in
         << "\" does not start with board size" << endl;
    return; // end function immediately
  }
  if (board_size_read > BOARD_SIZE_MAX) {
    cout << "Error: File \"" << filename_in << "\" has board size "
         << board_size_read << ", but maximum is " << BOARD_SIZE_MAX << endl;
    return; // end function immediately
  }
  if (board_size_read < BOARD_SIZE_MIN) {
    cout << "Error: File \"" << filename_in << "\" has board size "
         << board_size_read << ", but minimum is " << BOARD_SIZE_MIN << endl;
    return; // end function immediately
  }
  assert(fin);
  string dummy;
  getline(fin, dummy); // throw away whatever else is on the line

  // replace this board with a new one of the correct size
  *this = Board(board_size_read);

  // read in board state
  bool is_print_error = true;
  for (int r = 0; r < board_size; r++) {
    string line;
    getline(fin, line);
    if (!fin) {
      if (is_print_error) {
        cout << "Error: Could not read line " << r << " of file \""
             << filename_in << "\"" << endl;
        cout << "       Replacing with '" << BOARD_VALUE_EMPTY << "'s" << endl;
        is_print_error = false;
      }
      line = string(BOARD_VALUE_EMPTY, board_size); // set to '.'s
    } else if ((int)(line.length()) < board_size) {
      if (is_print_error) {
        cout << "Error: Line " << r << " of file \"" << filename_in
             << "\" only contains " << line.length() << " / " << board_size
             << " characters" << endl;
        cout << "       Adding '" << BOARD_VALUE_EMPTY << "'s to end" << endl;
        is_print_error = false;
      }
      line += string(BOARD_VALUE_EMPTY, board_size); // add '.'s
    }

    for (int c = 0; c < board_size; c++) {
      if (isBoardValueValid(line[c]))
        setAt(r, c, line[c]);
      else {
        setAt(r, c, BOARD_VALUE_EMPTY);
        if (is_print_error) {
          cout << "Error: Line " << r << ", character " << c << " of file \""
               << filename_in << "\" is an invalid '" << line[c]
               << "' character" << endl;
          cout << "       Substituting '" << BOARD_VALUE_EMPTY << "'" << endl;
          is_print_error = false;
        }
      }
    }
  }

  assert(isInvariantTrue());
  // file will be closed automatically when fin goes out of scope
}

StonesRemoved Board ::playStone(int row_in, int column_in, char us_value_in) {
  assert(isInvariantTrue());
  assert(isOnBoard(row_in, column_in));
  char pos = p_places[toIndex(row_in, column_in)];
  assert(pos == BOARD_VALUE_EMPTY);
  assert(isBoardValuePlayer(us_value_in));

  setAt(row_in, column_in, us_value_in);

  char them_value = getOtherPlayer(us_value_in);
  StonesRemoved removed;
  removed.them = capturePlayer(them_value);
  removed.us = capturePlayer(us_value_in);

  assert(isInvariantTrue());
  return removed;
}

// this function would normally be private
void Board ::replaceAll(char old_value_in, char new_value_in) {
  assert(isInvariantTrue());
  assert(isBoardValueValid(old_value_in));
  assert(isBoardValueValid(new_value_in));
  /*
          // from Assignments 3 and 4
          for(int r = 0; r < BOARD_SIZE; r++)
          {
                  for(int c = 0; c < BOARD_SIZE; c++)
                  {
                          if(getAt(r, c) == old_value_in)
                                  setAt(r, c, new_value_in);
                  }
          }
  */
  // does the same thing, but runs faster
  for (int i = 0; i < place_count; i++) {
    if (p_places[i] == old_value_in)
      p_places[i] = new_value_in;
  }

  assert(isInvariantTrue());
}

// this function would normally be private
void Board ::fillConnected(char old_value_in, char new_value_in,
                           char neighbour_value_in) {
  assert(isInvariantTrue());
  assert(isBoardValueValid(old_value_in));
  assert(isBoardValueValid(new_value_in));
  assert(isBoardValueValid(neighbour_value_in));

  bool is_changed;
  do {
    is_changed = false;
    for (int r = 0; r < board_size; r++) {
      for (int c = 0; c < board_size; c++) {
        if (getAt(r, c) == old_value_in) {
          if (isANeighbourWithValue(r, c, neighbour_value_in) ||
              isANeighbourWithValue(r, c, new_value_in)) {
            setAt(r, c, new_value_in);
            is_changed = true;
          }
        }
      }
    }
  } while (is_changed);

  assert(isInvariantTrue());
}

// this function would normally be private
bool Board ::isANeighbourWithValue(int row_in, int column_in,
                                   char value_in) const {
  assert(isInvariantTrue());
  assert(isOnBoard(row_in, column_in));
  assert(isBoardValueValid(value_in));

  if (row_in - 1 >= 0)
    if (getAt(row_in - 1, column_in) == value_in)
      return true;
  if (row_in + 1 < board_size)
    if (getAt(row_in + 1, column_in) == value_in)
      return true;
  if (column_in - 1 >= 0)
    if (getAt(row_in, column_in - 1) == value_in)
      return true;
  if (column_in + 1 < board_size)
    if (getAt(row_in, column_in + 1) == value_in)
      return true;
  return false;
}

int Board ::toIndex(int row_in, int column_in) const {
  assert(isOnBoard(row_in, column_in));

  int index = row_in * board_size + column_in;
  assert(index < place_count);
  return index;
}

int Board ::calculatePlaceCount() const { return board_size * board_size; }

bool Board ::isAlignedForStarPoint(int index_in) const {
  assert(index_in >= 0);

  int center_modulus = (board_size / 2) % STAR_POINT_SPACING;
  int index_modulus = index_in % STAR_POINT_SPACING;

  if (index_modulus == center_modulus)
    return true;
  else
    return false;
}

void Board ::printRowNumber(int row_in) const {
  cout << right << setw(2) << row_in;
}

void Board ::printColumnLetters() const {
  cout << "   "; // space for row numbers

  // column headings
  for (int c = 0; c < board_size; c++) {
    char letter = 'A' + c;
    if (letter >= 'I')
      letter++;
    if (letter >= 'O')
      letter++;
    cout << letter << " ";
  }

  // don't need to leave space at end of line
  cout << endl;
}

int Board ::capturePlayer(char player_value_in) {
  assert(isBoardValuePlayer(player_value_in));

  replaceAll(player_value_in, BOARD_VALUE_MARKED);
  fillConnected(BOARD_VALUE_MARKED, player_value_in, BOARD_VALUE_EMPTY);
  int capture_count = countWithValue(BOARD_VALUE_MARKED);
  replaceAll(BOARD_VALUE_MARKED, BOARD_VALUE_EMPTY);
  return capture_count;
}

void Board ::copyData(const Board &board_in) {
  assert(board_in.isInvariantTrue());
  assert(p_places == nullptr);

  board_size = board_in.board_size;
  place_count = board_in.place_count;
  p_places = new char[place_count];
  for (int i = 0; i < place_count; i++) {
    p_places[i] = board_in.p_places[i];
  }

  assert(p_places != nullptr);
}

void Board ::destroyData() {
  assert(p_places != nullptr);

  delete[] p_places;
  p_places = nullptr;

  assert(p_places == nullptr);
}

bool Board ::isInvariantTrue() const {
  // this line disables the class invariant and makes the program run faster
  // return true;

  if (board_size < BOARD_SIZE_MIN)
    return false;
  if (board_size > BOARD_SIZE_MAX)
    return false;
  if (place_count != calculatePlaceCount()) // board_size must be set
    return false;
  if (p_places == nullptr)
    return false;
  for (int i = 0; i < place_count; i++) {
    if (!isBoardValueValid(p_places[i]))
      return false;
  }
  return true;
}

bool Board::operator==(const Board &board_in) const {
  assert(isInvariantTrue());
  assert(board_in.isInvariantTrue());
  if (!(board_in.getSize() == getSize() &&
        calculatePlaceCount() == board_in.calculatePlaceCount())) {
    return false;
  }
  for (int i = 0; i < place_count; i++) {
    if(!(p_places[i] == board_in.p_places[i])){
      return false;
    }
  }
  return true;
}



































