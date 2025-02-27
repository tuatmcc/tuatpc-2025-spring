#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

const int MIN_A = 1;
const int MAX_A = 100;
const int MIN_B = 1;
const int MAX_B = 100;

void gen(string name, int A, int B) {
  ofstream ofs(name);
  ofs << A << " " << B << endl;
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);

  // sample1
  gen("00_sample_01.in", 2, 3);

  // sample2
  gen("00_sample_02.in", 5, 2);

  // sample3
  gen("00_sample_03.in", 5, 20);

  for (int t = 0; t < 20; t++) {
    gen(format("01_random_%02d.in", t + 1).c_str(), rnd.next(MIN_A, MAX_A),
        rnd.next(MIN_B, MAX_B));
  }

  // min
  gen("02_min_01.in", 1, 1);

  // max
  gen("02_max_01.in", 100, 100);

  return 0;
}
