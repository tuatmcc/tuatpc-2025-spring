#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
    int N, Q; cin >> N >> Q;
    string S; cin >> S;

    const int C = 26;
    using ll = long long;
    vector c1(N + 1, vector(C, ll{}));
    vector c2(N + 1, vector(C, vector(C, ll{})));
    vector c3(N + 1, vector(C, vector(C, ll{})));
    vector c4(N + 1, vector(C, vector(C, ll{})));

    for(int i = 1; i <= N; ++i){
        int s = S[i - 1] - 'a';
        for(int j = 0; j < C; ++j) c1[i][j] += c1[i - 1][j];
        ++c1[i][s];
    }
    for(int i = 2; i <= N; ++i){
        int s = S[i - 1] - 'a';
        for(int j = 0; j < C; ++j){
            for(int k = 0; k < C; ++k){
                c2[i][j][k] = c2[i - 1][j][k];
            }
        }
        for(int j = 0; j < C; ++j){
            if(j == s) continue;
            c2[i][j][s] += c1[i - 1][j];
        }
    }
    for(int i = 3; i <= N; ++i){
        int s = S[i - 1] - 'a';
        for(int j = 0; j < C; ++j){
            for(int k = 0; k < C; ++k){
                c3[i][j][k] = c3[i - 1][j][k];
            }
        }
        for(int j = 0; j < C; ++j){
            if(j == s) continue;
            c3[i][s][j] += c2[i - 1][s][j];
        }
    }
    for(int i = 4; i <= N; ++i){
        int s = S[i - 1] - 'a';
        for(int j = 0; j < C; ++j){
            for(int k = 0; k < C; ++k){
                c4[i][j][k] = c4[i - 1][j][k];
            }
        }
        for(int j = 0; j < C; ++j){
            if(j == s) continue;
            c4[i][j][s] += c3[i - 1][j][s];
        }
    }

    vector f1(C, ll{});
    vector f2(C, vector(C, ll{}));
    vector f3(C, vector(C, ll{}));
    vector f4(C, vector(C, ll{}));
    while(Q--){
        int l, r; cin >> l >> r, --l;
        ll ans = 0;
        for(int i = 0; i < C; ++i) f1[i] = c1[r][i] - c1[l][i];
        for(int i = 0; i < C; ++i){
            for(int j = 0; j < C; ++j){
                if(i == j) continue;
                f2[i][j] = c2[r][i][j] - c2[l][i][j];
                f2[i][j] -= c1[l][i] * f1[j];
            }
        }
        for(int i = 0; i < C; ++i){
            for(int j = 0; j < C; ++j){
                if(i == j) continue;
                f3[i][j] = c3[r][i][j] - c3[l][i][j];
                f3[i][j] -= c1[l][i] * f2[j][i];
                f3[i][j] -= c2[l][i][j] * f1[i];
            }
        }
        for(int i = 0; i < C; ++i){
            for(int j = 0; j < C; ++j){
                if(i == j) continue;
                f4[i][j] = c4[r][i][j] - c4[l][i][j];
                f4[i][j] -= c1[l][i] * f3[j][i];
                f4[i][j] -= c2[l][i][j] * f2[i][j];
                f4[i][j] -= c3[l][i][j] * f1[j];
                ans += f4[i][j];
            }
        }
        cout << ans << endl;
    }
}