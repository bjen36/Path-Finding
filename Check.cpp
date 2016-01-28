#include "Check.h"
#include <vector>
#include <stdlib.h>

// EFFECTS: Checks to see if the north route has been taken or is possible to move to
bool north_check(vector<vector<vector<path_tracker> > > & maze, const coordinates & starting, bool & finish)
{
	int new_row = starting.row - 1;
	if (new_row < 0)
	{
		return false;
	}
	if (maze[starting.room_val][new_row][starting.column].symbol == 'R')
	{
		finish = true;
		return true;
	}
	if (maze[starting.room_val][new_row][starting.column].checked != 0)
	{
		return false;
	}
	if (maze[starting.room_val][new_row][starting.column].symbol == '#')
	{
		return false;
	}

	// change it to checked
	maze[starting.room_val][new_row][starting.column].checked = true;
	return true;
}

// EFFECTS: Checks to see if the east route has been taken or is possible to move to
bool east_check(vector<vector<vector<path_tracker> > > & maze, int bounds, const coordinates & starting, bool & finish)
{
	int new_col = starting.column + 1;
	if (new_col >= bounds)
	{
		return false;
	}
	if (maze[starting.room_val][starting.row][new_col].symbol == 'R')
	{
		finish = true;
		return true;
	}
	if (maze[starting.room_val][starting.row][new_col].checked != 0)
	{
		return false;
	}
	if (maze[starting.room_val][starting.row][new_col].symbol == '#')
	{
		return false;
	}
	// change it to checked
	maze[starting.room_val][starting.row][new_col].checked = true;
	return true;
}

// EFFECTS: Checks to see if the south route has been taken or is possible to move to
bool south_check(vector<vector<vector<path_tracker> > > & maze, int bounds, const coordinates & starting, bool & finish)
{
	int new_row = starting.row + 1;
	if (new_row >= bounds)
	{
		return false;
	}
	if (maze[starting.room_val][new_row][starting.column].symbol == 'R')
	{
		finish = true;
		return true;
	}
	if (maze[starting.room_val][new_row][starting.column].checked != 0)
	{
		return false;
	}
	if (maze[starting.room_val][new_row][starting.column].symbol == '#')
	{
		return false;
	}
	// set to checked
	maze[starting.room_val][new_row][starting.column].checked = true;
	return true;
}

// EFFECTS: Checks to see if the west route has been taken or is possible to move to 
bool west_check(vector<vector<vector<path_tracker> > > & maze, const coordinates & starting, bool & finish)
{
	int new_col = starting.column - 1;
	if (new_col < 0)
	{
		return false;
	}
	if (maze[starting.room_val][starting.row][new_col].symbol == 'R')
	{
		finish = true;
		return true;
	}
	if (maze[starting.room_val][starting.row][new_col].checked != 0)
	{
		return false;
	}
	if (maze[starting.room_val][starting.row][new_col].symbol == '#')
	{
		return false;
	}
	// sset to checked
	maze[starting.room_val][starting.row][new_col].checked = true;
	return true;
}

// EFFECTS: Checks if current is portal and checks if it is a ring. Checks if portal is in range of rooms
// if not, ignore it
bool portal_check(vector<vector<vector<path_tracker> > > & maze, int bounds, const coordinates & starting, bool & finish, int * new_room)
{
	//int new_room = atoi(&maze[starting.room_val][starting.row][starting.column].symbol);
	if (isdigit(starting.symbol))
	{
		*new_room = atoi(&starting.symbol);

		// checks if portal is in range of number of rooms
		if (*new_room >= bounds)
		{
			return false;
		}
		else
		{
			// checks coordinate in the new room if it is 'R'
			if (maze[*new_room][starting.row][starting.column].symbol == 'R')
			{
				finish = true;
				return true;
			}
			// checks if it is #
			else if (maze[*new_room][starting.row][starting.column].symbol == '#')
			{
				return false;
			}
			else if (maze[*new_room][starting.row][starting.column].checked != 0)
			{
				return false;
			}
			// returns true because it is either '.' or another portal
		}
	}
	else
	{
		return false;
	}
	// set to checked
	maze[*new_room][starting.row][starting.column].checked = true;
	return true;
}
