#include "camera_control.h"

#include "include.h"

CameraControl::CameraControl(Camera* _camera)
  : camera(_camera), pan(false), orbit(false), mx(0.0), my(0.0)
{
  mousePressed = [this](int button, int mods, double x, double y)
  {
    if (button == GLFW_MOUSE_BUTTON_LEFT) orbit = true;
    if (button == GLFW_MOUSE_BUTTON_RIGHT) pan = true;

    mx = x; my = y;
  };
  mouseReleased = [this](int button, int mods, double x, double y)
  {
    if (button == GLFW_MOUSE_BUTTON_LEFT) orbit = false;
    if (button == GLFW_MOUSE_BUTTON_RIGHT) pan = false;
  };
  mouseMoved = [this](double x, double y)
  {
    float dx = (float)(x-mx), dy = (float)(y-my);
    if (orbit)
    {
      mat4 m;
      m = rotate(m, dy, normalize(camera->getRight()));
      m = rotate(m, -dx, vec3(0,1,0));
      vec4 d2 = m * vec4(camera->getDir(),0);
      camera->setEye(camera->getAt() - d2.xyz());
    } else if (pan)
    {
      vec3 v = normalize(camera->getRight()) * (dx * 0.01f) + normalize(camera->getRealUp()) * (dy * 0.01f);
      camera->setEye(camera->getEye() + v);
      camera->setAt(camera->getAt() + v);
    }
    mx = x; my = y;
  };
  scrollWheelMoved = [this](double dx, double dy)
  {
    vec3 d = camera->getDir();
    if (dy < 0)
    {
      for (float y = 0; y < -dy; y+=1)
        d *= 1.05;
    } else
    {
      for (float y = 0; y < dy; y+=1)
        d *= 0.95;
    }
    camera->setEye(camera->getAt() - d);
  };
};