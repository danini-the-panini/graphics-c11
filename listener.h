#pragma once

#include "include.h"

struct Listener
{
   function<void (int button, int mods, double x, double y)> mousePressed = [](int button, int mods, double x, double y) {};
   function<void (int button, int mods, double x, double y )> mouseReleased = [](int button, int mods, double x, double y ) {};

   function<void (double x, double y)> mouseMoved = [](double x, double y) {};

   function<void ()> mouseEntered = []() {};
   function<void ()> mouseExited = []() {};

   function<void (double dx, double dy)> scrollWheelMoved = [](double dx, double dy) {};

   function<void (int key, int keycode, int mods)> keyPressed = [](int key, int keycode, int mods) {};
   function<void (int key, int keycode, int mods)> keyReleased = [](int key, int keycode, int mods) {};
   function<void (int key, int keycode, int mods)> keyTyped = [](int key, int keycode, int mods) {};
};