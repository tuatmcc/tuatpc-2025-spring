#include <bits/stdc++.h>
using namespace std;

/*
    - 初期化: O(QlogQ) // 座標圧縮のためのソート
    - クエリ1, 2: O(logQ)  // 圧縮後の座標でのset操作
    - クエリ3: O(QlogQ)    // 最悪QステップでそれぞれlogQ
    - 全体: O(Q + Q^2 * logQ)
*/

int main() {
    int N, M;
    cin >> N >> M;

    int Q;
    cin >> Q;

    // クエリを全部保存
    vector<vector<int>> queries(Q);
    vector<int> y_coords;    // 座標圧縮用
    y_coords.reserve(Q + 1); // M + 各クエリの高さ

    for (int i = 0; i < Q; i++) {
        int t;
        cin >> t;
        if (t == 1 || t == 2) {
            int x, y;
            cin >> x >> y;
            queries[i] = {t, x, y};
            y_coords.push_back(y - 1); // 0-based index
        } else {
            int s;
            cin >> s;
            queries[i] = {t, s, -1};
        }
    }

    // 座標圧縮のための準備
    y_coords.push_back(M); // 終端も含める
    sort(y_coords.begin(), y_coords.end());
    y_coords.erase(unique(y_coords.begin(), y_coords.end()), y_coords.end());

    // 圧縮後のMの値（終端）
    int compressed_M = lower_bound(y_coords.begin(), y_coords.end(), M) - y_coords.begin();

    // 各縦棒に対して存在する横棒の{圧縮後の高さ, 左端かどうか}を管理
    vector<set<pair<int, bool>>> to(N);

    // クエリ処理
    for (const auto &query : queries) {
        int t = query[0];
        if (t == 1) {
            int x = query[1] - 1; // 0-based
            int y = query[2] - 1; // 0-based

            // 元の座標から圧縮後の座標を取得
            int compressed_y = lower_bound(y_coords.begin(), y_coords.end(), y) - y_coords.begin();

            // 対象の置換を更新
            to[x].insert({compressed_y, true});
            to[x + 1].insert({compressed_y, false});
        } else if (t == 2) {
            int x = query[1] - 1; // 0-based
            int y = query[2] - 1; // 0-based

            // 元の座標から圧縮後の座標を取得
            int compressed_y = lower_bound(y_coords.begin(), y_coords.end(), y) - y_coords.begin();

            // 対象の置換を更新
            to[x].erase({compressed_y, true});
            to[x + 1].erase({compressed_y, false});
        } else {
            int s = query[1] - 1; // 0-based

            int cur_x = s;
            int cur_y = 0;
            while (true) {
                // 圧縮座標での探索
                auto next_itr = to[cur_x].lower_bound({cur_y, false});
                if (next_itr != to[cur_x].end()) {
                    if (next_itr->second) {
                        // 左端の場合は右に移動
                        cur_x = cur_x + 1;
                    } else {
                        // 右端の場合は左に移動
                        cur_x = cur_x - 1;
                    }
                    cur_y = next_itr->first + 1;
                } else {
                    cur_y = compressed_M;
                }

                // 下まで到達したら終了
                if (cur_y == compressed_M) {
                    cout << cur_x + 1 << endl;
                    break;
                }
            }
        }
    }
}
