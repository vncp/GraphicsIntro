#include "argwrapper.h"
#include <iostream>
#include <cstring>
#include <assert.h>

ArgWrapper::ArgWrapper(Args *args) : m_args(args) {
}

ArgWrapper::~ArgWrapper() {
}

bool ArgWrapper::processArgs(int &argc, char **argv, Args *args_out) {
  assert( args_out != NULL);

  // [OPTION] "--help"
  for (int i = 0; i < argc; i++) {
    if (!strcmp(argv[i], "--help")) {
      printUsage();
      return false;
    }
  }

  // Count required args
  if (argc != 5) {
    printUsage();
    return false;
  }

  // Check OPTIONS correct
  if (!strcmp(argv[1], "-f") && !strcmp(argv[3], "-v")) {
    args_out->fragmentShaderPath = argv[2];
    args_out->vertexShaderPath = argv[4];
  }
  else if (!strcmp(argv[1], "-v") && !strcmp(argv[3], "-f")) {
    args_out->vertexShaderPath = argv[2];
    args_out->fragmentShaderPath = argv[4];
  }
  else {
    printUsage();
    return false;
  }

  return true;
}

void ArgWrapper::printUsage() {
    printf("Usage: Tutorial\n"
      "Orbitting spinning cube\n"
      "Example: Tutorial -v ../shaders/vertexShader.glsl -f ../shaders/fragmentShader.glsl\n"
      "Shader specification:\n"
      "\t-v\tPath to vertex shader file\n"
      "\t-f\tPath to fragment shader file\n");
}
