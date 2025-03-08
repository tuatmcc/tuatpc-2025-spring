
/**
 * @brief テンプレート
 * @docs docs/template.md
 */

// #pragma GCC target("avx2")
// #pragma GCC optimize("O3")
// #pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using ull = unsigned long long;
using vl = vector<ll>;
using vvl = vector<vl>;
using vvvl = vector<vvl>;
using pl = pair<ll, ll>;
using vp = vector<pl>;
using vvp = vector<vp>;
using vs = vector<string>;
using vvs = vector<vs>;
using vb = vector<bool>;
using vvb = vector<vb>;
using vvvb = vector<vvb>;
using vd = vector<double>;
using vvd = vector<vd>;
using vvvd = vector<vvd>;

#define _overload3(_1, _2, _3, name, ...) name
#define _rep(i, n) repi(i, 0, n)
#define repi(i, a, b) for(ll i = ll(a); i < ll(b); ++i)
#define rep(...) _overload3(__VA_ARGS__, repi, _rep, )(__VA_ARGS__)
#define all(x) std::begin(x), std::end(x)

constexpr ll inf = 0x1fffffffffffffffLL; // 2.3 * 10^18

template <class T, class U>
istream &operator>>(istream &is, pair<T, U> &p) {
    is >> p.first >> p.second;
    return is;
}

template <class T, class U>
ostream &operator<<(ostream &os, pair<T, U> &p) {
    os << p.first << " " << p.second;
    return os;
}

template <class T>
istream &operator>>(istream &is, vector<T> &v) {
    for(auto &x : v) {
        is >> x;
    }
    return is;
}

template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
    for(int i = 0; i < (int)v.size(); i++) {
        if(i != (int)v.size() - 1)
            os << v[i] << " ";
        else
            os << v[i];
    }
    return os;
}

template <typename T, typename... Args>
auto vec(T x, int arg, Args... args) {
    if constexpr(sizeof...(args) == 0)
        return vector<T>(arg, x);
    else
        return vector(arg, vec<T>(x, args...));
}

template <class T>
bool chmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}
template <class T>
bool chmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
}

constexpr ll bit(ll x) {
    return 1LL << x;
}
constexpr ll msk(ll x) {
    return (1LL << x) - 1;
}
constexpr bool stand(ll x, int i) {
    return x & bit(i);
}

struct IoSetup {
    IoSetup() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
        cerr << fixed << setprecision(10);
    }
} iosetup;

/**
 * @brief Modint
 * @cite https://nyaannyaan.github.io/library/modint/modint.hpp
 */

template <uint32_t mod>
struct LazyMontgomeryModInt {
    using mint = LazyMontgomeryModInt;
    using i32 = int32_t;
    using u32 = uint32_t;
    using u64 = uint64_t;

    static constexpr u32 get_r() {
        u32 ret = mod;
        for(i32 i = 0; i < 4; ++i)
            ret *= 2 - mod * ret;
        return ret;
    }

    static constexpr u32 r = get_r();
    static constexpr u32 n2 = -u64(mod) % mod;
    static_assert(mod < (1 << 30), "invalid, mod >= 2 ^ 30");
    static_assert((mod & 1) == 1, "invalid, mod % 2 == 0");
    static_assert(r * mod == 1, "this code has bugs.");

    u32 a;

    constexpr LazyMontgomeryModInt()
        : a(0) {}
    constexpr LazyMontgomeryModInt(const int64_t &b)
        : a(reduce(u64(b % mod + mod) * n2)){};

    static constexpr u32 reduce(const u64 &b) {
        return (b + u64(u32(b) * u32(-r)) * mod) >> 32;
    }

    constexpr mint &operator+=(const mint &b) {
        if(i32(a += b.a - 2 * mod) < 0) a += 2 * mod;
        return *this;
    }

    constexpr mint &operator-=(const mint &b) {
        if(i32(a -= b.a) < 0) a += 2 * mod;
        return *this;
    }

    constexpr mint &operator*=(const mint &b) {
        a = reduce(u64(a) * b.a);
        return *this;
    }

    constexpr mint &operator/=(const mint &b) {
        *this *= b.inverse();
        return *this;
    }

    constexpr mint operator+(const mint &b) const { return mint(*this) += b; }
    constexpr mint operator-(const mint &b) const { return mint(*this) -= b; }
    constexpr mint operator*(const mint &b) const { return mint(*this) *= b; }
    constexpr mint operator/(const mint &b) const { return mint(*this) /= b; }
    constexpr bool operator==(const mint &b) const {
        return (a >= mod ? a - mod : a) == (b.a >= mod ? b.a - mod : b.a);
    }
    constexpr bool operator!=(const mint &b) const {
        return (a >= mod ? a - mod : a) != (b.a >= mod ? b.a - mod : b.a);
    }
    constexpr mint operator-() const { return mint() - mint(*this); }
    constexpr mint operator+() const { return mint(*this); }

    constexpr mint pow(u64 n) const {
        mint ret(1), mul(*this);
        while(n > 0) {
            if(n & 1) ret *= mul;
            mul *= mul;
            n >>= 1;
        }
        return ret;
    }

    constexpr mint inverse() const {
        int x = get(), y = mod, u = 1, v = 0, t = 0, tmp = 0;
        while(y > 0) {
            t = x / y;
            x -= t * y, u -= t * v;
            tmp = x, x = y, y = tmp;
            tmp = u, u = v, v = tmp;
        }
        return mint{u};
    }

    friend ostream &operator<<(ostream &os, const mint &b) {
        return os << b.get();
    }

    friend istream &operator>>(istream &is, mint &b) {
        int64_t t;
        is >> t;
        b = LazyMontgomeryModInt<mod>(t);
        return (is);
    }

    constexpr u32 get() const {
        u32 ret = reduce(a);
        return ret >= mod ? ret - mod : ret;
    }

    static constexpr u32 get_mod() { return mod; }
};

constexpr long long mod998 = 998244353;
constexpr long long mod107 = 1000000007;
using mint998 = LazyMontgomeryModInt<mod998>;
using mint107 = LazyMontgomeryModInt<mod107>;

#define vm vector<mint>
#define vvm vector<vm>
#define vvvm vector<vvm>

using mint = mint998;

ll N;
vs S;

using Result = pair<mint, int>;

Result parallel(int y, int l);
mint serial(int y, int l, int r);

mint circuit(){
    assert(S[0].substr(0, 4) == "o---");
    assert(S[0].substr(S[0].size() - 4, 4) == "---o");
    return serial(0, 4, S[0].size() - 4);
}

Result resistance(int y, int x){
    assert(S[y].substr(x, 6) == "^v^v^v");
    return Result(mint(1), x + 6);
}

bool is_resistance(int y, int x){
    return S[y].substr(x, 6) == "^v^v^v";
}

bool is_parallel(int y, int x){
    return S[y][x] == '+' || S[y][x] == '^';
}

pair<int, int> find_parallel_size(int y, int l){
    assert(S[y][l] == '+');
    int height = 0;
    while(y + height < N && S[y + height][l] != ' '){
        height++;
    }
    assert(S[y + height - 1][l] == '+');
    int width = 0;
    while(l + width < S[y + height - 1].size() && S[y + height - 1][l + width] != ' '){
        width++;
    }
    assert(S[y + height - 1][l + width - 1] == '+');
    return {height, width};
}

pair<mint, int> parallel(int y, int l){
    if(is_resistance(y, l)){
        Result res = resistance(y, l);
        return res;
    }
    auto [height, width] = find_parallel_size(y, l);
    int r = l + width;
    mint rev_sum = 0;
    rep(i, y, y + height){
        if(S[i][l] == '+'){
            rev_sum += serial(i, l + 4, r).inverse();
        }
    }
    return Result(rev_sum.inverse(), r);
}

mint serial(int y, int l, int r){
    if(l + 1 >= r || S[y][l] == '-') return mint(0);
    auto [R, nx] = parallel(y, l);
    if(nx == r) return R;
    return R + serial(y, nx + 3, r);
}

void solve(){
    cin >> N;
    cin.ignore();
    S.resize(N);
    rep(i, N){
        getline(cin, S[i]);
    }
    cout << circuit() << endl;
}

int main() {
    int q;
    std::cin >> q;
    while (q--) {
        solve();
    }
}