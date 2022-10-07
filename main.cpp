#include<SFML/Graphics.hpp>
#include<iostream>
#include<cmath>

#define G 6.67 * pow(10,-2)

using namespace std;
using namespace sf;

class logic{

public:
    CircleShape body;
    float distance;
    float forc;
    float acceleration;
    float velocity;
    Vector2f directionm;


    logic()
    {
        body.setFillColor(Color(255, 95, 95)); // red
    }

    logic(string color)
    {
        body.setFillColor(Color( 95, 255, 250)); // blue
    }


    void create_ball(float x, float y)
    {
        body.setRadius(50.f);
        Vector2f position(x,y);
        body.setPosition(position);
    }

    Vector2f direction(Vector2f p1, Vector2f p2)
    {
        distance = sqrt((pow((p2.x - p1.x),2) )+ pow((p2.y - p1.y),2));
        directionm = (p2 - p1)/distance;
        return directionm;
    }

    float force(float mass1, float mass2)
    {
        if(distance < 100)
        {
            distance = 10;
        }
        forc = (G * mass1 * mass2)/(pow(distance,2));
        acceleration = forc/mass1;
        velocity += acceleration;
        return velocity;
    }

};

int main(int argc, char *argv[])
{

    RenderWindow window(VideoMode(1600,900), "gravity pls work", Style::Default);


    float velocity;
    string cyan = "cyan";
    logic b1;
    logic b2(cyan);

    b1.create_ball(1500/2, 600/2);
    float massb1 = 10;

    b2.create_ball(0,0);
    float massb2 = 10;

    Event event;
    Clock clock;
    window.setFramerateLimit(100000);
    while(window.isOpen())
    {
        Time dt = clock.restart();
        while(window.pollEvent(event))
        {
            if(event.type == Event::Closed)
            {
                window.close();
            }
        }

        Vector2f directb1 = b1.direction(b1.body.getPosition(), b2.body.getPosition());
        Vector2f directb2 = b2.direction(b2.body.getPosition(), b1.body.getPosition());

       float magnib1 = b1.force(massb1, massb2);
       float magnib2 = b2.force(massb2, massb1);

       b1.body.move(directb1 * (magnib1 * 100.f));
       b2.body.move(directb2 * (magnib2 * 100.f));

       cout<<b1.body.getPosition().x<<" "<<b1.body.getPosition().y<<"\n";

        window.clear();
        window.draw(b1.body);
        window.draw(b2.body);
        window.display();


    }


}