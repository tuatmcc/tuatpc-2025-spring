#include "testlib.h"
#include "bits/stdc++.h"

using namespace std;

const int MIN_length_of_N = 1;
const int MAX_length_of_N = 100000;

int main(int argc, char* argv[]){
    registerGen(argc,argv,1);

    ofstream of(format("001_small_rid_%02d.in").c_str());
    const int N = rnd.next(MIN_length_of_N,MAX_length_of_N);
    string S(N,'.');
    for(int i=0;i<N;i++){
        if(i == 0)S[i] = (char)('0' + rnd.next(1,9));
        else S[i] = (char)('0' + rnd.next(0,9));
    }
    of << S << endl;
}
