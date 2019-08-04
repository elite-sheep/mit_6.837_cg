/* Copyright 2019 The Microsoft Edge authors */

#include "Renderer.h"

#include <iostream>

#include "Camera.h"
#include "Group.h"
#include "Hit.h"
#include "Image.h"
#include "Light.h"
#include "Ray.h"
#include "SceneParser.h"
#include <vecmath.h>

Renderer::Renderer(Args args):
  args_(args) {
    std::cout << "Renderer: " << args_.inputFilename << std::endl;
    sceneParser_ = new SceneParser(args.inputFilename.c_str());
  }

void Renderer::render() {
  Image image(args_.width, args_.height);

  Vector3f color = sceneParser_->getBackgroundColor();

  image.SetAllPixels(color);

  Group* group = sceneParser_->getGroup();
  Camera* camera = sceneParser_->getCamera();
  Vector3f ambientLight = sceneParser_->getAmbientLight();
  int numLight = sceneParser_->getNumLights();
  if (group != nullptr) {
    for (int i = 0; i < args_.width; ++i) {
      float nw = 2 * (i / (args_.width - 1.0f)) - 1.0f;
      for (int j = 0; j < args_.height; ++j) {
        float nh = 2 * (j / (args_.height - 1.0f)) - 1.0f;
        Ray ray = camera->generateRay(Vector2f(nw, nh));
        Hit h = Hit();
        Vector3f shadedColor = Vector3f::ZERO;
        if (group->intersect(ray, h, camera->getTMin())) {
          Material* material = h.getMaterial();
          for (int k = 0; k < numLight; ++k) {
            Vector3f dirLight;
            Vector3f colorLight;
            float disToLight;
            Light* l = sceneParser_->getLight(k);
            l->getIllumination(ray.pointAtParameter(h.getT()), dirLight, colorLight, disToLight);
            shadedColor += material->Shade(ray, h, dirLight, colorLight);
          }

          shadedColor += material->getDiffuseColor() * ambientLight;
          image.SetPixel(i, j, shadedColor);
        }
      }
    }
  }

  image.SaveImage(args_.outputFilename.c_str());
}
