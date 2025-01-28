//#include "../../common/testlib.h"
#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;

const int MIN_N = 1;
const int MAX_N = 100000;
const int MIN_M = 1;
const int MIN_L = 1;
const int MAX_L = 8;
const int MIN_W = 1;

void makeSampleTestcase(){
    ofstream of(format("00_sample_01.in").c_str());
    of << "2" << endl;
    of << "A B" << endl;
    of << "1" << endl;
    of << "2" << endl;
    of << "100" << endl;
    of << "1" << endl;
    of << "2" << endl;
    of << "100" << endl;
    of << "CDGD" << endl;
    of.close();
}

void makeEdgeTestcase(){
    /*同じ文字を含む場合*/
    ofstream of1(format("01_edge_01.in").c_str());
    of1 << "4" << endl;
    of1 << "A A A B" << endl;
    of1 << "1" << endl;
    of1 << "2" << endl;
    of1 << "100" << endl;
    of1 << "2" << endl;
    of1 << "1 3" << endl;
    of1 << "45 55" << endl;
    of1 << "2" << endl;
    of1 << "3 4" << endl;
    of1 << "40 60" << endl;
    of1 << "1" << endl;
    of1 << "3" << endl;
    of1 << "100" << endl;
    of1 << "AAA" << endl;
    of1.close();

    /*L = 1の場合*/
    ofstream of2(format("01_edge_02.in").c_str());
    of2 << "1" << endl;
    of2 << "A" << endl;
    of2 << "1" << endl;
    of2 << "1" << endl;
    of2 << "100" << endl;
    of2 << "A" << endl;
    of2.close();

    ofstream of3(format("01_edge_03.in").c_str());
    of3 << "1" << endl;
    of3 << "A" << endl;
    of3 << "1" << endl;
    of3 << "1" << endl;
    of3 << "100" << endl;
    of3 << "B" << endl;
    of3.close();

    /*全ての頂点が辺を持たないとき*/
    ofstream of4(format("01_edge_04.in").c_str());
    of4 << "3" << endl;
    of4 << "A B C" << endl;
    of4 << "1" << endl;
    of4 << "1" << endl;
    of4 << "100" << endl;
    of4 << "1" << endl;
    of4 << "2" << endl;
    of4 << "100" << endl;
    of4 << "1" << endl;
    of4 << "3" << endl;
    of4 << "100" << endl;
    of4 << "ABC" << endl;
    of4.close();

    /*自己ループがあるとき*/
    ofstream of5(format("01_edge_05.in").c_str());
    of5 << "3" << endl;
    of5 << "A A B" << endl;
    of5 << "1" << endl;
    of5 << "1" << endl;
    of5 << "100" << endl;
    of5 << "1" << endl;
    of5 << "2" << endl;
    of5 << "100" << endl;
    of5 << "1" << endl;
    of5 << "2" << endl;
    of5 << "100" << endl;
    of5 << "AA" << endl;
    of5.close();
}

void makeRandomTestcase(){
    for(int i = 0; i < 20; i++){
        ofstream of(format("02_random_%02d.in", i + 1).c_str());
        /*N*/
        int N = rnd.next(MIN_N, MAX_N);
        of << N << endl;
        /*X*/
        for(int j = 0; j < N; j++){
            if(j != 0)of << " ";
            of << (char)('A' + rnd.next(0, 6));
        }
        of << endl;
        /*M*/
        int MAX_MSUM_ = min((long long)pow(N, 2), (long long)100000);
        int MAX_MSUM = rnd.next(N, MAX_MSUM_);
        set<int> mset;
        while(mset.size() < N){
            mset.insert(rnd.next(1, MAX_MSUM));
        }
        int mPrev = 0;
        for(auto m : mset){
            int M = min(100, m - mPrev);
            mPrev = m;
            of << M << endl;
            /*V*/
            set<int> vset;
            while(vset.size() < M){
                vset.insert(rnd.next(1, N));
            }
            bool flag = false;
            for(auto v : vset){
                if(flag)of << " ";
                else flag = true;
                of << v;
            }
            of << endl;
            /*W*/
            set<int> wset;
            while(wset.size() < M - 1){
                wset.insert(rnd.next(1, 99));
            }
            int wPrev = 0;
            for(auto w : wset){
                int W = w - wPrev;
                wPrev = w;
                of << W << " ";
            }
            of << 100 - wPrev << endl;
        }
        /*S*/
        int L = rnd.next(MIN_L, MAX_L);
        for(int j = 0; j < L; j++){
            of << (char)('A' + rnd.next(0, 6));
        }
        of << endl;
        of.close();
    }
}

void makeMaxTestcase(){
    /*Nが最大かつMiの総和が最大*/
    ofstream of(format("03_max_01.in").c_str());
    /*N*/
    int N = MAX_N;
    of << N << endl;
    /*X*/
    for(int j = 0; j < N; j++){
        if(j != 0)of << " ";
        of << (char)('A' + rnd.next(0, 6));
    }
    of << endl;

    for(int i = 0; i < N; i++){
        /*Mi*/
        of << "1" << endl;
        /*V*/
        of << rnd.next(1, N) << endl;
        /*W*/
        of << "100" << endl;
    }
    /*S*/
    int L = 8;
    for(int j = 0; j < L; j++){
        of << (char)('A' + rnd.next(0, 6));
    }
    of << endl;
    of.close();  

    /*dfsだとTLEする(?), N = 1000でThe sum of Mi = 100*/
    ofstream of2(format("03_max_02.in").c_str());
    /*N*/
    N = MAX_N / 100;
    of2 << N << endl;
    /*X*/
    for(int i = 0; i < N; i++){
        if(i != 0)of2 << " ";
        of2 << 'A';
    } 
    of2 << endl;

    for(int i = 0; i < N; i++){
        /*Mi*/
        of2 << "100" << endl;
        /*V*/
        set<int> vset;
        while(vset.size() < 100){
            vset.insert(rnd.next(1, 1000));
        }
        bool flag = false;
        for(auto v : vset){
            if(flag)of2 << " ";
            else flag = true;
            of2 << v;
        }
        of2 << endl;
        /*W*/
        for(int j = 0; j < 100; j++){
            if(j != 0)of2 << " ";
            of2 << "1";
        }
        of2 << endl;
    }
    /*S*/
    of2 << "AAAAAAAA" << endl;
    of2.close();
}

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    //サンプル
    makeSampleTestcase();
    //エッジケース
    makeEdgeTestcase();
    //ランダム
    makeRandomTestcase();
    //最大ケース
    makeMaxTestcase();
}