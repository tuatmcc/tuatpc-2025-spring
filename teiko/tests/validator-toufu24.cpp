#include "testlib.h"
#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using namespace atcoder;

using mint = modint998244353;

// constexpr int MAX_HW = 1500000;
constexpr int MAX_T = 100000;
constexpr int MAX_L = 1500000;

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    const int T = inf.readInt();
    inf.readEoln();
    inf.ensuref(1 <= T && T <= MAX_T, "T must be 1 <= T <= %d\n", MAX_T);
    int sum_L = 0;
    for (int tt = 0; tt < T; tt++) {
        const int H = inf.readInt();
        inf.readEoln();
        const vector<string> s = inf.readLines(H);
        int W = 0;
        for (int i = 0; i < H; i++) {
            W = max(W, (int)s[i].size());
            sum_L += s[i].size();
            // cerr << i << "  ";
            // cerr << s[i] << endl;
        }
        inf.ensuref(H >= 1 && W >= 1, "H and W must be >= 1\n");
        // inf.ensuref(H * W <= MAX_HW, "H * W must be <= %d\n", MAX_HW);

        // 文字種のチェック
        set<char> chs = {'|', '-', 'o', ' ', '^', 'v', '+'};
        map<char, int> cnt;
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < s[i].size(); j++) {
                cnt[s[i][j]]++;
                inf.ensuref(chs.contains(s[i][j]), "s[%d][%d] is invalid character '%c'\n", i, j, s[i][j]);
            }
        }
        inf.ensuref(cnt['o'] == 2, "There must be exactly 2 'o'\n");
        // 抵抗器のチェック
        int res_cnt = 0;
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < s[i].size(); j++) {
                if (s[i][j] == '^') {
                    inf.ensuref(i % 2 == 0, "only even row can have '^' at s[%d][%d]\n", i, j);
                    res_cnt++;
                    // 前3つは-で埋まっている
                    for (int k = 1; k <= 3; k++) {
                        inf.ensuref(s[i][j - k] == '-', "- must be at s[%d][%d]\n", i, j);
                    }
                    // ^v^v^v
                    const string resist = "^v^v^v";
                    if (j + resist.size() >= s[i].size()) {
                        inf.ensuref(false, "There must be a resistor at s[%d][%d]\n", i, j);
                    } else {
                        string substr = s[i].substr(j, resist.size());
                        inf.ensuref(substr == resist, "There must be a resistor '^v^v^v' at s[%d][%d]\n", i, j);
                    }
                    j += resist.size();
                    // 後ろ3つは-で埋まっている
                    for (int k = 0; k < 3; k++) {
                        inf.ensuref(j + k < s[i].size() && s[i][j + k] == '-', "- must be at s[%d][%d] back\n", i, j + k);
                    }
                }
            }
        }
        inf.ensuref(res_cnt > 0, "There must be at least one resistor\n");
        inf.ensuref(res_cnt <= 30, "There must be at most 30 resistors\n");
        // 右端は o か | か + で埋まっている
        for (int i = 0; i < H; i++) {
            inf.ensuref(s[i].back() == 'o' || s[i].back() == '|' || s[i].back() == '+', "s[%d].back() must be 'o' or '|'\n", i);
        }

        // + には上下/左右に-|がある
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < s[i].size(); j++) {
                if (s[i][j] == '+') {
                    int dx[] = {0, 0, -1, 1};
                    int dy[] = {-1, 1, 0, 0};
                    bool tate = false, yoko = false;
                    for (int k = 0; k < 4; k++) {
                        int ni = i + dx[k];
                        int nj = j + dy[k];
                        if (ni < 0 || ni >= H || nj < 0 || nj >= s[ni].size())
                            continue;
                        if (k < 2) {
                            if (s[ni][nj] == '-') {
                                yoko = true;
                            }
                        } else {
                            if (s[ni][nj] == '|') {
                                tate = true;
                            }
                        }
                    }
                    assert(s[i][j] == '+');
                    // cerr << s[i][j] << " " << tate << " " << yoko << endl;
                    // cerr << i << " " << j << " " << tate << " " << yoko << endl;
                    inf.ensuref(tate && yoko, "invalid '+' at s[%d][%d]\n", i, j);
                }
            }
        }

        // o はi = 0, j = 0,W-1にある
        inf.ensuref(s[0][0] == 'o', "s[0][0] must be 'o'\n");
        inf.ensuref(s[0][W - 1] == 'o', "s[0][W-1] must be 'o'\n");

        // 奇数行は|と のみ
        // 偶数行は-と^とvとoと+と|と のみ
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < s[i].size(); j++) {
                if (i % 2 == 0) {
                    set<char> st = {'-', '^', 'v', 'o', '+', ' ', '|'};
                    inf.ensuref(st.contains(s[i][j]), "Invalid character in even row at s[%d][%d]\n", i, j);
                } else {
                    inf.ensuref(s[i][j] == '|' || s[i][j] == ' ', "Invalid character in odd row at s[%d][%d]\n", i, j);
                }
            }
        }

        // 回路は連結している
        auto s2 = s;
        queue<pair<int, int>> que;
        que.push({0, 0});
        s2[0][0] = ' ';
        while (!que.empty()) {
            auto [i, j] = que.front();
            que.pop();
            int dx[] = {0, 0, -1, 1};
            int dy[] = {-1, 1, 0, 0};
            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (ni < 0 || ni >= H || nj < 0 || nj >= s[ni].size())
                    continue;
                if (s2[ni][nj] == ' ')
                    continue;
                if (s2[ni][nj] == '|' || s2[ni][nj] == '-' || s2[ni][nj] == 'o' || s2[ni][nj] == '+' || s2[ni][nj] == '^' || s2[ni][nj] == 'v') {
                    s2[ni][nj] = ' ';
                    que.push({ni, nj});
                }
            }
        }
        // s2には空白のみが入っている
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < s[i].size(); j++) {
                inf.ensuref(s2[i][j] == ' ', "Circuit is not connected\n");
            }
        }

        // v,^は抵抗器のとこにしかない
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < s[i].size(); j++) {
                const int dx[] = {0, 0};
                const int dy[] = {-1, 1};
                if (s[i][j] == '^' || s[i][j] == 'v') {
                    bool ok = false;
                    // 左右のどっちかに^vがある
                    for (int k = 0; k < 2; k++) {
                        int ni = i + dx[k];
                        int nj = j + dy[k];
                        if (ni < 0 || ni >= H || nj < 0 || nj >= s[ni].size())
                            continue;
                        if (s[ni][nj] == '^' || s[ni][nj] == 'v') {
                            ok = true;
                        }
                    }
                    inf.ensuref(ok, "There must be '^' or 'v' at s[%d][%d]\n", i, j);
                }
            }
        }

        // -があったら3つ以上連続している
        for (int i = 0; i < H; i++) {
            for (int j = 0; j < s[i].size(); j++) {
                if (s[i][j] == '-') {
                    int cnt = 1;
                    for (int k = j + 1; k < s[i].size(); k++) {
                        if (s[i][k] == '-') {
                            cnt++;
                            j = k;
                        } else {
                            break;
                        }
                    }
                    inf.ensuref(cnt >= 3, "There must be at least 3 '-' at s[%d][%d] in %d\n", i, j, tt);
                }
            }
        }
    }
    inf.ensuref(sum_L <= MAX_L, "sum of L must be <= %d\n", MAX_L);
    inf.readEof();
}
