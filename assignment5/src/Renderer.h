/* Copyright 2019 The Microsoft Edge authors */

#ifndef RENDERER_H
#define RENDERER_H

#include "ArgsParser.h"
#include "Image.h"
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

    static Vector3f getPixel(const Image& image, int x, int y) {
      if (x < 0) x = 0;
      else if (x >= image.Width()) x = image.Width() - 1;
      if (y < 0) y = 0;
      else if (y >= image.Height()) y = image.Height() - 1;

      return image.GetPixel(x, y);
    }

  private:
    Args args_;
    SceneParser* sceneParser_;
};

#endif
