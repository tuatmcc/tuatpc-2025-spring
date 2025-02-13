// 参考: https://yukicoder.me/wiki/offline_dsp

// O(Q log^2(Q)) で解けてると思っている

#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#include "OfflineDynamicConnectivity.hpp"

int32_t main() {
    // 入力
    int N, M;
    cin >> N >> M;
    int Q;
    cin >> Q;
    vector<tuple<int, int, int>> queries;
    set<int> require_node;                  // 構築が必要なノードの集合
    map<int, set<int>> require_init_height; // 縦線ごとの構築が必要な高さ
    for (int i = 0; i < Q; i++) {
        int t;
        cin >> t;
        if (t == 1 || t == 2) {
            int x, y;
            cin >> x >> y;
            x--; // 0-based index
            queries.emplace_back(t, x, y);
            // 横線で変化する頂点
            require_node.insert(x + y * N);
            require_node.insert(x + (y + 1) * N);
            require_node.insert((x + 1) + y * N);
            require_node.insert((x + 1) + (y + 1) * N);
            require_init_height[x].insert(y);
            require_init_height[x].insert(y + 1);
            require_init_height[x + 1].insert(y);
            require_init_height[x + 1].insert(y + 1);

            // 端点の追加
            require_node.insert(x + 0 * N);
            require_node.insert(x + (M + 1) * N);
            require_node.insert((x + 1) + 0 * N);
            require_node.insert((x + 1) + (M + 1) * N);
            require_init_height[x].insert(0);
            require_init_height[x].insert(M + 1);
            require_init_height[x + 1].insert(0);
            require_init_height[x + 1].insert(M + 1);
        } else {
            int s;
            cin >> s;
            s--; // 0-based index

            queries.emplace_back(t, s, -1);
            require_node.insert(s + 0 * N);
            require_node.insert(s + (M + 1) * N);
            require_init_height[s].insert(0);
            require_init_height[s].insert(M + 1);
        }
    }

    OfflineDynamicConnectivity odc(require_node.size() + 2, Q + 2);
    map<int, int> convert, rev_convert;
    int idx = 0;
    int prev = -1;
    for (auto x : require_node) {
        assert(prev < x);
        prev = x;
        convert[x] = idx;
        rev_convert[idx] = x;
        idx++;
    }

    // 初期状態
    for (auto [x, ys] : require_init_height) {
        vector<int> y_vec(ys.begin(), ys.end());
        for (int i = 0; i < y_vec.size() - 1; i++) {
            odc.insert(0, convert[x + y_vec[i] * N], convert[x + y_vec[i + 1] * N]);
        }
    }

    // クエリの追加
    for (int i = 1; i <= Q; i++) {
        int t, x, y;
        tie(t, x, y) = queries[i - 1];
        if (t == 1) {
            // 斜めに辺を張る
            odc.erase(i, convert[x + y * N], convert[x + (y + 1) * N]);
            odc.erase(i, convert[(x + 1) + y * N], convert[(x + 1) + (y + 1) * N]);
            odc.insert(i, convert[x + y * N], convert[(x + 1) + (y + 1) * N]);
            odc.insert(i, convert[(x + 1) + y * N], convert[x + (y + 1) * N]);
        } else if (t == 2) {
            // 縦に辺を張る
            odc.erase(i, convert[x + y * N], convert[(x + 1) + (y + 1) * N]);
            odc.erase(i, convert[(x + 1) + y * N], convert[x + (y + 1) * N]);
            odc.insert(i, convert[x + y * N], convert[x + (y + 1) * N]);
            odc.insert(i, convert[(x + 1) + y * N], convert[(x + 1) + (y + 1) * N]);
        } else {
            odc.insert(i, require_node.size(), require_node.size() + 1);
            odc.erase(i, require_node.size(), require_node.size() + 1);
        }
    }

    odc.build();
    odc.run([&](int i) -> void {
        int t, x, y;
        tie(t, x, y) = queries[i];
        if (t == 3) {
            cout << rev_convert[odc.uf.get_data(convert[x + 0 * N])] - N * (M + 1) + 1 << endl;
        }
    });
}
