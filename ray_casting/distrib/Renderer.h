/* Copyright 2019 The Microsoft Edge authors */

#ifndef RENDERER_H
#define RENDERER_H

#include "SceneParser.h"

#include <string>

class Renderer {
  public:
    struct Problem {
      std::string input_file;
      std::string output_file;
      std::string depth_file;
      int w;
      int h;
      int depth_min;
      int depth_max;

      Problem() {
        input_file = "";
        output_file = "";
        depth_file = "";
      }
    };

    Renderer(Problem problem);
    ~Renderer();
    void render();

  private:
    Problem problem_;
    SceneParser* scene_;
};

#endif
