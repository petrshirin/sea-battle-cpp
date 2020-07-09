#pragma once
#include "Cell.h"
#include <vector>
class Field
{
private:
	void fill_void_field();
	bool check_in_double_vector(std::vector<std::vector <int> > last_cells, int _x, int _y);

public:
	Cell cells[10][10];
	int check_ship_near_cell(int _x, int _y, std::vector<std::vector <int> > last_cells);
	int select_near_ship_cells(int _x, int _y);
	int count_ship = 10;
	int select_cell(int _x, int _y);
	bool add_ship(int** table_cells, int count_cells);
	void print_field();
	void print_private_field();
	Field();
	//Field(Cell** field);
	~Field();
};

