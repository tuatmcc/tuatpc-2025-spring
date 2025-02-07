#!/usr/local/bin/pypy3
import math
from functools import cmp_to_key

def main():
    N, Q = map(int, input().split())
    S = input()
    A = list(map(lambda x : ord(x) - ord('a'), S))
    queries = []
    for i in range(Q):
        l, r = map(int, input().split())
        l -= 1  # 0-indexedに変換
        queries.append((l, r, i))
    
    block_size = N // min(N, int(math.sqrt(Q)))

    def comp(a, b):
        la, ra, _ = a
        lb, rb, _ = b
        block_a = la // block_size
        block_b = lb // block_size
        if block_a != block_b:
            return -1 if block_a < block_b else 1
        if block_a % 2 == 1:
            return -1 if ra > rb else 1
        else:
            return -1 if ra < rb else 1

    queries.sort(key=cmp_to_key(comp))

    M = 26
    lsum = [[0] * M for _ in range(M)]
    rsum = [[0] * M for _ in range(M)]
    mid = [0] * M
    cnt = [0] * M

    l, r = 0, 0
    cans = 0

    ans = [0] * Q
    for li, ri, idx in queries:
        while l > li:
            c = A[l - 1]  # 新しく追加される文字
            cans += mid[c]  # c + (? + c + ?)
            for i in range(M):
                if i == c:
                    continue
                mid[i] += rsum[i][c]
                lsum[i][c] += cnt[i]
                rsum[c][i] += cnt[i]
            cnt[c] += 1
            l -= 1
        while r < ri:
            c = A[r]  # 新しく追加される文字
            cans += mid[c]  # (? + c + ?) + c
            for i in range(M):
                if i == c:
                    continue
                mid[i] += lsum[i][c]
                lsum[c][i] += cnt[i]
                rsum[i][c] += cnt[i]
            cnt[c] += 1
            r += 1
        while l < li:
            c = A[l]  # 削除される文字
            cans -= mid[c]  # c + (? + c + ?)
            for i in range(M):
                if i == c:
                    continue
                mid[i] -= rsum[i][c]
                lsum[i][c] -= cnt[i]
                rsum[c][i] -= cnt[i]
            cnt[c] -= 1
            l += 1

        while r > ri:
            c = A[r - 1]  # 削除される文字
            cans -= mid[c]  # (? + c + ?) + c
            for i in range(M):
                if i == c:
                    continue
                mid[i] -= lsum[i][c]
                lsum[c][i] -= cnt[i]
                rsum[i][c] -= cnt[i]
            cnt[c] -= 1
            r -= 1
        ans[idx] = cans

    for x in ans:
        print(x)

if __name__ == "__main__":
    main()
