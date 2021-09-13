#include <iostream>
#include "engine.h"
#include "argwrapper.h"

int main(int argc, char **argv)
{
  Args args;
  if( !ArgWrapper::processArgs(argc, argv, &args) ) {
    std::cerr << "Error processing args" << std::endl;
    exit(EXIT_FAILURE);
  }
  // Start an engine and run it then cleanup after
  Engine *engine = new Engine("PA2: Interaction", 800, 600, &args);
  if(!engine->Initialize())
  {
    printf("The engine failed to start.\n");
    delete engine;
    engine = nullptr;
    return 1;
  }
  engine->Run();
  delete engine;
  engine = nullptr;
  return 0;
}
