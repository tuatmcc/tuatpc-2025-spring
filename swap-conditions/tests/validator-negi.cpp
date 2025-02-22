#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const int MIN_K = 1;
const int MAX_K = 4;
const ll MIN_A = -1e18;
const ll MAX_A = 1e18;

int main(int argc, char* argv[]){
    registerValidation(argc, argv);
    int k = inf.readInt(MIN_K, MAX_K, "X");
    inf.readSpace();
    int j = inf.readInt(MIN_K, MAX_K, "Y");
    inf.readEoln();
    assert(k != j);
    for(int i = 0; i < 4; i++){
        inf.readLong(MIN_A, MAX_A, "A");
        if(i == 3)inf.readEoln();
        else inf.readSpace();
    }
    inf.readEof();
    return 0;
}