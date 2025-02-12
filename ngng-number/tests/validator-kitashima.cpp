#include <bits/stdc++.h>

#include "constraints.h"
#include "testlib.h"

using namespace std;

int main() {
  registerValidation();
  
  // 1以上10^100000以下の整数を読み込む
  string s = inf.readToken(format("([1-9][0-9]{0,%d}|10{%d})", MAX_DIGIT - 1, MAX_DIGIT));

  inf.readEof();
  return 0;
}