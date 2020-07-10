#include "pch.h"
#include "Game.h"
#include <ctime>
#include <sstream>
#include <vector>
#include <fstream>


Game::Game() {
	turn = choice_turn();
	for (int i = 0; i < 1; i++) {
		field_1[i] = Field();
		field_2[i] = Field();
	}
}

Game::Game(int _turn) {
	turn = _turn;
	for (int i = 0; i < 1; i++) {
		field_1[i] = Field();
		field_2[i] = Field();
	}
}

Game::Game(int _turn, int _count_fields) {
	turn = _turn;
	if (_count_fields > 10)
		throw "count_fields error max 10";
	for (int i = 0; i < _count_fields; i++) {
		field_1[i] = Field();
		field_2[i] = Field();
	}
	count_fields = _count_fields;
}

int Game::choice_turn() {
	srand(time(0));
	return std::rand() % 2 + 1;
}

void Game::preload_game() {
	if (turn == 1) {
		fill_player_field();
		change_turn();
		fill_player_field();
	}
	else {
		fill_player_field();
		change_turn();
		fill_player_field();
	}
	current_field = 0;

}

bool Game::validate_cell(std::string cell) {

	std::map <char, int> ::iterator it;

	it = table_simv.find(cell[0]);
	if (cell.length() == 2) {
		try
		{
			if ((it != table_simv.end()) && (((int)cell[1] - 48 >= 0) && ((int)cell[1] - 48 <= 9)))
				return true;
		}
		catch (const std::exception&)
		{
			return false;
		}
		

	}
	return false;
}

bool Game::validate_cells_position(std::vector<std::string> &cells, int count_cells) {
	bool valid = true;
	for (int i = 0; i < count_cells; i++) {
		if (cells[i][0] != cells[0][0]) {
			valid = false;
			break;
		}
	}
	if (valid) {
		return true;
	}
	else {
		valid = true;
		for (int i = 0; i < count_cells; i++) {
			if (cells[i][1] != cells[0][1]) {
				valid = false;
				break;
			}
		}
	}
	if (valid) {
		return true;
	}
	else
		return false;

}

void Game::fill_player_field() {
	//print_field(player);

	for (int board = 0; board < count_fields; board++) {
		current_field = board;
		int count_cells_per_ship[4] = { 4, 3, 2, 1 };
		int count_ships[4] = { 1, 2, 3, 4 };
		for (int i = 0; i < 4; i++) {
			fill_ship(count_cells_per_ship[i], count_ships[i]);
		}
	}
	
}

void Game::fill_ship(int count_cells, int count_ships) {
	// проверить как передается кол во кораблей
	std::string row, cell;
	std::vector<std::string> cells;

	int** table_cells = new int*[count_cells];
	for (int i = 0; i < count_cells; i++)
		table_cells[i] = new int[2];

		while (count_ships)
		{
			print_current_field();
			std::cout << "Игрок" << turn << ": Введите клетки Корабля (" << count_cells << " клетки через пробел) кораблей осталось: " << count_ships << std::endl;
			std::getline(std::cin, row);
			std::stringstream split_stream(row);
			cells.clear();
			while (std::getline(split_stream, cell, ' ')) {
				cells.push_back(cell);
			}
			if (cells.size() != count_cells) {
				system("cls");
				std::cout << "Неверное кол-во клеток" << std::endl;
				continue;
			}
			bool valid = true;
			for (int j = 0; j < count_cells; j++) {

				if (!validate_cell(cells[j])) {
					valid = false;
					break;
				}

			}
			if (!valid) {
				system("cls");
				std::cout << "Неверный формат ввода, повторите попытку" << std::endl;
				continue;
			}
			if (!validate_cells_position(cells, count_cells)) {
				system("cls");
				std::cout << "Неверный расположение краблей, повторите попытку" << std::endl;
				continue;
			}

			for (int i = 0; i < count_cells; i++) {
				table_cells[i][0] = table_simv[cells[i][0]];
				table_cells[i][1] = (int)cells[i][1] - 48;
			}
			if (turn == 1) {
				if (!field_1[current_field].add_ship(table_cells, count_cells)) {
					system("cls");
					std::cout << "Нельзя распологать корабли рядом, повторите попытку" << std::endl;
					continue;
				}
				else {
					system("cls");
					count_ships -= 1;
				}


			}
			else if (turn == 2) {
				if (!field_2[current_field].add_ship(table_cells, count_cells)) {
					system("cls");
					std::cout << "Нельзя распологать корабли рядом, повторите попытку" << std::endl;
					continue;
				}
				else {
					system("cls");
					count_ships -= 1;
				}

			}
		}
	
}

void Game::print_all_fields() {
	system("cls");
	std::cout << "Ход игрока " << turn  << std::endl;
	if (turn == 1) {
		std::cout << "Ваше поле" << std::endl;
		field_1[current_field].print_field();
		std::cout << "Поле противника" << std::endl;
		field_2[current_field].print_private_field();
	}
	else {
		std::cout << "Ваше поле" << std::endl;
		field_2[current_field].print_field();
		std::cout << "Поле противника" << std::endl;
		field_1[current_field].print_private_field();
	}
}

void Game::print_current_field() {
	//system("cls");
	std::cout << "Поле " << current_field << std::endl;
	if (turn == 1) {
		field_1[current_field].print_field();
	}
	else
		field_2[current_field].print_field();
}

int Game::check_winner() {
	if (field_1[current_field].count_ship == 0)
		return 2;
	else if (field_2[current_field].count_ship == 0)
		return 1;
	else
		return 0;

}

void Game::change_turn() {
	if (turn == 1)
		turn = 2;
	else
		turn = 1;

}


void Game::start_game() {
	std::string step;
	int is_select;
	std::ofstream file("history.txt");
	while (!winner) {
		system("cls");
		winner = check_winner();
		if (winner) {
			change_turn();
			print_all_fields();
			std::cout << "Победил Игрок " << winner << std::endl;
			exit(0);
		}
		std::cout << "Ход игрока " << turn << std::endl;
		print_all_fields();
		std::cout << "Я рекомендую вам ход " << optimal_turn() << std::endl;
		std::cout << "Сделайте ход: ";
		std::cin >> step;

		if (validate_cell(step)) {
			if (turn == 1) {
				is_select = field_2[current_field].select_cell(table_simv[step[0]], (int)step[1] - 48);
				if (!is_select) {
					std::cout << "Выбрана неверная клетка" << std::endl;
				}
				else if (is_select == 2) {
					file << current_field << '-' << turn << ':' << step << '\n';
					continue;
				}
				else {
					file << current_field << '-' << turn << ':' << step << '\n';
					change_turn();
					change_current_field();
				}
					
			}
			else {
				is_select = field_1[current_field].select_cell(table_simv[step[0]], (int)step[1] - 48);
				if (!is_select) {
					std::cout << "Выбрана неверная клетка" << std::endl;
				}
				else if (is_select == 2) {
					file << current_field << '-' << turn << ':' << step << '\n';
					continue;
				}
				else {
					file << current_field << '-' << turn << ':' << step << '\n';
					change_turn();
					change_current_field();
				}
					
			}
		}
		else {
			std::cout << "Неверный формат клетки" << std::endl;
		}
	}
	file.close();
}

void Game::change_current_field() {
	int answer;
	int new_field;
	system("cls");
	while (true)
	{
		std::cout << "Вы хотите поменять поле для игры (Текущее поле: " << current_field << ", Максимальный номер поля: " << count_fields - 1 << ")" << std::endl;
		std::cout << "Введите 1 - да или 2 - нет: ";
		std::cin >> answer;
		
		if (std::cin.fail()) {
			std::cin.clear();
			std::cin.ignore();
		}
		
		if (answer == 1) {
			while (true)
			{
				try
				{
					std::cout << "Введите номер поля: ";
					std::cin >> new_field;
					if ((new_field >= 0) && (new_field <= count_fields)) {
						current_field = new_field;
						return;
					}
					else {
						std::cout << "Неверный номер поля" << std::endl;
					}

				}
				catch (const std::exception&)
				{
					continue;
				}
			}
		}
		else if (answer == 2) {
			return;
		}
	}
	
}


std::string Game::optimal_turn() {
	int mask[10][10] = {
		{0, 1, 0, 2, 0, 1, 0, 2, 0, 1},
		{1, 0, 2, 0, 1, 0, 2, 0, 1, 0},
		{0, 2, 0, 1, 0, 2, 0, 1, 0, 2},
		{2, 0, 1, 0, 2, 0, 1, 0, 2, 0},
		{0, 1, 0, 2, 0, 1, 0, 2, 0, 1},
		{1, 0, 2, 0, 1, 0, 2, 0, 1, 0},
		{0, 2, 0, 1, 0, 2, 0, 1, 0, 2},
		{2, 0, 1, 0, 2, 0, 1, 0, 2, 0},
		{0, 1, 0, 2, 0, 1, 0, 2, 0, 1},
		{1, 0, 2, 0, 1, 0, 2, 0, 1, 0},
	};

	std::string letters[] = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J" };

	std::string optimal_step = "A0";
	int status = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (turn == 1) {
				if (!field_2[current_field].cells[i][j].is_selected()) {
					if (mask[i][j] > status) {
						status = mask[i][j];
						optimal_step = letters[i] + std::to_string(j);
					}
				}
			}
			else {
				if (!field_1[current_field].cells[i][j].is_selected()) {
					if (mask[i][j] > status) {
						status = mask[i][j];
						optimal_step = letters[i] + std::to_string(j);
					}
				}
			}
		}
	}
	return optimal_step;


}




Game::~Game()
{
}
