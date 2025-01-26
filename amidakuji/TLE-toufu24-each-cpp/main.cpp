#include <bits/stdc++.h>
using namespace std;

/*
    - 初期化: O(N)
    - クエリ1, 2: O(logN)
    - クエリ3: O(QlogN)
    - 全体: O(N + Q^2 * logN)
*/

int main() {
    int N, M;
    cin >> N >> M;

    int Q;
    cin >> Q;

    // 各縦棒に対して存在する横棒の{高さ, 左端かどうか}を管理
    vector<set<pair<int, bool>>> to(N);

    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y;
            cin >> x >> y;
            x--, y--; // 0-based index

            // 対象の置換を更新
            to[x].insert({y, true});
            to[x + 1].insert({y, false});
        } else if (t == 2) {
            int x, y;
            cin >> x >> y;
            x--, y--; // 0-based index

            // 対象の置換を更新
            to[x].erase({y, true});
            to[x + 1].erase({y, false});
        } else {
            int s;
            cin >> s;
            s--; // 0-based index

            int cur_x = s;
            int cur_y = 0;
            while (true) {
                // 最大でもQ回のループで終わる
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
                    cur_y = M;
                }

                // 下まで到達したら終了
                if (cur_y == M) {
                    cout << cur_x + 1 << endl;
                    break;
                }
            }
        }
    }
}
