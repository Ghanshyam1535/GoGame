//
//  Name:- Ghanshyam Savaliya
//  Student ID:- 200486455
//

#include "Search.h"

#include <cassert>

#include "Move.h"

using namespace std;



int linearSearch (const SortableMove data_in[],
                  int count_in,
                  const SortableMove& value_in)
{
	for(int i = 0; i < count_in; i++)
	{
		if(data_in[i] == value_in)
			return i;  // end function immediately
	}

	// value not in array
	return VALUE_NOT_FOUND;
}

 int unsortedFindSmallest (const SortableMove data_in[],
                           int count_in)
{
	assert(count_in >= 1);

	int smallest_index = 0;

	for(int i = 1; i < count_in; i++)
	{
		if(data_in[i] < data_in[smallest_index])
			smallest_index = i;
	}

	return smallest_index;
}

int unsortedFindLargest (const SortableMove data_in[],
                         int count_in)
{
	assert(count_in >= 1);

	int largest_index = 0;

	for(int i = 1; i < count_in; i++)
	{
		if(data_in[largest_index] < data_in[i])
			largest_index = i;
	}

	return largest_index;
}

void mySort (SortableMove data_in[],
             int count_in)
{
	// selection sort

	for(int i = 0; i + 1 < count_in; i++)
	{
		// find smallest remaining element
		int smallest_index = i;
		for(int j = i + 1; j < count_in; j++)
		{
			if(data_in[j] < data_in[smallest_index])
				smallest_index = j;
		}

		// move smallest element to correct location
		SortableMove temp = data_in[i];
		data_in[i] = data_in[smallest_index];
		data_in[smallest_index] = temp;
	}
}
/*
void mySort (SortableMove data_in[],
             int count_in)
{
	// insertion sort

	for(int i = 1; i < count_in; i++)
	{
		// find insert location
		int insert_index = 0;
		while(        insert_index  <         i &&  // still in sorted portion
		      data_in[insert_index] < data_in[i])   // still smaller data
		{
			insert_index++;
		}

		// insert into sorted area, shifting data right
		SortableMove temp = data_in[i];
		for(int j = i; j > insert_index; j--)
		{
			data_in[j] = data_in[j - 1];
		}
		data_in[insert_index] = temp;
	}
}
*/
bool isSorted (const SortableMove data_in[],
               int count_in)
{
	for(int i = 1; i < count_in; i++)
	{
		if(data_in[i] < data_in[i - 1])
			return false;
	}
	return true;
}

int sortedFindSmallest (const SortableMove data_in[],
                        int count_in)
{
	assert(count_in >= 1);
	assert(isSorted(data_in, count_in));

	return 0;
}

int sortedFindLargest (const SortableMove data_in[],
                       int count_in)
{
	assert(count_in >= 1);
	assert(isSorted(data_in, count_in));

	return count_in - 1;
}

int binarySearch (const SortableMove data_in[],
                  int count_in,
                  const SortableMove& value_in)
{
	assert(isSorted(data_in, count_in));

	// using semi-open interval [low, high)
	int low  = 0;
	int high = count_in;

	while(low < high)  // loop also return out if value found
	{
		int mid = (high + low) / 2;
		if(data_in[mid] == value_in)
			return mid;  // return out of loop
		else if(data_in[mid] < value_in)
			low = mid + 1;
		else // data[mid] > value
			high = mid;
	}

	// value not in array
	return VALUE_NOT_FOUND;
}

int binarySearchFirst (const SortableMove data_in[],
                       int count_in,
                       const SortableMove& value_in)  //  NEEDS TESTING  <|>
{
	assert(isSorted(data_in, count_in));

	// using semi-open interval [low, high)
	int low  = 0;
	int high = count_in;

	while(low < high)  // loop also return out if value found
	{
		int mid = (high + low) / 2;
		if(data_in[mid    ] == value_in &&
		   (mid < 1 || data_in[mid - 1] <  value_in))
		{
			return mid;  // return out of loop
		}
		else if(data_in[mid] < value_in)
			low = mid + 1;
		else // data[mid] > value
			high = mid;
	}

	// value not in array
	return VALUE_NOT_FOUND;
}
