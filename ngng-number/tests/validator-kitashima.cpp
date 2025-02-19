#include <bits/stdc++.h>

#include "constraints.h"
#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
  registerValidation(argc, argv);
  
  // 1以上10^100000以下の整数を読み込む
  string s = inf.readToken(format("([1-9][0-9]{0,%d}|10{%d})", MAX_length_of_N - 1, MAX_length_of_N));
  inf.readEoln();
  inf.readEof();
  return 0;
}