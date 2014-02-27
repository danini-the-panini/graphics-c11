#pragma once

#include "include.h"
#include "listener.h"

static void mousebuttonfun(GLFWwindow * window, int button, int action, int mods);
static void cursorposfun(GLFWwindow * window, double x, double y);
static void cursorenterfun(GLFWwindow * window, int enter);
static void scrollfun(GLFWwindow * window, double dx, double dy);
static void keyfun(GLFWwindow * window, int key, int scancode, int action, int mods);

class Input
{
public:
  vector <function<void (int button, int mods, double x, double y)> > mousePressedF;
  vector <function<void (int button, int mods, double x, double y )> > mouseReleasedF;

  vector <function<void (double x, double y)> > mouseMovedF;

  vector <function<void ()> > mouseEnteredF;
  vector <function<void ()> > mouseExitedF;

  vector <function<void (double dx, double dy)> > scrollWheelMovedF;

  vector <function<void (int key, int keycode, int mods)> > keyPressedF;
  vector <function<void (int key, int keycode, int mods)> > keyReleasedF;
  vector <function<void (int key, int keycode, int mods)> > keyTypedF;

  static void addListener(Listener* l);

  static void init(GLFWwindow* window);

};

static Input* getInputInstance();