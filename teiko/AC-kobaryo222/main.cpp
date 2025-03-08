#include <bits/stdc++.h>

using namespace std;

template <class T>
bool chmin(T &a, const T &b) {
    return a > b ? a = b, true : false;
}
template <class T>
bool chmax(T &a, const T &b) {
    return a < b ? a = b, true : false;
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

constexpr long long mod = 998244353;
using mint = LazyMontgomeryModInt<mod>;

int N;
vector<string> S;

using Result = pair<mint, int>;

Result parallel(int y, int l);
mint serial(int y, int l, int r);

mint circuit(){
    return serial(0, "o---"s.size(), S[0].size() - "---o"s.size());
}

const string RESISTANCE = "^v^v^v";

Result resistance(int y, int x){
    return Result(mint(1), x + RESISTANCE.size());
}

pair<int, int> find_parallel_size(int y, int l){
    int height = 0;
    while(y + height < N && S[y + height][l] != ' '){
        height++;
    }
    int width = 0;
    while(l + width < S[y + height - 1].size() && S[y + height - 1][l + width] != ' '){
        width++;
    }
    return {height, width};
}

pair<mint, int> parallel(int y, int l){
    if(S[y].substr(l, RESISTANCE.size()) == RESISTANCE){
        Result res = resistance(y, l);
        return res;
    }
    auto [height, width] = find_parallel_size(y, l);
    int r = l + width;
    mint rev_sum = 0;
    for(int i = y; i < y + height; i++){
        if(S[i][l] == '+'){
            rev_sum += serial(i, l + "+---"s.size(), r).inverse();
        }
    }
    return Result(rev_sum.inverse(), r);
}

mint serial(int y, int l, int r){
    if(l + 1 >= r || S[y][l] == '-' || S[y][l] == ' ') return mint(0);
    auto [R, nx] = parallel(y, l);
    return R + serial(y, nx + "---"s.size(), r);
}

int solve(){
    cin >> N;
    cin.ignore();
    S.resize(N);
    int width = 0;
    for(int i = 0; i < N; i++){
        getline(cin, S[i]);
        chmax(width, (int)S[i].size());
        S[i].resize(width, ' ');
    }
    cout << circuit() << endl;
    return 0;
}

int main() {
    int q;
    std::cin >> q;
    while (q--) {
        solve();
    }
}