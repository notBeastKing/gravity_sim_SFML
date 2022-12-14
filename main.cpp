#include<SFML/Graphics.hpp>
#include<iostream>
#include<cmath>

#define G 6.67 * pow(10,-3)
#define MAX(x,y) x>=y?x:y //
                         //
#define MAGN(v) sqrt(pow(v.x,2) + pow(v.y,2))

#define NORM(v) v/(float)MAGN(v)


using namespace std;
using namespace sf;


class logic{

public:
    CircleShape body;
    float distance;
    float force;
    Vector2f acceleration;
    Vector2f Velocity;
    Vector2f  forcev;
    Vector2f direction;

    logic()
    {
        body.setFillColor(Color(255, 95, 95)); // red
        Velocity = Vector2f (0,0);
    }

    logic(string color)
    {
        body.setFillColor(Color( 95, 255, 250)); // blue
        Velocity = Vector2f (0,0);
    }


    void create_ball(float x, float y)
    {

        body.setRadius(50.f);
        Vector2f position(x,y);
        body.setPosition(position);
    }

    Vector2f forcef(float mass1, float mass2)
    {  
        force = (G * mass1 * mass2)/(pow(MAX(distance,90),2));
          forcev  = force * direction;

        cout<<"force : " << force<<"\n";

         acceleration = forcev/mass1;

         Velocity = Velocity + acceleration;
        return Velocity;
    }

    void directionf(Vector2f p1, Vector2f p2)
    {

        direction = (p2 - p1);
        distance = MAGN(direction);
        direction = NORM(direction);
    }

};

int main(int argc, char *argv[])
{

    RenderWindow window(VideoMode(1600,900), "gravity pls work", Style::Default);


    string cyan = "cyan";
    logic b1;
    logic b2(cyan);

    b1.create_ball(0, 900/2);
    float massb1 = 100000;


    b2.create_ball(1500,900/2);
    float massb2 = 100000;

    Event event;
    Clock clock;
    window.setFramerateLimit(60);
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

        b1.directionf(b1.body.getPosition(), b2.body.getPosition()); //direction of b1
        b2.directionf(b2.body.getPosition(), b1.body.getPosition()); // direction of b2

       Vector2f magnib1 = b1.forcef(massb1, massb2); // velocity for b1
       Vector2f magnib2 = b2.forcef(massb2, massb1); // velocity for b2

           b2.body.setPosition(b2.body.getPosition()  + magnib2 );
           b1.body.setPosition(b1.body.getPosition()  + magnib1 );

        window.clear();
        window.draw(b1.body);
        window.draw(b2.body);
        window.display();


    }


}
