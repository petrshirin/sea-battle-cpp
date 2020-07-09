// sea_battle.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>
#include "Game.h"

using namespace std;


int main() {
	setlocale(LC_ALL, "Russian");
	Game g = Game();
	g.preload_game();
	g.start_game();

}
