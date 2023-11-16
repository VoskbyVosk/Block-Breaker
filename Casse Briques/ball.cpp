#include "ball.hpp"

Ball::Ball(float mouseX, float mouseY) : GameObject(320, 480, 10, sf::Color::White)
{
    float ballX = hitBox->getPosition().x;
    float ballY = hitBox->getPosition().y;

    setDirection(mouseX - ballX, mouseY - ballY);
}

Ball::~Ball()
{
}

bool Ball::eraseBall() {

	float positionX = pShape->getPosition().x;
	float positionY = pShape->getPosition().y;

	if (positionY > 480) {
		std::cout << "erased" << std::endl;
		return true;
	}
	return false;

}