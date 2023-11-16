#include "brick.hpp"

Brick::Brick(int x, int y) : GameObject(x, y, 100, 50, sf::Color::Magenta)
{
	life = 7;
}

Brick::~Brick()
{
}

bool Brick::damage() {

	life = life - 1;

	if (life < 7) {
		pShape->setFillColor(sf::Color::Blue);
	}
	if (life < 6) {
		pShape->setFillColor(sf::Color::Cyan);
	}
	if (life < 5) {
		pShape->setFillColor(sf::Color::Green);
	}
	if (life < 4) {
		pShape->setFillColor(sf::Color::Yellow);
	}
	if (life < 3) {
		pShape->setFillColor(sf::Color(255, 127, 0, 255));
	}
	if (life < 2) {
		pShape->setFillColor(sf::Color::Red);
	}

	if (life < 1) {
		return true;
	}

	return false;
}