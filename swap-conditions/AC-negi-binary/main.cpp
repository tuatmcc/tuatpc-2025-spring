# include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;

int judge(vl a, ll s, int x, int y){
    ll tokoko = a[x] + 4 * s;
    int rt = 1;
    for(int i = 0; i < 4; i++){
        if(i == x) continue;
        ll fr = a[i];
        if(i == y) fr -= 2 * s;
        else fr -= s;
        if(fr > tokoko){
            rt++;
        }else if(fr == tokoko){
            if(i < x) rt++;
        }
    }
    return rt;
}


int main() {
    int t;
    cin >> t;
    for(; t > 0; t--){
        int x, y, r;
        vl a(4);
        cin >> x >> y >> r;
        x--;
        y--;
        for(int i = 0; i < 4; i++) cin >> a[i];
        if(judge(a, 0, x, y) < r){
            cout << -1 << endl;
            continue;
        }
        ll le = 0, ri = 5e17;
        while(le != ri){
            ll c = (le + ri) / 2;
            if(judge(a, c, x, y) <= r){
                ri = c;
            }else{
                le = c + 1;
            }
        }
        if(judge(a, le, x, y) == r){
            cout << le << endl;
        }else{
            cout << -1 << endl;
        }
    }
}