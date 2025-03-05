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

int main(){
    ll n,q;
    string s;
    cin >> n >> q >> s;
    vll l(q),r(q);
    rep(i,0,q)cin >> l[i] >> r[i];

    ll moji = 26;
    vvll g1(n+1,vll(26,0));
    vvvll g2(n+1,vvll(26,vll(26,0)));
    vvvll g3(n+1,vvll(26,vll(26,0)));
    vvvll g4(n+1,vvll(26,vll(26,0)));

    rep(i,0,n){
        ll cnt = s[i] - 'a';
        g1[i+1][cnt]++;
        rep(j,0,26)g1[i+1][j] += g1[i][j];
    }

    rep(i,1,n){
        ll cnt = s[i] - 'a';
        rep(j,0,26){
            rep(k,0,26){
                g2[i+1][j][k] = g2[i][j][k];
            }
        }
        rep(j,0,26){
            if(j == cnt)continue;
            g2[i+1][j][cnt] += g1[i][j];
        }
    }

    rep(i,2,n){
        ll cnt = s[i] - 'a';
        rep(j,0,26){
            rep(k,0,26){
                g3[i+1][j][k] = g3[i][j][k];
            }
        }
        rep(j,0,26){
            if(j == cnt)continue;
            g3[i+1][cnt][j] += g2[i][cnt][j];
        } 
    }

    rep(i,3,n){
        ll cnt = s[i] - 'a';
        rep(j,0,26){
            rep(k,0,26){
                g4[i+1][j][k] = g4[i][j][k];
            }
        }
        rep(j,0,26){
            if(j == cnt)continue;
            g4[i+1][j][cnt] += g3[i][j][cnt];
        } 
    }

    vll f1(26,0);
    vvll f2(26,vll(26,0));
    vvll f3(26,vll(26,0));
    vvll f4(26,vll(26,0));

    rep(idx,0,q){
        ll L = l[idx],R = r[idx];
        ll ans = 0;
        rep(i,0,26)f1[i] = g1[R][i] - g1[L-1][i];
        rep(i,0,26)rep(j,0,26){
            if(i == j)continue;
            f2[i][j] = g2[R][i][j] - g2[L-1][i][j] - g1[L-1][i] * f1[j];
        }
        rep(i,0,26)rep(j,0,26){
            if(i == j)continue;
            f3[i][j] = g3[R][i][j] - g3[L-1][i][j] - g1[L-1][i] * f2[j][i] - g2[L-1][i][j] * f1[i];
        }
        rep(i,0,26)rep(j,0,26){
            if(i == j)continue;
            ans += g4[R][i][j] - g4[L-1][i][j] - g1[L-1][i] * f3[j][i] - g2[L-1][i][j] * f2[i][j] - g3[L-1][i][j] * f1[j];
        }

        cout << ans << '\n';
    }
} 