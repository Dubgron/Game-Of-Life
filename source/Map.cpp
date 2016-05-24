#include "Map.h"


void Map::set(int squaresAmount, int windowSize, bool isInfinite) {

	this->squaresAmount = squaresAmount;
	//this->isInfinite = isInfinite;
	cellSize = windowSize / squaresAmount;

	squares.setPrimitiveType(sf::Quads);
	squares.resize(squaresAmount * squaresAmount * 4);

	isAlive = new bool*[squaresAmount];
	willBeAlive = new bool*[squaresAmount];

	for (int x = 0; x < squaresAmount; x++) {

		isAlive[x] = new bool[squaresAmount];
		willBeAlive[x] = new bool[squaresAmount];
		
		for (int y = 0; y < squaresAmount; y++) {

			sf::Vertex* square = &squares[(x + y * squaresAmount) * 4];

			square[0].position = sf::Vector2f((float)cellSize * x, (float)cellSize * y);
			square[1].position = sf::Vector2f((float)cellSize * (x + 1), (float)cellSize * y);
			square[2].position = sf::Vector2f((float)cellSize * (x + 1), (float)cellSize * (y + 1));
			square[3].position = sf::Vector2f((float)cellSize * x, (float)cellSize * (y + 1));

			statusChange(square, settings.theme[1]);
			isAlive[x][y] = false;
		}
	}
}

void Map::draw(sf::RenderWindow &window) {

	for (int y = 0; y < squaresAmount; y++)
		for (int x = 0; x < squaresAmount; x++)
			statusChange(isAlive[x][y], x, y);

	window.draw(squares);
}

void Map::loadMap() {

	int iPath;

	do {

		system("cls");
		std::cout << "-= The Game of Life =-\n\n";

		loadList();
		showList();

		std::cout << "Choose map from list above: ";
		std::cin >> iPath;

		file.open("maps/" + list[iPath - 1] + ".txt", std::ios::in);

		file.good() ? system("cls") : loadError();
		
	} while (!file.good());

	std::string lineContent;
	int lineXCounter = 0;
	int lineYCounter = 0;

	while (std::getline(file, lineContent)) {

		for (lineXCounter = 0; lineXCounter < squaresAmount; lineXCounter++) {

			isAlive[lineXCounter][lineYCounter] = (lineContent[lineXCounter] == '1' ? true : false);
			statusChange(isAlive[lineXCounter][lineYCounter], lineXCounter, lineYCounter);
		}
		lineYCounter++;
	}

	file.close();
}

void Map::save() {

	std::string sPath;

	system("cls");
	std::cout << "-= The Game of Life =-\n\n";
	std::cout << "Title of map: ";
	std::cin >> sPath;

	file.open("maps/" + sPath + ".txt", std::ios::out);
	
	for (int y = 0; y < squaresAmount; y++) {
		for (int x = 0; x < squaresAmount; x++) {

			file << isAlive[x][y];
		}
		file << "\n";
	}

	file.close();

	file.open("maps/List.txt", std::ios::app);

	file << "\n" << sPath;

	file.close();
}

void Map::loadList() {

	file.open("maps/List.txt", std::ios::in);

	std::string lineContent;

	while (std::getline(file, lineContent)) 
		list.push_back(lineContent);

	file.close();
}

void Map::showList() {

	int i = 1;

	for (std::vector<std::string>::const_iterator iterator = list.begin(); iterator != list.end(); iterator++) {

		std::cout << i << ". " << *iterator << std::endl;
		i++;
	}
	std::cout << "\n";
}

void Map::loadError() {

	std::cout << "\nError! File doesn't exist!";
	file.close();
	_getch();
}

void Map::statusChange(bool &isAlive, int x, int y) {

	statusChange(&squares[(x + y * squaresAmount) * 4], ((isAlive) ? settings.theme[0] : settings.theme[1]));
}

void Map::statusChange(sf::Vertex* square, sf::Color color) {

	for (int i = 0; i < 4; i++)
		square[i].color = color;
}
