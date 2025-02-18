#include<bits/stdc++.h>
using namespace std;
using ll = long long int;
typedef vector<ll> vll;
typedef vector<vll> vvll;
typedef vector<vvll> vvvll;
typedef vector<vvvll> vvvvll;
typedef vector<bool> vb;
typedef vector<string> vs;
typedef pair<ll,ll> pll;
typedef vector<pair<ll,ll>> vp;
#define rep(i,a,n) for(ll i=a;i<n;i++)
#define revrep(i,a,n) for(ll i=n-1;i>=a;i--)
#define mod 998244353
#define all(a) a.begin(),a.end()

bool in_field(ll l,ll r,ll x){
    if(l <= x && x < r)return true;
    else return false;
}

ll distance(ll ax,ll ay,ll bx, ll by){
    return (ax-bx)*(ax-bx) + (ay-by)*(ay-by);
}

ll modinv(ll a, ll m) {
    ll b=m,u=1,v=0;
    while(b){
        ll t=a/b;
        a-=t*b;swap(a,b);
        u-=t*v;swap(u,v);
    }
    u%=m; 
    if(u<0)u+=m;
    return u;
}

ll dx4[4] = {1,0,-1,0};
ll dy4[4] = {0,-1,0,1};
ll dx8[8] = {1,1,0,-1,-1,-1,0,1};
ll dy8[8] = {0,-1,-1,-1,0,1,1,1};

int main(){
    // N文字の整数列が与えられる
    // ngng整数: A...AB...BA...AB...Bとなっている数(ランレングス圧縮で2種類の文字しかなく，圧縮後の各文字の登場回数が同じ)
    // 2つの数字を何にするか ... A:1-9 B:0-9 (A≠B)

    // S[0] > A ... k=4~n桁の整数をA,Bのみ使って作れる      ->  2^(k-1) - k - 2^(k-2) + 1 通り，Aは(S[0]-1)通り, Bは各9通り
    // S[0] < A ... k=4~(n-1)桁の整数をABのみ使って作れる   ->  2^(k-1) - k - 2^(k-2) + 1 通り，Aは(9-S[0])通り，Bは各9通り
    // S[0] = A ... k=4~(n-1)桁は S[0] < A　同様作れる

    // S[0] = A かつ　n桁の整数がいくつあるか？
    // 1: S以下で
    // 2: Bで終わり
    // 3: A...AB..Bの形でないもの　
    // を数える
    string s;
    cin >> s;
    ll n = s.size();

    ll ans = 0;

    if(s.size() < 4){
        cout << 0;
        return 0;
    }

    vll beki(n+1,1);
    rep(i,1,n+1){
        beki[i] = beki[i-1]*2;
        beki[i] %= mod;
    }
    rep(i,4,n){
        ll cnt = beki[i-2] - i + 1 + mod;
        cnt %= mod;
        cnt *= 81;
        cnt %= mod;
        ans += cnt;
        ans %= mod;
    }

    // N桁の条件を満たす数字の個数
    ll cnt = beki[n-2] - n + 1 +mod; 
    cnt %= mod;
    cnt *= ll(s[0]-'1')*9;
    cnt %= mod;
    ans += cnt;
    ans %= mod;

    // S[0] = A かつN桁の整数がいくつあるか
    ll A = s[0] - '0';
    rep(idx,0,10){
        if(A == idx)continue;
        ll cnt = 0;
        // i桁目，j: 数字を好きに使えるか 0:使える 1:使えるとは限らない k: 末尾が 0:A 1:B
        //  dp[n][0][1] + dp[n][1][1] 
        vvvll dp(n+1,vvll(2,vll(2,0)));
        dp[1][1][0] = 1;
        rep(i,2,n+1){
            if(ll(s[i-1] - '0') == A)dp[i][1][0] = dp[i-1][1][0] + dp[i-1][1][1];
            if(ll(s[i-1] - '0') == idx)dp[i][1][1] = dp[i-1][1][1] + dp[i-1][1][0];
            dp[i][0][0] = dp[i-1][0][0] + dp[i-1][0][1] + dp[i-1][1][0] + dp[i-1][1][1];
            dp[i][0][1] = dp[i-1][0][1] + dp[i-1][0][0] + dp[i-1][1][0] + dp[i-1][1][1];
            dp[i][0][0] %= mod;
            dp[i][0][1] %= mod;
        }
        cnt = dp[n][0][1] + dp[n][1][1] + mod;
        string x(n,'0'+A);
        revrep(i,1,n){
            x[i] = '0' + idx;
            if(x <= s)cnt--;
        }
        cnt %= mod;
        ans += cnt;
        ans %= mod;
    }

    cout << ans << endl;
} 