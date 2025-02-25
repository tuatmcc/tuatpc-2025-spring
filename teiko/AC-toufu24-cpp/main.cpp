#include <bits/stdc++.h>
#include <atcoder/modint>
#include <atcoder/dsu>
using namespace std;
using namespace atcoder;

using mint = modint998244353;

// エッジ（回路の接続部，重みはその区間の抵抗の合計）を表す構造体
struct edge {
    int to;
    mint resist;

    bool operator<(const edge &other) const {
        return to < other.to;
    }
};

// ハッシュ関数
struct EdgeHash {
    size_t operator()(const edge &e) const {
        return hash<int>()(e.to) ^ hash<int>()(e.resist.val());
    }
};

/// @brief 0 抵抗のエッジをまとめる
/// @param graph グラフ
/// @param start_idx スタートノードのインデックス
/// @param goal_idx ゴールノードのインデックス
/// @return 縮約後のグラフとスタート・ゴールノードのインデックス
pair<vector<vector<edge>>, pair<int, int>> reduce_zero_edge(
    const vector<vector<edge>> &graph, int start_idx, int goal_idx) {
    int n = graph.size();
    dsu dsu(n);
    for (int i = 0; i < n; i++) {
        for (const auto &e : graph[i]) {
            if (e.resist.val() == 0) {
                dsu.merge(i, e.to);
            }
        }
    }
    vector<int> comp(n);
    map<int, int> comp_map;
    int new_id = 0;
    for (int i = 0; i < n; i++) {
        comp[i] = dsu.leader(i);
        if (comp_map.find(comp[i]) == comp_map.end()) {
            comp_map[comp[i]] = new_id++;
        }
    }
    vector<vector<edge>> new_graph(new_id);
    for (int i = 0; i < n; i++) {
        for (const auto &e : graph[i]) {
            if (e.resist.val() != 0) {
                int u = comp_map[dsu.leader(i)];
                int v = comp_map[dsu.leader(e.to)];
                if (u != v) {
                    new_graph[u].push_back(edge{v, e.resist});
                }
            }
        }
    }
    int new_start = comp_map[dsu.leader(start_idx)];
    int new_goal = comp_map[dsu.leader(goal_idx)];
    return {new_graph, {new_start, new_goal}};
}

/// @brief 入力からグラフを構築する
/// @param s 入力のグリッド
/// @return グラフ, スタートノードのインデックス, ゴールノードのインデックス
tuple<vector<vector<edge>>, int, int> make_graph(const vector<string> &s) {
    int h = s.size();
    int w = s[0].size();
    pair<int, int> start, goal;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (j + 3 <= w && s[i].substr(j, 3) == "o--")
                start = {i, j};
            else if (j + 3 <= w && s[i].substr(j, 3) == "--o")
                goal = {i, j + 2};
        }
    }
    int start_idx, goal_idx;
    map<pair<int, int>, int> node_idx;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (s[i][j] == 'o' || s[i][j] == '+') {
                if (!node_idx.count({i, j}))
                    node_idx[{i, j}] = node_idx.size();
                if (i == start.first && j == start.second)
                    start_idx = node_idx[{i, j}];
                if (i == goal.first && j == goal.second)
                    goal_idx = node_idx[{i, j}];
            }
        }
    }

    vector<vector<edge>> graph(node_idx.size());
    // 右方向と下方向にのみ探索
    int dx[2] = {0, 1}, dy[2] = {1, 0};
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (node_idx.count({i, j})) {
                for (int direction = 0; direction < 2; direction++) {
                    int ni = i + dx[direction], nj = j + dy[direction];
                    mint resist = 0;
                    while (0 <= ni && ni < h &&
                           0 <= nj && nj < w &&
                           node_idx.find({ni, nj}) == node_idx.end() &&
                           s[ni][nj] != ' ') {

                        if (s[ni][nj] == 'v' || s[ni][nj] == '^') {
                            resist = resist + 1;
                            while (0 <= ni && ni < h &&
                                   0 <= nj && nj < w &&
                                   (s[ni][nj] == 'v' || s[ni][nj] == '^')) {
                                ni += dx[direction];
                                nj += dy[direction];
                            }
                            continue;
                        }
                        ni += dx[direction];
                        nj += dy[direction];
                    }

                    if (node_idx.count({ni, nj})) {
                        graph[node_idx[{i, j}]].emplace_back(node_idx[{ni, nj}], resist);
                        graph[node_idx[{ni, nj}]].emplace_back(node_idx[{i, j}], resist);
                    }
                }
            }
        }
    }

    auto [new_graph, new_start_goal] = reduce_zero_edge(graph, start_idx, goal_idx);
    return {new_graph, new_start_goal.first, new_start_goal.second};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w = 0;
    cin >> h;
    cin.ignore();
    vector<string> s(h);
    for (auto &si : s) {
        getline(cin, si);
        w = max(w, (int)si.size());
    }
    // 各行の長さをそろえる
    for (auto &line : s)
        if ((int)line.size() < w)
            line.resize(w, '.');

    auto [g, start_idx, goal_idx] = make_graph(s);

    int n = g.size();
    vector<multiset<edge>> graph(n);
    for (int i = 0; i < n; i++) {
        for (auto &e : g[i]) {
            graph[i].insert(e);
        }
    }

    // cerr << graph.size() << endl;
    // for (int i = 0; i < graph.size(); i++) {
    //     for (auto &e : graph[i]) {
    //         cerr << i << " " << e.to << " " << e.resist.val() << endl;
    //     }
    // }
    // cerr << "start goal" << endl;
    // cerr << start_idx << " " << goal_idx << endl;

    // 直列・並列縮約の反復処理
    vector<bool> active(n, true);
    int cnt = 0;
    while (true) {
        cnt++;
        // if (cnt % 100 == 0) {
        //     // cerr << "cnt: " << cnt << endl;
        //     int active_cnt = 0;
        //     for (int i = 0; i < n; i++) {
        //         if (active[i])
        //             active_cnt++;
        //     }
        //     cerr << "active_cnt: " << active_cnt << endl;
        // }
        bool reduced = false;
        // --- 並列縮約 ---
        for (int u = 0; u < n; u++) {
            if (!active[u])
                continue;
            map<int, mint> combined;
            for (auto &e : graph[u]) {
                if (!active[e.to])
                    continue;
                int v = e.to;
                if (combined.find(v) == combined.end())
                    combined[v] = e.resist;
                else {
                    // 並列接続： 1/R_new = 1/R_existing + 1/R_edge
                    mint inv_existing = combined[v].inv();
                    mint inv_new = e.resist.inv();
                    combined[v] = (inv_existing + inv_new).inv();
                }
            }
            vector<edge> newEdges;
            for (auto &p : combined)
                newEdges.push_back({p.first, p.second});
            graph[u].clear();
            for (auto &e : newEdges)
                graph[u].insert(e);
        }
        // --- 直列縮約 ---
        // スタート・ゴール以外のノードで次数が 2 のものを縮約
        for (int v = 0; v < n; v++) {
            if (!active[v])
                continue;
            if (v == start_idx || v == goal_idx)
                continue;
            if (graph[v].size() != 2)
                continue;
            // ノード v に接続する隣接ノード u, w とそのエッジ抵抗
            // int u = graph[v][0].to, w = graph[v][1].to;
            // mint r1 = graph[v][0].resist, r2 = graph[v][1].resist;
            auto it = graph[v].begin();
            int u = it->to;
            mint r1 = it->resist;
            it++;
            int w = it->to;
            mint r2 = it->resist;
            // 直列接続：合成抵抗は r1 + r2
            mint newR = r1 + r2;

            // ノード v を削除
            active[v] = false;

            // u と w の間に新たなエッジ（直列接続の合成抵抗）を追加
            bool found = false;
            for (auto &e : graph[u]) {
                if (e.to == w) {
                    // 並列接続の場合に備え合成
                    mint inv_existing = e.resist.inv();
                    mint inv_new = newR.inv();
                    mint new_resist = (inv_existing + inv_new).inv();
                    graph[u].erase(e);
                    graph[u].insert({w, new_resist});
                    found = true;
                    break;
                }
            }
            if (!found) {
                graph[u].insert({w, newR});
            }
            found = false;
            for (auto &e : graph[w]) {
                if (e.to == u) {
                    mint inv_existing = e.resist.inv();
                    mint inv_new = newR.inv();
                    mint new_resist = (inv_existing + inv_new).inv();
                    graph[w].erase(e);
                    graph[w].insert({u, new_resist});
                    found = true;
                    break;
                }
            }
            if (!found) {
                graph[w].insert({u, newR});
            }

            reduced = true;
        }

        if (!reduced)
            break;
    }

    // cerr << graph.size() << endl;
    // for (int i = 0; i < graph.size(); i++) {
    //     if (!active[i])
    //         continue;
    //     for (auto &e : graph[i]) {
    //         cerr << i << " " << e.to << " " << e.resist.val() << endl;
    //     }
    // }
    // cerr << "start goal" << endl;
    // cerr << start_idx << " " << goal_idx << endl;

    // 最終的に、スタートとゴールを直接結ぶエッジが残っているはず
    mint ans = 0;
    for (auto &e : graph[start_idx]) {
        if (e.to == goal_idx) {
            ans = e.resist;
            break;
        }
    }
    cout << ans.val() << endl;
}
