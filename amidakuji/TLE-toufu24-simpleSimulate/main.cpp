#include <bits/stdc++.h>
using namespace std;
/*
配列確保 : $O(NM)$
クエリ1 : $O(1)$
クエリ2 : $O(1)$
クエリ3 : $O(M)$
合計 $O(NM + QM)$
でTLEするはず
*/
int main() {
    int N, M;
    cin >> N >> M;
    assert(2 <= N && N <= 20);
    assert(1 <= M && M <= 100000);

    // 横線の有無を管理するあみだくじ
    vector<vector<bool>> grid(M, vector<bool>(N - 1, false));

    int Q;
    cin >> Q;

    while (Q--) {
        int t;
        cin >> t;

        if (t == 1) {
            int x, y;
            cin >> x >> y;
            x--, y--;          // 0-based index
            grid[y][x] = true; // 横線を挿入
        } else if (t == 2) {
            int x, y;
            cin >> x >> y;
            x--, y--;           // 0-based index
            grid[y][x] = false; // 横線を削除
        } else if (t == 3) {
            int s;
            cin >> s;
            s--; // 0-based index

            // 探索
            int current = s;
            for (int y = 0; y < M; y++) {
                // 横線があれば左右に移動
                if (current > 0 && grid[y][current - 1]) {
                    current--; // 左へ移動
                } else if (current < N - 1 && grid[y][current]) {
                    current++; // 右へ移動
                }
            }
            cout << (current + 1) << endl; // 1-based indexで出力
        }
    }
}
