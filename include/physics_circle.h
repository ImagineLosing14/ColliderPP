#pragma once
#include <SFML/Graphics.hpp>
#include "physics_object.h"

class JObject;

class Circle : public PhysicsObject {
private:
    float radius;
    sf::CircleShape shape;

    void sync();
public:
    Circle(float r, sf::Vector2f position);
    Circle(const JObject &obj_circle);

    void update(sf::Time deltaTime) override;
    void draw(sf::RenderWindow& window) override;

    float getRadius() const;
    void setRadius(const float r);

    const sf::FloatRect getGlobalBounds() const;
};

