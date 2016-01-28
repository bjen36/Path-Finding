#include <vector>
#include <deque>
#include <stdlib.h>
#include <stdio.h>
#include "Output.h"

void update_M(vector<vector<vector<path_tracker> > > & table, deque<coordinates> & path_finder)
{
	coordinates previous; // path_tracker instead of coordinates
	coordinates previous_behind;

	std::deque<coordinates>::iterator it = path_finder.begin();

	previous = *it; //.front()

	//previous = path_finder.front(); // set end coordinates to previous in order to work backwards

	//path_finder.pop_front(); // need to set next coordinate

	while (it != path_finder.end())
	{
		(++it);
		previous_behind = *it;

		if (previous.direction == 'N')
		{
			if ((previous.room_val == previous_behind.room_val) && (previous.row == (previous_behind.row - 1)) && 
				(previous.column == previous_behind.column ))
			{
				table[previous_behind.room_val][previous_behind.row][previous_behind.column].symbol = 'n';
				previous = previous_behind;
			}
		}
		else if (previous.direction == 'E')
		{
			if ((previous.room_val == previous_behind.room_val) && (previous.row == (previous_behind.row)) && 
				(previous.column == (previous_behind.column + 1)))
			{
				table[previous_behind.room_val][previous_behind.row][previous_behind.column].symbol = 'e';
				previous = previous_behind;
			}
		}
		else if (previous.direction == 'S')
		{
			if ((previous.room_val == previous_behind.room_val) && (previous.row == (previous_behind.row + 1)) && 
				(previous.column == previous_behind.column))
			{
				table[previous_behind.room_val][previous_behind.row][previous_behind.column].symbol = 's';
				previous = previous_behind;
			}
		}
		else if (previous.direction == 'W')
		{
			if ((previous.room_val == previous_behind.room_val) && (previous.row == (previous_behind.row)) && 
				(previous.column == (previous_behind.column - 1)))
			{
				table[previous_behind.room_val][previous_behind.row][previous_behind.column].symbol = 'w';
				previous = previous_behind;
			}
		}
		else if (previous.direction == 'P')
		{
			if ((previous.room_val == atoi(&previous_behind.symbol)) && (previous.row == (previous_behind.row)) && 
				(previous.column == previous_behind.column))
			{
				table[previous_behind.room_val][previous_behind.row][previous_behind.column].symbol = 'p';
				previous = previous_behind;
			}
		}
	}
/*
 	//the latest code I was using
	while(!(path_finder.empty()))
	{
		previous_behind = path_finder.front();
		if (previous.direction == 'N')
		{
			if ((previous.room_val == previous_behind.room_val) && (previous.row == (previous_behind.row - 1)) && 
				(previous.column == previous_behind.column ))
			{
				table[previous_behind.room_val][previous_behind.row][previous_behind.column].symbol = 'n';
				previous = previous_behind;
			}
		}
		else if (previous.direction == 'E')
		{
			if ((previous.room_val == previous_behind.room_val) && (previous.row == (previous_behind.row)) && 
				(previous.column == (previous_behind.column + 1)))
			{
				table[previous_behind.room_val][previous_behind.row][previous_behind.column].symbol = 'e';
				previous = previous_behind;
			}
		}
		else if (previous.direction == 'S')
		{
			if ((previous.room_val == previous_behind.room_val) && (previous.row == (previous_behind.row + 1)) && 
				(previous.column == previous_behind.column))
			{
				table[previous_behind.room_val][previous_behind.row][previous_behind.column].symbol = 's';
				previous = previous_behind;
			}
		}
		else if (previous.direction == 'W')
		{
			if ((previous.room_val == previous_behind.room_val) && (previous.row == (previous_behind.row)) && 
				(previous.column == (previous_behind.column - 1)))
			{
				table[previous_behind.room_val][previous_behind.row][previous_behind.column].symbol = 'w';
				previous = previous_behind;
			}
		}
		else if (previous.direction == 'P')
		{
			if ((previous.room_val == atoi(&previous_behind.symbol)) && (previous.row == (previous_behind.row)) && 
				(previous.column == previous_behind.column))
			{
				table[previous_behind.room_val][previous_behind.row][previous_behind.column].symbol = 'p';
				previous = previous_behind;
			}
		}
		path_finder.pop_front();
	}*/
}

void print_M(vector<vector<vector<path_tracker> > > & table, int room_print, int size_print)
{
	printf("%d\n", size_print);
	printf("%d\n", room_print);

	for (int i = 0; i < room_print; i++)
	{
		printf("//room %d\n", i);
		for (int j = 0; j < size_print; j++)
			{
				for (int z = 0; z < size_print; z++)
				{
					printf("%c", table[i][j][z].symbol);
				}
				printf("\n");
			}	
	}
}


void print_L(deque<coordinates> & path_finder, int room_print, int size_print)
{
	printf("%d\n", size_print);
	printf("%d\n", room_print);
	printf("//path taken\n");

	coordinates previous;
	coordinates previous_behind;

	std::deque<coordinates>::iterator it = path_finder.begin();

	previous = *it; //.front()
	vector<coordinates> storage;

	while (it != path_finder.end())
	{
		(++it);
		previous_behind = *it;

		if (previous.direction == 'N')
		{
			if ((previous.room_val == previous_behind.room_val) && (previous.row == (previous_behind.row - 1)) && 
				(previous.column == previous_behind.column ))
			{
				coordinates input = {previous_behind.room_val, previous_behind.row, previous_behind.column, '\0', 'n'};
				storage.push_back(input);
				//printf("(%d,%d,%d,%c)\n", previous_behind.row, previous_behind.column, previous_behind.room_val, 'n');
				previous = previous_behind;
			}
		}
		else if (previous.direction == 'E')
		{
			if ((previous.room_val == previous_behind.room_val) && (previous.row == (previous_behind.row)) && 
				(previous.column == (previous_behind.column + 1)))
			{
				coordinates input = {previous_behind.room_val, previous_behind.row, previous_behind.column, '\0', 'e'};
				storage.push_back(input);
				//printf("(%d,%d,%d,%c)\n", previous_behind.row, previous_behind.column, previous_behind.room_val, 'e');
				previous = previous_behind;
			}
		}
		else if (previous.direction == 'S')
		{
			if ((previous.room_val == previous_behind.room_val) && (previous.row == (previous_behind.row + 1)) && 
				(previous.column == previous_behind.column))
			{
				coordinates input = {previous_behind.room_val, previous_behind.row, previous_behind.column, '\0', 's'};
				storage.push_back(input);
				//printf("(%d,%d,%d,%c)\n", previous_behind.row, previous_behind.column, previous_behind.room_val, 's');
				previous = previous_behind;
			}
		}
		else if (previous.direction == 'W')
		{
			if ((previous.room_val == previous_behind.room_val) && (previous.row == (previous_behind.row)) && 
				(previous.column == (previous_behind.column - 1)))
			{
				coordinates input = {previous_behind.room_val, previous_behind.row, previous_behind.column, '\0', 'w'};
				storage.push_back(input);
				//printf("(%d,%d,%d,%c)\n", previous_behind.row, previous_behind.column, previous_behind.room_val, 'w');
				previous = previous_behind;
			}
		}
		else if (previous.direction == 'P')
		{
			if ((previous.room_val == atoi(&previous_behind.symbol)) && (previous.row == (previous_behind.row)) && 
				(previous.column == previous_behind.column))
			{
				coordinates input = {previous_behind.room_val, previous_behind.row, previous_behind.column, '\0', 'p'};
				storage.push_back(input);
				//printf("(%d,%d,%d,%c)\n", previous_behind.row, previous_behind.column, previous_behind.room_val, 'p');
				previous = previous_behind;
			}
		}
	}
	std::vector<coordinates>::iterator op = storage.end();
	std::vector<coordinates>::iterator beginning = storage.begin();
	--beginning;
	--op;
	for ( ; op != beginning; --op)
	{
		printf("(%d,%d,%d,%c)\n", (*op).row, (*op).column, (*op).room_val, (*op).symbol);
	}
}
