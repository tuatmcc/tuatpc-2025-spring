#include"testlib.h"
#include<bits/stdc++.h>
using namespace std;

const int MIN_K = 1;
const int MAX_K = 4;
const long long MIN_A = -1000000000000000000;
const long long MAX_A = 1000000000000000000;

int main(int argc, char *argv[]){
    registerValidation(argc, argv);
    int k = inf.readInt(MIN_K, MAX_K, "K");
    for(int i = 0; i < 4; i++){
        inf.readSpace();
        inf.readLong(MIN_A, MAX_A, format("A%d", i + 1).c_str());
    }
    inf.readEoln();
    int j;
    for(int i = 0; i < 3; i++){
        if(i != 0)inf.readSpace();
        j = inf.readInt(MIN_K, MAX_K, format("J%d", i + 1).c_str());
        ensuref(k != j, "K and J are duplicates");
    }
    inf.readEoln();
    inf.readEof();
}