#include "Game.h"


Game::Game(int windowSize, std::string title)
	:windowSize(windowSize), title(title) {

	map.set(100, windowSize, true);
}

void Game::start() {

	menu();
	Simulator::setOptions(map);
	Simulator::simulation(window, event, map, windowSize, title);
}

void Game::menu() {

	char menu;

	std::cout << "-= The Game of Life =-\n\n";
	std::cout << "1. Create map yourself!" << std::endl;
	std::cout << "2. Load someones map!";

	menu = std::cin.get();

	switch (menu) {

		case '1':
			Editor::edit(window, event, map, windowSize, title);
			break;
		case '2':
			map.loadMap();
			break;
	}
}
