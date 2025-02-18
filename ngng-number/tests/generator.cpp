#include "testlib.h"
#include "bits/stdc++.h"
#include "constraints.h"

using namespace std;

int main(int argc, char* argv[]){
    registerGen(argc,argv,1);
    for(int i=0;i<20;i++){
        ofstream of(format("001_small_rid_%02d.in",i+1).c_str());
        const int N = rnd.next(MIN_length_of_N,MAX_length_of_N);
        string S(N,'.');
        for(int j=0;j<N;j++){
            if(j == 0)S[j] = (char)('0' + rnd.next(1,9));
            else S[j] = (char)('0' + rnd.next(0,9));
        }
        of << S << endl;
    }

    for(int i=0;i<5;i++){
        ofstream of(format("002_small_rid_%02d.in",i+1).c_str());
        const int N = rnd.next(MIN_length_of_N,MAX_length_of_N_subtask);
        string S(N,'.');
        for(int j=0;j<N;j++){
            if(j == 0)S[j] = (char)('0' + rnd.next(1,9));
            else S[j] = (char)('0' + rnd.next(0,9));
        }
        of << S << endl;
    }


}
