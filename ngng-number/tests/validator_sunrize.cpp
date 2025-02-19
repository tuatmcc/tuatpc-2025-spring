#include "testlib.h"
#include "bits/stdc++.h"
#include "constraints.h"

using namespace std;

int main(int argc, char* argv[]){
    registerInteraction(argc,argv);
    string S = inf.readToken(format("([1-9][0-9]{0,%d}|10{%d})",MAX_length_of_N-1,MAX_length_of_N));
    inf.readEoln();
    inf.readEof();
    return 0;
}