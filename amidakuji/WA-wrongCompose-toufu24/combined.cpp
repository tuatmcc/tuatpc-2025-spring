#include <bits/stdc++.h>

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>


#ifdef _MSC_VER
#include <intrin.h>
#endif

#if __cplusplus >= 202002L
#include <bit>
#endif

namespace atcoder {

namespace internal {

#if __cplusplus >= 202002L

using std::bit_ceil;

#else

unsigned int bit_ceil(unsigned int n) {
    unsigned int x = 1;
    while (x < (unsigned int)(n)) x *= 2;
    return x;
}

#endif

int countr_zero(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}

constexpr int countr_zero_constexpr(unsigned int n) {
    int x = 0;
    while (!(n & (1 << x))) x++;
    return x;
}

}  // namespace internal

}  // namespace atcoder


namespace atcoder {

#if __cplusplus >= 201703L

template <class S, auto op, auto e> struct segtree {
    static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                  "op must work as S(S, S)");
    static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                  "e must work as S()");

#else

template <class S, S (*op)(S, S), S (*e)()> struct segtree {

#endif

  public:
    segtree() : segtree(0) {}
    explicit segtree(int n) : segtree(std::vector<S>(n, e())) {}
    explicit segtree(const std::vector<S>& v) : _n(int(v.size())) {
        size = (int)internal::bit_ceil((unsigned int)(_n));
        log = internal::countr_zero((unsigned int)size);
        d = std::vector<S>(2 * size, e());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) const {
        assert(0 <= p && p < _n);
        return d[p + size];
    }

    S prod(int l, int r) const {
        assert(0 <= l && l <= r && r <= _n);
        S sml = e(), smr = e();
        l += size;
        r += size;

        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }
        return op(sml, smr);
    }

    S all_prod() const { return d[1]; }

    template <bool (*f)(S)> int max_right(int l) const {
        return max_right(l, [](S x) { return f(x); });
    }
    template <class F> int max_right(int l, F f) const {
        assert(0 <= l && l <= _n);
        assert(f(e()));
        if (l == _n) return _n;
        l += size;
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(sm, d[l]))) {
                while (l < size) {
                    l = (2 * l);
                    if (f(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*f)(S)> int min_left(int r) const {
        return min_left(r, [](S x) { return f(x); });
    }
    template <class F> int min_left(int r, F f) const {
        assert(0 <= r && r <= _n);
        assert(f(e()));
        if (r == 0) return 0;
        r += size;
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], sm))) {
                while (r < size) {
                    r = (2 * r + 1);
                    if (f(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
};

}  // namespace atcoder

using namespace std;
using namespace atcoder;

/*
op, e ともに$O(N)$である．

- セグ木構築 : $O(NM)$
- クエリ処理 :
    - クエリ回数 : $Q$
    - クエリ1 : $O(N \log M)$
    - クエリ2 : $O(N \log M)$
    - クエリ3 : $O(N)$
    - 合計 : $O(QN \log M)$
- 全体 : $O(NM + QN \log M)$
*/

int N, M;

// セグ木に乗せる置換
struct Perm {
    vector<int> perm;

    // 恒等置換で初期化
    Perm() : perm(N) {
        for (int i = 0; i < N; i++) {
            perm[i] = i;
        }
    }

    // 置換の合成
    Perm compose(const Perm &other) const {
        Perm result;
        for (int i = 0; i < perm.size(); i++) {
            result.perm[i] = perm[other.perm[i]]; // ここを逆にしてWA化
        }
        return result;
    }
};

// 置換の合成を演算とする
Perm op(Perm a, Perm b) {
    return a.compose(b);
}

// 恒等置換が単位元
Perm e() {
    return Perm();
}

int main() {
    cin >> N >> M;

    segtree<Perm, op, e> seg(M);

    int Q;
    cin >> Q;

    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y;
            cin >> x >> y;
            x--, y--; // 0-based index
            // y行目の置換を更新
            Perm p = seg.get(y);
            // x番目とx+1番目の要素を入れ替える
            swap(p.perm[x], p.perm[x + 1]);
            seg.set(y, p);
        } else if (t == 2) {
            int x, y;
            cin >> x >> y;
            x--, y--; // 0-based index
            // y行目の置換を更新
            Perm p = seg.get(y);
            // x番目とx+1番目の要素を入れ替える
            swap(p.perm[x], p.perm[x + 1]);
            seg.set(y, p);
        } else if (t == 3) {
            int s;
            cin >> s;
            s--; // 0-based index
            // 全行の置換を合成することであみだくじの結果を求める
            Perm result_perm = seg.all_prod();
            // s行目の移動先が答え
            int result = result_perm.perm[s];
            cout << (result + 1) << endl; // 1-based index
        }
    }
}