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
    of << "4" << endl;
    of << "CDGD" << endl;
    of.close();
    /**ans: 
     * 0 1
     * 0 1
     * */

    /*同じ文字を含む場合*/
    ofstream of1(format("00_sample_02.in").c_str());
    of1 << "4" << endl;
    of1 << "A A A B" << endl;
    of1 << "1" << endl;
    of1 << "2" << endl;
    of1 << "100" << endl;
    of1 << "2" << endl;
    of1 << "1 3" << endl;
    of1 << "20 80" << endl;
    of1 << "2" << endl;
    of1 << "2 4" << endl;
    of1 << "60 40" << endl;
    of1 << "1" << endl;
    of1 << "3" << endl;
    of1 << "100" << endl;
    of1 << "3" << endl;
    of1 << "AAA" << endl;
    of1.close();
    /**ans: 
     * 1 1
     * 17 25
     * 3 5
     * 0 1
     * */
}

void makeHandTestcase(){
    /*L = 1の場合*/
    ofstream of2(format("01_hand_01.in").c_str());
    of2 << "1" << endl;
    of2 << "A" << endl;
    of2 << "1" << endl;
    of2 << "1" << endl;
    of2 << "100" << endl;
    of2 << "1" << endl;
    of2 << "A" << endl;
    of2.close();
    /**ans: 
     * 1 1
     * */

    ofstream of3(format("01_hand_02.in").c_str());
    of3 << "1" << endl;
    of3 << "A" << endl;
    of3 << "1" << endl;
    of3 << "1" << endl;
    of3 << "100" << endl;
    of3 << "1" << endl;
    of3 << "B" << endl;
    of3.close();
    /**ans: 
     * 0 1
     * */

    ofstream of4(format("01_hand_03.in").c_str());
    of4 << "5" << endl;
    of4 << "A B C B A" << endl;
    of4 << "1" << endl;
    of4 << "2" << endl;
    of4 << "100" << endl;
    of4 << "1" << endl;
    of4 << "3" << endl;
    of4 << "100" << endl;
    of4 << "1" << endl;
    of4 << "4" << endl;
    of4 << "100" << endl;
    of4 << "1" << endl;
    of4 << "5" << endl;
    of4 << "100" << endl;
    of4 << "1" << endl;
    of4 << "1" << endl;
    of4 << "100" << endl;
    of4 << "1" << endl;
    of4 << "B" << endl;
    of4.close();
    /**ans: 
     * 0 1
     * 1 1
     * 0 1
     * 1 1
     * 0 1
     * */

    /*全ての頂点が辺を持たないとき*/
    ofstream of5(format("01_hand_04.in").c_str());
    of5 << "3" << endl;
    of5 << "A B C" << endl;
    of5 << "1" << endl;
    of5 << "1" << endl;
    of5 << "100" << endl;
    of5 << "1" << endl;
    of5 << "2" << endl;
    of5 << "100" << endl;
    of5 << "1" << endl;
    of5 << "3" << endl;
    of5 << "100" << endl;
    of5 << "3" << endl;
    of5 << "ABC" << endl;
    of5.close();
    /**ans: 
     * 0 1
     * 0 1
     * 0 1
     * */

    /*自己ループがあるとき*/
    ofstream of6(format("01_hand_05.in").c_str());
    of6 << "3" << endl;
    of6 << "A A B" << endl;
    of6 << "1" << endl;
    of6 << "1" << endl;
    of6 << "100" << endl;
    of6 << "3" << endl;
    of6 << "1 2 3" << endl;
    of6 << "30 40 30" << endl;
    of6 << "1" << endl;
    of6 << "2" << endl;
    of6 << "100" << endl;
    of6 << "2" << endl;
    of6 << "AA" << endl;
    of6.close();
    /**ans: 
     * 1 1
     * 7 10
     * 0 1
     * */

    /*分母が最大になるケース1*/
    ofstream of7(format("01_hand_06.in").c_str());
    /*N*/
    int _MAX_N = 10000;
    int N = rnd.next(MIN_N, _MAX_N);
    of7 << N << endl;
    /*X*/
    for(int j = 0; j < N; j++){
        if(j != 0)of7 << " ";
        of7 << (char)('A' + rnd.next(0, 6));
    }
    of7 << endl;

    for(int j = 0; j < N; j++){
        /*M*/
        of7 << "10" << endl;

        /*V*/
        set<int> vset;
        while(vset.size() < 10){
            vset.insert(rnd.next(1, N));
        }
        bool flag = false;
        for(auto v : vset){
            if(flag)of7 << " ";
            else flag = true;
            of7 << v;
        }
        of7 << endl;

        /*W*/
        for(int k = 0; k < 10; k++){
            if(k == 0)of7 << "1";
            else of7 << " 11";
        }
        of7 << endl;
    }

    /*L*/
    of7 << "8" << endl;

    /*S*/
    for(int j = 0; j < 8; j++){
        of7 << (char)('A' + rnd.next(0, 6));
    }
    of7 << endl;
    of7.close();

    /*分母が最大になるケース2*/
    ofstream of8(format("01_hand_07.in").c_str());
    /*N*/
    N = rnd.next(MIN_N, _MAX_N);
    of8 << N << endl;
    /*X*/
    for(int j = 0; j < N; j++){
        if(j != 0)of8 << " ";
        of8 << (char)('A' + rnd.next(0, 6));
    }
    of8 << endl;

    for(int j = 0; j < N; j++){
        /*M*/
        of8 << "8" << endl;

        /*V*/
        set<int> vset;
        while(vset.size() < 8){
            vset.insert(rnd.next(1, N));
        }
        bool flag = false;
        for(auto v : vset){
            if(flag)of8 << " ";
            else flag = true;
            of8 << v;
        }
        of8 << endl;

        /*W*/
        for(int k = 0; k < 8; k++){
            if(k == 0)of8 << "9";
            else of8 << " 13";
        }
        of8 << endl;
    }

    /*L*/
    of8 << "8" << endl;

    /*S*/
    for(int j = 0; j < 8; j++){
        of8 << (char)('A' + rnd.next(0, 6));
    }
    of8 << endl;
    of8.close();

    /*約分が必要になるケース1*/
    ofstream of9(format("01_hand_08.in").c_str());
    /*N*/
    N = rnd.next(MIN_N, _MAX_N);
    of9 << N << endl;
    /*X*/
    for(int j = 0; j < N; j++){
        if(j != 0)of9 << " ";
        of9 << (char)('A' + rnd.next(0, 6));
    }
    of9 << endl;

    for(int j = 0; j < N; j++){
        /*M*/
        of9 << "10" << endl;

        /*V*/
        set<int> vset;
        while(vset.size() < 10){
            vset.insert(rnd.next(1, N));
        }
        bool flag = false;
        for(auto v : vset){
            if(flag)of9 << " ";
            else flag = true;
            of9 << v;
        }
        of9 << endl;

        /*W*/
        for(int k = 0; k < 10; k++){
            if(k == 0)of9 << "10";
            else of9 << " 10";
        }
        of9 << endl;
    }

    /*L*/
    of9 << "8" << endl;

    /*S*/
    for(int j = 0; j < 8; j++){
        of9 << (char)('A' + rnd.next(0, 6));
    }
    of9 << endl;
    of9.close();

    /*約分が必要になるケース2*/
    ofstream of10(format("01_hand_09.in").c_str());
    /*N*/
    N = rnd.next(MIN_N, _MAX_N);
    of10 << N << endl;
    /*X*/
    for(int j = 0; j < N; j++){
        if(j != 0)of10 << " ";
        of10 << (char)('A' + rnd.next(0, 6));
    }
    of10 << endl;

    for(int j = 0; j < N; j++){
        /*M*/
        of10 << "9" << endl;

        /*V*/
        set<int> vset;
        while(vset.size() < 9){
            vset.insert(rnd.next(1, N));
        }
        bool flag = false;
        for(auto v : vset){
            if(flag)of10 << " ";
            else flag = true;
            of10 << v;
        }
        of10 << endl;

        /*W*/
        for(int k = 0; k < 9; k++){
            if(k == 0)of10 << "4";
            else of10 << " 12";
        }
        of10 << endl;
    }

    /*L*/
    of10 << "8" << endl;

    /*S*/
    for(int j = 0; j < 8; j++){
        of10 << (char)('A' + rnd.next(0, 6));
    }
    of10 << endl;
    of10.close();
}

void makeRandomTestcaseEasy(){
    for(int i = 0; i < 10; i++){
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
            int M = min(10, min(m - mPrev, N));
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
        int MAX_L_EASY = 4;
        int L = rnd.next(MIN_L, MAX_L_EASY);
        of << L << endl;
        for(int j = 0; j < L; j++){
            of << (char)('A' + rnd.next(0, 6));
        }
        of << endl;
        of.close();
    }
    //最大ケース
    ofstream of2(format("02_max_01.in").c_str());
    /*N*/
    int N = MAX_N / 10;
    of2 << N << endl;
    /*X*/
    for(int i = 0; i < N; i++){
        if(i != 0)of2 << " ";
        of2 << 'A';
    } 
    of2 << endl;

    for(int i = 0; i < N; i++){
        /*Mi*/
        of2 << "10" << endl;
        /*V*/
        set<int> vset;
        while(vset.size() < 10){
            vset.insert(rnd.next(1, N));
        }
        bool flag = false;
        for(auto v : vset){
            if(flag)of2 << " ";
            else flag = true;
            of2 << v;
        }
        of2 << endl;
        /*W*/
        for(int j = 0; j < 10; j++){
            if(j != 0)of2 << " ";
            of2 << "10";
        }
        of2 << endl;
    }
    /*S*/
    of2 << "4" << endl;
    of2 << "AAAA" << endl;
    of2.close();
}

void makeRandomTestcase(){
    //for(int i = 0; i < 20; i++){
    for(int i = 0; i < 10; i++){
        ofstream of(format("03_random_%02d.in", i + 1).c_str());
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
            int M = min(100, min(m - mPrev, N));
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
        of << L << endl;
        for(int j = 0; j < L; j++){
            of << (char)('A' + rnd.next(0, 6));
        }
        of << endl;
        of.close();
    }
}

/*分岐が多いテストケース*/
void makeRandomTestcase2(){
    //for(int i = 0; i < 20; i++){
    for(int i = 10; i < 20; i++){
        ofstream of(format("03_random_%02d.in", i + 1).c_str());
        /*N*/
        int MAX_N_ = 1000;
        int N = rnd.next(MIN_N, MAX_N_);
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
            int M = min(100, min(m - mPrev, N));
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
        of << L << endl;
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
    of << L << endl;
    for(int j = 0; j < L; j++){
        of << (char)('A' + rnd.next(0, 6));
    }
    of << endl;
    of.close();  

    /*dfsだとTLEする, N = 1000でThe sum of Mi = 100*/
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
    of2 << "8" << endl;
    of2 << "AAAAAAAA" << endl;
    of2.close();
}

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    //サンプル
    makeSampleTestcase();
    //手動で作成したケース(要ります？)
    makeHandTestcase();
    //部分点
    makeRandomTestcaseEasy();
    //ランダム
    makeRandomTestcase();
    //ランダム
    makeRandomTestcase2();
    //最大ケース
    makeMaxTestcase();
}