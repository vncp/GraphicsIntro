#ifndef __ARGWRAPPER_H__
#define __ARGWRAPPER_H__

// Args Struct
struct Args {
  char *vertexShaderPath;
  char *fragmentShaderPath;
};

// Wrapper class to add pointers to args
class ArgWrapper {
public:
  ArgWrapper(Args *args);
  ~ArgWrapper();
  //vargs for processing
  static bool processArgs(int &argc, char **argv, Args *args_out);
  static void printUsage();
protected:
  Args *m_args;
};

#endif /* __ARGS_H__ */
