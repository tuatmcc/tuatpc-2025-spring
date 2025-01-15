#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;

const int MIN_A = 1;
const int MAX_A = 1000;
const int MIN_B = 1;
const int MAX_B = 1000;

void gen(string name, int A, int B){
    ofstream ofs(name);
    ofs << A << " " << B << endl;
}

int main(int argc, char* argv[]){
  registerGen(argc, argv, 1);

  // sample1
  gen("00_sample_01.in", 5, 2);

  // sample2
  gen("00_sample_02.in", 1, 45);

  // min
  gen("min.in", 1, 1);

  // max
  gen("max.in", 100, 100);

  for (int t = 0; t < 20; t++) {
    gen(format("02_random_%02d.in", t+1).c_str(), rnd.next(MIN_A, MAX_A), rnd.next(MIN_B, MAX_B));
  }
  return 0;
}