#pragma once

#include "include.h"

class Camera
{
public:
  Camera(vec3 _eye, vec3 _at, vec3 _up = vec3(0,1,0));
  ~Camera();

  mat4 getView();

  vec3 getEye();
  vec3 getAt();
  vec3 getUp();

  vec3 getRight();
  vec3 getRealUp();
  vec3 getDir();

  void setEye(vec3);
  void setAt(vec3);
  void setUp(vec3);

private:
  vec3 eye;
  vec3 at;
  vec3 up;

  vec3 right;
  vec3 realUp;
  vec3 dir;

  mat4 view;
  bool invalid;

  void recalc();
};