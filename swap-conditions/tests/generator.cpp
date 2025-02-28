#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;
using ll = long long;
const int MIN_XYR = 1;
const int MAX_XYR = 4;
const ll MIN_A = -1e18;
const ll MAX_A = 1e18;
const ll MIN_T = 1;
const ll MAX_T = 1e4;


void vec_fileout(ofstream &f, vector<ll> x){
    int n = x.size();
    for(int i = 0; i < n; i++){
        f << x[i];
        if(i == n - 1) f << endl;
        else f << " ";
    }
    return;
}

void perm_add(vector<vector<ll>> &rt, vector<ll> p, set<ll> left, int s){
    if(s == 0){
        rt.push_back(p);
        return;
    }
    for(auto &z : left){
        auto l_copy = left;
        auto p_copy = p;
        p_copy.push_back(z);
        l_copy.erase(z);
        perm_add(rt, p_copy, l_copy, s - 1);
    }
    return;
}

vector<vector<ll>> perm(int k){
    vector<vector<ll>> rt;
    vector<ll> p;
    set<ll> l;
    for(int i = 0; i < k; i++) l.insert(i);
    perm_add(rt, p, l, k);
    return rt;
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
    
    //completely random
    for(int f_ct = 0; f_ct < 5; f_ct++){
        ofstream of(format("10_random_%02d.in", f_ct+1).c_str());
        ll t1 = rnd.next(MIN_T, MAX_T / 2);
        ll t2 = rnd.next((ll)0, MAX_T - t1);
        of << t1 + t2 << endl;
        for(int i = 0; i < t1; i++){
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
        //case which tokoko needs huge point to swap
        for(int i = 0; i < t2; i++){
            vector<int> v = {1, 2, 3, 4};
            int u = rnd.next(0, 3);
            xyr[0] = v[u];
            v.erase(v.begin() + u);
            u = rnd.next(0, 2);
            xyr[1] = v[u];
            xyr[2] = rnd.next(MIN_XYR, MAX_XYR);
            vec_fileout(of, xyr);
            for(int ii = 0; ii < 4; ii++){
                if(ii == xyr[0] - 1) a[ii] = rnd.next((ll)-1e18, (ll)-95e16);
                else a[ii] = rnd.next((ll)95e16, (ll)1e18);
            }
            vec_fileout(of, a);
        }
        of.close();
    }
    //set A randomly, then make all case of {x, y, r}
    auto p = perm(4);
    for(int f_ct = 0; f_ct < 5; f_ct++){
        ofstream of(format("10_random_%02d.in", f_ct+6).c_str());
        ll t = rnd.next(MIN_T, MAX_T / 1152);
        of << t * 1152 << endl;
        for(int i = 0; i < t; i++){
            for(int ii = 0; ii < 4; ii++) a[ii] = rnd.next(MIN_A, MAX_A);
            for(xyr[0] = 1; xyr[0] <= 4; xyr[0]++){
                for(xyr[1] = 1; xyr[1] <= 4; xyr[1]++){
                    if(xyr[0] == xyr[1]) continue;
                    for(xyr[2] = 1; xyr[2] <= 4; xyr[2]++){
                        for(auto &z : p){
                            vector<ll> a2(4);
                            for(int ii = 0; ii < 4; ii++){
                                a2[ii] = a[z[ii]];
                            }
                            vec_fileout(of, xyr);
                            vec_fileout(of, a2);
                        }
                    }
                }
            }
        }
        of.close();
    }


    //tokoko and friends have same points if tokoko select the S.
    for(int f_ct = 0; f_ct < 3; f_ct++){
        ofstream of(format("10_random_%02d.in", f_ct+11).c_str());
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
    for(int f_ct = 0; f_ct < 3; f_ct++){
        ofstream of(format("10_random_%02d.in", f_ct+14).c_str());
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


    ofstream of(format("20_max_01.in").c_str());
    int t = MAX_T;
    of << t << endl;
    for(int i = 0; i < t; i++){
        vector<int> v = {1, 2, 3, 4};
        int u = rnd.next(0, 3);
        xyr[0] = v[u];
        v.erase(v.begin() + u);
        u = rnd.next(0, 2);
        xyr[1] = v[u];
        xyr[2] = rnd.next(MIN_XYR, MAX_XYR);
        if(i == 0){
            for(int ii = 0; ii < 4; ii++){
                a[ii] = MAX_A;
                if(rnd.next(0, 1) == 0) a[ii] *= -1;
            }
        }else{
            for(int ii = 0; ii < 4; ii++) a[ii] = rnd.next(MIN_A, MAX_A);
        }
        vec_fileout(of, xyr);
        vec_fileout(of, a);
    }
    of.close();
    return 0;
}