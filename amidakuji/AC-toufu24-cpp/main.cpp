#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(0);
    ios::sync_with_stdio(false);
    // 入力処理
    int N, M_orig, Q;
    cin >> N >> M_orig >> Q;

    vector<vector<int>> queries(Q, vector<int>(3));
    vector<int> ys;

    for (int i = 0; i < Q; i++) {
        int t;
        cin >> t;
        if (t == 1 || t == 2) {
            int x, y;
            cin >> x >> y;
            queries[i] = {t, x, y};
            ys.push_back(y);
        } else {
            int s;
            cin >> s;
            queries[i] = {t, s, -1};
        }
    }

    // y座標の座標圧縮
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    unordered_map<int, int> zipy;
    for (int i = 0; i < (int)ys.size(); i++) {
        zipy[ys[i]] = i + 1;
    }
    for (auto &q : queries) {
        if (q[0] != 3) {
            q[2] = zipy[q[2]];
        }
    }

    // 平方分割
    int M = ys.size();
    int block_size = sqrt(M) + 1;
    int block_cnt = (M + block_size - 1) / block_size + 1;

    vector<unordered_map<int, int>> to(block_cnt);
    vector<unordered_map<int, unordered_set<int>>> lines(block_cnt);

    auto block_first_pos = [&](int x, int y) -> int {
        int block_idx = y / block_size;
        int nx = x, ny = y % block_size;
        while (ny >= 0) {
            if (lines[block_idx].contains(nx - 1) &&
                lines[block_idx][nx - 1].contains(ny)) {
                nx -= 1;
            } else if (lines[block_idx].contains(nx) &&
                       lines[block_idx][nx].contains(ny)) {
                nx += 1;
            }
            ny--;
        }
        return nx;
    };

    vector<int> ans;
    for (const auto &q : queries) {
        int t = q[0], x = q[1], y = q[2];
        if (t == 1 || t == 2) {
            int block_id = y / block_size;
            int left = block_first_pos(x, y);
            int right = block_first_pos(x + 1, y);
            if (!to[block_id].contains(left))
                to[block_id][left] = left;
            if (!to[block_id].contains(right))
                to[block_id][right] = right;

            swap(to[block_id][left], to[block_id][right]);

            if (t == 1) {
                lines[block_id][x].insert(y % block_size);
            } else {
                lines[block_id][x].erase(y % block_size);
            }
        } else {
            int cur = x;
            for (int i = 0; i < block_cnt; i++) {
                if (to[i].contains(cur))
                    cur = to[i][cur];
            }
            ans.push_back(cur);
        }
    }

    for (const auto &s : ans)
        cout << s << '\n';
}
