/* Copyright 2019 The Microsoft Edge authors */

#include "Renderer.h"
#include "SceneParser.h"

Renderer::Renderer(Renderer::Problem problem)
  :problem_(problem) {
    scene_ = new SceneParser(problem.input_file.c_str());
  }

Renderer::~Renderer() {
  delete scene_;
}

void Renderer::render() {
}
