#include "testlib.h"
#include<bits/stdc++.h>
using namespace std;

using ll = long long;
using vl = vector<ll>;
const int MIN_K = 1;
const int MAX_K = 4;
const ll MIN_A = -1e18;
const ll MAX_A = 1e18;
const ll MIN_S = 0;
const ll MAX_S = 1e18;

int judge(vl a, ll s, int k, int j){
    vector<pair<ll, ll>> p(4);
    for(int i = 0; i < 4; i++){
        if((i + 1) == k) p[i] = make_pair(a[i] + 4 * s, 4 - (i + 1));
        else if((i + 1) == j) p[i] = make_pair(a[i] - 2 * s, 4 - (i + 1));
        else p[i] = make_pair(a[i] - s, 4 - (i + 1));
    }
    sort(p.begin(), p.end());
    reverse(p.begin(), p.end());
    for(int i = 0; i < 4; i++){
        if(p[i].second == 4 - k) return (i + 1);
    }
    return 0;
}


int main(int argc, char* argv[]){
    registerTestlibCmd(argc, argv);
    vl ac_kj;
    ac_kj.push_back(inf.readInt(MIN_K, MAX_K, "K"));
    inf.readSpace();
    vl ac_a;
    for(int i = 0; i < 4; i++){
        ac_a.push_back(inf.readLong(MIN_A, MAX_A, "A"));
        if(i == 3)inf.readEoln();
        else inf.readSpace();
    }
    for(int i = 1; i < 4; i++){
        ac_kj.push_back(inf.readInt(MIN_K, MAX_K, "J"));
        if(i == 3)inf.readEoln();
        else inf.readSpace();
    }

    for(int i = 0; i < 4; i++){
        ll res_s = ouf.readLong(MIN_S, MAX_S, "S");
        if(i == 3)ouf.readEoln();
        else inf.readSpace();

        if(res_s == -1){
            //不可能をどう判断するか。悪魔の証明。
        }else if(res_s == 0){
            if(judge(ac_a, res_s, ac_kj[0], ac_kj[3]) == i + 1){
                continue;
            }else{
                quitf(_wa, "wa");
            }
        }else{
            if(judge(ac_a, res_s, ac_kj[0], ac_kj[3]) == i + 1 && judge(ac_a, res_s - 1, ac_kj[0], ac_kj[3]) != i + 1){
                continue;
            }else{
                quitf(_wa, "wa");
            }
        }
    }
    quitf(_ok, "ok");
    return 0;
}