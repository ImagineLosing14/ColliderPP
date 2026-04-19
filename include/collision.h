#include<SFML/Graphics.hpp>
class PhysicsObject;

class Collider{
public:

    static bool CheckCollision(PhysicsObject* a0,PhysicsObject* b0, sf::Vector2f &direction);
    static bool ResolveBoundaryCollision(PhysicsObject &a, sf::RenderWindow &window);
    static void move(PhysicsObject* a,PhysicsObject* b,sf::Vector2f &direction);
    static void changeVelocity(PhysicsObject* a,PhysicsObject* b, sf::Vector2f &direction);
};
