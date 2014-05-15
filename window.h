#pragma once

#include "include.h"

#include <functional>

#include "shader.h"
#include "camera.h"
#include "lense.h"
#include "light.h"
#include "listener.h"

class Window
{
public:
  Window(int width, int height, const char* title);
  ~Window();

  void init(std::function<void (void)>);
  void eachFrame(std::function<void (int, int)>);
  void withShader(Shader*, std::function<void (Shader*)>);

  void background(vec3);

  void useCamera(Camera*);
  void useLense(Lense*);

  void addLight(Light*);
  void removeLight(Light*);

  void addListener(Listener*);

private:
  GLFWwindow* handle;
  Camera* camera;
  Lense* lense;
  int width;
  int height;
  vector<Light*> lights;
  vec3 sharm[16]; // used for spherical harmonic lighting
};