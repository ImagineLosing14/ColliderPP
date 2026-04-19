#include<SFML/Graphics.hpp>
class PhysicsObject;

class Collider{
public:
    static bool CheckCollision(PhysicsObject a,PhysicsObject b, sf::Vector2f &direction);
    static sf::Vector2f move(PhysicsObject &a,PhysicsObject &b,sf::Vector2f &direction);
    static void changeVelocity(PhysicsObject &a,PhysicsObject &b, sf::Vector2f &direction);
};