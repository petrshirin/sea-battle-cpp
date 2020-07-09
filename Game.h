#pragma once
#include "Field.h" 
#include <string>
#include <vector>
#include <map>
class Game
{
private:
	Field field_1 = Field();
	Field field_2 = Field();
	int winner = 0;
	std::map<char, int> table_simv = {
		{'A', 0},
		{'B', 1},
		{'C', 2},
		{'D', 3},
		{'E', 4},
		{'F', 5},
		{'G', 6},
		{'H', 7},
		{'I', 8},
		{'J', 9}
	};
	void fill_player_field(Field field);
	int choice_turn();
	bool validate_cell(std::string cell);
	bool validate_cells_position(std::vector<std::string> &cells, int count_cells);
	void fill_ship(int count_cells, int count_ships);


public:
	int turn;

	void preload_game();
	void start_game();
	void change_turn();
	int check_winner();
	void print_current_field();
	void print_all_fields();
	std::string optimal_turn();
	
	Game();
	Game(int _turn);
	~Game();

};

