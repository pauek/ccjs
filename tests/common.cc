#include "common.h"
#include <sstream>

int s2i(const string &s) {
  istringstream iss(s);
  int i;
  iss >> i;
  return i;
}
