#include "physics_engine.h"

#include "physics_circle.h"

namespace {
bool circlecircleCollision(PhysicsObject* a, PhysicsObject* b) {
    ShapeID id1 = (*a).getID();
    ShapeID id2 = (*b).getID();

    Circle* x = dynamic_cast<Circle*>(a);
    Circle* y = dynamic_cast<Circle*>(b);
    sf::Vector2f posa = x->getPosition();
    sf::Vector2f posb = y->getPosition();
    sf::Vector2f ua = x->getVelocity();
    sf::Vector2f ub = y->getVelocity();
    float ra = x->getRadius();
    float rb = y->getRadius();
    PhysicalAttributes a1 = x->getAttributes();
    PhysicalAttributes a2 = y->getAttributes();
    float ma = a1.mass;
    float mb = a2.mass;
    float coeff1 = a1.restitution;
    float coeff2 = a2.restitution;
    float dist_sq = (posa.x - posb.x) * (posa.x - posb.x) + (posa.y - posb.y) * (posa.y - posb.y);
    if (dist_sq <= (ra + rb) * (ra + rb))
        return 1;
    else
        return 0;
}
}  // namespace

//*PhysicsEngine::collisionTable[0][0] = circlecircleCollision;

void PhysicsEngine::addObject(PhysicsObject* obj) {
    objects.push_back(std::move(obj));
}

void PhysicsEngine::update(sf::Time dt, sf::RenderWindow& window) {
    for (size_t i = 0; i < objects.size(); i++) {
        for (size_t j = i + 1; j < objects.size(); j++) {
            // if (objects[i]->checkCollision(*objects[j])) {
            //   objects[i]->resolveCollision(*objects[j]);
            //}
        }
    }
    for (auto& obj : objects)
        obj->update(dt, window);
}

void PhysicsEngine::draw(sf::RenderWindow& window) {
    for (auto& obj : objects)
        obj->draw(window);
}
