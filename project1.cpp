#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <getopt.h>
#include <deque>
#include <vector>
#include <ctype.h>
#include <string>
#include <deque>

#include "Check.h"
#include "Output.h"

using namespace std;

static struct option longopts[] = 
{
	{"stack", no_argument, NULL, 's'},
	{"queue", no_argument, NULL, 'q'},
	{"output", required_argument, NULL, 'o'},
	{"help", no_argument, NULL, 'h'}
	//{NULL, 0, NULL, 0}
};

int main(int argc, char *argv[])
{
    ios_base::sync_with_stdio(false);

	int idx = 0; // getopt long stores the option index here
	int Sflag = 0, Qflag = 0, Mflag = 1; //, Lflag = 0;
	int opt = 0, start_room = 0, start_row = 0, start_col = 0;
	int size = 0, room = 0;
	int room_tracker = 0, row_tracker = 0, col_tracker = 0;
	//char *op = NULL;
	char mode; 
	bool found = false;

	string line;
	while ((opt = getopt_long(argc, argv, "sqo:h", longopts, &idx)) != (-1))
	{
		switch (opt)
		{
			case 's': 
				//printf("Option '-s' specified.\n"); 
				Sflag = 1;	
				//printf("s: %d\n", Sflag);
				break;
			case 'q':
				//printf("Option '-q' specified.\n");
				Qflag = 1;
				//printf("q: %d\n", Qflag);
				break;
			case 'o':
				if (*optarg == 'M')
				{
					//op = optarg;
					//printf("Mflag: %d\n", Mflag);						
					//printf("m: %s\n", op);
				}	
				else if (*optarg == 'L')
				{
					//op = optarg;
					Mflag = 0;
					//Lflag = 1;
					//printf("Lflag: %d\n", Lflag);	
					//printf("L: %s\n", op);
				}
				break;
			case 'h': 
				// print help message				
				printf("The program uses a path-finding algorithm to guide ");
				printf("Perry to the magic ring.\n");
				printf("'s' switch uses stack-based routing scheme.\n");
				printf("'q' switch uses the queue-based routing scheme.\n");
				printf("'o' switch indicates the output file format. This "); 
				printf("choice needs to be followed by an argumenent of 'M' or 'L'\n");
				printf("If not followed by an argument, automatically places M\n");
				exit(0);
			default: 
				cerr << "Unknown option character\n";
				exit(1); 
		}// switch
		
	}// while
	
	if (Qflag == 1 && Sflag == 1)
	{
		cerr << "More than one was specified\n";
		exit(1);
	}
	else if ((Qflag == 0) && (Sflag == 0))
	{
		cerr << "Specify queue or stack\n";
		exit(1);
	}
		
	cin >> mode >> size >> room;

	vector<vector<vector<path_tracker> > >//vec_table;
		vec_table(room, vector<vector<path_tracker> >(size, vector<path_tracker>(size)));

	if (mode == 'M') // mode M
	{
		while (std::getline(std::cin >> std::ws, line) && !line.empty())
		{
			if (line[0] != '/')
			{
				for (int x = 0; x < size; ++x)
				{
					if ((line[x] != '.') && (line[x] != '#') && (!isdigit(line[x])) &&
						(line[x] != 'R') && (line[x] != 'S'))
					{
						printf("%d\n", size);
						printf("%d\n", room);
						cerr << "Input illegal character\n";
						exit(1);
					}
					else
					{
						path_tracker a = {false, line[x]};
						vec_table[room_tracker][row_tracker][col_tracker] = a;
						if (line[x] == 'S')
						{
							start_room = room_tracker;
							start_row = row_tracker;
							start_col = col_tracker;
							vec_table[room_tracker][row_tracker][col_tracker].checked = true;
						}
						++col_tracker;
					}
				}	

					++row_tracker;
					col_tracker = 0;

				if (row_tracker == size)
				{
					++room_tracker;
					row_tracker = 0;
					col_tracker = 0;
				}	
			}		
		}
	} // mode M
	
	else // mode L
	{
		path_tracker setup = {false, '.'};
		vector<vector<vector<path_tracker> > > * vec_ptr = &vec_table;
		for (int i = 0; i < room; i++)
		{
			for (int j = 0; j < size; j++)
				{
					for (int z = 0; z < size; z++)
					{
						(*vec_ptr)[i][j][z] = setup;
					}
				}
		}

		while (std::getline(cin >> std::ws, line) && !line.empty())
		{
			if (line[0] != '/')
			{		
				int first_comma = line.find(",");
				int second_comma = line.find(",", first_comma + 1);
				int third_comma = line.find(",", second_comma + 1);
				int first_number = atoi(line.substr(1,first_comma - 1).c_str()); // row
				int second_number = atoi(line.substr(first_comma + 1, second_comma - 1).c_str()); // column
				int room_number = atoi(&line[third_comma - 1]);
				char symbol_val = line[third_comma + 1];

				if ((first_number < 0) || (first_number > size))
				{
					printf("%d\n", size);
					printf("%d\n", room);
					cerr << "row " << first_number << " does not exist!\n";
					exit(1);
				}	
				if (second_number < 0 || second_number > size)
				{	
					printf("%d\n", size);
					printf("%d\n", room);
					cerr << "col " << second_number << " does not exist!\n";
					exit(1);
				}
				if (room_number < 0 || room_number > room)
				{
					printf("%d\n", size);
					printf("%d\n", room);
					cerr << "room " << room_number << " does not exist!\n";
					exit(1);
				}
				if ((symbol_val != '.') && (symbol_val != '#') &&
				 	(!isdigit(symbol_val)) &&
					(symbol_val != 'R') && (symbol_val != 'S'))
				{
					printf("%d\n", size);
					printf("%d\n", room);
					cerr << symbol_val << " is an invalid map character!\n";
					exit(1);
				}

				if (symbol_val == 'S')
				{
					start_room = room_number;
					start_row = first_number;
					start_col = second_number;
					vec_table[start_room][start_row][start_col].checked = true;
				}
				//path_tracker a = {false, symbol_val};
				vec_table[room_number][first_number]
					[second_number].symbol = symbol_val;
			}	
		}

	} // L mode

	deque<coordinates> traceback; // store the paths taken
	deque<coordinates> path;

	coordinates temp = {start_room, start_row, start_col, '\0', vec_table[start_room][start_row][start_col].symbol};

	int a = 0, b = 0, c = 0;
	int new_room = 0;
	char d = '\0', e = '\0';

	if (Sflag == 1) // stack route
	{
		path.push_front(temp);

		while (path.size() != 0)	
		{
			a = path.front().room_val;
			b = path.front().row;
			c = path.front().column;
			d = path.front().direction;
			e = path.front().symbol;

			coordinates store = {a, b, c, d, e};

			traceback.push_front(store); // add 

			path.pop_front();

			if(north_check(vec_table, store, found))
			{	
				coordinates input = {a, b - 1, c, 'N', vec_table[a][b - 1][c].symbol};
				if (found)
				{
					traceback.push_front(input);
					break;
				}
				path.push_front(input);

			}

			if(east_check(vec_table, size, store, found))
			{
				coordinates input = {a, b, c + 1, 'E', vec_table[a][b][c + 1].symbol};
				if (found)
				{
					traceback.push_front(input);
					break;
				}
				path.push_front(input);

			}
			if(south_check(vec_table, size, store, found))
			{
				coordinates input = {a, b + 1, c, 'S', vec_table[a][b + 1][c].symbol};
				if (found)
				{
					traceback.push_front(input);
					break;
				}
				path.push_front(input);

			}
			if(west_check(vec_table, store, found))
			{
				coordinates input = {a, b, c - 1, 'W', vec_table[a][b][c - 1].symbol};
				if (found)
				{
					traceback.push_front(input);
					break;
				}
				path.push_front(input);
			}

			if(portal_check(vec_table, room, store, found, &new_room))
			{
				coordinates input = {new_room, b, c, 'P', vec_table[new_room][b][c].symbol};	
				if (found)
				{
					traceback.push_front(input);
					break;
				}
				path.push_front(input);
			}
			
		} // while loop

	}	
	else // Queue route
	{
		path.push_back(temp);

		while (!(path.empty()))
		{
			a = path.front().room_val;
			b = path.front().row;
			c = path.front().column;
			d = path.front().direction;
			e = path.front().symbol;

			coordinates store = {a, b, c, d, e};

			traceback.push_front(store); // don't need but put in direction into 3D vector at the end

			path.pop_front();

			if(north_check(vec_table, store, found))
			{	
				coordinates input = {a, b - 1, c, 'N', vec_table[a][b - 1][c].symbol};
				if (found)
				{
					traceback.push_front(input); // put in direction into 3D vector
					
					break;
				}
				path.push_back(input);

			}

			if(east_check(vec_table, size, store, found))
			{
				coordinates input = {a, b, c + 1, 'E', vec_table[a][b][c + 1].symbol};
				if (found)
				{
					traceback.push_front(input);
					break;
				}
				path.push_back(input);

			}
			if(south_check(vec_table, size, store, found))
			{
				coordinates input = {a, b + 1, c, 'S', vec_table[a][b + 1][c].symbol};
				if (found)
				{
					traceback.push_front(input);
					break;
				}
				path.push_back(input);

			}
			if(west_check(vec_table, store, found))
			{
				coordinates input = {a, b, c - 1, 'W', vec_table[a][b][c - 1].symbol};
				if (found)
				{
					traceback.push_front(input);
					break;
				}
				path.push_back(input);
			}

			if(portal_check(vec_table, room, store, found, &new_room))
			{
				coordinates input = {new_room, b, c, 'P', vec_table[new_room][b][c].symbol};	
				if (found)
				{
					traceback.push_front(input);
					break;
				}
				path.push_back(input);
			}
		}
	}

	if (found) // found 'R' print output
	{
		if (Mflag == 1) // update 3D table and print M
		{
			update_M(vec_table, traceback);
			print_M(vec_table, room, size);
		}
		else // print traceback for L
		{
			print_L(traceback, room, size);
		}
	}
	else // not found
	{
		if (Mflag == 1)
		{
			print_M(vec_table, room, size);
		}
		else
		{
			printf("%d\n", size);
			printf("%d\n", room);
			printf("//path taken\n");
		}
	}

	return 0;
}