/* Copyright 2019 The Microsoft Edge authors */

#ifndef RENDERER_H
#define RENDERER_H

#include "ArgsParser.h"

class SceneParser;

class Renderer {
  public:
    Renderer(Args args);
    void render();

  private:
    Args args_;
    SceneParser* sceneParser_;
};

#endif
