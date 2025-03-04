// 参考: https://yukicoder.me/wiki/offline_dsp

// O(Q log^2(Q)) で解けてると思っている

#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#include "RollbackUnionFindWithData.hpp"

struct SegmentTreeNode {
    int tl, tr;                    // 区間[l, r)
    vector<pair<int, int>> edges;  // ノードで管理する辺
    SegmentTreeNode *left, *right; // セグ木の子ノード
    SegmentTreeNode(int l, int r) : tl(l), tr(r), left(nullptr), right(nullptr) {}
};

void register_edge(SegmentTreeNode *node, int L, int R, pair<int, int> edge) {
    // 区間[L, R)とノードの区間が交差しない場合は何もしない
    if (R <= node->tl || L >= node->tr)
        return;
    // ノードの区間が完全に[L, R)を含む場合は辺を追加
    if (L <= node->tl && node->tr <= R) {
        node->edges.push_back(edge);
        return;
    }
    // そうでない場合は再帰的に子ノードに辺を追加
    int mid = (node->tl + node->tr) / 2;
    if (!node->left) {
        node->left = new SegmentTreeNode(node->tl, mid);
        node->right = new SegmentTreeNode(mid, node->tr);
    }
    register_edge(node->left, L, R, edge);
    register_edge(node->right, L, R, edge);
}

SegmentTreeNode *build_segment_tree(const vector<pair<pair<int, int>, pair<int, int>>> &intervals, int Q) {
    // セグメントツリーを構築
    SegmentTreeNode *root = new SegmentTreeNode(0, Q);
    for (const auto &[interval, edge] : intervals) {
        auto [L, R] = interval;
        register_edge(root, L, R, edge);
    }
    return root;
}

int32_t main() {
    // 入力
    int N, M;
    cin >> N >> M;
    int Q;
    cin >> Q;
    vector<tuple<int, int, int>> queries;
    map<int, set<int>> require_height; // 縦線ごとの構築が必要な高さ
    for (int i = 0; i < Q; i++) {
        int t;
        cin >> t;
        if (t == 1 || t == 2) {
            int x, y;
            cin >> x >> y;
            x--; // 0-based index
            queries.emplace_back(t, x, y);
            // 横線で変化する頂点
            require_height[x].insert(y);
            require_height[x].insert(y + 1);
            require_height[x + 1].insert(y);
            require_height[x + 1].insert(y + 1);

            // 端点の追加
            require_height[x].insert(0);
            require_height[x].insert(M + 1);
            require_height[x + 1].insert(0);
            require_height[x + 1].insert(M + 1);
        } else {
            int s;
            cin >> s;
            s--; // 0-based index

            queries.emplace_back(t, s, -1);
            require_height[s].insert(0);
            require_height[s].insert(M + 1);
        }
    }

    // 辺の生存期間を記録
    // 辺の追加，削除のタイミングを記録
    // {辺のインデックス, 追加時間}
    map<pair<int, int>, int> active_edges;
    set<int> require_node_set; // 構築が必要なノードの集合
    // 縦線ごとに辺を張る
    for (auto [x, ys] : require_height) {
        vector<int> y_vec(ys.begin(), ys.end());
        for (int i = 0; i < y_vec.size() - 1; i++) {
            pair<int, int> edge = {x + y_vec[i] * N, x + y_vec[i + 1] * N};
            active_edges[edge] = 0;
            require_node_set.insert(x + y_vec[i] * N);
            require_node_set.insert(x + y_vec[i + 1] * N);
        }
    }

    // {時間, 辺のインデックス}
    vector<pair<pair<int, int>, pair<int, int>>> edges_interval;
    // すべての時間にノードを持つセグメントツリーを構築
    for (int i = 0; i < Q + 2; i++) {
        edges_interval.push_back({{i, i}, {-1, -1}});
    }

    for (int i = 1; i <= Q; i++) {
        auto [t, x, y] = queries[i - 1];
        if (t == 1) {
            // 辺の追加，削除のタイミングを記録
            pair<int, int> edge1 = {x + y * N, x + (y + 1) * N};
            pair<int, int> edge2 = {(x + 1) + y * N, (x + 1) + (y + 1) * N};
            edges_interval.push_back({{active_edges[edge1], i}, edge1});
            edges_interval.push_back({{active_edges[edge2], i}, edge2});
            active_edges.erase(edge1);
            active_edges.erase(edge2);

            // 斜めに辺を張る
            pair<int, int> new_edge1 = {x + y * N, (x + 1) + (y + 1) * N};
            pair<int, int> new_edge2 = {(x + 1) + y * N, x + (y + 1) * N};
            active_edges[new_edge1] = i;
            active_edges[new_edge2] = i;
        } else if (t == 2) {
            // 辺の追加，削除のタイミングを記録
            pair<int, int> edge1 = {x + y * N, (x + 1) + (y + 1) * N};
            pair<int, int> edge2 = {(x + 1) + y * N, x + (y + 1) * N};
            edges_interval.push_back({{active_edges[edge1], i}, edge1});
            edges_interval.push_back({{active_edges[edge2], i}, edge2});
            active_edges.erase(edge1);
            active_edges.erase(edge2);

            // 縦に辺を張る
            pair<int, int> new_edge1 = {x + y * N, x + (y + 1) * N};
            pair<int, int> new_edge2 = {(x + 1) + y * N, (x + 1) + (y + 1) * N};
            active_edges[new_edge1] = i;
            active_edges[new_edge2] = i;
        }
    }
    // 残りの辺の削除のタイミングを記録
    for (auto [edge, st] : active_edges) {
        edges_interval.push_back({{st, Q + 1}, edge});
    }

    // ノードのインデックスを振り直す
    map<int, int> convert;
    map<int, int> convert_rev;
    int idx = 0;
    assert(require_node_set.size() <= 8 * Q);
    for (int x : require_node_set) {
        convert[x] = idx++;
        convert_rev[convert[x]] = x;
    }

    // edges_intervalもインデックスを振り直す
    for (auto &p : edges_interval) {
        if (p.second.first == -1) {
            continue;
        }
        p.second.first = convert[p.second.first];
        p.second.second = convert[p.second.second];
    }

    // セグ木を構築
    // 最初と最後のノードを考慮するために+2
    auto root = build_segment_tree(edges_interval, Q + 2);

    // dfsでクエリを処理
    vector<int> ans(Q, -2);
    RollbackUnionFindWithData uf(require_node_set.size());

    auto dfs = [&](SegmentTreeNode *node, auto &&dfs) -> void {
        int cnt = 0;
        if (!node)
            return;

        // 辺を追加
        for (auto [u, v] : node->edges) {
            if (u == -1 || v == -1) continue;
            if (uf.unite(u, v))
                cnt++;
        }

        if (node->tl + 1 == node->tr) {
            // 葉ノードの処理
            int t = node->tl - 1;
            if (0 <= t && t < Q && get<0>(queries[t]) == 3) {
                int s = get<1>(queries[t]);
                assert(0 <= s && s < N);
                // どの行に到達するか
                ans[t] = convert_rev[uf.get_data(convert[s])] - N * (M + 1);
                assert(ans[t] >= 0);
                assert(ans[t] < N);
            }
        } else {
            // 左右の子に伝搬
            dfs(node->left, dfs);
            dfs(node->right, dfs);
        }

        // 帰るときに巻き戻す
        while (cnt--)
            uf.undo();
    };
    dfs(root, dfs);

    // 出力
    for (int i = 0; i < Q; i++) {
        if (get<0>(queries[i]) == 3) {
            cout << ans[i] + 1 << "\n";
        }
    }

    // メモリ解放
    // auto delete_tree = [&](SegmentTreeNode *node, auto &&delete_tree) -> void {
    //     if (!node)
    //         return;
    //     delete_tree(node->left, delete_tree);
    //     delete_tree(node->right, delete_tree);
    //     delete node;
    // };
    // delete_tree(root, delete_tree);
}
