#include <bits/stdc++.h>
using namespace std;
#include "OnlineDynamicConnectivity.hpp"

/*
    - 前処理 O(NM)
    - クエリ1,2 O(log^2 {NM})
    - クエリ3 O(Nlog {NM})
    - 全体 O(NM + QNlog^2 {NM})
*/

int main() {
    int N, M;
    cin >> N >> M;

    int Q;
    cin >> Q;
    dynamic_connectivity<int> dc(N * (M + 1));
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dc.link(i + j * N, i + (j + 1) * N);
        }
    }

    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int x, y;
            cin >> x >> y;
            x--, y--; // 0-based index
            // 左の付け替え
            dc.cut(x + y * N, x + (y + 1) * N);
            dc.link(x + y * N, (x + 1) + (y + 1) * N);
            // 右の付け替え
            dc.cut((x + 1) + y * N, (x + 1) + (y + 1) * N);
            dc.link((x + 1) + y * N, x + (y + 1) * N);
        } else if (t == 2) {
            int x, y;
            cin >> x >> y;
            x--, y--; // 0-based index

            // 左の付け替え
            dc.cut(x + y * N, (x + 1) + (y + 1) * N);
            dc.link(x + y * N, x + (y + 1) * N);
            // 右の付け替え
            dc.cut((x + 1) + y * N, x + (y + 1) * N);
            dc.link((x + 1) + y * N, (x + 1) + (y + 1) * N);
        } else {
            int s;
            cin >> s;
            s--; // 0-based index
            for (int i = 0; i < N; i++) {
                if (dc.same(s, i + N * M)) {
                    cout << i + 1 << endl;
                    break;
                }
            }
        }
    }
}
