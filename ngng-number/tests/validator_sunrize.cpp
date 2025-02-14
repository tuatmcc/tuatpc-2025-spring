#include "testlib.h"
#include "bits/stdc++.h"
#include "constraints.h"

using namespace std;

int main(int argc, char* argv[]){
    registerInteraction(argc,argv);
    string S = inf.readToken(format("[0-9]{%d,%d}",MIN_length_of_N,MAX_length_of_N));
    inf.readEoln();
    inf.readEof();
    return 0;
}