#include <bits/stdc++.h>
using namespace std;

// ----------有理数型----------
struct Fraction {
    int64_t numerator, denominator;

    // 整数から作成（x → x/1）
    Fraction(int64_t x) : numerator(x), denominator(1) {}

    // 2つの整数から作成(a, b -> a/b)
    Fraction(int64_t num, int64_t den) {
        if (den == 0) {
            throw invalid_argument("Denominator cannot be zero");
        }
        int64_t g = gcd(num, den);
        numerator = num / g;
        denominator = den / g;

        // 分母を正に統一
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    // 演算子オーバーロード
    Fraction operator+(const Fraction &other) const {
        return Fraction(numerator * other.denominator + other.numerator * denominator,
                        denominator * other.denominator);
    }

    Fraction operator-(const Fraction &other) const {
        return Fraction(numerator * other.denominator - other.numerator * denominator,
                        denominator * other.denominator);
    }

    Fraction operator*(const Fraction &other) const {
        return Fraction(numerator * other.numerator, denominator * other.denominator);
    }

    Fraction operator/(const Fraction &other) const {
        if (other.numerator == 0) {
            throw invalid_argument("Division by zero");
        }
        return Fraction(numerator * other.denominator, denominator * other.numerator);
    }
};

ostream &operator<<(ostream &os, const Fraction &frac) {
    return os << frac.numerator << "/" << frac.denominator;
}

// ----------エッジ（回路の抵抗）を表す構造体----------
struct edge {
    int to;
    Fraction resist;
};

/// @brief 入力からグラフを構築する
/// @param s 入力のグリッド
/// @return グラフ, スタートノードのインデックス, ゴールノードのインデックス
tuple<vector<vector<edge>>, int, int> make_graph(const vector<string> &s) {
    int h = s.size();
    int w = s[0].size();
    // スタートとゴールの座標を探す
    pair<int, int> start, goal;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (j + 3 <= w && s[i].substr(j, 3) == "o--") {
                start = {i, j};
            } else if (j + 3 <= w && s[i].substr(j, 3) == "--o") {
                goal = {i, j + 2};
            }
        }
    }

    // ノードのインデックスを割り振る
    int start_idx, goal_idx;
    map<pair<int, int>, int> node_idx;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (s[i][j] == 'o' || s[i][j] == '+') {
                node_idx[{i, j}] = node_idx.size();
                if (i == start.first && j == start.second) {
                    start_idx = node_idx[{i, j}];
                }
                if (i == goal.first && j == goal.second) {
                    goal_idx = node_idx[{i, j}];
                }
            }
        }
    }

    // グラフを構築
    vector<vector<edge>> graph(node_idx.size());
    // 右と下方向にのみ進む
    int dx[] = {0, 1};
    int dy[] = {1, 0};
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (s[i][j] == 'o' || s[i][j] == '+') {
                for (int direction = 0; direction < 2; direction++) {
                    int ni = i + dx[direction];
                    int nj = j + dy[direction];
                    int resist = 0;
                    while (ni >= 0 && ni < h && nj >= 0 && nj < w && !node_idx.contains({ni, nj})) {
                        if (s[ni][nj] == 'v' || s[ni][nj] == '^') { // 抵抗だった場合
                            resist++;
                            // 抵抗を飛び越える
                            while (ni >= 0 && ni < h && nj >= 0 && nj < w && (s[ni][nj] == 'v' || s[ni][nj] == '^')) {
                                ni += dx[direction];
                                nj += dy[direction];
                            }
                            continue;
                        }
                        ni += dx[direction];
                        nj += dy[direction];
                    }
                    if (node_idx.contains({ni, nj})) {
                        graph[node_idx[{i, j}]].push_back({node_idx[{ni, nj}], Fraction(resist)});
                        graph[node_idx[{ni, nj}]].push_back({node_idx[{i, j}], Fraction(resist)});
                    }
                }
            }
        }
    }

    return {graph, start_idx, goal_idx};
}

/// @brief 2つのノード間に複数のエッジがある場合、それらを並列合成して1本のエッジにまとめる
/// @param n ノード数
/// @param graph グラフ
/// @param removed 削除済みノードのフラグ
/// @return 圧縮を行った場合は true、何も変更がなければ false
bool reduce_parallel(int n, vector<vector<edge>> &graph, vector<bool> &removed) {
    bool changed = false; // 変更があったかどうかのフラグ

    // ノード i と j の組み合わせを全探索
    for (int i = 0; i < n; i++) {
        if (removed[i]) continue;
        for (int j = i + 1; j < n; j++) {
            if (removed[j]) continue;

            // ノード i の隣接リストから、接続先が j であるエッジのインデックスを収集
            vector<int> indices;
            for (int k = 0; k < graph[i].size(); k++) {
                if (graph[i][k].to == j) {
                    indices.push_back(k);
                }
            }
            // 複数のエッジが存在する場合は並列合成
            if (indices.size() > 1) {
                changed = true;
                // 各エッジの逆数を足し合わせる： Σ (1 / R)
                Fraction inv_sum = {0, 1}; // 初期値は 0/1
                for (int k : indices) {
                    Fraction invR = Fraction(1, 1) / graph[i][k].resist;
                    inv_sum = inv_sum + invR;
                }
                // 合成抵抗 = 1 / (Σ (1/R))
                Fraction new_R = Fraction(1, 1) / inv_sum;

                // --- 既存の並列エッジを削除する処理 ---
                // ノード i の隣接リストから、接続先が j のエッジを削除
                auto &edges_i = graph[i];
                edges_i.erase(remove_if(edges_i.begin(), edges_i.end(), [j](const edge &e) {
                                  return e.to == j;
                              }),
                              edges_i.end());
                // 同様に、ノード j の隣接リストから、接続先が i のエッジを削除
                auto &edges_j = graph[j];
                edges_j.erase(remove_if(edges_j.begin(), edges_j.end(), [i](const edge &e) {
                                  return e.to == i;
                              }),
                              edges_j.end());

                // 新たに並列合成したエッジを追加
                edges_i.push_back({j, new_R});
                edges_j.push_back({i, new_R});
            }
        }
    }
    return changed;
}

/// @brief 隣接数が2のノードを直列接続とみなし、両側のエッジの抵抗値を加算して新たなエッジにまとめる
/// @param start_idx スタートノードのインデックス
/// @param end_idx ゴールノードのインデックス
/// @param n ノード数
/// @param graph グラフ
/// @param removed 削除済みノードのフラグ
/// @return 圧縮を行った場合は true、何も変更がなければ false
bool reduce_series(int start_idx, int end_idx, int n, vector<vector<edge>> &graph, vector<bool> &removed) {
    bool changed = false;
    for (int u = 0; u < n; u++) {
        if (removed[u]) continue;                     // u がすでに削除されている場合はスキップ
        if (u == start_idx || u == end_idx) continue; // 端は対象外
        if (graph[u].size() == 2) {                   // 隣接エッジが 2 本なら直列とみなす
            changed = true;
            // ノード u に接続している2本のエッジを取得
            int v = graph[u][0].to;           // 1本目の隣接ノード
            int w = graph[u][1].to;           // 2本目の隣接ノード
            Fraction R1 = graph[u][0].resist; // v - u の抵抗
            Fraction R2 = graph[u][1].resist; // u - w の抵抗
            // 直列接続では抵抗値は単純加算
            Fraction new_R = R1 + R2;

            // --- ノード u を経由しているエッジを、隣接ノード側からも削除 ---
            auto &edges_v = graph[v];
            edges_v.erase(remove_if(edges_v.begin(), edges_v.end(), [u](const edge &e) {
                              return e.to == u;
                          }),
                          edges_v.end());
            auto &edges_w = graph[w];
            edges_w.erase(remove_if(edges_w.begin(), edges_w.end(), [u](const edge &e) {
                              return e.to == u;
                          }),
                          edges_w.end());
            // --------------------------------------------------------------

            // ノード u を削除済みにする
            removed[u] = true;
            graph[u].clear();

            // ノード v と w を直列接続する新たなエッジを追加
            graph[v].push_back({w, new_R});
            graph[w].push_back({v, new_R});
        }
    }
    return changed;
}

int main() {
    vector<string> s;
    string tmp;
    while (getline(cin, tmp)) {
        s.push_back(tmp);
    }

    // 長さを揃える
    int max_len = 0;
    for (const auto &line : s) {
        max_len = max(max_len, (int)line.size());
    }
    for (auto &line : s) {
        line.resize(max_len, '.');
    }

    auto [graph, start_idx, goal_idx] = make_graph(s);

    // -------------グラフ圧縮-------------
    int n = graph.size();
    vector<bool> removed(n, false);
    while (true) {
        // 並列回路を圧縮する
        if (reduce_parallel(n, graph, removed)) {
            continue; // 圧縮が行われたら再度最初から処理
        }
        // 直列回路を圧縮する
        if (reduce_series(start_idx, goal_idx, n, graph, removed)) {
            continue; // 圧縮が行われたら再度最初から処理
        }
        // 並列圧縮と直列圧縮のどちらも適用できなければ終了
        break;
    }

    // スタートノードとゴールノード以外のノードは削除されているはず
    for (int i = 0; i < graph.size(); i++) {
        if (i == start_idx || i == goal_idx) {
            assert(graph[i].size() == 1);
            assert(!removed[i]);
        } else {
            assert(graph[i].size() == 0);
            assert(removed[i]);
        }
    }

    Fraction ans = graph[start_idx][0].resist;
    cout << ans << endl;
}
