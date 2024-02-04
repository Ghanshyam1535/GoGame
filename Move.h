//
//  Name:- Ghanshyam Savaliya
//  Student ID:- 200486455
//

#pragma once

struct Move
{
	bool is_played;
	int row;
	int column;
};

// implementation inheritance
struct SortableMove : public Move
{
	float net_score;
};

bool operator== (const SortableMove& lhs_in,
                 const SortableMove& rhs_in);
bool operator< (const SortableMove& lhs_in,
                const SortableMove& rhs_in);

