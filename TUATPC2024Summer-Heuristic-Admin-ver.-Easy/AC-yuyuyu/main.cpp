#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main()
{
    int n;
    cin >> n;
    vector<ll> a(n), b(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
        cin >> b[i];

    if (n <= 2)
    {
        cout << "Yes" << endl;
        return 0;
    }

    ll s = 0;
    ll l = 0;
    for (int i = 0; i < n; i++)
    {
        l = max({l, a[i], b[i]});
        s += max(a[i], b[i]);
    }

    if (l < 1600 || s < 4200)
    {
        cout << "Yes" << endl;
    }
    else
    {
        cout << "No" << endl;
    }

    return 0;
}