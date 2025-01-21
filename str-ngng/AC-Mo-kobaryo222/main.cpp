#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
    int N, Q;
    cin >> N >> Q;
    string S;
    cin >> S;
    vector<tuple<int, int, int>> queries(Q);
    for (int i = 0; i < Q; i++) {
        int l, r;
        cin >> l >> r;
        --l;
        queries.emplace_back(l, r, i);
    }

    // 要調整
    const int block_size = N / min<int>(N, sqrt(Q));
    auto comp = [block_size](tuple<int, int, int>& a, tuple<int, int, int>& b) {
        auto [la, ra, _] = a;
        auto [lb, rb, __] = b;
        int block_a = la / block_size, block_b = lb / block_size;
        if (block_a != block_b)
            return block_a < block_b;
        // ブロック番号の偶奇でソート順を変える
        if (block_a % 2 == 1)
            return ra > rb;
        else
            return ra < rb;
    };
    sort(queries.begin(), queries.end(), comp);

    // 文字種
    const int M = 26;
    // lsum[a][b] := 区間内に存在する各文字 a について、それより左にある b の数の総和
    // rsum[a][b] := 区間内に存在する各文字 a について、それより右にある b の数の総和
    vector<vector<long long>> lsum(M, vector<long long>(M)), rsum(M, vector<long long>(M));
    // mid[a] := 区間内に存在する各文字 a について、それらの左右にある同じ文字の組の総和
    // cnt[a] := 区間内に存在する文字 a の数
    vector<long long> mid(M), cnt(M);
    int l = 0, r = 0;
    long long cans = 0;

    auto add_left = [&]() {
        int c = S[l - 1] - 'a'; // 新しく追加される文字
        cans += mid[c]; // c + (? + c + ?)
        for (int i = 0; i < M; i++) {
            if (i == c)
                continue;
            mid[i] += rsum[i][c];
            lsum[i][c] += cnt[i];
            rsum[c][i] += cnt[i];
        }
        cnt[c]++;
        l--;
    };
    auto add_right = [&]() {
        int c = S[r] - 'a'; // 新しく追加される文字
        cans += mid[c]; // (? + c + ?) + c
        for (int i = 0; i < M; i++) {
            if (i == c)
                continue;
            mid[i] += lsum[i][c];
            lsum[c][i] += cnt[i];
            rsum[i][c] += cnt[i];
        }
        cnt[c]++;
        r++;
    };
    auto erase_left = [&]() {
        int c = S[l] - 'a'; // 削除される文字
        cans -= mid[c]; // c + (? + c + ?)
        for (int i = 0; i < M; i++) {
            if (i == c)
                continue;
            mid[i] -= rsum[i][c];
            lsum[i][c] -= cnt[i];
            rsum[c][i] -= cnt[i];
        }
        cnt[c]--;
        l++;
    };
    auto erase_right = [&]() {
        int c = S[r - 1] - 'a'; //  削除される文字
        cans -= mid[c]; // (? + c + ?) + c
        for (int i = 0; i < M; i++) {
            if (i == c)
                continue;
            mid[i] -= lsum[i][c];
            lsum[c][i] -= cnt[i];
            rsum[i][c] -= cnt[i];
        }
        cnt[c]--;
        r--;
    };

    vector<long long int> ans(Q);
    for (auto [li, ri, idx] : queries) {
        while (l > li)
            add_left();
        while (r < ri)
            add_right();
        while (l < li)
            erase_left();
        while (r > ri)
            erase_right();
        ans[idx] = cans;
    }

    for (auto& x : ans)
        cout << x << endl;
}