//
//  Name:- Ghanshyam Savaliya
//  Student ID:- 200486455
//

#include <cassert>
#include <string>
#include <iostream>

#include "PlaceString.h"
#include "Game.h"

using namespace std;

int askBoardSize ();



int main ()
{
	cout << "Welcome to my Go game!" << endl;
	string name;
	while(name == "")
	{
		cout << "Enter your name:  ";
		getline(cin, name);
	}
	cout << "Hello " << name << ".  You will play black." << endl;
	cout << endl;

	int board_size = askBoardSize();
	assert(board_size >= BOARD_SIZE_MIN);
	assert(board_size <= BOARD_SIZE_MAX);
	Game game(board_size);

	bool playing = true;
	while(playing)
	{
		game.printBoard();
		cout << "Enter your move:  ";
		string move_string;
		getline(cin, move_string);

		if(move_string == "quit")
			playing = false;
		else if(move_string == "new")
		{
			game.printWinner();

			board_size = askBoardSize();
			assert(board_size >= BOARD_SIZE_MIN);
			assert(board_size <= BOARD_SIZE_MAX);
			game = Game(board_size);
		}
		else if(move_string == "load")
		{
			game.printWinner();

			string filename;
			cout << "Enter the file name:  ";
			getline(cin, filename);
			game = Game(filename);
		}
		else if(move_string == "pass")
		{
			game.blackPass();

			bool is_white_played = game.whiteAi();
			if(is_white_played == false)
				playing = false;
		}
    else if (move_string == "undo"){
      game.undo2Moves();
    }
		else if(isPlaceStringWellFormed(move_string))
		{
			int row    = placeStringToRow   (move_string);
			int column = placeStringToColumn(move_string);

			bool result = game.blackPlay(row, column);
			if(result == true)
				game.whiteAi();
			// else failure message is printed by blackPlay
		}
		else
			cout << "\"" << move_string << "\" is ill-formed." << endl;
		cout << endl;
	}

	game.printWinner();
	cout << "Goodbye, " << name << "!" << endl;
	return 0;
}

int askBoardSize ()
{
	int board_size = 0;
	while(board_size < BOARD_SIZE_MIN ||
	      board_size > BOARD_SIZE_MAX)
	{
		cout << "Enter the board size:  ";
		cin >> board_size;

		cin.clear();  // clear error state (if any)
		string dummy;
		getline(cin, dummy);  // throw away whatever else is on the line

		if(board_size < BOARD_SIZE_MIN)
			cout << "Too small: minimum size is " << board_size << endl;
		if(board_size > BOARD_SIZE_MAX)
			cout << "Too large: maximum size is " << board_size << endl;
	}
	cout << endl;

	assert(board_size >= BOARD_SIZE_MIN);
	assert(board_size <= BOARD_SIZE_MAX);
	return board_size;
}
