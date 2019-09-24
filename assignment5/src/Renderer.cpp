/* Copyright 2019 The Microsoft Edge authors */

#include "Renderer.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

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
const float GAUSSIAN_KERNAL[5] = {0.1201, 0.2339, 0.2931, 0.2339, 0.1201};

Renderer::Renderer(Args args):
  args_(args) {
    std::cout << "Renderer: " << args_.inputFilename << std::endl;
    sceneParser_ = new SceneParser(args.inputFilename.c_str());
  }

void Renderer::render() {

  srand(time(nullptr));

  Image image(args_.width, args_.height);

  Group* group = sceneParser_->getGroup();
  Camera* camera = sceneParser_->getCamera();
  Image upsampleImage(args_.width * 3, args_.height * 3);
  if (group != nullptr) {
    RayTracer tracer(this->sceneParser_, args_);
    for (int i = 0; i < args_.width; ++i) {
      for (int j = 0; j < args_.height; ++j) {
        Vector3f color;
        if (args_.jittered) {
          color = Vector3f::ZERO;
          for (int k = -1; k <= 1; ++k) {
            for (int l = -1; l <= 1; ++l) {

              float rw = rand() / RAND_MAX - 0.5f;
              float rh = rand() / RAND_MAX - 0.5f;

              float nw = 2 * ((i + rw) / (args_.width)) - 1.0f;
              float nh = 2 * ((j + rh) / (args_.height)) - 1.0f;
              
              Ray ray = camera->generateRay(Vector2f(nw, nh));
              Hit hit = Hit();
              Vector3f upsampleColor = tracer.traceRay(ray, camera->getTMin(), 0, 1.0, hit);
              upsampleImage.SetPixel(3 * i + k + 1, 3 * j + l + 1, upsampleColor);
            }
          }
        } else {
          float nw = 2 * (i / (args_.width - 1.0f)) - 1.0f;
          float nh = 2 * (j / (args_.height - 1.0f)) - 1.0f;
          Ray ray = camera->generateRay(Vector2f(nw, nh));
          Hit hit = Hit();
          Vector3f color = tracer.traceRay(ray, camera->getTMin() + EPS, 0, 1.0, hit);
          image.SetPixel(i, j, color);
        }
      }
    }
  }

  if (args_.jittered) {
    Image blurImage1(upsampleImage.Width(), upsampleImage.Height());
    for (int ii = 0; ii < upsampleImage.Width(); ++ii) {
      for (int jj = 0; jj < upsampleImage.Height(); ++jj) {
        Vector3f tmpColor = getPixel(upsampleImage, ii, jj - 2) * GAUSSIAN_KERNAL[0] + 
          getPixel(upsampleImage, ii, jj - 1) * GAUSSIAN_KERNAL[1] + 
          getPixel(upsampleImage, ii, jj) * GAUSSIAN_KERNAL[2] + 
          getPixel(upsampleImage, ii, jj + 1) * GAUSSIAN_KERNAL[3] +
          getPixel(upsampleImage, ii, jj + 2) * GAUSSIAN_KERNAL[4];
        blurImage1.SetPixel(ii, jj, tmpColor);
      }
    }

    Image blurImage2(upsampleImage.Width(), upsampleImage.Height());
    for (int ii = 0; ii < upsampleImage.Height(); ++ii) {
      for (int jj = 0; jj < upsampleImage.Width(); ++jj) {
        Vector3f tmpColor = getPixel(blurImage1, jj - 2, ii) * GAUSSIAN_KERNAL[0] + 
          getPixel(blurImage1, jj - 1, ii) * GAUSSIAN_KERNAL[1] + 
          getPixel(blurImage1, jj, ii) * GAUSSIAN_KERNAL[2] + 
          getPixel(blurImage1, jj, ii + 1) * GAUSSIAN_KERNAL[3] +
          getPixel(blurImage1, jj, ii + 2) * GAUSSIAN_KERNAL[4];
        blurImage2.SetPixel(jj, ii, tmpColor);
      }
    }

    for (int ii = 0; ii < image.Width(); ++ii) {
      for (int jj = 0; jj < image.Height(); ++jj) {
        Vector3f tmp_color = 
          getPixel(blurImage2, 3 * ii, 3 * jj) +
          getPixel(blurImage2, 3 * ii, 3 * jj + 1) +
          getPixel(blurImage2, 3 * ii, 3 * jj + 2) +
          getPixel(blurImage2, 3 * ii + 1, 3 * jj) +
          getPixel(blurImage2, 3 * ii + 1, 3 * jj + 1) +
          getPixel(blurImage2, 3 * ii + 1, 3 * jj + 2) +
          getPixel(blurImage2, 3 * ii + 2, 3 * jj) +
          getPixel(blurImage2, 3 * ii + 2, 3 * jj + 1) +
          getPixel(blurImage2, 3 * ii + 2, 3 * jj + 2);
        tmp_color = tmp_color / 9.0f;
        image.SetPixel(ii, jj, tmp_color);
      }
    }
  }
  image.SaveImage(args_.outputFilename.c_str()); 
}
