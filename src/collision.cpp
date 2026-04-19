#include "collision.h"

#include <SFML/Graphics.hpp>

#include "physics_circle.h"

inline float dot(sf::Vector2f a, sf::Vector2f b) {
    return a.x * b.x + a.y * b.y;
}

inline float lengthSquared(sf::Vector2f a) {
    return dot(a, a);
}

bool Collider::CheckCollision(PhysicsObject* a0, PhysicsObject* b0, sf::Vector2f& direction) {
    Circle* a = dynamic_cast<Circle*>(a0);
    Circle* b = dynamic_cast<Circle*>(b0);
    float r1 = a->getRadius(), r2 = b->getRadius();
    sf::Vector2f p1 = a->getPosition();
    sf::Vector2f p2 = b->getPosition();
    sf::Vector2f p3 = p2 - p1;

    float dist_squared = lengthSquared(p3);
    direction = p3;
    if (dist_squared <= (r1 + r2) * (r1 + r2)) {
        return true;
    }
    return false;
}

static bool ResolveBoundaryCollision(PhysicsObject* a0, sf::RenderWindow& window) {
    Circle* a = dynamic_cast<Circle*>(a0);
    float r = a->getRadius();
    sf::Vector2f p = a->getPosition();
    sf::Vector2f v = a->getVelocity();
    sf::Vector2f w = sf::Vector2f(window.getSize());
    sf::Vector2f v_new = v;
    sf::Vector2f p_new = p;
    bool collided = false;

    if (p.x - r < 0.f) {
        v_new.x = std::abs(v_new.x);
        p_new.x = r;
        collided = true;
    } else if (p.x + r > w.x) {
        v_new.x = -1 * std::abs(v_new.x);
        p_new.x = w.x - r;
        collided = true;
    }
    if (p.y - r < 0.f) {
        v_new.y = std::abs(v_new.y);
        p_new.y = r;
        collided = true;
    } else if (p.y + r > w.y) {
        v_new.y = -1 * std::abs(v_new.y);
        p_new.y = w.y - r;
        collided = true;
    }

    a->setPosition(p_new);
    a->setVelocity(v_new);

    return collided;
}

static void move(PhysicsObject* a, PhysicsObject* b, sf::Vector2f& direction) {
    float ma = a->getAttributes().mass;
    float mb = b->getAttributes().mass;
    b->setPosition(b->getPosition() + (direction * (ma / (ma + mb))));
    a->setPosition(a->getPosition() - (direction * (mb / (ma + mb))));
}

static void changeVelocity(PhysicsObject* a, PhysicsObject* b, sf::Vector2f& direction) {
    sf::Vector2f p1 = a->getPosition();
    sf::Vector2f p2 = b->getPosition();
    sf::Vector2f v1 = a->getVelocity();
    sf::Vector2f v2 = b->getVelocity();
    float m1 = a->getAttributes().mass;
    float m2 = b->getAttributes().mass;

    float dist2 = lengthSquared(direction);
    if (dist2 == 0) return;

    float factor = dot(direction, v2 - v1) / dist2;
    float reduced_mass = (2 * m1 * m2) / (m1 + m2);
    sf::Vector2f change1 = direction * ((reduced_mass / m1) * factor);
    sf::Vector2f change2 = direction * ((reduced_mass / m2) * factor);

    a->applyImpulse(-change1 * m1, p1);
    b->applyImpulse(change2 * m2, p2);
}