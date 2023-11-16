#include "gameObject.hpp"

GameObject::GameObject(int x, int y, int w, int h, sf::Color oColor)
{
	pShape = new sf::RectangleShape(sf::Vector2f(w, h));
	pShape->setPosition(x, y);
	pShape->setFillColor(oColor);

	width = w;
	height = h;

	hitBox = new sf::RectangleShape(sf::Vector2f(w, h));
	hitBox->setPosition(x, y);
}

GameObject::GameObject(int x, int y, int radius, sf::Color oColor)
{
	pShape = new sf::CircleShape(radius);
	pShape->setPosition(x, y);
	pShape->setFillColor(oColor);

	width = radius * 2;
	height = radius * 2;
	
	hitBox = new sf::RectangleShape(sf::Vector2f(radius * 2, radius * 2));
	hitBox->setPosition(x, y);
	hitBox->setFillColor(sf::Color::Green);
}

GameObject::~GameObject()
{
}

void GameObject::rotation(float mouseX, float mouseY) {

	pShape->setOrigin(10, 40);
	float canonX = pShape->getPosition().x;
	float canonY = pShape->getPosition().y;

	float opp = mouseX - canonX;
	float adj = mouseY - canonY;

	float angle = -atan(opp / adj) * 180 / 3.14;
	pShape->setRotation(angle);

}

void GameObject::setDirection(float directionX, float directionY) {

	float norme = sqrt((directionX * directionX) + (directionY * directionY));
	this->directionX = directionX / norme;
	this->directionY = directionY / norme;

}

void GameObject::setPosition(float x, float y) {

	pShape->setPosition(x, y);
	hitBox->setPosition(x, y);

}

void GameObject::move(float fDeltaTime) {

	speed = 500.f;

	float ballX = pShape->getPosition().x;
	float ballY = pShape->getPosition().y;

	ballX = ballX + directionX * speed * fDeltaTime;
	ballY = ballY + directionY * speed * fDeltaTime;

	pShape->setPosition(ballX, ballY); 
	hitBox->setPosition(ballX, ballY); 

}

sf::Vector2f GameObject::getXMinMax() {

	sf::Vector2f vect;
	vect.x = pShape->getPosition().x;
	vect.y = pShape->getPosition().x + width;
	return vect;

}

sf::Vector2f GameObject::getYMinMax() {

	sf::Vector2f vect;
	vect.x = pShape->getPosition().y;
	vect.y = pShape->getPosition().y + height;
	return vect;

}

bool GameObject::isInside(float v, float vMin, float vMax) {

	if (v >= vMin && v <= vMax){
		return true;
	}
	return false;

}

bool GameObject::checkCollision(GameObject* object) {

	GameObject* minWidth;
	GameObject* maxWidth;
	if (width > object->width) {
		minWidth = object;
		maxWidth = this;
	}
	else {
		minWidth = this;
		maxWidth = object;
	}

	GameObject* minHeight;
	GameObject* maxHeight;
	if (height > object->height) {
		minHeight = object;
		maxHeight = this;
	}
	else {
		minHeight = this;
		maxHeight = object;
	}

	sf::Vector2f xMinMax = minWidth->getXMinMax();
	sf::Vector2f yMinMax = minHeight->getYMinMax();
	sf::Vector2f xMinMaxObj = maxWidth->getXMinMax();
	sf::Vector2f yMinMaxObj = maxHeight->getYMinMax();
	bool xMinInside = isInside(xMinMax.x, xMinMaxObj.x, xMinMaxObj.y);
	bool xMaxInside = isInside(xMinMax.y, xMinMaxObj.x, xMinMaxObj.y);
	bool yMinInside = isInside(yMinMax.x, yMinMaxObj.x, yMinMaxObj.y);
	bool yMaxInside = isInside(yMinMax.y, yMinMaxObj.x, yMinMaxObj.y);
	
	if ((xMinInside or xMaxInside) and (yMinInside or yMaxInside)) {
		return true;
	}
	else {
		std::cout << "-------" << std::endl;
		return false;
	}

}

void GameObject::checkBounceWindow() {
	
	float positionX = pShape->getPosition().x;
	float positionY = pShape->getPosition().y;

	if (positionX > 640) {
		std::cout << "collision" << std::endl;
		directionX = -directionX;
	}
	if (positionX < 0) {
		std::cout << "collision" << std::endl;
		directionX = -directionX;
	}
	if (positionY < 0) {
		std::cout << "collision" << std::endl;
		directionY = -directionY;
	}

}

void GameObject::checkBounce(GameObject* object) {

	float positionX = pShape->getPosition().x;
	float positionY = pShape->getPosition().y;

	sf::Vector2f xMinMax = getXMinMax();
	sf::Vector2f yMinMax = getYMinMax();
	sf::Vector2f xMinMaxObj = object->getXMinMax();
	sf::Vector2f yMinMaxObj = object->getYMinMax();

	float right = abs(xMinMaxObj.y - xMinMax.x);
	float left = abs(xMinMaxObj.x - xMinMax.y);
	float top = abs(yMinMaxObj.x - yMinMax.y);
	float bottom = abs(yMinMaxObj.y - yMinMax.x);

	if (right < left and right < top and right < bottom) {
		std::cout << "collision" << std::endl;
		directionX = -directionX;
	}
	if (left < right and left < top and left < bottom) {
		std::cout << "collision" << std::endl;
		directionX = -directionX;
	}
	if (top < right and top < left and top < bottom) {
		std::cout << "collision" << std::endl;
		directionY = -directionY;
	}
	if (bottom < right and bottom < left and bottom < top) {
		std::cout << "collision" << std::endl;
		directionY = -directionY;
	}

}