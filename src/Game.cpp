#include "Game.h"


Game::Game(int windowSize, std::string title)
	:windowSize(windowSize), title(title) {

	map = new Map();

	map->set(100, windowSize, true);
}

void Game::start() {

	menu();
	Simulator::setOptions(*map);
	Simulator::simulation(window, event, *map, windowSize, title);

	delete map;
}

void Game::menu() {

	char menu;

	std::cout << "-= The Game of Life =-\n\n";
	std::cout << "1. Create map yourself!\n";
	std::cout << "2. Load existing map!\n";
	std::cout << "\nChoose wisely: ";

	menu = std::cin.get();

	switch (menu) {

		case '1':
			Editor::edit(window, event, *map, windowSize, title);
			break;
		case '2':
			map->loadMap();
			break;
		default:
			// TODO loop menu in case when someone choose another option
			break;
	}
}
