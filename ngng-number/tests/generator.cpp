#include "testlib.h"
#include "bits/stdc++.h"
#include "constraints.h"

using namespace std;


int main(int argc, char* argv[]){
    registerGen(argc,argv,1);

    // sample1
    string sample1 = "1220";
    ofstream of(format("000_sample_%02d.in",1).c_str());
    of << sample1 << endl;
    of.close();

    // sample2
    string sample2 = "25500";
    ofstream of(format("000_sample_%02d.in",2).c_str());
    of << sample2 << endl;
    of.close();

    // sample2
    string sample3 = "20250309";
    ofstream of(format("000_sample_%02d.in",3).c_str());
    of << sample3 << endl;
    of.close();

    for(int i=0;i<10;i++){
        ofstream of(format("001_subtask_%02d.in",i+1).c_str());
        const int N = rnd.next(MIN_length_of_N,MAX_length_of_N_subtask);
        string S(N,'.');
        for(int j=0;j<N;j++){
            if(j == 0)S[j] = (char)('0' + rnd.next(1,9));
            else S[j] = (char)('0' + rnd.next(0,9));
        }
        of << S << endl;
        of.close();
    }

    for(int i=0;i<20;i++){
        ofstream of(format("002_random_rid_%02d.in",i+1).c_str());
        const int N = rnd.next(MIN_length_of_N,MAX_length_of_N);
        string S(N,'.');
        for(int j=0;j<N;j++){
            if(j == 0)S[j] = (char)('0' + rnd.next(1,9));
            else S[j] = (char)('0' + rnd.next(0,9));
        }
        of << S << endl;
        of.close();
    }


    for(int i=0;i<5;i++){
        ofstream of(format("003_long_%02d.in",i+1).c_str());
        const int N = rnd.next(100000,MAX_length_of_N);
        string S(N,'.');
        for(int j=0;j<N;j++){
            if(j == 0)S[j] = (char)('0' + rnd.next(1,9));
            else S[j] = (char)('0' + rnd.next(0,9));
        }
        of << S << endl;
        of.close();
    }

    // max-1
    ofstream of(format("004_max-1_%02d.in",1).c_str());
    string S_max_minus_one(999999,'.');
    for(int j=0;j<999999;j++){
        if(j == 0)S_max_minus_one[j] = (char)('0' + rnd.next(1,9));
        else S_max_minus_one[j] = (char)('0' + rnd.next(0,9));
    }
    of << S_max_minus_one << endl;
    of.close();

    // max
    ofstream of(format("005_max_%02d.in",1).c_str());
    string S_max(1000000,'.');
    for(int j=0;j<1000000;j++){
        if(j == 0)S_max[j] = (char)('0' + rnd.next(1,9));
        else S_max[j] = (char)('0' + rnd.next(0,9));
    }
    of << S_max << endl;
    of.close();

}
