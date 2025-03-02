# include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    int n;
    cin >> n;
    if(n <= 2){
        cout << "Yes" << endl;
        return 0;
    }
    vector<ll> a(n), b(n);
    ll s = 0, h = 0;
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < n; i++) cin >> b[i];
    for(int i = 0; i < n; i++){
        ll m = max(a[i], b[i]);
        h = max(h, m);
        s += m;
        if(h >= 1600 && s >= 4200){
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
    return 0;
}