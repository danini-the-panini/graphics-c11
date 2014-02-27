#pragma once

#include "listener.h"
#include "camera.h"

class CameraControl : public Listener
{
public:
  CameraControl(Camera*);

private:
  Camera* camera;
  bool pan;
  bool orbit;
  double mx;
  double my;
};