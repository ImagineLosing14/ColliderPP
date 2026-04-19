#include "physics_circle.h"
#include "mjson/json.h"

// Circle::Circle(float r, sf::Vector2f pos) : PhysicsObject(ShapeID::CIRCLE_SHAPE, pos), radius(r) {
//     shape.setRadius(radius);
//     shape.setOrigin(sf::Vector2f(radius, radius));
//     shape.setPosition(pos);
//     shape.setFillColor(getAttributes().color);

// }

Circle::Circle(const JObject &obj_circle) : PhysicsObject(ShapeID::CIRCLE_SHAPE,obj_circle["PhysicsObject"]), radius(obj_circle["Circle"]["radius"]){
    shape.setRadius(radius);
    shape.setOrigin(sf::Vector2f(radius, radius));
    shape.setPosition(getPosition());
    shape.setFillColor(getAttributes().color);
}

void Circle::sync() {
    shape.setPosition(PhysicsObject::getPosition());
}

void Circle::update(sf::Time dt, sf::RenderWindow& window) {
    PhysicsObject::update(dt, window);
    sync();
}

void Circle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

float Circle::getRadius() const {
    return radius;
}

void Circle::setRadius(const float r) {
    radius = r;
    shape.setRadius(radius);
    // shape.setOrigin(sf::Vector2f(radius, radius)); // pls check in future :)
}

const sf::FloatRect Circle::getGlobalBounds() const {
    sf::Vector2f a = sf::Vector2f(getRadius(),getRadius());
    return sf::FloatRect(getPosition() - a, a * 2.0f);
}