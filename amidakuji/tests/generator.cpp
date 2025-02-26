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
// use_vertical_lines: 使う縦線の位置を指定する(左側)
// random3query: クエリ3をある程度ランダムに選ぶかどうか
struct random_query_config {
    int one_prob = 1;
    int two_prob = 1;
    int three_prob = 1;
    vector<int> use_vertical_lines = {};
    vector<int> use_horizontal_lines = {};
    bool random3query = false;
};
Input make_input(const int N, const int M, int Q, const random_query_config &config = random_query_config()) {
    auto [one_prob, two_prob, three_prob, use_vertical_lines, use_horizontal_lines, random3query] = config;

    for (auto x : use_vertical_lines) {
        assert(1 <= x && x < N);
    }
    for (auto x : use_horizontal_lines) {
        assert(1 <= x && x <= M);
    }
    if (!use_vertical_lines.empty() && !use_horizontal_lines.empty()) {
        assert(4 * Q <= (int)use_vertical_lines.size() * (int)use_horizontal_lines.size());
    } else if (!use_vertical_lines.empty()) {
        assert(4 * Q <= (int)use_vertical_lines.size() * M);
    } else if (!use_horizontal_lines.empty()) {
        assert(4 * Q <= (N - 1) * (int)use_horizontal_lines.size());
    }

    Input in;
    in.N = N;
    in.M = M;
    in.Q = Q;

    set<pair<int, int>> able_place;
    // 4*Q個の位置をランダムに選ぶ
    if (int64_t(N - 1) * M < 4 * Q) {
        for (int i = 1; i < N; i++) {
            for (int j = 1; j <= M; j++) {
                able_place.insert({i, j});
            }
        }
    } else if (!use_vertical_lines.empty() && !use_horizontal_lines.empty()) {
        // 縦線と横線の交点から選ぶ
        int cnt = 0;
        for (int i = 0; i < 4 * Q; i++) {
            int x = use_vertical_lines[rnd.next(0, (int)use_vertical_lines.size() - 1)];
            int y = use_horizontal_lines[rnd.next(0, (int)use_horizontal_lines.size() - 1)];
            if (able_place.count({x, y})) {
                i--;
                cnt++;
                if (cnt > 100)
                    break;
                continue;
            }
            cnt = 0;
            able_place.insert({x, y});
        }
    } else if (!use_vertical_lines.empty()) {
        // 縦線のみを使う
        int cnt = 0;
        for (int i = 0; i < 4 * Q; i++) {
            int x = use_vertical_lines[rnd.next(0, (int)use_vertical_lines.size() - 1)];
            int y = rnd.next(1, M);
            if (able_place.count({x, y})) {
                i--;
                cnt++;
                if (cnt > 100)
                    break;
                continue;
            }
            cnt = 0;
            able_place.insert({x, y});
        }
    } else if (!use_horizontal_lines.empty()) {
        // 横線のみを使う
        int cnt = 0;
        for (int i = 0; i < 4 * Q; i++) {
            int x = rnd.next(1, N - 1);
            int y = use_horizontal_lines[rnd.next(0, (int)use_horizontal_lines.size() - 1)];
            if (able_place.count({x, y})) {
                i--;
                cnt++;
                if (cnt > 100)
                    break;
                continue;
            }
            cnt = 0;
            able_place.insert({x, y});
        }
    } else {
        // 完全ランダム
        for (int i = 0; i < 4 * Q; i++) {
            int x = rnd.next(1, N - 1);
            int y = rnd.next(1, M);
            if (able_place.count({x, y})) {
                i--;
                continue;
            }
            able_place.insert({x, y});
        }
    }
    auto original_able_place = able_place;

    // クエリをランダムに生成
    set<pair<int, int>> lines; // 現在の横線の位置
    set<pair<int, int>> lefts; // 現在の横線の左端の位置

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
        // 以下の二つを同時に満たすことはない
        assert(!((able_place.empty() && t == 1) && (lefts.empty() && t == 2)));
        if (able_place.empty() && t == 1) {
            // 新しい横線が入るスペースがないならt=1を除外
            int tmp_prob_sum = two_prob + three_prob;
            tmp = rnd.next(1, tmp_prob_sum);
            if (tmp <= two_prob) {
                t = 2;
            } else {
                t = 3;
            }
        }
        if (lefts.empty() && t == 2) {
            // 横線が存在しない場合t=2を除外
            int tmp_prob_sum = one_prob + three_prob;
            tmp = rnd.next(1, tmp_prob_sum);
            if (tmp <= one_prob) {
                t = 1;
            } else {
                t = 3;
            }
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
            assert(able_place.count({x, y}));
            able_place.erase({x, y});
            if (able_place.count({x + 1, y})) {
                able_place.erase({x + 1, y});
            }
            if (able_place.count({x - 1, y})) {
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
            assert(!able_place.count({x, y}));
            able_place.insert({x, y});
            if (x > 1) {
                bool ok = true;
                // 左の左にも横線がある場合はだめ
                if (lines.count({x - 2, y})) {
                    ok = false;
                }
                // 元のable_placeに含まれていない場合はだめ
                if (!original_able_place.count({x - 1, y})) {
                    ok = false;
                }
                if (ok) {
                    assert(!able_place.count({x - 1, y}));
                    able_place.insert({x - 1, y});
                }
            }
            if (x < N - 1) {
                bool ok = true;
                // 右の右にも横線がある場合はだめ
                if (lines.count({x + 2, y})) {
                    ok = false;
                }
                // 元のable_placeに含まれていない場合はだめ
                if (!original_able_place.count({x + 1, y})) {
                    ok = false;
                }
                if (ok) {
                    assert(!able_place.count({x + 1, y}));
                    able_place.insert({x + 1, y});
                }
            }

            in.queries.emplace_back(t, x, y);
        } else { // t == 3
            int s;
            if (use_vertical_lines.empty()) {
                s = rnd.next(1, N);
            } else {
                if (rnd.next(1, 5) <= 4 || !random3query) {
                    // 4/5の確率でuse_vertical_linesから選ぶ
                    s = use_vertical_lines[rnd.next(0, (int)use_vertical_lines.size() - 1)] + rnd.next(0, 1); // use_vertical_linesから選んで、左右どちらかを選ぶ
                } else {
                    // 1/5の確率でランダムに選ぶ
                    s = rnd.next(1, N);
                }
            }
            in.queries.emplace_back(t, s, -1); // 3つめの引数は使わない
        }
    }
    return in;
}

Input make_stairs_input(int N, int M, int Q, bool random3query = false) {
    Input in;
    in.N = N;
    in.M = M;
    in.Q = Q;

    int init_height = rnd.next(1, M);
    int init_width = rnd.next(1, N - 1);
    int height = init_height;
    int width = init_width;
    set<pair<int, int>> used;
    set<int> used_yokobou;
    bool hantenn = false;
    int i = 0;
    for (; i < Q / 2; i++) {
        if (used.contains({width, height})) {
            i--;
            height = rnd.next(1, M);
            width = rnd.next(1, N - 1);
            continue;
        }
        in.queries.emplace_back(1, width, height);
        used_yokobou.insert(width);
        used.insert({width, height});
        height++;
        if (rnd.next(1, 100) == 1) {
            if (height <= M - 2) {
                used.insert({width, height});
                in.queries.emplace_back(1, width, height++);
                i++;
                used.insert({width, height});
                in.queries.emplace_back(1, width, height++);
                i++;
            }
        }
        if (hantenn) {
            width--;
        } else {
            width++;
        }
        if (height > M) {
            height = 1;
        }
        if (width > N - 1) {
            width = rnd.next(1, N - 1);
        }
        if (width < 1) {
            width = rnd.next(1, N - 1);
        }

        if (rnd.next(1, 100) == 1) {
            hantenn = !hantenn;
        }
    }

    for (; i < Q; i++) {
        if (random3query) {
            int rnd_x = rnd.next(1, N);
            int rnd_y = rnd.next(1, M);
            auto itr = used_yokobou.lower_bound(rnd_x);
            if (itr != used_yokobou.end()) {
                in.queries.emplace_back(3, *itr, -1);
            } else {
                in.queries.emplace_back(3, rnd_x, -1);
            }

            // 1/1000の確率で挿入/削除
            if (rnd.next(1, 1000) == 1) {
                if (rnd.next(0, 1) == 0) {
                    int rnd_x = rnd.next(1, N - 1);
                    int rnd_y = rnd.next(1, M);
                    while (used.contains({rnd_x, rnd_y}) || used.contains({rnd_x + 1, rnd_y}) || used.contains({rnd_x - 1, rnd_y})) {
                        rnd_x = rnd.next(1, N - 1);
                        rnd_y = rnd.next(1, M);
                    }
                    in.queries.emplace_back(1, rnd_x, rnd_y);
                    used_yokobou.insert(rnd_x);
                    used.insert({rnd_x, rnd_y});
                    i++;
                } else {
                    int rnd_x = rnd.next(1, N - 1);
                    int rnd_y = rnd.next(1, M);
                    auto itr = used.lower_bound({rnd_x, rnd_y});
                    if (itr != used.end()) {
                        in.queries.emplace_back(2, itr->first, itr->second);
                        used.erase(itr);
                        i++;
                    }
                }
            }
        } else {
            in.queries.emplace_back(3, init_width, -1);
        }
    }

    return in;
}

void make_sample_testcase() {
    // 5 4
    // 8
    // 1 1 1
    // 1 2 2
    // 3 1
    // 1 3 1
    // 3 4
    // 2 1 1
    // 3 1
    // 3 3
    Input in;
    in.N = 5;
    in.M = 4;
    in.Q = 8;
    in.queries = {
        {1, 1, 1},
        {1, 2, 2},
        {3, 1, -1},
        {1, 3, 1},
        {3, 4, -1},
        {2, 1, 1},
        {3, 1, -1},
        {3, 3, -1},
    };
    write_output("00_sample_01.in", in);

    // 7 3
    // 20
    // 1 6 1
    // 1 3 1
    // 3 4
    // 1 1 1
    // 1 6 3
    // 2 6 1
    // 1 3 3
    // 3 1
    // 1 6 1
    // 2 6 1
    // 1 2 2
    // 2 3 1
    // 1 4 1
    // 3 5
    // 1 6 1
    // 1 6 2
    // 3 1
    // 1 1 3
    // 3 6
    // 1 4 2
    in.N = 7;
    in.M = 3;
    in.Q = 20;
    in.queries = {
        {1, 6, 1},
        {1, 3, 1},
        {3, 4, -1},
        {1, 1, 1},
        {1, 6, 3},
        {2, 6, 1},
        {1, 3, 3},
        {3, 1, -1},
        {1, 6, 1},
        {2, 6, 1},
        {1, 2, 2},
        {2, 3, 1},
        {1, 4, 1},
        {3, 5, -1},
        {1, 6, 1},
        {1, 6, 2},
        {3, 1, -1},
        {1, 1, 3},
        {3, 6, -1},
        {1, 4, 2},
    };
    write_output("00_sample_02.in", in);

    // 2 2
    // 3
    // 1 1 1
    // 2 1 1
    // 1 1 1
    in.N = 2;
    in.M = 2;
    in.Q = 3;
    in.queries = {
        {1, 1, 1},
        {2, 1, 1},
        {1, 1, 1},
    };
    write_output("00_sample_03.in", in);
}

int32_t main(int32_t argc, char *argv[]) {
    registerGen(argc, argv, 1);

    // ------------------sample------------------
    {
        make_sample_testcase();
    }

    // ------------------normal------------------
    {
        int t = 1;
        // Nが最小の場合
        {
            {
                string filename = ::format("11_normal_minN_%02d.in", t++);
                int N = NORMAL_MIN_N;
                int M = NORMAL_MAX_M;
                int Q = NORMAL_MAX_Q;
                Input in = make_input(N, M, Q);
                write_output(filename, in);
            }
        }
        // Mが最小の場合
        {
            t = 1;
            {
                string filename = ::format("12_normal_minM_%02d.in", t++);
                int N = NORMAL_MAX_N;
                int M = NORMAL_MIN_M;
                int Q = NORMAL_MAX_Q;
                Input in = make_input(N, M, Q);
                write_output(filename, in);
            }
        }
        // N,Mが最小の場合
        {
            t = 1;
            {
                string filename = ::format("13_normal_minNM_%02d.in", t++);
                int N = NORMAL_MIN_N;
                int M = NORMAL_MIN_M;
                int Q = NORMAL_MAX_Q;
                Input in = make_input(N, M, Q);
                write_output(filename, in);
            }
        }
        // N,M,Qが最大の場合
        {
            {
                string filename = ::format("14_normal_max_%02d.in", t++);
                int N = NORMAL_MAX_N;
                int M = NORMAL_MAX_M;
                int Q = NORMAL_MAX_Q;
                Input in = make_input(N, M, Q);
                write_output(filename, in);
            }
            {
                string filename = ::format("14_normal_max_%02d.in", t++);
                int N = NORMAL_MAX_N;
                int M = NORMAL_MAX_M;
                int Q = NORMAL_MAX_Q;
                random_query_config config;
                config.use_vertical_lines = {3, 10, 11, 12};
                config.one_prob = 10;
                config.two_prob = 1;
                config.three_prob = 2;
                Input in = make_input(N, M, Q, config);
                write_output(filename, in);
            }
        }
        // Qが小さい場合
        {
            t = 1;
            {
                string filename = ::format("15_normal_smallQ_%02d.in", t++);
                int N = NORMAL_MAX_N;
                int M = NORMAL_MAX_M;
                int Q = 10;
                Input in = make_input(N, M, Q);
                write_output(filename, in);
            }
        }
        // クエリ1,2が多い場合
        {
            t = 1;
            {
                string filename = ::format("16_normal_many12query_%02d.in", t++);
                int N = NORMAL_MAX_N;
                int M = NORMAL_MAX_M;
                int Q = NORMAL_MAX_Q;
                random_query_config config;
                config.one_prob = 5;
                config.two_prob = 5;
                config.three_prob = 1;
                Input in = make_input(N, M, Q, config);
                write_output(filename, in);
            }
        }
        // クエリ3が多い場合
        {
            t = 1;
            {
                string filename = ::format("17_normal_many3query_%02d.in", t++);
                int N = NORMAL_MAX_N;
                int M = NORMAL_MAX_M;
                int Q = NORMAL_MAX_Q;
                random_query_config config;
                config.one_prob = 1;
                config.two_prob = 1;
                config.three_prob = 10;
                config.use_vertical_lines = {3, 4, 5, 6};
                config.random3query = true;
                Input in = make_input(N, M, Q, config);
                write_output(filename, in);
            }
            {
                string filename = ::format("17_normal_many3query_%02d.in", t++);
                int N = NORMAL_MAX_N;
                int M = NORMAL_MAX_M;
                int Q = NORMAL_MAX_Q;
                random_query_config config;
                config.one_prob = 2;
                config.two_prob = 1;
                config.three_prob = 15;
                config.use_vertical_lines = {4, 5, 8, 9, 10, 14, 19};
                Input in = make_input(N, M, Q, config);
                write_output(filename, in);
            }
        }
        // 階段状の入力
        {
            t = 1;
            {
                string filename = ::format("18_normal_stairs_%02d.in", t++);
                int N = NORMAL_MAX_N;
                int M = NORMAL_MAX_M;
                int Q = NORMAL_MAX_Q - 1;
                Input in = make_stairs_input(N, M, Q);
                write_output(filename, in);
            }
            {
                string filename = ::format("18_normal_stairs_%02d.in", t++);
                int N = NORMAL_MAX_N;
                int M = NORMAL_MAX_M;
                int Q = NORMAL_MAX_Q;
                Input in = make_stairs_input(N, M, Q, true);
                write_output(filename, in);
            }
        }
    }

    // -------------------hard---------------------------
    {
        // Nが最小の場合
        int t = 1;
        {
            {
                string filename = ::format("21_hard_minN_%02d.in", t++);
                int N = HARD_MIN_N;
                int M = HARD_MAX_M;
                int Q = HARD_MAX_Q;
                Input in = make_input(N, M, Q);
                write_output(filename, in);
            }
        }
        // Mが最小の場合
        {
            t = 1;
            {
                string filename = ::format("22_hard_minM_%02d.in", t++);
                int N = HARD_MAX_N;
                int M = HARD_MIN_M;
                int Q = HARD_MAX_Q;
                Input in = make_input(N, M, Q);
                write_output(filename, in);
            }
        }
        // N,M,Qが最大の場合
        {
            t = 1;
            {
                string filename = ::format("24_hard_max_%02d.in", t++);
                int N = HARD_MAX_N;
                int M = HARD_MAX_M;
                int Q = HARD_MAX_Q;
                random_query_config config;
                config.random3query = true;
                Input in = make_input(N, M, Q, config);
                write_output(filename, in);
            }
            {
                string filename = ::format("24_hard_max_%02d.in", t++);
                int N = HARD_MAX_N;
                int M = HARD_MAX_M;
                int Q = HARD_MAX_Q;
                random_query_config config;
                config.use_vertical_lines = {100000000, 100000002};
                config.one_prob = 10;
                config.two_prob = 1;
                config.three_prob = 2;
                Input in = make_input(N, M, Q, config);
                write_output(filename, in);
            }
        }
        // クエリ1,2が多い場合
        {
            t = 1;
            {
                string filename = ::format("25_hard_many12query_%02d.in", t++);
                int N = HARD_MAX_N - rnd.next(0, 100);
                int M = HARD_MAX_M - rnd.next(0, 100);
                int Q = HARD_MAX_Q;
                random_query_config config;
                config.one_prob = 5;
                config.two_prob = 5;
                config.three_prob = 1;
                Input in = make_input(N, M, Q, config);
                write_output(filename, in);
            }
        }
        // クエリ3が多い場合
        {
            t = 1;
            {
                string filename = ::format("26_hard_many3query_%02d.in", t++);
                int N = HARD_MAX_N - rnd.next(0, 100);
                int M = HARD_MAX_M - rnd.next(0, 100);
                int Q = HARD_MAX_Q;
                random_query_config config;
                config.one_prob = 1;
                config.two_prob = 1;
                config.three_prob = 10;
                config.use_vertical_lines = {3, 4};
                Input in = make_input(N, M, Q, config);
                write_output(filename, in);
            }
        }
        // 階段状の入力
        {
            t = 1;
            {
                string filename = ::format("28_hard_stairs_%02d.in", t++);
                int N = HARD_MAX_N - rnd.next(0, 100);
                int M = HARD_MAX_M - rnd.next(0, 100);
                int Q = HARD_MAX_Q;
                Input in = make_stairs_input(N, M, Q);
                write_output(filename, in);
            }
            {
                string filename = ::format("28_hard_stairs_%02d.in", t++);
                int N = HARD_MAX_N - rnd.next(0, 100);
                int M = HARD_MAX_M - rnd.next(0, 100);
                int Q = HARD_MAX_Q;
                Input in = make_stairs_input(N, M, Q, true);
                write_output(filename, in);
            }
        }
    }
}
