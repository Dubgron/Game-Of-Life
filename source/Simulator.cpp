#include "Simulator.h"

bool Simulator::isStopped = false;
int Simulator::turn = 0;

int Simulator::fIncrease(Map &map, int n) {

	//if (n < map.squaresAmount - 1) return n + 1;
	//return 0;

	return n < map.squaresAmount - 1 ? n + 1 : 0;
}

int Simulator::fDecrease(Map &map, int n) {

	//if (n > 0) return n - 1;
	//return map.squaresAmount - 1;

	return n > 0 ? n - 1 : map.squaresAmount - 1;
}

int Simulator::fCounter(Map &map, int x, int y) {

	int counter = 0;

	int dX = fDecrease(map, x);
	int iX = fIncrease(map, x);
	int dY = fDecrease(map, y);
	int iY = fIncrease(map, y);

	if (map.isAlive[dX][dY]) counter++;
	if (map.isAlive[x][dY]) counter++;
	if (map.isAlive[iX][dY]) counter++;
	if (map.isAlive[iX][y]) counter++;
	if (map.isAlive[iX][iY]) counter++;
	if (map.isAlive[x][iY]) counter++;
	if (map.isAlive[dX][iY]) counter++;
	if (map.isAlive[dX][y]) counter++;

	return counter;
}

void Simulator::countDownToTheStart() {

	for (int i = 3; i > 0; i--) {

		system("cls");
		std::cout << "-= The Game of Life =-" << std::endl << std::endl;
		std::cout << "Simulation starts in " << i << (i == 1 ? " second." : " seconds.");
		Sleep(1000);
	}
	std::cout << "\nSimulation started.";
	system("cls");
}

void Simulator::simulation(sf::RenderWindow &window, sf::Event &event, Map &map, int windowSize, std::string title) {

	window.create(sf::VideoMode(windowSize, windowSize), title, sf::Style::Close);

	displayMap(window, map);
	countDownToTheStart();

	int counter;

	sf::Clock clock;
	sf::Time accumulator = sf::Time::Zero;
	sf::Time ups = sf::seconds(1.f / 60.f);

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			switch (event.type) {

				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
						window.close();
					break;
			}
		}

		while (accumulator > ups) {
			accumulator -= ups;

			window.clear(sf::Color::White);

			for (int y = 0; y < map.squaresAmount; y++) {
				for (int x = 0; x < map.squaresAmount; x++) {

					counter = fCounter(map, x, y);

					map.statusChange(map.isAlive[x][y], x, y);

					if (map.isAlive[x][y] && (counter < 2 || counter > 3)) 
						map.willBeAlive[x][y] = false;
					else if (counter == 3)
						map.willBeAlive[x][y] = true;
				}
			}
			window.draw(map.squares);
			window.display();
			for (int y = 0; y < map.squaresAmount; y++)
				for (int x = 0; x < map.squaresAmount; x++)
					map.isAlive[x][y] = map.willBeAlive[x][y];

			turn++;
		}
		accumulator += clock.restart();
	}
}

void Simulator::displayMap(sf::RenderWindow &window, Map &map) {

	window.clear(sf::Color::White);

	for (int y = 0; y < map.squaresAmount; y++) 
		for (int x = 0; x < map.squaresAmount; x++)
			map.willBeAlive[x][y] = map.isAlive[x][y];

	window.draw(map.squares);
	window.display();
}

void Simulator::displayTurnCounter(int turn) {

	system("cls");
	std::cout << "-= The Game of Life =-" << std::endl << std::endl;
	std::cout << "Amount of turns: " << turn << std::endl;
	std::cout << "Press SPACE to continue simulation.";
}
