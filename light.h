#pragma once

#include "include.h"

class Light
{
public:
  Light(vec3 _position, vec3 _color = vec3(1,1,1), float _strength = 1.0f);
  ~Light();

  vec3 getPosition();
  vec3 getColor();
  float getStrength();

  void setPosition(vec3);
  void setColor(vec3);
  void setStrength(float);

private:
  vec3 position;
  vec3 color;
  float strength;
};