#!/usr/bin/env uv run --python pypy3.10
# ac-library-python(https://github.com/not522/ac-library-python/tree/master)
from atcoder.segtree import SegTree
from typing import List

N, M = map(int, input().split())
Q = int(input())


def op(a: List[int], b: List[int]) -> List[int]:
    res = [0] * len(a)
    for i in range(len(a)):
        res[i] = b[a[i]]
    return res


if N * M > 10**9:
    # なんかメモリを食いつぶすので強制終了
    assert False
e = [i for i in range(N)]
v = [[i for i in range(N)] for _ in range(M)]
seg = SegTree(op, e, v)
for _ in range(Q):
    t, *args = map(int, input().split())
    if t == 1 or t == 2:
        x, y = args
        x -= 1
        y -= 1
        p = seg.get(y)
        p[x], p[x + 1] = p[x + 1], p[x]
        seg.set(y, p)
    else:
        s = args[0]
        s -= 1
        res = seg.all_prod()
        ans = res[s] + 1
        print(ans)
