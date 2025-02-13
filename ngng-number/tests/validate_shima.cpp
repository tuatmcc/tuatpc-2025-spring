#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]){
  registerValidation(argc, argv);
  // regx no shiyou wakaran
  string num =  inf.readToken("[0-9]{0, 100001}");
  ensure(num[0] != '0');
  if(num.size == 100001){
      ensure(num[0] == '1');
      for(int i = 1; i < num.size(); i++){
          ensure(num[i] == '0');
      }
  }
  inf.readEof();
}