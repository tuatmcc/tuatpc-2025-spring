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
    // S[0] < A ... k=4~(n-1)桁の整数をABのみ使って作れる   ->  2^(k-1) - k-1 - 2^(k-2) + 1 通り，Aは(9-S[0])通り，Bは各9通り
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


    
} 