#include "pch.h"
#include "Field.h"
#include <iostream>


void Field::fill_void_field() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			cells[i][j] = Cell(i, j);
		}
	}
}

int Field::check_ship_near_cell(int _x, int _y, std::vector<std::vector <int> > last_cells) {
	int count_ship_near = 0;
	
	if (check_in_double_vector(last_cells, _x, _y))
		return 0;
	else {
		std::vector <int> new_cell = { _x, _y };
		last_cells.push_back(new_cell);
	}

	if ((_x - 1 >= 0) && (_y - 1 >= 0)) {
		if ((cells[_x - 1][_y - 1].is_ship())) {
			count_ship_near++;
		}
	}
	if ((_x >= 0) && (_y - 1 >= 0)) {
		if ((cells[_x][_y - 1].is_ship()) && (!cells[_x][_y - 1].is_selected())) {
			count_ship_near++;
			count_ship_near += check_ship_near_cell(_x, _y - 1, last_cells);
		}
	}
	if ((_x + 1 <= 9) && (_y - 1 >= 0)) {
		if ((cells[_x + 1][_y - 1].is_ship())) {
			count_ship_near++;
		}
	}
	if ((_x + 1 <= 9) && (_y >= 0) && (!cells[_x + 1][_y].is_selected())) {
		if ((cells[_x + 1][_y].is_ship())) {
			count_ship_near++;
			count_ship_near += check_ship_near_cell(_x + 1, _y, last_cells);
		}
	}
	if ((_x + 1 <= 9) && (_y + 1 <= 9)) {
		if ((cells[_x + 1][_y + 1].is_ship())) {
			count_ship_near++;
		}
	}
	if ((_x <= 9) && (_y + 1 <= 9)) {
		if ((cells[_x][_y + 1].is_ship()) && (!cells[_x][_y + 1].is_selected())) {
			count_ship_near++;
			count_ship_near += check_ship_near_cell(_x, _y + 1, last_cells);
		}
	}
	if ((_x - 1 >= 0) && (_y + 1 <= 9)) {
		if ((cells[_x - 1][_y + 1].is_ship())) {
			count_ship_near++;
		}
	}
	if ((_x - 1 >= 0) && (_y >= 0)) {
		if ((cells[_x - 1][_y].is_ship()) && (!cells[_x - 1][_y].is_selected())) {
			count_ship_near++;
			count_ship_near += check_ship_near_cell(_x - 1, _y, last_cells);
		}
	}
	return count_ship_near;
}

int Field::select_near_ship_cells(int _x, int _y) {
	int count_selected = 0;
	cells[_x][_y].change_condition_select_near();
	if ((_x - 1 >= 0) && (_y - 1 >= 0)) {
		if (cells[_x - 1][_y - 1].select_cell())
			count_selected += 1;
	}
	if ((_x >= 0) && (_y - 1 >= 0)) {
		if (cells[_x][_y - 1].is_ship()) {
			if (!cells[_x][_y - 1].is_selected_near())
				count_selected += select_near_ship_cells(_x, _y - 1);
		}
		else
			cells[_x][_y - 1].select_cell();
	}
	if ((_x + 1 <= 9) && (_y - 1 >= 0)) {
		if (cells[_x + 1][_y - 1].select_cell())
			count_selected += 1;
	}
	if ((_x + 1 <= 9) && (_y >= 0)) {
		if (cells[_x + 1][_y].is_ship()) {
			if (!cells[_x + 1][_y].is_selected_near())
				count_selected += select_near_ship_cells(_x + 1, _y);
		}
		else
			cells[_x + 1][_y].select_cell();
	}
	if ((_x + 1 <= 9) && (_y + 1 <= 9)) {
		if (cells[_x + 1][_y + 1].select_cell())
			count_selected += 1;
	}
	if ((_x <= 9) && (_y + 1 <= 9)) {
		if (cells[_x][_y + 1].is_ship()) {
			if (!cells[_x][_y + 1].is_selected_near())
				count_selected += select_near_ship_cells(_x, _y + 1);
		}
		else
			cells[_x][_y + 1].select_cell();
	}
	if ((_x - 1 >= 0) && (_y + 1 <= 9)) {
		if (cells[_x - 1][_y + 1].select_cell())
			count_selected += 1;
	}
	if ((_x - 1 <= 9) && (_y <= 9)) {
		if (cells[_x - 1][_y].is_ship()) {
			if (!cells[_x - 1][_y].is_selected_near())
				count_selected += select_near_ship_cells(_x - 1, _y);
		}
		else
			cells[_x - 1][_y].select_cell();
	}
	return count_selected;
}


Field::Field()
{
	fill_void_field();
}

int Field::select_cell(int _x, int _y) {
	bool is_select = cells[_x][_y].select_cell();
	if ((is_select) && (cells[_x][_y].is_ship())) {
		std::vector<std::vector <int> > last_cells;
		int count_ships_near = check_ship_near_cell(_x, _y, last_cells);
		if (count_ships_near == 0) {
			select_near_ship_cells(_x, _y);
			count_ship -= 1;
		}
		return 2;
	}
	if (is_select)
		return 1;
	return 0;
}

bool Field::add_ship(int** table_cells, int count_cells) {
	for (int i = 0; i < count_cells; i++) {
		std::vector<std::vector <int> > last_cells;
		if (check_ship_near_cell(table_cells[i][0], table_cells[i][1], last_cells)) {
			return false;
		}
	}
	for (int i = 0; i < count_cells; i++) {
		cells[table_cells[i][0]][table_cells[i][1]].add_ship();
	}


	return true;
}


void Field::print_field() {
	std::cout << "# |A|B|C|D|E|F|G|H|I|J|" << std::endl;
	for (int i = 0; i < 10; i++) {
		std::cout << i << " |";
		for (int j = 0; j < 10; j++) {
			std::cout << cells[j][i] << "|";
		}
		std::cout << std::endl;
	}
		
}

void Field::print_private_field() {
	std::cout << "# |A|B|C|D|E|F|G|H|I|J|" << std::endl;
	for (int i = 0; i < 10; i++) {
		std::cout << i << " |";
		for (int j = 0; j < 10; j++) {
			if ((cells[j][i].is_ship()) && (cells[j][i].is_selected()))
				std::cout << 'X' << "|";
			else if (cells[j][i].is_selected())
				std::cout << '·' << "|";
			else
				std::cout << ' ' << "|";
		}
		std::cout << std::endl;
	}
}




Field::~Field()
{
}


bool Field::check_in_double_vector(std::vector<std::vector <int> > last_cells, int _x, int _y) {
	std::vector <int> check_vector = { _x, _y };
	for (int i = 0; i < last_cells.size(); i++) {
		if (check_vector == last_cells[i])
			return true;
	}
	return false;
}