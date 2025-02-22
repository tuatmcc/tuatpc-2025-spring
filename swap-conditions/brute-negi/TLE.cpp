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
    int x, y;
    vl a(4), r(4);
    cin >> x >> y;
    for(int i = 0; i < 4; i++) cin >> a[i];
    ll s = 2e18;//O(s) = 2e18 > 1e10
    for(int i = 1; i <= 4; i++){
        if(judge(a, 0, x, y) < i){
            r[i - 1] = -1;
            continue;
        }
        
        for(; judge(a, s, x, y) >= i; s--);
        if(judge(a, s + 1, x, y) != i){
            r[i - 1] = -1;
        }else{
            r[i - 1] = s + 1;
        }
    }
    for(int i = 0; i < 4; i++){
        cout << r[i] << endl;
    }
}