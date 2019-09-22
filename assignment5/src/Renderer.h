/* Copyright 2019 The Microsoft Edge authors */

#ifndef RENDERER_H
#define RENDERER_H

#include "ArgsParser.h"
#include "SceneParser.h"

class Renderer {
  public:
    Renderer(Args args);
    void render();
    ~Renderer() {
      if (sceneParser_ != nullptr) {
        delete sceneParser_;
      }
    }

  private:
    Args args_;
    SceneParser* sceneParser_;
};

#endif
