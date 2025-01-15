#include "testlib.h"

const int MIN_A = 1;
const int MAX_A = 100;
const int MIN_B = 1;
const int MAX_B = 100;

int main(int argc, char *argv[]) {
  registerValidation(argc, argv);
  inf.readInt(MIN_A, MAX_A, "A");
  inf.readSpace();
  inf.readInt(MIN_B, MAX_B, "B");
  inf.readEoln();
  inf.readEof();
  return 0;
}
