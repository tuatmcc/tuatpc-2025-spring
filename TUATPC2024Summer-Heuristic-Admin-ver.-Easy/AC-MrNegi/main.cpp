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
    ll s = 0, b = 0;
    for(int i = 0; i < n; i++){
        ll a, h;
        cin >> a >> h;
        s += max(a, h);
        b = max(b, a, h);
        if(b >= 1600 && s >= 4200){
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
    return 0;
}