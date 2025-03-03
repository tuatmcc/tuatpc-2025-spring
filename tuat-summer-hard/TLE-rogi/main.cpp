#line 2 "/Users/korogi/Desktop/cp-cpp/template.hpp"
#include <bits/stdc++.h>
using namespace std;

using i32 = int32_t;
using i64 = int64_t;
using i128 = __int128;
using u32 = unsigned int32_t;
using u64 = unsigned int64_t;
using u128 = unsigned __int128;
using f32 = double;
using f64 = long double;
using f128 = __float128;

#define DMP(x) cout << "[" << __LINE__ << "]" << " " << #x << ":" << " " << x << endl;

#define FOR1(n)          for(int _ =  0 , n_ = (n); _ < n_; _++)
#define FOR2(i, n)       for(int i =  0 , n_ = (n); i < n_; i++)
#define FOR3(i, s, t)    for(int i = (s), t_ = (t); i < t_; i++)
#define FOR4(i, s, t, d) for(int i = (s), t_ = (t), d_ = (d); i < t_; i += d_)
#define OVERLOAD4(a, b, c, d, e, ...) e
#define FOR(...) OVERLOAD4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)

#define REV1(n)          for(int _ = (n) - 1; _ >=  0 ; _--)
#define REV2(i, n)       for(int i = (n) - 1; i >=  0 ; i--)
#define REV3(i, s, t)    for(int i = (t) - 1, s_ = (s); i >= s_; i--)
#define REV4(i, s, t, d) for(int i = (t) - 1, s_ = (s), d_ = (d); i >= s_; i -= d_)
#define OVERLOAD3(a, b, c, d, ...) d
#define REV(...) OVERLOAD4(__VA_ARGS__, REV4, REV3, REV2, REV1)(__VA_ARGS__)

#define FOR_SUBSET(T, S) for(int S_ = (S), T = S_; T >= 0; T = (T == 0 ? -1 : (T - 1) & S_))

template < class T > using heap_max = priority_queue< T, vector< T >, less< T > >;
template < class T > using heap_min = priority_queue< T, vector< T >, greater< T >>;

template < class T, class U > bool chmin(T& a, const U& b) { return a > b ? a = b, 1 : 0; }
template < class T, class U > bool chmax(T& a, const U& b) { return a < b ? a = b, 1 : 0; }

i64 floor_div(const i64 n, const i64 d) { assert(d != 0); return n / d - ((n ^ d) <  0 && n % d != 0); }
i64  ceil_div(const i64 n, const i64 d) { assert(d != 0); return n / d + ((n ^ d) >= 0 && n % d != 0); }

template < class T, class F > T binary_search(T ok, T ng, F check) {
    while(abs(ok - ng) > 1) {
        T mid = (ok + ng) / 2;
        (check(mid) ? ok : ng) = mid;
    }
    return ok;
}
template < class T, class F > T binary_search_real(T ok, T ng, F check, int step = 100) {
    FOR(step) {
        T mid = (ok + ng) / 2;
        (check(mid) ? ok : ng) = mid;
    }
    return ok;
}

template < class T, class U > T accum(const vector< U >& a) { return accumulate(a.begin(), a.end(), T(0)); }
template < class T > pair< T, int > min(const vector< T >& a) { auto itr = min_element(a.begin(), a.end()); return {*itr, itr - a.begin()}; }
template < class T > pair< T, int > max(const vector< T >& a) { auto itr = max_element(a.begin(), a.end()); return {*itr, itr - a.begin()}; }
template < class T > void sort(vector< T >& a) { sort(a.begin(), a.end()); }
template < class T > void rsort(vector< T >& a) { sort(a.rbegin(), a.rend()); }
template < class T, class Cmp > void sort(vector< T >& a, Cmp cmp) { sort(a.begin(), a.end(), cmp); }
template < class T > int LB(vector< T >& a, T x) { return distance(a.begin(), lower_bound(a.begin(), a.end(), x)); }
template < class T > int UB(vector< T >& a, T x) { return distance(a.begin(), upper_bound(a.begin(), a.end(), x)); }
template < class T > void unique(vector< T >& a) { sort(a.begin(), a.end()); a.erase(unique(a.begin(), a.end()), a.end()); }
vector<int> iota(int n) { vector<int> a(n); iota(a.begin(), a.end(), 0); return a; }

namespace scan {
    struct x0 {
        template < class T > operator T() { T x; cin >> x; return x; }
    };
    struct x1 {
        int n; x1(int n) : n(n) {}
        template < class T > operator vector< T >() { vector< T > a(n); for(T& x : a) cin >> x; return a; }
    };
    struct x2 {
        int h, w; x2(int h, int w) : h(h), w(w) {}
        template < class T > operator vector< vector< T > >() { vector m(h, vector< T >(w)); for(vector< T >& a : m) for(T& x : a) cin >> x; return m; }
    };
    struct cppio { cppio() { cin.tie(0); ios::sync_with_stdio(0); } } cppio_instance;
}
scan::x0 in() { return scan::x0(); }
scan::x1 in(int n) { return scan::x1(n); }
scan::x2 in(int h, int w) { return scan::x2(h, w); }

template < class T > ostream& operator << (ostream& os, const vector< T > a) {
    const int n = a.size();
    FOR(i, n) { os << a[i]; if(i + 1 != n) os << ' '; }
    return os;
}
template < class T > int print_n(const vector< T > a) {
    for(T x : a) cout << x << '\n';
    return 0;
}
int print() { cout << '\n'; return 0; }
template < class Head, class... Tail > int print(Head&& h, Tail&&... t) {
    cout << h; if(sizeof...(Tail)) cout << ' ';
    return print(forward<Tail>(t)...);
}
namespace printer {
    void precision(int n) { cout << fixed << setprecision(n); }
    void flush() { cout.flush(); }
}

constexpr pair<int, int> dir4[] = {{-1, 0}, {0, -1}, {+1, 0}, {0, +1}};

vector<int>& operator ++ (vector<int>& a) { for(auto& e : a) e++; return a; }
vector<int>& operator -- (vector<int>& a) { for(auto& e : a) e--; return a; }
vector<int>  operator ++ (vector<int>& a, int) { vector<int> b = a; ++a; return b; }
vector<int>  operator -- (vector<int>& a, int) { vector<int> b = a; --a; return b; }
#line 2 "h.cpp"
#include <atcoder/modint>
using mint = atcoder::modint998244353;

int main() {
    int N = in();
    vector<int> C(N);
    {
        vector<int> A = in(N), B = in(N);
        FOR(i, N) C[i] = max(A[i], B[i]);
    }
    vector<int> C2;
    FOR(i, N) if(C[i] < 1600) C2.push_back(C[i]);

    mint ans1 = [&] {
        return mint(1) + mint(N) + mint(N) * (N - 1) / 2;
    }();

    mint ans2 = [&] {
        const mint m = C2.size();
        return mint(2).pow(m.val()) - 1 - m - m * (m - 1) / 2;
    }();

    mint ans3 = [&] {
        const int S = 4200;
        vector dp(S, mint(0));
        dp[0] = 1;
        FOR(i, N) if(C[i] < S) {
            REV(s, S - C[i]) dp[s + C[i]] += dp[s];
            // vector nt = dp;
            // FOR(s, S - C[i]) if(s + C[i] < S) nt[s + C[i]] += dp[s];
            // dp = move(nt);
        }
        mint sum = 0;
        FOR(s, S) sum += dp[s];

        sum -= 1;
        FOR(i, N) if(C[i] < 4200) sum -= 1;

        mint sub = 0;
        vector<int> V = C;
        sort(V);
        FOR(i, N) {
            sub += LB(V, S - C[i]);
            if(C[i] + C[i] < 4200) sub -= 1;
        }
        sum -= sub / 2;
        return sum;
    }();

    mint ans23 = [&] {
        const int M = C2.size();

        const int S = 4200;
        vector dp(S, mint(0));
        dp[0] = 1;
        FOR(i, M) if(C2[i] < S) {
            REV(s, S - C2[i]) dp[s + C2[i]] += dp[s];
            // vector nt = dp;
            // FOR(s, S - C2[i]) nt[s + C2[i]] += dp[s];
            // dp = move(nt);
        }
        mint sum = 0;
        FOR(s, S) sum += dp[s];

        sum -= 1;
        FOR(i, M) if(C2[i] < 4200) sum -= 1;

        mint sub = 0;
        vector<int> V = C2;
        sort(V);
        FOR(i, M) {
            sub += LB(V, S - C2[i]);
            if(C2[i] + C2[i] < 4200) sub -= 1;
        }
        sum -= sub / 2;
        return sum;
    }();

    print((ans1 + (ans2 + ans3 - ans23) - 1).val());
}
