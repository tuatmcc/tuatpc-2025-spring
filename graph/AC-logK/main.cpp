#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

using ll = long long;

int main(){
    int N; cin >> N;
    vector<char> X(N);
    for(int i = 0; i < N; ++i) cin >> X[i];
    vector<vector<int>> V(N), W(N);
    for(int i = 0; i < N; ++i){
        int M; cin >> M;
        V[i].resize(M);
        W[i].resize(M);
        for(int j = 0; j < M; ++j){
            cin >> V[i][j], --V[i][j];
        }
        for(int j = 0; j < M; ++j){
            cin >> W[i][j];
        }
    }
    int L; cin >> L;
    string S; cin >> S;

    vector<vector<pair<int, int>>> G(N);
    for(int i = 0; i < N; ++i){
        int M = V[i].size();
        for(int j = 0; j < M; ++j){
            G[i].emplace_back(V[i][j], W[i][j]);
        }
    }
    reverse(S.begin(), S.end());

    vector dp(L, vector(N, ll{}));
    for(int i = 0; i < N; ++i) dp[0][i] = S[0] == X[i];
    for(int i = 1; i < L; ++i){
        for(int j = 0; j < N; ++j){
            if(S[i] != X[j]) continue;
            for(auto [v, w] : G[j]){
                dp[i][j] += dp[i - 1][v] * w;
            }
        }
    }

    ll d = 1;
    for(int i = 1; i < L; ++i) d *= 100;
    for(int i = 0; i < N; ++i){
        ll a = dp.back()[i], b = d;
        for(ll g = gcd(a, b); g > 1; g = gcd(a, b)) a /= g, b /= g;
        if(!a) b = 1;
        cout << a << ' ' << b << endl;
    }
}