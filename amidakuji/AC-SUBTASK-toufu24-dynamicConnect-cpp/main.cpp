// 参考: https://yukicoder.me/wiki/offline_dsp

#include <bits/stdc++.h>
using namespace std;
#define int int64_t
// https://nyaannyaan.github.io/library/data-structure/rollback-union-find.hpp.html から引用&改変

struct HistoryEntry {
    enum Type { UF_OPERATION,
                DATA_OPERATION };
    Type type;
    int index;
    int old_value;
};

struct RollbackUnionFindWithData {
    vector<int> data;            // Union-Findの親とサイズを管理
    vector<int> node_data;       // 各ノードに載せるint型のデータ
    stack<HistoryEntry> history; // 操作履歴
    int inner_snap;              // スナップショット位置

    RollbackUnionFindWithData(int sz) : inner_snap(0) {
        data.assign(sz, -1); // Union-Findを初期化

        // ノードデータを初期化
        node_data.resize(sz);
        for (int i = 0; i < sz; i++) {
            node_data[i] = i;
        }
    }

    // データを設定
    void set_data(int k, int val) {
        history.push({HistoryEntry::DATA_OPERATION, k, node_data[k]}); // 変更前の値を記録
        node_data[k] = val;                                            // 新しい値を設定
    }

    // データを取得
    int get_data(int k) const {
        return node_data[find(k)];
    }

    // 2つの要素を結合
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        history.push({HistoryEntry::UF_OPERATION, x, data[x]}); // xの変更前の値を記録
        history.push({HistoryEntry::UF_OPERATION, y, data[y]}); // yの変更前の値を記録

        if (x == y) {
            history.push({HistoryEntry::DATA_OPERATION, -1, -1}); // ダミーの操作を積む
            return false;
        }
        if (data[x] > data[y])
            swap(x, y);

        // 各集合の最大値(下端を想定)を設定
        int connected_max_value = max({node_data[x], node_data[y]});
        set_data(x, connected_max_value);

        // x,yを結合すると、ルートノードはxになる
        data[x] += data[y];
        data[y] = x;
        return true;
    }

    // 要素のルートを検索
    int find(int k) const {
        if (data[k] < 0)
            return k;
        return find(data[k]);
    }

    // 2つの要素が同じ集合に属するか判定
    bool same(int x, int y) const {
        return find(x) == find(y);
    }

    // 集合のサイズを取得
    int size(int k) const {
        return -data[find(k)];
    }

    // 最後のUnite操作を元に戻す
    void undo() {
        // ufの2回分とnode_dataの1回分の操作を取り消す
        for (int i = 0; i < 3; i++) {
            auto [type, index, old_value] = history.top();
            history.pop();
            if (type == HistoryEntry::UF_OPERATION) {
                data[index] = old_value;
            } else {
                node_data[index] = old_value;
            }
        }
    }

    // スナップショットを記録
    void snapshot() {
        inner_snap = history.size();
    }

    // 指定された状態にロールバック
    void rollback(int state = -1) {
        if (state == -1)
            state = inner_snap;
        assert(state <= (int)history.size());
        while (state < (int)history.size())
            undo();
    }
};

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
            if (u == -1 || v == -1)
                continue;
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
                for (int i = 0; i < N; i++) {
                    if (convert.contains(i + N * (M + 1)) && convert.contains(s)) {
                        if (uf.same(convert[s], convert[i + N * (M + 1)])) {
                            ans[t] = i;
                            break;
                        }
                    }
                }
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
}
