// https://ei1333.github.io/library/structure/union-find/union-find-undo.hpp
// https://ei1333.github.io/library/other/offline-dynamic-connectivity.hpp
// から引用&改変

struct HistoryEntry {
    enum Type { UF_OPERATION,
                DATA_OPERATION };
    Type type;
    int index;
    int old_value;
};

struct UnionFindUndo {
    vector<int> data;
    stack<HistoryEntry> history;
    vector<int> connected_components_max; // 各連結成分の最大値(根ノードのみ有効)

    UnionFindUndo(int sz) {
        data.assign(sz, -1);
        // 連結成分の最大値を初期化
        connected_components_max.resize(sz);
        for (int i = 0; i < sz; i++) {
            connected_components_max[i] = i;
        }
    }

    // データを設定
    void set_data(int k, int val) {
        history.push({HistoryEntry::DATA_OPERATION, k, connected_components_max[k]}); // 変更前の値を記録
        connected_components_max[k] = val;                                            // 新しい値を設定
    }

    // データを取得
    int get_data(int k) {
        return connected_components_max[find(k)];
    }

    // 2つの要素を結合
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        history.push({HistoryEntry::UF_OPERATION, x, data[x]}); // xの変更前の値を記録
        history.push({HistoryEntry::UF_OPERATION, y, data[y]}); // yの変更前の値を記録

        if (x == y) return false;
        if (data[x] > data[y]) swap(x, y);

        // 各集合の最大値(下端を想定)を設定
        int connected_max_value = max({connected_components_max[x], connected_components_max[y]});
        set_data(x, connected_max_value);

        // x,yを結合すると、ルートノードはxになる
        data[x] += data[y];
        data[y] = x;
        return true;
    }

    int find(int k) {
        if (data[k] < 0) return (k);
        return (find(data[k]));
    }

    int size(int k) { return (-data[find(k)]); }

    // 最後のUnite操作を元に戻す
    void undo() {
        // ufの2回分とconnected_components_maxの1回分の操作を取り消す
        for (int i = 0; i < 3; i++) {
            auto [type, index, old_value] = history.top();
            history.pop();
            if (type == HistoryEntry::UF_OPERATION) {
                data[index] = old_value;
            } else {
                connected_components_max[index] = old_value;
            }
        }
    }

    void snapshot() {
        while (history.size())
            history.pop();
    }

    void rollback() {
        while (history.size())
            undo();
    }
};

struct OfflineDynamicConnectivity {
    using edge = pair<int, int>;

    UnionFindUndo uf;
    int V, Q, segsz;
    vector<vector<edge>> seg;
    int comp;

    vector<pair<pair<int, int>, edge>> pend;
    map<edge, int> cnt, appear;

    OfflineDynamicConnectivity(int V, int Q) : uf(V), V(V), Q(Q), comp(V) {
        segsz = 1;
        while (segsz < Q)
            segsz <<= 1;
        seg.resize(2 * segsz - 1);
    }

    void insert(int idx, int s, int t) {
        auto e = minmax(s, t);
        if (cnt[e]++ == 0) appear[e] = idx;
    }

    void erase(int idx, int s, int t) {
        auto e = minmax(s, t);
        if (--cnt[e] == 0) pend.emplace_back(make_pair(appear[e], idx), e);
    }

    void add(int a, int b, const edge &e, int k, int l, int r) {
        if (r <= a || b <= l) return;
        if (a <= l && r <= b) {
            seg[k].emplace_back(e);
            return;
        }
        add(a, b, e, 2 * k + 1, l, (l + r) >> 1);
        add(a, b, e, 2 * k + 2, (l + r) >> 1, r);
    }

    void add(int a, int b, const edge &e) {
        add(a, b, e, 0, 0, segsz);
    }

    void build() {
        for (auto &p : cnt) {
            if (p.second > 0) pend.emplace_back(make_pair(appear[p.first], Q), p.first);
        }
        for (auto &s : pend) {
            add(s.first.first, s.first.second, s.second);
        }
    }

    void run(const function<void(int)> &f, int k = 0) {
        int add = 0;
        for (auto &e : seg[k]) {
            add += uf.unite(e.first, e.second);
        }
        comp -= add;
        if (k < segsz - 1) {
            run(f, 2 * k + 1);
            run(f, 2 * k + 2);
        } else if (k - (segsz - 1) < Q) {
            int query_index = k - (segsz - 1);
            f(query_index);
        }
        for (auto &e : seg[k]) {
            uf.undo();
        }
        comp += add;
    }
};
