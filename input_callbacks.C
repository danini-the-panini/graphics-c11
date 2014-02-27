#include "input_callbacks.h"

void Input::addListener(Listener* l)
{
  Input* instance = getInputInstance();
  instance->mousePressedF.push_back(l->mousePressed);
  instance->mouseReleasedF.push_back(l->mouseReleased);
  instance->mouseMovedF.push_back(l->mouseMoved);
  instance->mouseEnteredF.push_back(l->mouseEntered);
  instance->mouseExitedF.push_back(l->mouseExited);
  instance->scrollWheelMovedF.push_back(l->scrollWheelMoved);
  instance->keyPressedF.push_back(l->keyPressed);
  instance->keyReleasedF.push_back(l->keyReleased);
  instance->keyTypedF.push_back(l->keyTyped);
}

void Input::init(GLFWwindow* window)
{
  glfwSetKeyCallback (window, keyfun);
  glfwSetMouseButtonCallback (window, mousebuttonfun);
  glfwSetCursorPosCallback (window, cursorposfun);
  glfwSetCursorEnterCallback (window, cursorenterfun);
  glfwSetScrollCallback (window, scrollfun);
}

Input* getInputInstance()
{
  static Input* instance = new Input();
  return instance;
}

void mousebuttonfun(GLFWwindow * window, int button, int action, int mods)
{
  Input* instance = getInputInstance();

  double x, y;
  glfwGetCursorPos(window, &x, &y);

  for (auto f: action == GLFW_PRESS ? instance->mousePressedF : instance->mouseReleasedF)
    f(button, mods, x, y);
}
void cursorposfun(GLFWwindow * window, double x, double y)
{
  Input* instance = getInputInstance();

  for (auto f: instance->mouseMovedF)
    f(x, y);
}
void cursorenterfun(GLFWwindow * window, int enter)
{
  Input* instance = getInputInstance();

  for (auto f: enter ? instance->mouseEnteredF : instance->mouseExitedF)
    f();
}
void scrollfun(GLFWwindow * window, double dx, double dy)
{
  Input* instance = getInputInstance();

  for (auto f: instance->scrollWheelMovedF)
    f(dx, dy);
}
void keyfun(GLFWwindow * window, int key, int scancode, int action, int mods)
{
  Input* instance = getInputInstance();

  auto* F = &(instance->keyPressedF);
  if (action == GLFW_RELEASE)
    F = &(instance->keyReleasedF);
  else
    F = &(instance->keyTypedF);
  for (auto f: *F)
    f(key,scancode,mods);
}