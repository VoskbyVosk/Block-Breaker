#include "ball.hpp"
#include "brick.hpp"
#include "canon.hpp"
#include <vector>

int main(int argc, char** argv)
{
    //Création d'une fenêtre
    sf::RenderWindow oWindow(sf::VideoMode(640, 480), "Casse Briques");

    std::vector<Ball*> listBall;
    Canon oCanon;
    std::vector<Brick*> listBrick;

    listBrick.push_back(new Brick(50, 50));
    listBrick.push_back(new Brick(152, 50));
    listBrick.push_back(new Brick(254, 50));
    listBrick.push_back(new Brick(356, 50));
    listBrick.push_back(new Brick(458, 50));
    listBrick.push_back(new Brick(50, 102));
    listBrick.push_back(new Brick(152, 102));
    listBrick.push_back(new Brick(254, 102));
    listBrick.push_back(new Brick(356, 102));
    listBrick.push_back(new Brick(458, 102));

    //GameLoop
    sf::Clock oClock;
    float fDeltaTime = 0;
    while (oWindow.isOpen())
    {
        //EVENT
        sf::Event oEvent;
        while (oWindow.pollEvent(oEvent))
        {
            if (oEvent.type == sf::Event::Closed)
                oWindow.close();

     
            if (oEvent.type == sf::Event::EventType::MouseButtonPressed && oEvent.mouseButton.button == sf::Mouse::Left)
            {
                listBall.push_back(new Ball(sf::Mouse::getPosition(oWindow).x, sf::Mouse::getPosition(oWindow).y));
            }

        }
        
        //UPDATE
        fDeltaTime = oClock.restart().asSeconds();

        oCanon.rotation(sf::Mouse::getPosition(oWindow).x, sf::Mouse::getPosition(oWindow).y);
        
        for (auto ball = listBall.begin(); ball != listBall.end();) {
            (*ball)->move(fDeltaTime);
            //oBall.setPosition(sf::Mouse::getPosition(oWindow).x, sf::Mouse::getPosition(oWindow).y);
            for (auto brick = listBrick.begin(); brick != listBrick.end(); brick++)
            {
                if ((*ball)->checkCollision(*brick))
                {
                    (*brick)->damage();
                    if ((*brick)->damage() == true) {
                        delete* brick;
                        brick = listBrick.erase(brick);
                    }
                    else {
                        brick++;
                    }
                    (*ball)->checkBounce(*brick);
                }
            }
            (*ball)->checkBounceWindow();
            if ((*ball)->eraseBall()) {
                delete* ball;
                ball = listBall.erase(ball);
            }
            else {
                ball++;
            }
        }

        //DRAW
        oWindow.clear();

        for (auto ball = listBall.begin(); ball != listBall.end(); ball++) {
            oWindow.draw(*(*ball)->pShape);
        }

        for (auto brick = listBrick.begin(); brick != listBrick.end(); brick++) {
            oWindow.draw(*(*brick)->pShape);
        }

        oWindow.draw(*oCanon.pShape);
       
        oWindow.display();

    }

    return 0;
}