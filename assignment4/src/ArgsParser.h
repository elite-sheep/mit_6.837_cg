/* Copyright 2019 The Microsoft Edge authors */

#ifndef ARGS_PARSER_H
#define ARGS_PARSER_H

#include <string>

struct Args {
  std::string inputFilename;
  std::string outputFilename;
  int width;
  int height;
};

class ArgsParser {
  public:
    ArgsParser();
    void parse(int, char*[]);

    Args getArgs() {
      return args_;
    }

  private:
    Args args_;
};

#endif
