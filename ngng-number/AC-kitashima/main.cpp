#include <bits/stdc++.h>

using namespace std;

const long long mod = 998244353;

int main() {
    // 入力
    string S;
    cin >> S;

    // n_index: 上位n_index桁がn'..
    // ng_index: 上位ng_index桁がn'..g'..
    int n_index = 0, ng_index = 0;
    char n = S[0], g;  // n'とg'の値
    int i = 0;
    while (S[i] == n) i++;
    n_index = i;
    g = S[i];
    while (S[i] == g) i++;
    ng_index = i;

    // dp[i][j][k]
    // i: 上からi+1桁目
    // j: 未満フラグ
    // k: n数, ng数, ngn数, ngng数の数
    vector<vector<vector<long long>>> dp(
        1000001, vector<vector<long long>>(2, vector<long long>(4, 0)));
    dp[0][0][0] = 1;
    dp[0][1][0] = (n - '0') - 1;
    for (int i = 1; i < S.size(); i++) {
        // n数について
        // 一致している場合の処理
        if (i < n_index) {  // 上位n_index桁がn..
            dp[i][0][0] = 1;
        } else if (i == n_index) {  // n数: {n'..}にn'がつく
            if (S[i] > n) {         // S[i]がn'より大きい(S未満)
                dp[i][1][0]++;
            }
        }
        // 未満フラグに関する処理
        dp[i][1][0] += dp[i - 1][1][0];  // n数: {n..}にnがつく
        dp[i][1][0] += 9;                // この桁から始まる1~9

        // ng数について
        // 一致している場合の処理
        if (i < n_index) {  // n数: {'n..}にg(n'未満)がつく
            dp[i][1][1] += (n - '0');
        } else if (n_index <= i && i < ng_index) {  // ng数: n'..g'..
            dp[i][0][1] = 1;
        } else if (i == ng_index && S[i] > g) {  // ng数: {n'..g'..}にg'がつく
            dp[i][1][1]++;
        }
        if (i == n_index) {  // n数: {n'..}にg(g'自身とn'を除く)がつく
            dp[i][1][1] += (g - '0') - (n < g ? 1 : 0);
        }
        // 未満フラグに関する処理
        dp[i][1][1] += dp[i - 1][1][1];      // ng数: {n..g..}にgがつく
        dp[i][1][1] += dp[i - 1][1][0] * 9;  // n数: {n..}にgがつく

        // ngn数について
        // 一致している場合の処理
        if (i < ng_index && dp[i - 1][0][1] &&
            S[i] > n) {  // ng数: {n'..g'..}にn'がつく(S未満)
            dp[i][1][2]++;
        }
        if (i == ng_index ||  // ng数: {n'..g'..}にn'がつく または
            (i > ng_index &&
             (dp[i - 1][0][2] == 1 ||  // ngn数: {n'..g'..n'..}にn'がつく または
              dp[i - 1][0][3] == 1))) {  // ngng数: {n'..g'..n'..g'..}にnがつく
            if (S[i] == n) {             // S[i]がn'でSと一致
                dp[i][0][2] = 1;
            } else if (S[i] > n) {  // S[i]がn'より大きい(S未満)
                dp[i][1][2]++;
            }
        }
        // 未満フラグに関する処理
        dp[i][1][2] += dp[i - 1][1][1];  // ng数: {n..g..} にnがつく
        dp[i][1][2] += dp[i - 1][1][2];  // ngn数: {n..g..n..}にnがつく
        dp[i][1][2] += dp[i - 1][1][3];  // ngng数: {n..g..n..g..}にnがつく

        // ngng数について
        // 一致している場合の処理
        if (dp[i - 1][0][2] == 1 ||  // ngn数: {n'..g'..n'..}にg'がつく または
            dp[i - 1][0][3] == 1) {  // ngng数: {n'..g'..n'..g'..}にg'がつく
            if (S[i] == g) {         // S[i]がg'でSと一致
                dp[i][0][3] = 1;
            } else if (S[i] > g) {  // S[i]がg'より大きい(S未満)
                dp[i][1][3]++;
            }
        }
        // 未満フラグに関する処理
        dp[i][1][3] += dp[i - 1][1][2];  // ngn数: {n..g..n..} にgがつく
        dp[i][1][3] += dp[i - 1][1][3];  // ngng数: {n..g..n..g..}にgがつく

        // 各値のmodを取る
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 4; k++) {
                dp[i][j][k] %= mod;
                // cout << "dp[" << i << "][" << j << "][" << k
                //      << "] = " << dp[i][j][k] << endl;
            }
        }
    }
    cout << (dp[S.size() - 1][0][3] + dp[S.size() - 1][1][3]) % mod << endl;
}