#include <bits/stdc++.h>
#include <atcoder/segtree> // AC-libraryに依存している．
using namespace std;
using namespace atcoder;

template <typename T>
struct Compress {
    vector<T> xs;

    Compress() = default;

    Compress(const vector<T> &vs) {
        add(vs);
    }

    Compress(const initializer_list<vector<T>> &vs) {
        for (auto &p : vs)
            add(p);
    }

    void add(const vector<T> &vs) {
        copy(begin(vs), end(vs), back_inserter(xs));
    }

    void add(const T &x) {
        xs.emplace_back(x);
    }

    void build() {
        sort(begin(xs), end(xs));
        xs.erase(unique(begin(xs), end(xs)), end(xs));
    }

    vector<int> get(const vector<T> &vs) const {
        vector<int> ret;
        transform(begin(vs), end(vs), back_inserter(ret), [&](const T &x) {
            return lower_bound(begin(xs), end(xs), x) - begin(xs);
        });
        return ret;
    }

    int get(const T &x) const {
        return lower_bound(begin(xs), end(xs), x) - begin(xs);
    }

    const T &operator[](int k) const {
        return xs[k];
    }
};

int compressed_N;

struct Perm {
    vector<int> perm;

    // 恒等置換で初期化
    Perm(int N) : perm(N) {
        for (int i = 0; i < N; i++) {
            perm[i] = i;
        }
    }

    // 置換の合成
    Perm compose(const Perm &other) const {
        Perm result(perm.size());
        for (int i = 0; i < perm.size(); i++) {
            result.perm[i] = other.perm[perm[i]];
        }
        return result;
    }
};

Perm op(Perm a, Perm b) {
    return a.compose(b);
}

Perm e() {
    return Perm(compressed_N);
}

struct Query {
    int t;
    int x, y;
};

int main() {
    int N, M;
    cin >> N >> M;

    int Q;
    cin >> Q;
    vector<Query> queries(Q);
    // 更新・取得が行われる行と列の座標を記録
    vector<int> update_rows, update_cols;
    for (int i = 0; i < Q; i++) {
        int t;
        cin >> t;
        queries[i].t = t;
        if (t == 1 || t == 2) {
            int x, y;
            cin >> x >> y;
            x--; // 0-index
            y--; // 0-index
            queries[i].x = x;
            queries[i].y = y;
            update_cols.push_back(x);
            update_cols.push_back(x + 1);
            update_rows.push_back(y);
        } else if (t == 3) {
            int s;
            cin >> s;
            s--; // 0-index
            queries[i].x = s;
            update_cols.push_back(s);
        }
    }

    // クエリ先読みによる座標圧縮
    Compress<int> comp_col(update_cols);
    comp_col.build();
    Compress<int> comp_row(update_rows);
    comp_row.build();
    assert(comp_col.xs.size() <= N);
    assert(comp_col.xs.size() <= Q);
    assert(comp_row.xs.size() <= M);
    assert(comp_row.xs.size() <= Q);
    compressed_N = comp_col.xs.size();
    // セグ木の構築
    int size = max(1, (int)comp_row.xs.size());
    segtree<Perm, op, e> seg(size);

    // クエリの処理
    for (const auto &q : queries) {
        if (q.t == 1 || q.t == 2) {
            int idx = comp_row.get(q.y);
            Perm p = seg.get(idx);
            // x番目とx+1番目の要素を入れ替える
            swap(p.perm[q.x], p.perm[q.x + 1]); // ここが間違っている
            seg.set(idx, p);
        } else if (q.t == 3) {
            Perm result = seg.all_prod();
            int ans = result.perm[q.x] + 1; // ここが間違っている
            cout << ans << "\n";
        }
    }
}
