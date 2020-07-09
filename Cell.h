#pragma once
#include <iostream>

class Cell {

private:
	bool selected = false;
	bool ship = false;
	bool selected_near = false;

public:
	int x, y;
	Cell(int _x, int _y);
	Cell();
	~Cell();
	bool add_ship();
	bool select_cell();
	bool is_ship();
	bool is_selected_near();
	bool is_selected();
	bool change_condition_select_near();

	friend std::ostream& operator<< (std::ostream &out, Cell &cell);

};

