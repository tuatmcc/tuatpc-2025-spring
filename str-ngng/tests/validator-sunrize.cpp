#include "testlib.h"
#include "bits/stdc++.h"
#include "constraints.hpp"

using namespace std;

int main(){
    registerValidation();
    int N = inf.readInt(MIN_N,MAX_N,"N");
    inf.readSpace();
    int Q = inf.readInt(MIN_Q,MAX_Q,"Q");
    inf.readEoln();
    string S = inf.readToken(format("[a-z]{%d}",N),"S");
    for(int i=0;i<Q;i++){
        int L = inf.readInt(1,N,"L");
        inf.readSpace();
        int R = inf.readInt(1,N,"R");
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}