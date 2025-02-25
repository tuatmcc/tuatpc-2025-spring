#!/usr/bin/env pypy3

import sys

sys.setrecursionlimit(10**6)

# 定数（履歴の操作種別）
UF_OPERATION = 0
DATA_OPERATION = 1


class HistoryEntry:
    def __init__(self, type, index, old_value):
        self.type = type
        self.index = index
        self.old_value = old_value


class RollbackUnionFindWithData:
    def __init__(self, sz):
        self.data = [-1] * sz
        # 各ノードの初期データはそのノード番号
        self.node_data = list(range(sz))
        self.history = []
        self.inner_snap = 0

    def set_data(self, k, val):
        # 変更前の値を記録
        self.history.append(HistoryEntry(DATA_OPERATION, k, self.node_data[k]))
        self.node_data[k] = val

    def get_data(self, k):
        return self.node_data[self.find(k)]

    def find(self, k):
        if self.data[k] < 0:
            return k
        return self.find(self.data[k])

    def unite(self, x, y):
        x = self.find(x)
        y = self.find(y)
        self.history.append(HistoryEntry(UF_OPERATION, x, self.data[x]))
        self.history.append(HistoryEntry(UF_OPERATION, y, self.data[y]))
        if x == y:
            self.history.append(HistoryEntry(DATA_OPERATION, -1, -1))  # 一応ダミー操作
            return False
        if self.data[x] > self.data[y]:
            x, y = y, x
        connected_max_value = max(self.node_data[x], self.node_data[y])
        self.set_data(x, connected_max_value)
        self.data[x] += self.data[y]
        self.data[y] = x
        return True

    def same(self, x, y):
        return self.find(x) == self.find(y)

    def size(self, k):
        return -self.data[self.find(k)]

    def undo(self):
        # uf の操作2回分と node_data の操作1回分を取り消す
        for _ in range(3):
            he = self.history.pop()
            if he.type == UF_OPERATION:
                self.data[he.index] = he.old_value
            else:
                self.node_data[he.index] = he.old_value

    def snapshot(self):
        self.inner_snap = len(self.history)

    def rollback(self, state=-1):
        if state == -1:
            state = self.inner_snap
        while len(self.history) > state:
            self.undo()


class SegmentTreeNode:
    def __init__(self, tl, tr):
        self.tl = tl
        self.tr = tr
        self.edges = []  # 各ノードが管理する辺 (u, v) のリスト
        self.left = None
        self.right = None


def register_edge(node, L, R, edge):
    # 区間 [L, R) とノードの区間 [node.tl, node.tr) が交差しなければ何もしない
    if R <= node.tl or L >= node.tr:
        return
    # ノードの区間が [L, R) に完全に含まれるなら辺を追加
    if L <= node.tl and node.tr <= R:
        node.edges.append(edge)
        return
    mid = (node.tl + node.tr) // 2
    if node.left is None:
        node.left = SegmentTreeNode(node.tl, mid)
        node.right = SegmentTreeNode(mid, node.tr)
    register_edge(node.left, L, R, edge)
    register_edge(node.right, L, R, edge)


def build_segment_tree(intervals, Q_value):
    # セグメント木を [0, Q_value) で構築
    root = SegmentTreeNode(0, Q_value)
    for interval, edge in intervals:
        L, R = interval
        register_edge(root, L, R, edge)
    return root


def main():
    N, M = map(int, input().split())
    Q = int(input())

    queries = []
    # 縦線ごとの構築が必要な高さを記録する辞書
    require_height = {}

    def add_height(key, value):
        if key not in require_height:
            require_height[key] = set()
        require_height[key].add(value)

    for i in range(Q):
        [t, *args] = list(map(int, input().split()))
        if t == 1 or t == 2:
            x = args[0] - 1
            y = args[1] - 1
            queries.append((t, x, y))
            # 横線で変化する頂点
            add_height(x, y)
            add_height(x, y + 1)
            add_height(x + 1, y)
            add_height(x + 1, y + 1)
            # 端点の追加
            add_height(x, 0)
            add_height(x, M + 1)
            add_height(x + 1, 0)
            add_height(x + 1, M + 1)
        else:  # t == 3
            s = args[0] - 1
            queries.append((t, s, -1))
            add_height(s, 0)
            add_height(s, M + 1)

    # 辺の生存期間の記録
    active_edges = {}
    require_node_set = set()
    for x, ys in require_height.items():
        y_vec = sorted(list(ys))
        for i in range(len(y_vec) - 1):
            # ノードの番号は x + y * N
            edge = (x + y_vec[i] * N, x + y_vec[i + 1] * N)
            active_edges[edge] = 0
            require_node_set.add(x + y_vec[i] * N)
            require_node_set.add(x + y_vec[i + 1] * N)

    # 辺の追加・削除のタイミングを記録するためのリスト
    # 各要素は ((L, R), (u, v)) の形
    edges_interval = []
    # 全ての時間にノードを持つセグメント木を構築するため、ダミーの区間 [i, i) と辺 (-1, -1) を追加
    for i in range(Q + 2):
        edges_interval.append(((i, i), (-1, -1)))

    # クエリを 1-indexed の時間で処理
    for i in range(1, Q + 1):
        t, x, y = queries[i - 1]
        if t == 1:
            edge1 = (x + y * N, x + (y + 1) * N)
            edge2 = ((x + 1) + y * N, (x + 1) + (y + 1) * N)
            if edge1 in active_edges:
                edges_interval.append(((active_edges[edge1], i), edge1))
                del active_edges[edge1]
            if edge2 in active_edges:
                edges_interval.append(((active_edges[edge2], i), edge2))
                del active_edges[edge2]
            # 斜めの辺を張る
            new_edge1 = (x + y * N, (x + 1) + (y + 1) * N)
            new_edge2 = ((x + 1) + y * N, x + (y + 1) * N)
            active_edges[new_edge1] = i
            active_edges[new_edge2] = i
        elif t == 2:
            edge1 = (x + y * N, (x + 1) + (y + 1) * N)
            edge2 = ((x + 1) + y * N, x + (y + 1) * N)
            if edge1 in active_edges:
                edges_interval.append(((active_edges[edge1], i), edge1))
                del active_edges[edge1]
            if edge2 in active_edges:
                edges_interval.append(((active_edges[edge2], i), edge2))
                del active_edges[edge2]
            # 縦の辺を張る
            new_edge1 = (x + y * N, x + (y + 1) * N)
            new_edge2 = ((x + 1) + y * N, (x + 1) + (y + 1) * N)
            active_edges[new_edge1] = i
            active_edges[new_edge2] = i
        # t == 3 の場合は何もしない

    # 残った辺の削除タイミングを記録
    for edge, st in active_edges.items():
        edges_interval.append(((st, Q + 1), edge))

    # ノードの番号の振り直し
    convert = {}
    convert_rev = {}
    idx = 0
    # 順序は任意ですが、ここでは昇順にソート
    for x in sorted(require_node_set):
        convert[x] = idx
        convert_rev[idx] = x
        idx += 1

    # edges_interval 内の辺の番号を変換（ダミー辺 (-1, -1) はそのまま）
    new_edges_interval = []
    for interval, edge in edges_interval:
        if edge == (-1, -1):
            new_edges_interval.append((interval, edge))
        else:
            new_edges_interval.append((interval, (convert[edge[0]], convert[edge[1]])))
    edges_interval = new_edges_interval

    # セグ木
    root = build_segment_tree(edges_interval, Q + 2)

    ans = [-2] * Q
    uf = RollbackUnionFindWithData(len(require_node_set))

    def dfs(node):
        nonlocal uf, ans, queries, convert, convert_rev, N, M
        cnt = 0
        if node is None:
            return
        for u, v in node.edges:
            # ダミー辺はスキップ
            if u == -1 or v == -1:
                continue
            if uf.unite(u, v):
                cnt += 1

        if node.tl + 1 == node.tr:
            t = node.tl - 1
            if 0 <= t < len(queries) and queries[t][0] == 3:
                s = queries[t][1]
                ans[t] = convert_rev[uf.get_data(convert[s])] - N * (M + 1)
        else:
            dfs(node.left)
            dfs(node.right)

        for _ in range(cnt):
            uf.undo()

    dfs(root)

    for i in range(Q):
        if queries[i][0] == 3:
            print(ans[i] + 1)


if __name__ == "__main__":
    main()
