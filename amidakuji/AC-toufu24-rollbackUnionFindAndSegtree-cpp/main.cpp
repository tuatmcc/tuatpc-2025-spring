#include <bits/stdc++.h>
using namespace std;
#include "RollbackUnionFind.hpp"

struct SegmentTreeNode {
    int tl, tr;
    vector<pair<int, int>> edges;
    SegmentTreeNode *left, *right;
    SegmentTreeNode(int l, int r) : tl(l), tr(r), left(nullptr), right(nullptr) {}
};

void register_edge(SegmentTreeNode *node, int L, int R, pair<int, int> edge) {
    if (R <= node->tl || L >= node->tr)
        return;
    if (L <= node->tl && node->tr <= R) {
        node->edges.push_back(edge);
        return;
    }
    int mid = (node->tl + node->tr) / 2;
    if (!node->left) {
        node->left = new SegmentTreeNode(node->tl, mid);
        node->right = new SegmentTreeNode(mid, node->tr);
    }
    register_edge(node->left, L, R, edge);
    register_edge(node->right, L, R, edge);
}

SegmentTreeNode *build_segment_tree(const vector<pair<pair<int, int>, pair<int, int>>> &intervals, int Q) {
    SegmentTreeNode *root = new SegmentTreeNode(0, Q);
    for (const auto &[interval, edge] : intervals) {
        auto [L, R] = interval;
        register_edge(root, L, R, edge);
    }
    return root;
}

int main() {
    // 入力
    int N, M;
    cin >> N >> M;
    int Q;
    cin >> Q;
    vector<tuple<int, int, int>> queries;
    for (int i = 0; i < Q; i++) {
        int t;
        cin >> t;
        if (t == 1 || t == 2) {
            int x, y;
            cin >> x >> y;
            x--, y--; // 0-based index
            queries.emplace_back(t, x, y);
        } else {
            int s;
            cin >> s;
            s--; // 0-based index
            queries.emplace_back(t, s, -1);
        }
    }

    // 辺の追加，削除のタイミングを記録
    // 始めにN*Mの辺があって，そのうえでQ回の操作がある
    // {辺のインデックス, 追加時間}
    map<pair<int, int>, int> active_edges;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            // 縦に辺を張る
            active_edges[{i + j * N, i + (j + 1) * N}] = 0;
        }
    }
    // {時間, 辺のインデックス}
    vector<pair<pair<int, int>, pair<int, int>>> edges_interval;

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
    // すべての時間にノードを持つセグメントツリーを構築
    for (int i = 0; i < Q + 2; i++) {
        edges_interval.push_back({{i, i}, {-1, -1}});
    }

    // セグ木を構築
    // 最初と最後のノードを考慮するために+2
    auto root = build_segment_tree(edges_interval, Q + 2);

    // dfsでクエリを処理
    vector<int> ans(Q, -2);
    RollbackUnionFind uf(N * (M + 1));
    auto dfs = [&](SegmentTreeNode *node, auto &&dfs) -> void {
        int cnt = 0;
        if (!node)
            return;

        // 辺を追加
        for (auto [u, v] : node->edges) {
            if (uf.unite(u, v))
                cnt++;
        }

        if (node->tl + 1 == node->tr) {
            // 葉ノードの処理
            int t = node->tl;
            if (t < Q && get<0>(queries[t]) == 3) {
                int s = get<1>(queries[t]);
                assert(0 <= s && s < N);
                // どの行に到達するか
                for (int i = 0; i < N; i++) {
                    if (uf.find(s) == uf.find(i + N * M)) {
                        ans[t] = i;
                        break;
                    }
                }
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
}
