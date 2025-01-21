#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>
#include <algorithm>

#include <atcoder/segtree>

using namespace std;

struct Monoid {
    long long a, b, ab, ba, aba, bab, abab;
    Monoid()
        : a(0)
        , b(0)
        , ab(0)
        , ba(0)
        , aba(0)
        , bab(0)
        , abab(0)
    {
    }
};

Monoid e()
{
    return Monoid();
}

Monoid op(Monoid a, Monoid b)
{
    Monoid res;
    res.a = a.a + b.a;
    res.b = a.b + b.b;
    res.ab = a.ab + a.a * b.b + b.ab;
    res.ba = a.ba + a.b * b.a + b.ba;
    res.aba = a.aba + a.ab * b.a + a.a * b.ba + b.aba;
    res.bab = a.bab + a.ba * b.b + a.b * b.ab + b.bab;
    res.abab = a.abab + a.a * b.bab + a.ab * b.ab + a.aba * b.b + b.abab;
    return res;
};

int main()
{
    int N, Q;
    cin >> N >> Q;
    string S;
    cin >> S;
    const int M = 26;
    vector<vector<atcoder::segtree<Monoid, op, e>>> seg(M, vector<atcoder::segtree<Monoid, op, e>>(M));
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < M; j++) {
            if (i == j)
                continue;
            vector<Monoid> v(N);
            for (int k = 0; k < N; k++) {
                if (S[k] == 'a' + i)
                    v[k].a = 1;
                if (S[k] == 'a' + j)
                    v[k].b = 1;
            }
            seg[i][j] = atcoder::segtree<Monoid, op, e>(v);
        }
    }

    for (int i = 0; i < Q; i++) {
        int l, r;
        cin >> l >> r;
        l--;
        long long ans = 0;
        for (int j = 0; j < M; j++) {
            for (int k = 0; k < M; k++) {
                if (j == k)
                    continue;
                Monoid res = seg[j][k].prod(l, r);
                ans += res.abab;
            }
        }
        cout << ans << endl;
    }
}