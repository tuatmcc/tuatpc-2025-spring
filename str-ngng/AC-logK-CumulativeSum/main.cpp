#include <iostream>
#include <string>
#include <vector>
#include <utility>
using namespace std;

using ll = long long;
using T = ll;
using P = pair<T, T>;
const int C = 26;

int main(){
    int N, Q; cin >> N >> Q;
    string S; cin >> S;

    // `c1[i][c]` := S の 0 文字目から i 文字目までに含まれる文字 c の個数
    vector c1(N + 1, vector(C, T{}));
    // `c2[i][c][d]` := S の 0 文字目から i 文字目までに含まれる (c < d)
    //                  部分文字列 cd の個数 (first)
    //                  部分文字列 dc の個数 (second)
    vector c2(N + 1, vector(C, vector(C, P{})));
    // `c3[i][c][d]` := S の 0 文字目から i 文字目までに含まれる (c < d)
    //                  部分文字列 cdc の個数 (first)
    //                  部分文字列 dcd の個数 (second)
    vector c3(N + 1, vector(C, vector(C, P{})));
    // `c4[i][c][d]` := S の 0 文字目から i 文字目までに含まれる (c < d)
    //                  部分文字列 cdcd の個数 (first)
    //                  部分文字列 dcdc の個数 (second)
    vector c4(N + 1, vector(C, vector(C, P{})));

    // c1 の前計算
    for(int i = 1; i <= N; ++i){
        int c = S[i - 1] - 'a';
        for(int j = 0; j < C; ++j) c1[i][j] += c1[i - 1][j];
        c1[i][c] += 1;
    }
    // c2 の前計算
    for(int i = 2; i <= N; ++i){
        int c = S[i - 1] - 'a';
        for(int j = 0; j < C; ++j){
            for(int k = j + 1; k < C; ++k){
                c2[i][j][k] = c2[i - 1][j][k];
            }
        }
        for(int d = 0; d < C; ++d){
            if(d == c) continue;
            if(c < d) c2[i][c][d].second += c1[i - 1][d];
            else c2[i][d][c].first += c1[i - 1][d];
        }
    }
    // c3 の前計算
    for(int i = 3; i <= N; ++i){
        int c = S[i - 1] - 'a';
        for(int j = 0; j < C; ++j){
            for(int k = j + 1; k < C; ++k){
                c3[i][j][k] = c3[i - 1][j][k];
            }
        }
        for(int d = 0; d < C; ++d){
            if(d == c) continue;
            if(c < d) c3[i][c][d].first += c2[i - 1][c][d].first;
            else c3[i][d][c].second += c2[i - 1][d][c].second;
        }
    }
    // c4 の前計算
    for(int i = 4; i <= N; ++i){
        int c = S[i - 1] - 'a';
        for(int j = 0; j < C; ++j){
            for(int k = j + 1; k < C; ++k){
                c4[i][j][k] = c4[i - 1][j][k];
            }
        }
        for(int d = 0; d < C; ++d){
            if(d == c) continue;
            if(c < d) c4[i][c][d].second += c3[i - 1][c][d].second;
            else c4[i][d][c].first += c3[i - 1][d][c].first;
        }
    }

    vector f1(C, T{});
    vector f2(C, vector(C, P{}));
    vector f3(C, vector(C, P{}));
    vector f4(C, vector(C, P{}));
    while(Q--){
        int l, r; cin >> l >> r, --l;
        T ans = 0;
        for(int i = 0; i < C; ++i) f1[i] = c1[r][i] - c1[l][i];
        for(int i = 0; i < C; ++i){
            for(int j = i + 1; j < C; ++j){
                f2[i][j].first = c2[r][i][j].first - c2[l][i][j].first;
                f2[i][j].first -= c1[l][i] * f1[j];
                f2[i][j].second = c2[r][i][j].second - c2[l][i][j].second;
                f2[i][j].second -= c1[l][j] * f1[i];
                f3[i][j].first = c3[r][i][j].first - c3[l][i][j].first;
                f3[i][j].first -= c1[l][i] * f2[i][j].second;
                f3[i][j].first -= c2[l][i][j].first * f1[i];
                f3[i][j].second = c3[r][i][j].second - c3[l][i][j].second;
                f3[i][j].second -= c1[l][j] * f2[i][j].first;
                f3[i][j].second -= c2[l][i][j].second * f1[j];
                f4[i][j].first = c4[r][i][j].first - c4[l][i][j].first;
                f4[i][j].first -= c1[l][i] * f3[i][j].second;
                f4[i][j].first -= c2[l][i][j].first * f2[i][j].first;
                f4[i][j].first -= c3[l][i][j].first * f1[j];
                ans += f4[i][j].first;
                f4[i][j].second = c4[r][i][j].second - c4[l][i][j].second;
                f4[i][j].second -= c1[l][j] * f3[i][j].first;
                f4[i][j].second -= c2[l][i][j].second * f2[i][j].second;
                f4[i][j].second -= c3[l][i][j].second * f1[i];
                ans += f4[i][j].second;
            }
        }
        cout << ans << '\n';
    }
}