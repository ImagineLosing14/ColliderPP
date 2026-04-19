#pragma once

#include <SFML/Graphics.hpp>
#include "physics_attributes.h"

class PhysicsObject {
private:
    sf::Vector2f position;
    sf::Vector2f velocity = sf::Vector2f(0.0f,0.0f);
    sf::Vector2f acceleration = sf::Vector2f(0.0f,0.0f);
    float angle = 0.0f;
    float angularVelocity = 0.0f;
    float angularAcceleration = 0.0f;

    ShapeID ID;
    
    PhysicalAttributes attributes;

public:
    //Constructor
    PhysicsObject(ShapeID id, const JObject& config_json);
    PhysicsObject(ShapeID id, const sf::Vector2f& pos, const PhysicalAttributes& attr= PhysicalAttributes::DEFAULT_PHYSICS_ATTRIBUTE());
    



    virtual ~PhysicsObject();

    const sf::Vector2f getPosition() const;
    void setPosition(const sf::Vector2f& newPosition);
    const sf::Vector2f getVelocity() const;
    void setVelocity(const sf::Vector2f& newVelocity);
    const sf::Vector2f getAcceleration() const;
    void setAcceleration(const sf::Vector2f& newAcceleration);
    const float getAngle() const;
    void setAngle(const float& newAngle);
    const float getAngularVelocity() const;
    void setAngularVelocity(const float& newAngularVelocity);
    const float getAngularAcceleration() const;
    void setAngularAcceleration(const float& newAngularAcceleration);

    const ShapeID getID() const;

    const PhysicalAttributes getAttributes() const;
    void setAttributes(const PhysicalAttributes& newAttributes);

   

    // apply force
    // apply impulse
    void applyForce(const sf::Vector2f& force, const sf::Vector2f& position);
    void applyImpulse(const sf::Vector2f& impulse, const sf::Vector2f& position);

    virtual const sf::FloatRect getGlobalBounds() const =0;

    virtual void update(sf::Time dt , sf::RenderWindow& window);
    virtual void draw(sf::RenderWindow& window) = 0;
};
