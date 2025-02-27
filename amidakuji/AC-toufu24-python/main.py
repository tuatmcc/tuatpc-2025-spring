#!/usr/bin/env pypy3

import math
import bisect


def main():
    # 入力
    N, M_orig = map(int, input().split())
    Q = int(input())
    queries = []
    for _ in range(Q):
        [t, *args] = list(map(int, input().split()))
        if t == 1 or t == 2:
            x = int(args[0])
            y = int(args[1])
            queries.append([t, x, y])
        else:
            s = int(args[0])
            queries.append([t, s, -1])

    # y 座標の座標圧縮
    ys = []
    for q in queries:
        if q[0] != 3:
            ys.append(q[2])
    ys = sorted(set(ys))
    zipy = {y: i + 1 for i, y in enumerate(ys)}
    for q in queries:
        if q[0] != 3:
            q[2] = zipy[q[2]]

    # 平方分割
    M = len(ys)
    block_size = int(math.sqrt(M)) + 1
    block_cnt = (M + block_size - 1) // block_size + 1

    # ブロックごとに管理するデータ構造
    # to[i]: ブロック i 内で各縦線 j の先頭がどこに行くかを記録する辞書
    to = [dict() for _ in range(block_cnt)]
    # lines[i]: ブロック i 内で、各縦線から出ている横線の (y % block_size) の値を昇順リストで管理する辞書
    lines = [dict() for _ in range(block_cnt)]

    # x 番目の縦線の座標 y の位置からブロックの先頭まで逆順にたどったときの縦線の番号を返す関数
    def block_first_pos(x, y):
        block_idx = y // block_size
        nx = x
        ny = y % block_size
        while ny >= 0:
            l = -1
            r = -1
            # 左側 (nx-1) の横線を調べる
            if (nx - 1) in lines[block_idx]:
                arr = lines[block_idx][nx - 1]
                pos = bisect.bisect_right(arr, ny)
                if pos > 0:
                    l = arr[pos - 1]
            # 右側 (nx) の横線を調べる
            if nx in lines[block_idx]:
                arr = lines[block_idx][nx]
                pos = bisect.bisect_right(arr, ny)
                if pos > 0:
                    r = arr[pos - 1]
            # 近い方に移動する
            if l >= r:
                if l == -1:
                    break
                ny = l
                nx -= 1
            else:
                ny = r
                nx += 1
            ny -= 1
        return nx

    ans = []
    for q in queries:
        if q[0] == 1:
            x = q[1]
            y = q[2]
            block_id = y // block_size
            first_pos_left = block_first_pos(x, y)
            first_pos_right = block_first_pos(x + 1, y)
            if first_pos_left not in to[block_id]:
                to[block_id][first_pos_left] = first_pos_left
            if first_pos_right not in to[block_id]:
                to[block_id][first_pos_right] = first_pos_right
            # swap
            to[block_id][first_pos_left], to[block_id][first_pos_right] = (
                to[block_id][first_pos_right],
                to[block_id][first_pos_left],
            )

            # 横線を追加する
            if x not in lines[block_id]:
                lines[block_id][x] = []
            bisect.insort(lines[block_id][x], y % block_size)
        elif q[0] == 2:
            x = q[1]
            y = q[2]
            block_id = y // block_size
            first_pos_left = block_first_pos(x, y)
            first_pos_right = block_first_pos(x + 1, y)
            if first_pos_left not in to[block_id]:
                to[block_id][first_pos_left] = first_pos_left
            if first_pos_right not in to[block_id]:
                to[block_id][first_pos_right] = first_pos_right
            # swap
            to[block_id][first_pos_left], to[block_id][first_pos_right] = (
                to[block_id][first_pos_right],
                to[block_id][first_pos_left],
            )

            # 横線を削除する
            if x in lines[block_id]:
                arr = lines[block_id][x]
                pos = bisect.bisect_left(arr, y % block_size)
                if pos < len(arr) and arr[pos] == y % block_size:
                    arr.pop(pos)
        else:
            cur = q[1]
            for i in range(block_cnt):
                if cur in to[i]:
                    cur = to[i][cur]
            ans.append(str(cur))

    for s in ans:
        print(s)


if __name__ == "__main__":
    main()
