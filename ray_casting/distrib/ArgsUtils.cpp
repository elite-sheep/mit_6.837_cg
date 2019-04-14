/* Copyright 2019 The Microsoft Edge authors */

#include "ArgsUtils.h"
#include "Renderer.h"

#include <iostream>
#include <cassert>
#include <cstring>
#include <cstdlib>
#include <string>

Renderer::Problem parseArgs(int argc, char* argv[]) {
  Renderer::Problem problem;

  for (int i = 0; i < argc; ++i) {
    if (!strcmp("-input", argv[i])) {
      ++i;
      assert(i < argc);
      problem.input_file = std::string(argv[i]);
    } else if (!strcmp("-output", argv[i])) {
      ++i;
      assert(i < argc);
      problem.output_file = std::string(argv[i]);
    } else if (!strcmp("-size", argv[i])) {
      ++i;
      assert(i < argc);
      problem.w = atoi(argv[i]);
      ++i;
      assert(i < argc);
      problem.h = atoi(argv[i]);
    } else if (strcmp("-depth", argv[i])) {
      ++i;
      assert(i < argc);
      problem.depth_min = atoi(argv[i]);
      ++i;
      assert(i < argc);
      problem.depth_max = atoi(argv[i]);
      ++i;
      assert(i < argc);
      problem.depth_file = std::string(argv[i]);
    } else {
      std::cerr << "Invalid command: " << argv[i];
    }
  }

  return problem;
}
