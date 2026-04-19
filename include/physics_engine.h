#pragma once

#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>
#include "physics_object.h"



class PhysicsEngine{
private:
    std::vector<PhysicsObject*> objects;
  
  //static bool(*collisionTable)(PhysicsObject*, PhysicsObject*) [4][4];

public:
  void addObject(PhysicsObject* obj);

  
  void update(sf::Time dt, sf::RenderWindow& window);
  void draw(sf::RenderWindow& window);
};


