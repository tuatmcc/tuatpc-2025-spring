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
    // ngng整数: A...AB...BA...AB...Bとなっている数
    // 桁DP: i桁目まで，j:全ての数字を使えるか, k:10-99(ゾロ目除く)A,Bの数字が何か, 
    //       l: ABABのどこまで完成しているか　0:A 1:AB 2:ABA 3:ABAB
    // 100000*2*100*4 = 8*10^7 状態
    // 
    string s;
    cin >> s;
    ll n = s.size();
    vvvvll dp(n+1,vvvll(2,vvll(100,vll(4,0))));
    rep(i,10,100)dp[1][0][i][0] = 1;
    
} 