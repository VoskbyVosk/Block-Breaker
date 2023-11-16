#include "gameObject.hpp"

class Brick : public GameObject
{
public:
	Brick(int x, int y);
	~Brick();

	bool damage();

private:

	int life;

};