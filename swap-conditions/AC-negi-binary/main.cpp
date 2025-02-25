# include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;

int judge(vl a, ll s, int x, int y){
    vector<pair<ll, ll>> p(4);
    for(int i = 0; i < 4; i++){
        if((i + 1) == x) p[i] = make_pair(a[i] + 4 * s, 4 - (i + 1));
        else if((i + 1) == y) p[i] = make_pair(a[i] - 2 * s, 4 - (i + 1));
        else p[i] = make_pair(a[i] - s, 4 - (i + 1));
    }
    sort(p.begin(), p.end());
    reverse(p.begin(), p.end());
    for(int i = 0; i < 4; i++){
        if(p[i].second == 4 - x) return (i + 1);
    }
    return 0;
}


int main() {
    int t;
    cin >> t;
    for(; t > 0; t--){
        int x, y, r;
        vl a(4);
        cin >> x >> y >> r;
        for(int i = 0; i < 4; i++) cin >> a[i];
        if(judge(a, 0, x, y) < r){
            cout << -1 << endl;
            continue;
        }
        ll le = 0, ri = 2e18;
        while(le != ri){
            ll c = (le + ri) / 2;
            if(judge(a, c, x, y) <= r){
                ri = c;
            }else{
                le = c + 1;
            }
        }
        if(judge(a, le, x, y) != r){
            cout << -1 << endl;
        }else{
            cout << le << endl;
        }
    }
}