#include "lense.h"

Lense::Lense(float _fovY, float _zNear, float _zFar)
  : fovY(_fovY), zNear(_zNear), zFar(_zFar)
{

}
Lense::~Lense()
{

}

mat4 Lense::getProjection(float aspect)
{
  return perspective(fovY, aspect, zNear, zFar);
}

float Lense::getFovY()
{
  return fovY;
}
float Lense::getZNear()
{
  return zNear;
}
float Lense::getZFar()
{
  return zFar;
}

void Lense::setFovY(float v)
{
  fovY = v;
}
void Lense::setZNear(float v)
{
  zNear = v;
}
void Lense::setZFar(float v)
{
  zFar = v;
}