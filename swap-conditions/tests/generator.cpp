#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MIN_XYR = 1;
const int MAX_XYR = 4;
const ll MIN_A = -1e18;
const ll MAX_A = 1e18;
const ll MIN_T = 1;
const ll MAX_T = 3e4;


void vec_fileout(ofstream &f, vector<ll> x){
    int n = x.size();
    for(int i = 0; i < n; i++){
        f << x[i];
        if(i == n - 1) f << endl;
        else f << " ";
    }
    return;
}

int main(int argc, char* argv[]){
    //sample
    vector<ll> xyr = {1, 4, 1}, a = {800, 1000, 2000, 4000};
    registerGen(argc, argv, 1);
    ofstream sample1(format("00_sample_01.in").c_str());
    sample1 << "4\n";
    for(int i = 0; i < 4; i++){
        vec_fileout(sample1, xyr);
        vec_fileout(sample1, a);
        xyr[2]++;
    }
    sample1.close();
    ofstream sample2(format("00_sample_02.in").c_str());
    sample2 << "8\n";
    xyr = {3, 2, 1}, a = vector<ll>(4, 25000);
    for(int i = 0; i < 4; i++){
        vec_fileout(sample2, xyr);
        vec_fileout(sample2, a);
        xyr[2]++;
    }
    xyr = {2, 4, 1}, a = {17000, 12000, 21000, 60000};
    for(int i = 0; i < 4; i++){
        vec_fileout(sample2, xyr);
        vec_fileout(sample2, a);
        xyr[2]++;
    }
    sample2.close();
    
    //all cases between -6 and 6. this for loop limits the scope of of.
    for(int f_ct = 0; f_ct < 1; f_ct++){
        int file_no = 0, file_l = 0;
        
        a = vector<ll>(4, -6);
        vector<vector<ll>> rt;
        for(a[0] = -6; a[0] <= 6; a[0]++){
            for(a[1] = a[0]; a[1] <= 6; a[1]++){
                for(a[2] = a[1]; a[2] <= 6; a[2]++){
                    for(a[3] = a[2]; a[3] <= 6; a[3]++){
                        vector<ll> a_cp = a;
                        shuffle(a_cp.begin(), a_cp.end());
                        for(xyr[0] = 1; xyr[0] <= 4; xyr[0]++){
                            for(xyr[1] = 1; xyr[1] <= 4; xyr[1]++){
                                if(xyr[0] == xyr[1]) continue;
                                for(xyr[2] = 1; xyr[2] <= 4; xyr[2]++){
                                    rt.push_back(xyr);
                                    rt.push_back(a_cp);
                                    file_l++;
                                    if(file_l == MAX_T){
                                        ofstream of(format("01_case_%02d.in", file_no+1).c_str());
                                        of << file_l << endl;
                                        for(auto &z: rt) vec_fileout(of, z);
                                        rt.clear();
                                        of.close();
                                        file_l = 0;
                                        file_no++;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        ofstream of(format("01_case_%02d.in", file_no+1).c_str());
        of << file_l << endl;
        for(auto &z: rt) vec_fileout(of, z);
        of.close();
    }


    //completely random
    for(int f_ct = 0; f_ct < 2; f_ct++){
        ofstream of(format("02_random_%02d.in", f_ct+1).c_str());
        ll t = rnd.next(MIN_T, MAX_T);
        of << t << endl;
        for(int i = 0; i < t; i++){
            vector<int> v = {1, 2, 3, 4};
            int u = rnd.next(0, 3);
            xyr[0] = v[u];
            v.erase(v.begin() + u);
            u = rnd.next(0, 2);
            xyr[1] = v[u];
            xyr[2] = rnd.next(MIN_XYR, MAX_XYR);
            vec_fileout(of, xyr);
            for(int ii = 0; ii < 4; ii++) a[ii] = rnd.next(MIN_A, MAX_A);
            vec_fileout(of, a);
        }
        of.close();
    }
    //set A randomly, then make all case of {x, y, r}
    for(int f_ct = 0; f_ct < 4; f_ct++){
        ofstream of(format("02_random_%02d.in", f_ct+3).c_str());
        ll t = rnd.next(MIN_T, MAX_T / 48);
        of << t * 48 << endl;
        for(int i = 0; i < t; i++){
            for(int ii = 0; ii < 4; ii++) a[ii] = rnd.next(MIN_A, MAX_A);
            for(xyr[0] = 1; xyr[0] <= 4; xyr[0]++){
                for(xyr[1] = 1; xyr[1] <= 4; xyr[1]++){
                    if(xyr[0] == xyr[1]) continue;
                    for(xyr[2] = 1; xyr[2] <= 4; xyr[2]++){
                        vec_fileout(of, xyr);
                        vec_fileout(of, a);
                    }
                }
            }
        }
        of.close();
    }


    //tokoko and friends have same points if tokoko select the S.
    for(int f_ct = 0; f_ct < 3; f_ct++){
        ofstream of(format("02_random_%02d.in", f_ct+7).c_str());
        ll t = rnd.next(MIN_T, MAX_T);
        of << t << endl;
        for(int i = 0; i < t; i++){
            vector<int> v = {1, 2, 3, 4};
            int u = rnd.next(0, 3);
            xyr[0] = v[u];
            v.erase(v.begin() + u);
            u = rnd.next(0, 2);
            xyr[1] = v[u];
            xyr[2] = rnd.next(MIN_XYR, MAX_XYR);
            ll tokoko = rnd.next(MIN_A, (ll)2e17);
            ll steal = rnd.next((ll)0, (ll)4e17);
            for(int ii = 0; ii < 4; ii++){
                if(ii == xyr[0] - 1) a[ii] = tokoko;
                else if(ii == xyr[2] - 1) a[ii] = tokoko + 2 * steal;
                else a[ii] = tokoko + steal;
            }
            vec_fileout(of, xyr);
            vec_fileout(of, a);
        }
        of.close();
    }

    //some friends are tie right now.
    for(int f_ct = 0; f_ct < 2; f_ct++){
        ofstream of(format("02_random_%02d.in", f_ct+10).c_str());
        ll t = rnd.next(MIN_T, MAX_T);
        of << t << endl;
        for(int i = 0; i < t; i++){
            vector<int> v = {1, 2, 3, 4};
            int u = rnd.next(0, 3);
            xyr[0] = v[u];
            v.erase(v.begin() + u);
            u = rnd.next(0, 2);
            xyr[1] = v[u];
            xyr[2] = rnd.next(MIN_XYR, MAX_XYR);
            int rd = rnd.next(1, 3);
            vector<ll> a2(rd);
            for(int ii = 0; ii < rd; ii++) a2[ii] = rnd.next(MIN_A, MAX_A);
            for(int ii = 0; ii < 4; ii++){
                a[ii] = a2[rnd.next(0, rd - 1)];
            }
            vec_fileout(of, xyr);
            vec_fileout(of, a);
        }
        of.close();
    }

    //maximize abs of A
    ofstream of(format("03_max_01.in").c_str());
    int t = 0;
    vector<vector<ll>> rt;
    for(int i = 0; i < (1 << 4); i++){
        int bi = i;
        for(int j = 0; j < 4; j++){
            if(bi & 1) a[j] = MIN_A;
            else a[j] = MAX_A;
            bi >>= 1;
        }
        for(xyr[0] = 1; xyr[0] <= 4; xyr[0]++){
            for(xyr[1] = 1; xyr[1] <= 4; xyr[1]++){
                if(xyr[0] == xyr[1]) continue;
                for(xyr[2] = 1; xyr[2] <= 4; xyr[2]++){
                    rt.push_back(xyr);
                    rt.push_back(a);
                    t++;
                }
            }
        }
    }
    of << t << endl;
    for(auto &z : rt) vec_fileout(of, z);
    of.close();
    return 0;
}