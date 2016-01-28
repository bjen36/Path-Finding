#ifndef COMMON_H
#define COMMON_H

struct path_tracker
{
	bool checked;
	char symbol;
};

struct coordinates
{
	int room_val;
	int row;
	int column;
	char direction;
	char symbol;
};


#endif