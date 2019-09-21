/* Copyright 2019 The Microsoft Edge authors */

#include "ArgsParser.h"

#include <cstring>
#include <iostream>

ArgsParser::ArgsParser() {
  // Set args to default values.
  args_.outputFilename = "output.bmp";
  args_.width = 100;
  args_.height = 100;
}

void ArgsParser::parse(int argc, char* argv[]) {
  for (int i = 0; i < argc; ++i) {
    if (!strcmp(argv[i], "-input")) {
      ++i;
      if (i < argc) {
        args_.inputFilename = std::string(argv[i]);
      }
    } else if (!strcmp(argv[i], "-output")) {
      ++i;
      if (i < argc) {
        args_.outputFilename = std::string(argv[i]);
      }
    } else if (!strcmp(argv[i], "-size")) {
      i += 2;
      if (i < argc) {
        args_.width = std::stoi(argv[i-1]);
        args_.height = std::stoi(argv[i]);
      }
    } else {
      std::cerr << "ArgsParser: Unable to parse current arg: " << argv[i] << std::endl;
    }
  }
}
