// 参考: https://yukicoder.me/wiki/offline_dsp

#include <bits/stdc++.h>
using namespace std;
#define int int64_t
// https://ei1333.github.io/luzhiled/snippets/other/offline-dynamic-connectivity.html から引用

struct UnionFindUndo {
    vector<int> data;
    stack<pair<int, int>> history;

    UnionFindUndo(int sz) {
        data.assign(sz, -1);
    }

    bool unite(int x, int y) {
        x = find(x), y = find(y);
        history.emplace(x, data[x]);
        history.emplace(y, data[y]);
        if (x == y)
            return (false);
        if (data[x] > data[y])
            swap(x, y);
        data[x] += data[y];
        data[y] = x;
        return (true);
    }

    int find(int k) {
        if (data[k] < 0)
            return (k);
        return (find(data[k]));
    }

    int size(int k) {
        return (-data[find(k)]);
    }

    void undo() {
        data[history.top().first] = history.top().second;
        history.pop();
        data[history.top().first] = history.top().second;
        history.pop();
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
        if (cnt[e]++ == 0)
            appear[e] = idx;
    }

    void erase(int idx, int s, int t) {
        auto e = minmax(s, t);
        if (--cnt[e] == 0)
            pend.emplace_back(make_pair(appear[e], idx), e);
    }

    void add(int a, int b, const edge &e, int k, int l, int r) {
        if (r <= a || b <= l)
            return;
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
            if (p.second > 0)
                pend.emplace_back(make_pair(appear[p.first], Q), p.first);
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

int32_t main() {
    cin.tie(0);
    ios::sync_with_stdio(0);
    // 入力
    int N, M;
    cin >> N >> M;
    assert(N <= 20);
    assert(M <= 100000);
    int Q;
    cin >> Q;
    vector<tuple<int, int, int>> queries;
    for (int i = 0; i < Q; i++) {
        int t;
        cin >> t;
        if (t == 1 || t == 2) {
            int x, y;
            cin >> x >> y;
            x--; // 0-based index
            queries.emplace_back(t, x, y);
        } else {
            int s;
            cin >> s;
            s--; // 0-based index
            queries.emplace_back(t, s, -1);
        }
    }

    OfflineDynamicConnectivity odc(N * (M + 2), Q + 2);

    // 初期状態
    for (int x = 0; x < N; x++) {
        for (int y = 0; y <= M; y++) {
            odc.insert(0, x + y * N, x + (y + 1) * N);
        }
    }

    // クエリの追加
    for (int i = 1; i <= Q; i++) {
        int t, x, y;
        tie(t, x, y) = queries[i - 1];
        if (t == 1) {
            // 斜めに辺を張る
            odc.erase(i, x + y * N, x + (y + 1) * N);
            odc.erase(i, (x + 1) + y * N, (x + 1) + (y + 1) * N);
            odc.insert(i, x + y * N, (x + 1) + (y + 1) * N);
            odc.insert(i, (x + 1) + y * N, x + (y + 1) * N);
        } else if (t == 2) {
            // 縦に辺を張る
            odc.erase(i, x + y * N, (x + 1) + (y + 1) * N);
            odc.erase(i, (x + 1) + y * N, x + (y + 1) * N);
            odc.insert(i, x + y * N, x + (y + 1) * N);
            odc.insert(i, (x + 1) + y * N, (x + 1) + (y + 1) * N);
        }
    }

    odc.build();
    odc.run([&](int i) -> void {
        if (i == 0)
            return;
        if (i == Q + 1)
            return;
        int t, x, y;
        tie(t, x, y) = queries[i - 1];
        if (t == 3) {
            for (int s = 0; s < N; s++) {
                if (odc.uf.find(s + (M + 1) * N) == odc.uf.find(x)) {
                    cout << s + 1 << endl;
                    return;
                }
            }
        }
    });
}
