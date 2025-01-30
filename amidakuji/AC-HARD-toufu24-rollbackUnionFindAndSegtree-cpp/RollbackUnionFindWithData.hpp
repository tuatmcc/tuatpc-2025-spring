// https://nyaannyaan.github.io/library/data-structure/rollback-union-find.hpp.html から引用&改変
#define int int64_t

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

        if (x == y) return false;
        if (data[x] > data[y]) swap(x, y);

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
        if (data[k] < 0) return k;
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
        if (state == -1) state = inner_snap;
        assert(state <= (int)history.size());
        while (state < (int)history.size())
            undo();
    }
};

// int main() {
//     RollbackUnionFindWithData uf(5); // サイズ5のUnion-Findを初期化
//     uf.unite(0, 1);
//     uf.unite(0, 4);
//     for (int i = 0; i < 5; i++) {
//         cout << uf.get_data(i) << " "; // 4 4 2 3 4
//     }
//     cout << endl;
//     uf.undo();
//     for (int i = 0; i < 5; i++) {
//         cout << uf.get_data(i) << " "; // 1 1 2 3 4
//     }
//     cout << endl;
// }