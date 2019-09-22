/* Copyright 2019 The Microsoft Edge authors */

#include "Renderer.h"

#include <iostream>

#include "Camera.h"
#include "Group.h"
#include "Hit.h"
#include "Image.h"
#include "Light.h"
#include "Ray.h"
#include "RayTracer.h"
#include "SceneParser.h"
#include <vecmath.h>

const float EPS = 1e-4;

Renderer::Renderer(Args args):
  args_(args) {
    std::cout << "Renderer: " << args_.inputFilename << std::endl;
    sceneParser_ = new SceneParser(args.inputFilename.c_str());
  }

void Renderer::render() {
  Image image(args_.width, args_.height);

  Group* group = sceneParser_->getGroup();
  Camera* camera = sceneParser_->getCamera();
  if (group != nullptr) {
    RayTracer tracer(this->sceneParser_, args_);
    for (int i = 0; i < args_.width; ++i) {
      float nw = 2 * (i / (args_.width - 1.0f)) - 1.0f;
      for (int j = 0; j < args_.height; ++j) {
        float nh = 2 * (j / (args_.height - 1.0f)) - 1.0f;
        Ray ray = camera->generateRay(Vector2f(nw, nh));
        Hit hit = Hit();
        Vector3f color = tracer.traceRay(ray, camera->getTMin() + EPS, 0, 1.0, hit);
        image.SetPixel(i, j, color);
      }
    }
  }

  image.SaveImage(args_.outputFilename.c_str()); 
}
