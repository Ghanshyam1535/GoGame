//
//  Name:- Ghanshyam Savaliya
//  Student ID:- 200486455
//

#include "Move.h"



bool operator== (const SortableMove& lhs_in,
                 const SortableMove& rhs_in)
{
	return lhs_in.net_score == rhs_in.net_score;
}

bool operator< (const SortableMove& lhs_in,
                const SortableMove& rhs_in)
{
	return lhs_in.net_score < rhs_in.net_score;
}