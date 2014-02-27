#include "light.h"

Light::Light(vec3 _position, vec3 _color, float _strength)
  : position(_position), color(_color), strength(_strength)
{

}
Light::~Light()
{

}

vec3 Light::getPosition()
{
  return position;
}
vec3 Light::getColor()
{
  return color;
}
float Light::getStrength()
{
  return strength;
}

void Light::setPosition(vec3 v)
{
  position = v;
}
void Light::setColor(vec3 v)
{
  color = v;
}
void Light::setStrength(float v)
{
  strength = v;
}