#include <bits/stdc++.h>
using namespace std;
/*
配列確保 : $O(WH)$
クエリ1 : $O(1)$
クエリ2 : $O(1)$
クエリ3 : $O(H)$
合計 $O(WH + QH)$
でTLEするはず
*/
int main() {
    int W, H;
    cin >> W >> H;

    // 横線の有無を管理するあみだくじ
    vector<vector<bool>> grid(H, vector<bool>(W - 1, false));

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
            for (int y = 0; y < H; ++y) {
                // 横線があれば左右に移動
                if (current > 0 && grid[y][current - 1]) {
                    current--; // 左へ移動
                } else if (current < W - 1 && grid[y][current]) {
                    current++; // 右へ移動
                }
            }
            cout << (current + 1) << endl; // 1-based indexで出力
        }
    }
}

