#!/usr/local/bin/pypy3

from sys import stdin

input = stdin.readline

def main():
    N, Q = map(int, input().split())
    S = input().rstrip()

    assert((N + Q) * 26**2 <= 10 ** 7) # TLE のケースは強制的に RE にする

    queries = []
    for i in range(Q):
        l, r = map(int, input().split())
        l -= 1  # 0-indexedに変換
        queries.append((l, r))
    C = 26
    c1 = [[0] * C for _ in range(N + 1)]
    c2 = [[[0] * C for _ in range(C)] for _ in range(N + 1)]
    c3 = [[[0] * C for _ in range(C)] for _ in range(N + 1)]
    c4 = [[[0] * C for _ in range(C)] for _ in range(N + 1)]

    for i in range(1, N + 1):
        s = ord(S[i - 1]) - ord('a')
        for j in range(C):
            c1[i][j] = c1[i - 1][j]
        c1[i][s] += 1

    for i in range(2, N + 1):
        s = ord(S[i - 1]) - ord('a')
        for j in range(C):
            for k in range(C):
                c2[i][j][k] = c2[i - 1][j][k]
        for j in range(C):
            if j == s:
                continue
            c2[i][j][s] += c1[i - 1][j]

    for i in range(3, N + 1):
        s = ord(S[i - 1]) - ord('a')
        for j in range(C):
            for k in range(C):
                c3[i][j][k] = c3[i - 1][j][k]
        for j in range(C):
            if j == s:
                continue
            c3[i][s][j] += c2[i - 1][s][j]

    for i in range(4, N + 1):
        s = ord(S[i - 1]) - ord('a')
        for j in range(C):
            for k in range(C):
                c4[i][j][k] = c4[i - 1][j][k]
        for j in range(C):
            if j == s:
                continue
            c4[i][j][s] += c3[i - 1][j][s]

    f1 = [0] * C
    f2 = [[0] * C for _ in range(C)]
    f3 = [[0] * C for _ in range(C)]
    f4 = [[0] * C for _ in range(C)]
    results = []

    for l, r in queries:
        ans = 0
        for i in range(C):
            f1[i] = c1[r][i] - c1[l][i]
        for i in range(C):
            for j in range(C):
                if i == j:
                    continue
                f2[i][j] = c2[r][i][j] - c2[l][i][j]
                f2[i][j] -= c1[l][i] * f1[j]
        for i in range(C):
            for j in range(C):
                if i == j:
                    continue
                f3[i][j] = c3[r][i][j] - c3[l][i][j]
                f3[i][j] -= c1[l][i] * f2[j][i]
                f3[i][j] -= c2[l][i][j] * f1[i]
        for i in range(C):
            for j in range(C):
                if i == j:
                    continue
                f4[i][j] = c4[r][i][j] - c4[l][i][j]
                f4[i][j] -= c1[l][i] * f3[j][i]
                f4[i][j] -= c2[l][i][j] * f2[i][j]
                f4[i][j] -= c3[l][i][j] * f1[j]
                ans += f4[i][j]
        results.append(ans)

    for result in results:
        print(result)

if __name__ == "__main__":
    main()
