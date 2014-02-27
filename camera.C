#include "camera.h"

Camera::Camera(vec3 _eye, vec3 _at, vec3 _up)
  : eye(_eye), at(_at), up(_up), view(mat4()), invalid(true)
{
  recalc();
}

Camera::~Camera()
{

}


mat4 Camera::getView()
{
  if (invalid)
  {
    view = lookAt(eye,at,up);
    invalid = false;
  }
  return view;
}

vec3 Camera::getEye()
{
  return eye;
}
vec3 Camera::getAt()
{
  return at;
}
vec3 Camera::getUp()
{
  return up;
}

vec3 Camera::getRight()
{
  return right;
}
vec3 Camera::getRealUp()
{
  return realUp;
}
vec3 Camera::getDir()
{
  return dir;
}

void Camera::setEye(vec3 v)
{
  eye = v;
  recalc();
}
void Camera::setAt(vec3 v)
{
  at = v;
  recalc();
}
void Camera::setUp(vec3 v)
{
  up = v;
  recalc();
}

void Camera::recalc()
{
  dir = at - eye;
  right = cross(up,dir);
  realUp = cross(dir,right);
  invalid = true;
}