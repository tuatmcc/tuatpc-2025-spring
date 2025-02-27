#include "testlib.h"
#include "bits/stdc++.h"
#include "constraints.h"

using namespace std;


int main(int argc, char* argv[]){
    registerGen(argc,argv,1);

    // sample1
    string sample1 = "1220";
    ofstream of(format("00_sample_%02d.in",1).c_str());
    of << sample1 << endl;
    of.close();

    // sample2
    string sample2 = "12345";
    ofstream of2(format("00_sample_%02d.in",2).c_str());
    of2 << sample2 << endl;
    of2.close();

    // sample2
    string sample3 = "2025030920250309202503092025030920250309";
    ofstream of3(format("00_sample_%02d.in",3).c_str());
    of3 << sample3 << endl;
    of3.close();

    for(int i=0;i<10;i++){
        ofstream of4(format("01_subtask_%02d.in",i+1).c_str());
        const int N = rnd.next(MIN_length_of_N,MAX_length_of_N_subtask);
        string S(N,'.');
        for(int j=0;j<N;j++){
            if(j == 0)S[j] = (char)('0' + rnd.next(1,9));
            else S[j] = (char)('0' + rnd.next(0,9));
        }
        of4 << S << endl;
        of4.close();
    }

    // sample2
    string sample22 = "12345";
    ofstream of22(format("01_subtask_%02d.in",11).c_str());
    of22 << sample22 << endl;
    of22.close();


    string sample23 = "25500";
    ofstream of23(format("01_subtask_%02d.in",12).c_str());
    of23 << sample23 << endl;
    of23.close();

    for(int i=0;i<20;i++){
        ofstream of5(format("02_random_%02d.in",i+1).c_str());
        const int N = rnd.next(MIN_length_of_N,MAX_length_of_N);
        string S(N,'.');
        for(int j=0;j<N;j++){
            if(j == 0)S[j] = (char)('0' + rnd.next(1,9));
            else S[j] = (char)('0' + rnd.next(0,9));
        }
        of5 << S << endl;
        of5.close();
    }


    for(int i=0;i<5;i++){
        ofstream of6(format("03_long_%02d.in",i+1).c_str());
        const int N = rnd.next(100000,MAX_length_of_N);
        string S(N,'.');
        for(int j=0;j<N;j++){
            if(j == 0)S[j] = (char)('0' + rnd.next(1,9));
            else S[j] = (char)('0' + rnd.next(0,9));
        }
        of6 << S << endl;
        of6.close();
    }

    // max-1
    ofstream of7(format("04_nines_%02d.in",1).c_str());
    string S_max_minus_one(99999,'.');
    for(int j=0;j<99999;j++){
        S_max_minus_one[j] = '9';
    }
    of7 << S_max_minus_one << endl;
    of7.close();

    // max
    ofstream of8(format("05_max_%02d.in",1).c_str());
    string S_max(100000,'.');
    for(int j=0;j<100000;j++){
        if(j == 0)S_max[j] = '1';
        else S_max[j] = '0';
    }
    of8 << S_max << endl;
    of8.close();

}
