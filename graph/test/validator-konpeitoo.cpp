//#include "../../common/testlib.h"
#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;

const int MIN_N = 1;
const int MAX_N = 100000;
const int MIN_M = 1;
const int MAX_M = 100;
const int MIN_V = 1;
const int MIN_W = 1;
const int MAX_W = 100;
const int MIN_L = 1;
const int MAX_L = 8;
const int MIN_A = 1;

int main(int argc, char* argv[]){
    registerValidation(argc, argv);
    /*N*/
    int N = inf.readInt(MIN_N, MAX_N, "N");
    inf.readSpace();
    /*L*/
    int L = inf.readInt(MIN_L, MAX_L, "L");
    inf.readEoln();
    /*A*/
    //string S = inf.readToken("[A-G]+", "S");
    //ensuref(1 <= S.size() && S.size() <= 8, "S is invalid\n");
    vector<int> A(N);
    for(int i = 0; i < L; i++){
        if(i != 0)inf.readSpace();
        A[i] = inf.readInt(MIN_A, N, format("A(%d)", i + 1).c_str());
    }
    inf.readEoln();

    /*X*/
    vector<int> X(N);
    /*for(int i = 0; i < N; i++){
        if(i != 0)inf.readSpace();
        char c = inf.readChar();
        ensure('A' <= c && c <= 'G');
    }*/
    //inf.readEoln();

    int SUM_M = 0;
    for(int i = 0; i < N; i++){
        /*M*/
        int M = inf.readInt(MIN_M, MAX_M, format("M(%d)", i + 1));
        SUM_M += M;
        inf.readSpace();
        /*X*/
        X[i] = inf.readInt(MIN_A, N, format("X(%d)", i + 1).c_str());
        inf.readEoln();

        /*V*/
        const int MAX_V = N;
        int prev_V;
        int V;
        for(int j = 0; j < M; j++){
            if(j != 0)inf.readSpace();
            if(j == 0)V = inf.readInt(MIN_V, MAX_V, format("M%dV%d", i + 1, j + 1));
            else V = inf.readInt(prev_V + 1, MAX_V, format("M%dV%d", i + 1, j + 1));
            prev_V = V;
        }
        inf.readEoln();

        /*W*/
        int SUM_W = 0;
        int W;
        for(int j = 0; j < M; j++){
            if(j != 0)inf.readSpace();
            W = inf.readInt(MIN_W, MAX_W, format("M%dW%d", i + 1, j + 1));
            SUM_W += W;
        }
        inf.readEoln();
        ensuref(SUM_W == 100, "The sum of W is not 100\n");
    }
    int MAX_SUM_M = min((long long)pow((long long)N, 2), (long long)100000);
    ensuref(SUM_M <= MAX_SUM_M , "The sum of M is too large\n");

    inf.readEof();
}