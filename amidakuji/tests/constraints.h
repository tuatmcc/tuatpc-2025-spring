#ifndef CONSTRAINTS_H
#define CONSTRAINTS_H

// 定数定義

constexpr int NORMAL_MIN_N = 2;
constexpr int NORMAL_MAX_N = 20;
constexpr int NORMAL_MIN_M = 1;
constexpr int NORMAL_MAX_M = 100000;
constexpr int NORMAL_MIN_Q = 1;
constexpr int NORMAL_MAX_Q = 100000; // 1e5

constexpr int HARD_MIN_N = 2;
constexpr int HARD_MAX_N = 1000000000; // 1e9
constexpr int HARD_MIN_M = 1;
constexpr int HARD_MAX_M = 1000000000; // 1e9
constexpr int HARD_MIN_Q = 1;
constexpr int HARD_MAX_Q = 100000; // 1e5

constexpr int MIN_N = HARD_MIN_N;
constexpr int MAX_N = HARD_MAX_N;
constexpr int MIN_M = HARD_MIN_M;
constexpr int MAX_M = HARD_MAX_M;
constexpr int MIN_Q = HARD_MIN_Q;
constexpr int MAX_Q = HARD_MAX_Q;

#endif
