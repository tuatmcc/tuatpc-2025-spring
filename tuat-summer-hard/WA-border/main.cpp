# include <bits/stdc++.h>

#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
using namespace std;
typedef long long ll;
const double EPS = 1e-9;
template<typename T> bool isZero(T x) { return x == 0; }
bool isZero(double x) { return abs(x) < EPS; }
template<typename T> T pw(T a, ll b) { T r = T(1); for (; b > 0; b >>= 1) { if (b & 1) r *= a; a *= a; } return r; }

// ========================================================================

int euclid(int x, int y, int &ax, int &ay) {
  if (y == 0) {
    ax = 1; ay = 0;
    return x;
  }
  int b;
  int g = euclid(y, x % y, b, ax);
  ay = b - (x / y) * ax;
  return g;
}
int invMod(int a, int mod) {
  int x, y;
  int g = euclid(mod, a, y, x);
  assert(g == 1);
  x %= mod; if (x < 0) x += mod;
  return x;
}

template<int M>
struct mint_t {
  int v;
  
  mint_t() = default;
  mint_t(int v) : v(v % M) { if (this->v < 0) this->v += M; }
  mint_t(ll v) : v(v % M) { if (this->v < 0) this->v += M; }
  mint_t(mint_t<M> const& b) = default;

  mint_t& operator = (mint_t const& b) = default;

  mint_t& operator += (mint_t b) { v += b.v; if (v >= M) v -= M; return *this; }
  mint_t& operator -= (mint_t b) { v -= b.v; if (v < 0) v += M; return *this; }
  mint_t& operator *= (mint_t b) { v = 1LL * v * b.v % M; return *this; }
  mint_t& operator /= (mint_t b) { return *this *= invMod(b.v, M);}

  mint_t operator - () const { return mint_t(v == 0 ? 0 : M - v); }

  mint_t& operator ++() { if (++v == M) v = 0; return *this; }
  mint_t& operator --() { if (v == 0) v = M - 1; else --v; return *this; }
  mint_t operator ++(int) { mint_t a = *this; ++*this; return a; }
  mint_t operator --(int) { mint_t a = *this; --*this; return a; }

  operator int() const { return v; }
};

template<int M> mint_t<M> operator + (mint_t<M> a, mint_t<M> b) { return a += b; }
template<int M> mint_t<M> operator - (mint_t<M> a, mint_t<M> b) { return a -= b; }
template<int M> mint_t<M> operator * (mint_t<M> a, mint_t<M> b) { return a *= b; }
template<int M> mint_t<M> operator / (mint_t<M> a, mint_t<M> b) { return a /= b; }

template<int M> mint_t<M> operator + (mint_t<M> a, int b) { return a += b; }
template<int M> mint_t<M> operator - (mint_t<M> a, int b) { return a -= b; }
template<int M> mint_t<M> operator * (mint_t<M> a, int b) { return a *= b; }
template<int M> mint_t<M> operator / (mint_t<M> a, int b) { return a /= b; }

template<int M> mint_t<M> operator + (int a, mint_t<M> b) { mint_t<M> aa = a; return aa += b; }
template<int M> mint_t<M> operator - (int a, mint_t<M> b) { mint_t<M> aa = a; return aa -= b; }
template<int M> mint_t<M> operator * (int a, mint_t<M> b) { mint_t<M> aa = a; return aa *= b; }
template<int M> mint_t<M> operator / (int a, mint_t<M> b) { mint_t<M> aa = a; return aa /= b; }

template<int M> mint_t<M> operator + (ll a, mint_t<M> b) { mint_t<M> aa = a; return aa += b; }
template<int M> mint_t<M> operator - (ll a, mint_t<M> b) { mint_t<M> aa = a; return aa -= b; }
template<int M> mint_t<M> operator * (ll a, mint_t<M> b) { mint_t<M> aa = a; return aa *= b; }
template<int M> mint_t<M> operator / (ll a, mint_t<M> b) { mint_t<M> aa = a; return aa /= b; }

template<int M> mint_t<M> operator + (mint_t<M> a, ll b) { return a += b; }
template<int M> mint_t<M> operator - (mint_t<M> a, ll b) { return a -= b; }
template<int M> mint_t<M> operator * (mint_t<M> a, ll b) { return a *= b; }
template<int M> mint_t<M> operator / (mint_t<M> a, ll b) { return a /= b; }

template<int M> bool operator == (mint_t<M> a, mint_t<M> b) { return a.v == b.v; }
template<int M> bool operator != (mint_t<M> a, mint_t<M> b) { return a.v != b.v; }
template<int M> bool operator < (mint_t<M> a, mint_t<M> b) { return a.v < b.v; }
template<int M> bool operator > (mint_t<M> a, mint_t<M> b) { return a.v > b.v; }
template<int M> bool operator <= (mint_t<M> a, mint_t<M> b) { return a.v <= b.v; }
template<int M> bool operator >= (mint_t<M> a, mint_t<M> b) { return a.v >= b.v; }
template<int M> bool operator == (mint_t<M> a, int b) { return a == mint_t<M>(b); }
template<int M> bool operator != (mint_t<M> a, int b) { return a != mint_t<M>(b); }
template<int M> bool operator < (mint_t<M> a, int b) { return a < mint_t<M>(b); }
template<int M> bool operator > (mint_t<M> a, int b) { return a > mint_t<M>(b); }
template<int M> bool operator <= (mint_t<M> a, int b) { return a <= mint_t<M>(b); }
template<int M> bool operator >= (mint_t<M> a, int b) { return a >= mint_t<M>(b); }
template<int M> bool operator == (int a, mint_t<M> b) { return b == mint_t<M>(a); }
template<int M> bool operator != (int a, mint_t<M> b) { return b != mint_t<M>(a); }
template<int M> bool operator < (int a, mint_t<M> b) { return b < mint_t<M>(a); }
template<int M> bool operator > (int a, mint_t<M> b) { return b > mint_t<M>(a); }
template<int M> bool operator <= (int a, mint_t<M> b) { return b <= mint_t<M>(a); }
template<int M> bool operator >= (int a, mint_t<M> b) { return b >= mint_t<M>(a); }
template<int M> bool operator == (mint_t<M> a, ll b) { return a == mint_t<M>(b); }
template<int M> bool operator != (mint_t<M> a, ll b) { return a != mint_t<M>(b); }
template<int M> bool operator < (mint_t<M> a, ll b) { return a < mint_t<M>(b); }
template<int M> bool operator > (mint_t<M> a, ll b) { return a > mint_t<M>(b); }
template<int M> bool operator <= (mint_t<M> a, ll b) { return a <= mint_t<M>(b); }
template<int M> bool operator >= (mint_t<M> a, ll b) { return a >= mint_t<M>(b); }
template<int M> bool operator == (ll a, mint_t<M> b) { return b == mint_t<M>(a); }
template<int M> bool operator != (ll a, mint_t<M> b) { return b != mint_t<M>(a); }
template<int M> bool operator < (ll a, mint_t<M> b) { return b < mint_t<M>(a); }
template<int M> bool operator > (ll a, mint_t<M> b) { return b > mint_t<M>(a); }
template<int M> bool operator <= (ll a, mint_t<M> b) { return b <= mint_t<M>(a); }
template<int M> bool operator >= (ll a, mint_t<M> b) { return b >= mint_t<M>(a); }

template<int M> mint_t<M> inv(mint_t<M> a) { return mint_t<M>(invMod(a.v, M)); }

namespace std {
  template<int M>
  struct hash<mint_t<M>> {
    size_t operator()(mint_t<M> const& a) const {
      return hash<int>()(a.v);
    }
  };
}

template<int M>
istream& operator >> (istream &in, mint_t<M> &a) {
  int x;
  in >> x;
  a = x;
  return in;
}

template<int M>
ostream& operator << (ostream &out, mint_t<M> a) {
  return out << a.v;
}

const int MOD = 998244353;
typedef mint_t<MOD> mint;

namespace ffti {
  const int D = 21;
  const int DMAX = 23;
  const int W = 31; // DO NOT TOUCH
  const int MOD = 998244353;
  const int N = 1 << D;
  int w[N];
  int p[N];

  int pw(int a, int b) {
    int r = 1;
    for (; b; b >>= 1) {
      if (b & 1) r = 1LL * r * a % MOD;
      a = 1LL * a * a % MOD;
    }
    return r;
  }

  void init() {
    static bool inited = false;
    if (inited) return;
    inited = true;
    assert(D <= DMAX);
    int w0 = W;
    for (int i = 0; i < DMAX - D; ++i)
      w0 = 1LL * w0 * w0 % MOD;
    int wi = 0;
    for (int cn = 2; cn <= N; cn *= 2) {
      w[wi++] = 1;
      int cw0 = pw(w0, N / cn);
      for (int i = 1; i < cn / 2; ++i, ++wi)
        w[wi] = 1LL * cw0 * w[wi - 1] % MOD;
    }
    int j = 0;
    for (int i = 1; i < N; ++i) {
      if (!(i & (1 << j))) ++j;
      p[i] = p[i ^ (1 << j)] | (1 << (D - 1 - j));
    }
  }

  void fft(int *a, int n) {
    assert(n <= N && n != 0 && !(n&(n - 1)));
    init();
    for (int i = 0; i < n; ++i) {
      int ni = p[i] / (N / n);
      if (i > ni) swap(a[i], a[ni]);
    }
    int wi0 = 0;
    for (int cn = 1; cn < n; cn *= 2) {
      for (int s = 0; s < n; s += 2*cn)
        for (int i = 0; i < cn; ++i) {
          int x = a[s + i];
          int y = 1LL * a[s + cn + i] * w[wi0 + i] % MOD;
          int x1 = x + y; if (x1 >= MOD) x1 -= MOD;
          int y1 = x - y; if (y1 < 0) y1 += MOD;
          a[s + i] = x1;
          a[s + cn + i] = y1;
        }
      wi0 += cn;
    }
  }

  void fftInv(int *a, int n) {
    int ni = pw(n, MOD - 2);
    for (int i = 0; i < n; ++i)
      a[i] = 1LL * a[i] * ni % MOD;
    reverse(a + 1, a + n);
    fft(a, n);
  }

}

int polyMulMod(int const* a1, int n1, int const* a2, int n2, int *a3, int m3 = -1) {
  if (n1 <= 0 || n2 <= 0 || m3 == 0) {
    if (m3 != -1) memset(a3, 0, sizeof(int) * m3);
    return 0;
  }
  if (m3 != -1) {
    n1 = min(n1, m3);
    n2 = min(n2, m3);
  }
  int n3 = n1 + n2 - 1;
  if (m3 == -1) m3 = n3;
  int n = 1;
  while (n < n3) n *= 2;
  assert(n <= ffti::N);
  static int buf1[ffti::N], buf2[ffti::N];
  for (int i = 0; i < n; ++i)
    buf1[i] = (i < n1 ? a1[i] : 0);
  for (int i = 0; i < n; ++i)
    buf2[i] = (i < n2 ? a2[i] : 0);
  ffti::fft(buf1, n);
  ffti::fft(buf2, n);
  int ni = ffti::pw(n, ffti::MOD - 2);
  for (int i = 0; i < n; ++i)
    buf1[i] = 1LL * buf1[i] * buf2[i] % ffti::MOD * ni % ffti::MOD;
  reverse(buf1 + 1, buf1 + n);
  ffti::fft(buf1, n);
  memcpy(a3, buf1, sizeof(int) * min(m3, n3));
  if (m3 > n3)
    memset(a3 + n3, 0, sizeof(int) * (m3 - n3));
  return min(n3, m3);
}

typedef mint_t<ffti::MOD> mintf;
int polyMul(mintf const* a1, int n1, mintf const* a2, int n2, mintf *a3, int n3 = -1) {
  return polyMulMod((int const*)a1, n1, (int const*)a2, n2, (int*)a3, n3);
}

void polyFft(mintf *a, int n) { ffti::fft((int*)a, n); }
void polyFftInv(mintf *a, int n) { ffti::fftInv((int*)a, n); }

void polyInv(mintf const* a, int n, mintf *b, int m) {
  assert(n > 0 && a[0] != 0);
  assert(a != b);
  if (m <= 0) return;
  static mintf bf[ffti::N];
  bf[0] = 1 / a[0];
  for (int s = 1; s < m; s *= 2) {
    static mintf af[ffti::N];
    for (int i = 0; i < s * 2; ++i)
      af[i] = (i < n ? a[i] : mintf(0));
    memset(af + s * 2, 0, sizeof(mintf) * s * 2);
    polyFft(af, s * 4);
    memset(bf + s, 0, sizeof(mintf) * s * 3);
    polyFft(bf, s * 4);
    mintf ni = (mintf)1 / (s * 4);
    for (int i = 0; i < s * 4; ++i)
      bf[i] = bf[i] * (2 - af[i] * bf[i]) * ni;
    reverse(bf + 1, bf + s * 4);
    polyFft(bf, s * 4);
  }
  memcpy(b, bf, sizeof(mintf) * m);
}

template<typename T>
void polyLog(T const* a, int n, T *b, int m) {
  n = min(n, m);
  assert(n != 0 && isZero(a[0] - 1));
  polyInv(a, n, b, m - 1);
  vector<T> da(n - 1);
  for (int i = 1; i < n; ++i)
    da[i - 1] = a[i] * i;
  polyMul(da.data(), n - 1, b, m - 1, b, m - 1);
  for (int i = m - 1; i > 0; --i)
    b[i] = b[i - 1] / i;
  b[0] = 0;
}

template<typename T>
vector<T> polyLog(vector<T> const& a, int m) {
  vector<T> b(m);
  polyLog(a.data(), sz(a), b.data(), m);
  return b;
}

template<typename T>
void polyExp(T const* a, int n, T *b, int m) {
  if (m == 0) return;
  assert(n == 0 || isZero(a[0]));
  n = min(n, m);
  b[0] = 1;
  vector<T> c(m);
  for (int s = 1; s < m; s *= 2) {
    int s2 = min(m, s * 2);
    polyLog(b, s, c.data(), s2);
    for (int i = 0; i < s2; ++i)
      c[i] = (i < n ? a[i] : T(0)) - c[i];
    ++c[0];
    polyMul(b, s, c.data(), s2, b, s2);
  }
}

template<typename T>
vector<T> polyExp(vector<T> const& a, int m) {
  vector<T> b(m);
  polyExp(a.data(), sz(a), b.data(), m);
  return b;
}

template<typename T>
T subsetSum(vector<int> const& a, int t) {
  t += 1;
  vector<int> cnt(t);
  for (int x : a)
    if (x < t)
      ++cnt[x];
  vector<T> p(t, 0);
  for (int j = 1; j < t; ++j) {
    T j2 = (j & 1 ? T(1) / j : T(-1) / j);
    for (int i = 1; i * j < t; ++i)
      p[i * j] += cnt[i] * j2;
  }
  p = polyExp(p, t);
  T p2 = pw(T(2), cnt[0]);
  for (T &x : p)
    x *= p2;
  
  T ret = 0;
  for (int i = 1; i <= t; i++) {
    ret += p[i];
  }

  return ret;
}

int main() {
   int n;
   std::cin >> n;
   std::vector<int> x(n);
   //  for (int i = 0; i < n; i++) {
   //     int a, h;
   //     std::cin >> a >> h;
   //     x[i] = std::max(a, h);
   //  }
   for(int i = 0; i < n; ++i){
     int a; cin >> a; x[i] = a;
   }
   for(int i = 0; i < n; ++i){
     int a; cin >> a; x[i] = max(x[i], a);
   }

   mint s1 = [&] {
      int cnt = std::ranges::count_if(x, [](int e) { return e < 1600; });
      return pw(mint(2), cnt) - 1;
      // return mint(2).pow(cnt) - 1;
   }();
   mint s2 = subsetSum<mint>(x, 4199);
   std::vector<int> x2;
   std::vector<int> x3;
   for (int xi : x) {
      if (xi < 1600) {
         x2.push_back(xi);
      }
      // else {
      //     x3.push_back(xi);
      // }
   }
   mint s12 = subsetSum<mint>(x2, 4199);

   mint s = s1 + s2 - s12;

   mint t = [&] {
      mint ret{0};
      std::sort(x.begin(), x.end());
      for (int i = 0; i < x.size(); i++) {
         if (x[i] >= 4200) {
            ret = ret + mint(1);
         }
         if (i >= 1 && x[i] >= 1600) {
          auto it = std::lower_bound(x.begin(), x.begin() + i, 4200 - x[i]);
          ret = ret + mint((ll)((x.begin() + i) - it));
         }

        //  for (int j = i + 1; j < n; j++) {
        //     if (std::max(x[i], x[j]) >= 1600 && x[i] + x[j] >= 4200) {
        //        ret++;
        //     }
        //  }
      }
      return ret;
   }();

   mint ans = s + t;

   std::cout << ans << std::endl;
}