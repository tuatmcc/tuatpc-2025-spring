#include <iostream>
#include <string>
using namespace std;

using ll = long long;
using T = ll;

const int MAX_N = 30010;
const int C = 26;
T c1[MAX_N][C];
T c2[MAX_N][C][C];
T c3[MAX_N][C][C];
T c4[MAX_N][C][C];
T f1[C];
T f2[C][C];
T f3[C][C];
T f4[C][C];

int main(){
    cin.tie(0)->sync_with_stdio(false);
    int N, Q; cin >> N >> Q;
    string S; cin >> S;

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
            for(int k = 0; k < C; ++k){
                c2[i][j][k] = c2[i - 1][j][k];
            }
        }
        for(int d = 0; d < C; ++d){
            if(d == c) continue;
            c2[i][d][c] += c1[i - 1][d];
        }
    }
    // c3 の前計算
    for(int i = 3; i <= N; ++i){
        int c = S[i - 1] - 'a';
        for(int j = 0; j < C; ++j){
            for(int k = 0; k < C; ++k){
                c3[i][j][k] = c3[i - 1][j][k];
            }
        }
        for(int d = 0; d < C; ++d){
            if(d == c) continue;
            c3[i][c][d] += c2[i - 1][c][d];
        }
    }
    // c4 の前計算
    for(int i = 4; i <= N; ++i){
        int c = S[i - 1] - 'a';
        for(int j = 0; j < C; ++j){
            for(int k = 0; k < C; ++k){
                c4[i][j][k] = c4[i - 1][j][k];
            }
        }
        for(int d = 0; d < C; ++d){
            if(d == c) continue;
            c4[i][d][c] += c3[i - 1][d][c];
        }
    }

    while(Q--){
        int l, r; cin >> l >> r, --l;
        T ans = 0;
        for(int i = 0; i < C; ++i) f1[i] = c1[r][i] - c1[l][i];
        for(int i = 0; i < C; ++i){
            for(int j = i + 1; j < C; ++j){
                f2[i][j] = c2[r][i][j] - c2[l][i][j];
                f2[i][j] -= c1[l][i] * f1[j];
                f2[j][i] = c2[r][j][i] - c2[l][j][i];
                f2[j][i] -= c1[l][j] * f1[i];

                f3[i][j] = c3[r][i][j] - c3[l][i][j];
                f3[i][j] -= c1[l][i] * f2[j][i];
                f3[i][j] -= c2[l][i][j] * f1[i];
                f3[j][i] = c3[r][j][i] - c3[l][j][i];
                f3[j][i] -= c1[l][j] * f2[i][j];
                f3[j][i] -= c2[l][j][i] * f1[j];
                
                f4[i][j] = c4[r][i][j] - c4[l][i][j];
                f4[i][j] -= c1[l][i] * f3[j][i];
                f4[i][j] -= c2[l][i][j] * f2[i][j];
                f4[i][j] -= c3[l][i][j] * f1[j];
                f4[j][i] = c4[r][j][i] - c4[l][j][i];
                f4[j][i] -= c1[l][j] * f3[i][j];
                f4[j][i] -= c2[l][j][i] * f2[j][i];
                f4[j][i] -= c3[l][j][i] * f1[i];

                ans += f4[i][j] + f4[j][i];
            }
        }
        cout << ans << '\n';
    }
}