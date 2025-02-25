# include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vl = vector<ll>;




int main() {
    int t;
    cin >> t;
    for(; t > 0; t--){
        int x, y, r;
        vl a(4), delta(4), s;
        cin >> x >> y >> r;
        x--;
        y--;
        r = 4 - r;//下にr人いれば良い
        for(int i = 0; i < 4; i++){
            cin >> a[i];
        }
        for(int i = 0; i < 4; i++){
            delta[i] = a[i] - a[x];
            if(delta[i] < 0){
                r--;//r人抜かせばよい
                continue;
            }
            if(i == x) continue;
            if(i < x) delta[i]++;
            if(i == y) s.push_back((delta[i] + 1) / 6 + 1);
            else s.push_back((delta[i] + 1) / 5 + 1);
        }
        sort(s.begin(), s.end());//一人抜かすために必要なsの値
        if(r < 0){
            cout << -1 << endl;
        }
        if(r == 0){
            cout << 0 << endl;
            continue;
        }
        if(r < 0){
            cout << -1 << endl;
            continue;
        }
        ll rt = s[r - 1];
        if(r < s.size() && rt == s[r]){
            cout << -1 << endl;
            continue;
        }
        cout << rt << endl;
    }
}