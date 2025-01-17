#include <bits/stdc++.h>
#include "testlib.h"
using namespace std;

const int MIN_W = 2;
const int MAX_W = 60;
const int MIN_H = 1;
const int MAX_H = 100000;
const int MIN_Q = 1;
const int MAX_Q = 100000;

struct Input {
    int W, H;
    int Q;
    vector<tuple<int, int, int>> queries;
};

Input make_input_by_WHQ(const string filename, const int W, const int H, int Q) {
    Input in;
    in.W = W;
    in.H = H;
    in.Q = Q;

    // クエリをランダムに生成
    set<pair<int, int>> lines;      // 現在の横線の位置
    set<pair<int, int>> lefts;      // 現在の横線の左端の位置
    set<pair<int, int>> able_place; // 横線が引ける場所
    for (int i = 1; i < W; i++) {
        for (int j = 1; j <= H; j++) {
            able_place.insert({i, j});
        }
    }

    while (Q--) {
        int t = rnd.next(1, 3);

        if (lines.empty() && t == 2) {
            t = rnd.next(1, 2) == 1 ? 1 : 3; // 横線が存在しない場合t=2を除外
        }
        if (able_place.empty() && t == 1) {
            t = rnd.next(1, 2) == 1 ? 2 : 3; // 新しい横線が入るスペースがないならt=1を除外
        }

        if (t == 1) {
            assert(!able_place.empty());
            // able_placeからランダムに選ぶ
            int x = rnd.next(1, W - 1);
            int y = rnd.next(1, H);
            while (!able_place.contains({x, y})) {
                x = rnd.next(1, W - 1);
                y = rnd.next(1, H);
            }

            assert(1 <= x && x <= W - 1);
            assert(1 <= x + 1 && x + 1 <= W);
            assert(1 <= y && y <= H);

            // 線を引く
            lefts.insert({x, y});
            lines.insert({x, y});
            lines.insert({x + 1, y});

            // 置ける場所を更新
            assert(able_place.contains({x, y}));
            able_place.erase({x, y});
            if (able_place.contains({x + 1, y})) {
                able_place.erase({x + 1, y});
            }
            if (able_place.contains({x - 1, y})) {
                able_place.erase({x - 1, y});
            }

            in.queries.emplace_back(t, x, y);
        } else if (t == 2) {
            assert(!lefts.empty());
            // leftsからランダムに選ぶ
            vector<pair<int, int>> lefts_vec(lefts.begin(), lefts.end());
            int rand_idx = rnd.next(0, (int)lefts.size() - 1);
            auto rand_left = lefts_vec[rand_idx];
            assert(lefts.count(rand_left));

            int x = rand_left.first;
            int y = rand_left.second;

            assert(lines.count({x, y}));
            assert(lines.count({x + 1, y}));

            // 線を消す
            lefts.erase(rand_left);
            lines.erase({x, y});
            lines.erase({x + 1, y});

            // 置ける場所を更新
            assert(!able_place.contains({x, y}));
            able_place.insert({x, y});
            if (x > 1) {
                bool ok = true;
                // 左の左にも横線がある場合はだめ
                if (lines.contains({x - 2, y})) {
                    ok = false;
                }
                if (ok) {
                    assert(!able_place.contains({x - 1, y}));
                    able_place.insert({x - 1, y});
                }
            }
            if (x < W - 1) {
                bool ok = true;
                // 右の右にも横線がある場合はだめ
                if (lines.contains({x + 2, y})) {
                    ok = false;
                }
                if (ok) {
                    assert(!able_place.contains({x + 1, y}));
                    able_place.insert({x + 1, y});
                }
            }

            in.queries.emplace_back(t, x, y);
        } else { // t == 3
            int s = rnd.next(1, W);
            in.queries.emplace_back(t, s, -1); // 3つめの引数は使わない
        }
    }

    // ファイルに書き込む
    ofstream of(filename);
    of << in.W << " " << in.H << endl;
    of << in.Q << endl;
    assert(in.Q == (int)in.queries.size());
    for (auto [t, x, y] : in.queries) {
        of << t;
        if (t == 1 || t == 2) {
            of << " " << x << " " << y;
        } else {
            assert(t == 3);
            of << " " << x;
        }
        of << endl;
    }
    of.close();

    // cerr << "Generated: " << filename << endl;
    return in;
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    // Wが最小の場合
    for (int t = 0; t < 5; t++) {
        string filename = std::format("01_Wsmall{:02}.in", t + 1);
        int W = MIN_W;
        int H = MIN_H + t;
        int Q = rnd.next(MIN_Q, MAX_Q);
        Input in = make_input_by_WHQ(filename, W, H, Q);
    }

    // Hが最小の場合
    for (int t = 0; t < 5; t++) {
        string filename = std::format("02_Hsmall{:02}.in", t + 1);
        int W = MIN_W + t;
        int H = MIN_H;
        int Q = rnd.next(MIN_Q, MAX_Q);
        Input in = make_input_by_WHQ(filename, W, H, Q);
    }

    // W, Hが大きい場合
    for (int t = 0; t < 10; t++) {
        string filename = std::format("03_large{:02}.in", t + 1);
        int W = rnd.next(max(MIN_W, MAX_W - 10), MAX_W);
        int H = rnd.next(max(MIN_H, MAX_H - 10), MAX_H);
        int Q = rnd.next(MIN_Q, MAX_Q);
        Input in = make_input_by_WHQ(filename, W, H, Q);
    }

    // ランダム
    for (int t = 0; t < 30; t++) {
        string filename = std::format("04_random{:02}.in", t + 1);
        int W = rnd.next(MIN_W, MAX_W);
        int H = rnd.next(MIN_H, MAX_H);
        int Q = rnd.next(MIN_Q, MAX_Q);
        Input in = make_input_by_WHQ(filename, W, H, Q);
    }
}