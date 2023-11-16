#include "gameObject.hpp"

class Ball : public GameObject
{
public:
	Ball(float mouseX, float mouseY);
	~Ball();

	bool eraseBall();

	std::vector<GameObject*> colliding;

private:

};