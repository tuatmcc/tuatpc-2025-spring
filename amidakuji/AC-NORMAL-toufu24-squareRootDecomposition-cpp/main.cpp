#include <bits/stdc++.h>
using namespace std;

/*
    - 初期化: O(N * M)
    - クエリ1, 2: O(N√M)
    - クエリ3: O(N + √M)
    - 全体: O(N * M + Q * N√M)
    だと思う
*/

// 恒等置換を表す初期化関数
vector<int> identity_perm(int size) {
    vector<int> perm(size);
    iota(perm.begin(), perm.end(), 0);
    return perm;
}

// 置換の合成
vector<int> compose(const vector<int> &a, const vector<int> &b) {
    vector<int> result(a.size());
    for (int i = 0; i < a.size(); i++) {
        result[i] = b[a[i]];
    }
    return result;
}

int main() {
    int N, M;
    cin >> N >> M;

    const int SQRT = sqrt(M);               // 平方分割のブロックサイズ
    int num_blocks = (M + SQRT - 1) / SQRT; // 必要なブロック数(ceil(√M))

    vector<vector<int>> block_perms(num_blocks, identity_perm(N)); // 各ブロックの置換を管理する
    vector<vector<vector<int>>> block_inner_perms(num_blocks, vector<vector<int>>(SQRT, identity_perm(N))); // 各ブロック内の置換を管理する

    int Q;
    cin >> Q;

    while (Q--) {
        int t;
        cin >> t;
        if (t == 1 || t == 2) {
            int x, y;
            cin >> x >> y;
            x--, y--; // 0-based index

            int block = y / SQRT;
            int idx = y % SQRT;

            // 対象の置換を更新
            swap(block_inner_perms[block][idx][x], block_inner_perms[block][idx][x + 1]);

            // ブロックを再計算
            block_perms[block] = identity_perm(N);
            for (int i = 0; i < block_inner_perms[block].size(); i++) {
                block_perms[block] = compose(block_perms[block], block_inner_perms[block][i]);
            }
        } else if (t == 3) {
            int s;
            cin >> s;
            s--; // 0-based index

            vector<int> result_perm = identity_perm(N);

            // 各ブロックの置換を順番に適用
            for (int i = 0; i < num_blocks; i++) {
                s = block_perms[i][s];
            }

            // s行目の移動先を出力
            cout << (result_perm[s] + 1) << endl; // 1-based index
        }
    }
}
