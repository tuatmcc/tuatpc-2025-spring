#include <bits/stdc++.h>
#include <atcoder/segtree> // AC-libraryに依存している．atcoder/以下に置いてあります．
using namespace std;
using namespace atcoder;

/*
op, e ともに$O(N)$である．

- セグ木構築 : $O(NM)$
- クエリ処理 :
    - クエリ回数 : $Q$
    - クエリ1 : $O(N \log M)$
    - クエリ2 : $O(N \log M)$
    - クエリ3 : $O(N)$
    - 合計 : $O(QN \log M)$
- 全体 : $O(NM + QN \log M)$
*/

int N, M;

// セグ木に乗せる置換
struct Perm {
    vector<int> perm;

    // 恒等置換で初期化
    Perm() : perm(N) {
        for (int i = 0; i < N; i++) {
            perm[i] = i;
        }
    }

    // 置換の合成
    Perm compose(const Perm &other) const {
        Perm result;
        for (int i = 0; i < perm.size(); i++) {
            result.perm[i] = other.perm[perm[i]];
        }
        return result;
    }
};

// 置換の合成を演算とする
Perm op(Perm a, Perm b) {
    return a.compose(b);
}

// 恒等置換が単位元
Perm e() {
    return Perm();
}

int main() {
    cin >> N >> M;

    segtree<Perm, op, e> seg(M);

    int Q;
    cin >> Q;

    while (Q--) {
        int t;
        cin >> t;
        if (t == 1 || t == 2) {
            int x, y;
            cin >> x >> y;
            x--, y--; // 0-based index
            // y行目の置換を更新
            Perm p = seg.get(y);
            // x番目とx+1番目の要素を入れ替える
            swap(p.perm[x], p.perm[x + 1]);
            seg.set(y, p);
        } else if (t == 3) {
            int s;
            cin >> s;
            s--; // 0-based index
            // 全行の置換を合成することであみだくじの結果を求める
            Perm result_perm = seg.all_prod();
            // s行目の移動先が答え
            int result = result_perm.perm[s];
            cout << (result + 1) << endl; // 1-based index
        }
    }
}
