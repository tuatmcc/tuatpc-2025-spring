#include <bits/stdc++.h>
#include "testlib.h"
#include "constraints.h"
using namespace std;

// 入力の構造体
struct Input {
    int N, M;
    int Q;
    vector<tuple<int, int, int>> queries;
};

// ファイルに書き込む
void write_output(const string filename, const Input &in) {
    ofstream of(filename);
    of << in.N << " " << in.M << endl;
    of << in.Q << endl;
    assert(in.Q == (int)in.queries.size());
    for (auto [t, x, y] : in.queries) {
        of << t << " ";
        if (t == 1 || t == 2) {
            of << x << " " << y;
        } else {
            assert(t == 3);
            of << x;
        }
        of << endl;
    }
    of.close();
    // cerr << "Generated: " << filename << endl;
}

// N, M, Qからクエリを生成する
// one_prob: t=1の確率, two_prob: t=2の確率, three_prob: t=3の確率 (確率は3つの総和で割ったものとして算出する)
Input make_input_by_NMQ(const string filename, const int N, const int M, int Q, const int one_prob = 1, const int two_prob = 1, const int three_prob = 1) {
    Input in;
    in.N = N;
    in.M = M;
    in.Q = Q;

    // クエリをランダムに生成
    set<pair<int, int>> lines;      // 現在の横線の位置
    set<pair<int, int>> lefts;      // 現在の横線の左端の位置
    set<pair<int, int>> able_place; // 横線が引ける場所
    for (int i = 1; i < N; i++) {
        for (int j = 1; j <= M; j++) {
            able_place.insert({i, j});
        }
    }

    const int prob_sum = one_prob + two_prob + three_prob;
    assert(prob_sum > 0);
    while (Q--) {
        int t;
        // クエリ1, 2, 3をそれぞれone_prob, two_prob, three_probの確率で選ぶ
        int tmp = rnd.next(1, prob_sum);
        if (tmp <= one_prob) {
            t = 1;
        } else if (tmp <= one_prob + two_prob) {
            t = 2;
        } else {
            t = 3;
        }

        // 制約違反を避けるための処理
        if (lines.empty() && t == 2) {
            t = rnd.next(1, 2) == 1 ? 1 : 3; // 横線が存在しない場合t=2を除外
        }
        if (able_place.empty() && t == 1) {
            t = rnd.next(1, 2) == 1 ? 2 : 3; // 新しい横線が入るスペースがないならt=1を除外
        }

        if (t == 1) {
            assert(!able_place.empty());
            // able_placeからランダムに選ぶ
            int rnd_x = rnd.next(1, N - 1);
            int rnd_y = rnd.next(1, M);
            auto itr = able_place.lower_bound({rnd_x, rnd_y});
            if (itr == able_place.end()) {
                itr = able_place.begin();
            }
            auto [x, y] = *itr;

            assert(1 <= x && x <= N - 1);
            assert(1 <= x + 1 && x + 1 <= N);
            assert(1 <= y && y <= M);

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
            int rnd_x = rnd.next(1, N - 1);
            int rnd_y = rnd.next(1, M);
            auto itr = lefts.lower_bound({rnd_x, rnd_y});
            if (itr == lefts.end()) {
                itr = lefts.begin();
            }
            auto [x, y] = *itr;

            assert(lines.count({x, y}));
            assert(lines.count({x + 1, y}));

            // 線を消す
            lefts.erase({x, y});
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
            if (x < N - 1) {
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
            int s = rnd.next(1, N);
            in.queries.emplace_back(t, s, -1); // 3つめの引数は使わない
        }
    }
    return in;
}

int main(int argc, char *argv[]) {
    registerGen(argc, argv, 1);

    // Nが最小の場合
    for (int t = 0; t < 2; t++) {
        string filename = std::format("01_Nmin{:02}.in", t + 1);
        if (t < 1) {
            int N = MIN_N;
            int M = rnd.next(MIN_M, MAX_M);
            int Q = rnd.next(MIN_Q, MAX_Q);
            Input in = make_input_by_NMQ(filename, N, M, Q);
            write_output(filename, in);
        } else {
            int N = MIN_N;
            int M = rnd.next(MIN_M, MAX_M);
            int Q = MAX_Q;
            Input in = make_input_by_NMQ(filename, N, M, Q, 10, 1, 2);
            write_output(filename, in);
        }
    }

    // Mが最小の場合
    for (int t = 0; t < 1; t++) {
        string filename = std::format("02_Mmin{:02}.in", t + 1);
        int N = rnd.next(MIN_N, MAX_N);
        int M = MIN_M;
        int Q = rnd.next(MIN_Q, MAX_Q);
        Input in = make_input_by_NMQ(filename, N, M, Q);
        write_output(filename, in);
    }

    // // N, Mが小さい場合
    // for (int t = 0; t < 2; t++) {
    //     string filename = std::format("03_small{:02}.in", t + 1);
    //     int N = rnd.next(MIN_N + 1, 5);
    //     int M = rnd.next(MIN_M + 1, 5);
    //     int Q = rnd.next(MIN_Q, MAX_Q);
    //     Input in = make_input_by_NMQ(filename, N, M, Q);
    //     write_output(filename, in);
    // }

    // N, Mが最小の場合
    for (int t = 0; t < 1; t++) {
        string filename = std::format("04_min{:02}.in", t + 1);
        int N = MIN_N;
        int M = MIN_M;
        int Q = rnd.next(MIN_Q, MAX_Q);
        Input in = make_input_by_NMQ(filename, N, M, Q);
        write_output(filename, in);
    }

    // // N, M, Qが大きい場合
    // for (int t = 0; t < 2; t++) {
    //     string filename = std::format("05_large{:02}.in", t + 1);
    //     int N = rnd.next(max(MIN_N, MAX_N - 10), MAX_N);
    //     int M = rnd.next(max(MIN_M, MAX_M - 10), MAX_M);
    //     int Q = rnd.next(max(MIN_Q, MAX_Q - 10), MAX_Q);
    //     Input in = make_input_by_NMQ(filename, N, M, Q);
    //     write_output(filename, in);
    // }

    // N, M, Qが最大の場合
    for (int t = 0; t < 1; t++) {
        string filename = std::format("06_max{:02}.in", t + 1);
        int N = MAX_N;
        int M = MAX_M;
        int Q = MAX_Q;
        Input in = make_input_by_NMQ(filename, N, M, Q);
        write_output(filename, in);
    }

    // // ランダム
    // for (int t = 0; t < 5; t++) {
    //     string filename = std::format("07_random{:02}.in", t + 1);
    //     int N = rnd.next(MIN_N, MAX_N);
    //     int M = rnd.next(MIN_M, MAX_M);
    //     int Q = rnd.next(MIN_Q, MAX_Q);
    //     Input in = make_input_by_NMQ(filename, N, M, Q);
    //     write_output(filename, in);
    // }

    // 1,2が多い場合
    for (int t = 0; t < 1; t++) {
        string filename = std::format("08_many12query{:02}.in", t + 1);
        int N = MAX_N;
        int M = MAX_M;
        int Q = MAX_Q;
        Input in = make_input_by_NMQ(filename, N, M, Q, 5, 5, 1);
        write_output(filename, in);
    }

    // 3が多い場合
    for (int t = 0; t < 1; t++) {
        string filename = std::format("09_many3query{:02}.in", t + 1);
        int N = MAX_N;
        int M = MAX_M;
        int Q = MAX_Q;
        Input in = make_input_by_NMQ(filename, N, M, Q, 1, 1, 10);
        write_output(filename, in);
    }
}
