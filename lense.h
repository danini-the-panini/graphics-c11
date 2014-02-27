#pragma once

#include "include.h"

class Lense
{
public:
  Lense(float _fovY, float _zNear = 0.1f, float _zFar = 100.0f);
  ~Lense();

  mat4 getProjection(float aspect);

  float getFovY();
  float getZNear();
  float getZFar();

  void setFovY(float);
  void setZNear(float);
  void setZFar(float);

private:
  float fovY;
  float zNear;
  float zFar;
};