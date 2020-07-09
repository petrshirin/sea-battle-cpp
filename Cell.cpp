#include "pch.h"
#include "Cell.h"


Cell::Cell(int _x, int _y)
{
	x = _x;
	y = _y;

}

Cell::Cell()
{
	x = 0;
	y = 0;

}


Cell::~Cell() {

}

bool Cell::add_ship() {
	if (ship)
		return false;
	else
		ship = true;
	return true;
}

bool Cell::select_cell() {
	if (selected)
		return false;
	else
		selected = true;
	return true;
}

bool Cell::is_ship() {
	return ship;
}

bool Cell::is_selected() {
	return selected;
}

bool Cell::is_selected_near() {
	return selected_near;
}

bool Cell::change_condition_select_near() {
	if (selected_near)
		return false;
	else
		selected_near = true;
	return true;
}

std::ostream& operator<< (std::ostream &out, Cell &cell) {
	if ((cell.is_ship()) && (cell.is_selected()))
		out << 'X';
	else if (cell.is_ship())
		out << '☐';
	else if (cell.is_selected())
		out << '·';
	else
		out << ' ';
	return out;
}
