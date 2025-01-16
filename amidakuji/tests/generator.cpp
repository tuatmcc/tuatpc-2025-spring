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

Input generate_random_input() {
    Input in;
    int W = rnd.next(MIN_W, MAX_W);
    int H = rnd.next(MIN_H, MAX_H);
    int Q = rnd.next(MIN_Q, MAX_Q);
    in.W = W;
    in.H = H;
    in.Q = Q;

    set<pair<int, int>> lines; // 現在の横線の位置
    set<pair<int, int>> lefts; // 現在の横線の左端の位置

    while (Q--) {
        int t = rnd.next(1, 3);

        if (lines.empty() && t == 2) {
            t = rnd.next(1, 2) == 1 ? 1 : 3; // 横線が存在しない場合t=2を除外
        }
        if (lefts.size() == (W - 1) * H && t == 1) {
            t = rnd.next(1, 2) == 1 ? 2 : 3; // 新しい横線が入るスペースがないならt=1を除外
        }

        if (t == 1) {
            int x = rnd.next(1, W - 1);
            int y = rnd.next(1, H);
            // 左端か右端が既に横線上にある場合はやり直し
            while (lines.contains({x, y}) || lines.contains({x + 1, y})) {
                x = rnd.next(1, W - 1);
                y = rnd.next(1, H);
            }

            assert(1 <= x && x <= W - 1);
            assert(1 <= x + 1 && x + 1 <= W);
            assert(1 <= y && y <= H);

            lefts.insert({x, y});
            lines.insert({x, y});
            lines.insert({x + 1, y});

            in.queries.emplace_back(t, x, y);
        } else if (t == 2) {
            // leftsからランダムに選ぶ
            vector<pair<int, int>> lefts_vec(lefts.begin(), lefts.end());
            int rand_idx = rnd.next(0, (int)lefts.size() - 1);
            auto rand_left = lefts_vec[rand_idx];
            assert(lefts.count(rand_left));

            int x = rand_left.first;
            int y = rand_left.second;

            assert(lines.count({x, y}));
            assert(lines.count({x + 1, y}));

            lefts.erase(rand_left);
            lines.erase({x, y});
            lines.erase({x + 1, y});

            in.queries.emplace_back(t, x, y);
        } else { // t == 3
            int s = rnd.next(1, W);
            in.queries.emplace_back(t, s, -1); // 3つめの引数は使わない
        }
    }
    return in;
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    for (int t = 0; t < 30; t++) {
        string filename = std::format("02_random{:02}.in", t + 1);
        ofstream of(filename);
        Input in = generate_random_input();
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
    }
}