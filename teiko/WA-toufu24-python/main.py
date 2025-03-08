#!/usr/bin/env pypy3
MOD = 998244353


class ModInt:
    def __init__(self, value):
        self.value = value % MOD

    def __add__(self, other):
        return ModInt(self.value + other.value)

    def __sub__(self, other):
        return ModInt(self.value - other.value)

    def __mul__(self, other):
        return ModInt(self.value * other.value)

    def __truediv__(self, other):
        return ModInt(
            self.value * pow(other.value, MOD - 2, MOD)
        )  # フェルマーの小定理で逆元

    def val(self):
        return self.value


class DSU:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [1] * n
        self.size = [1] * n

    def find(self, x):
        if self.parent[x] != x:
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        root_x = self.find(x)
        root_y = self.find(y)
        if root_x != root_y:
            if self.rank[root_x] < self.rank[root_y]:
                root_x, root_y = root_y, root_x
            self.parent[root_y] = root_x
            if self.rank[root_x] == self.rank[root_y]:
                self.rank[root_x] += 1
            self.size[root_x] += self.size[root_y]

    def leader(self, x):
        return self.find(x)


class Edge:
    def __init__(self, to, resist):
        self.to = to
        self.resist = resist

    def __lt__(self, other):
        return (self.to, self.resist.val()) < (other.to, other.resist.val())


def reduce_zero_edge(graph, start_idx, goal_idx):
    n = len(graph)
    dsu = DSU(n)

    for i in range(n):
        for e in graph[i]:
            if e.resist.val() == 0:
                dsu.union(i, e.to)

    comp = [dsu.leader(i) for i in range(n)]
    comp_map = {}
    new_id = 0

    for i in range(n):
        r = comp[i]
        if r not in comp_map:
            comp_map[r] = new_id
            new_id += 1

    new_graph = [[] for _ in range(new_id)]

    for i in range(n):
        for e in graph[i]:
            if e.resist.val() != 0:
                u, v = comp_map[dsu.leader(i)], comp_map[dsu.leader(e.to)]
                if u != v and u < v:
                    new_graph[u].append(Edge(v, e.resist))

    new_start = comp_map[dsu.leader(start_idx)]
    new_goal = comp_map[dsu.leader(goal_idx)]

    return new_graph, new_start, new_goal


class Edge:
    def __init__(self, to, resist):
        self.to = to
        self.resist = resist


def make_graph(s):
    """入力からグラフを構築する"""
    h = len(s)
    w = len(s[0])

    start, goal = None, None

    for i in range(h):
        for j in range(w):
            if j + 3 <= w and s[i][j : j + 3] == "o--":
                start = (i, j)
            elif j + 3 <= w and s[i][j : j + 3] == "--o":
                goal = (i, j + 2)

    node_idx = {}
    start_idx = goal_idx = -1

    for i in range(h):
        for j in range(w):
            if s[i][j] in {"o", "+"}:
                node_idx[(i, j)] = len(node_idx)
                if (i, j) == start:
                    start_idx = node_idx[(i, j)]
                if (i, j) == goal:
                    goal_idx = node_idx[(i, j)]

    graph = [[] for _ in range(len(node_idx))]
    dx = [0, 1]
    dy = [1, 0]

    for i in range(h):
        for j in range(w):
            if (i, j) in node_idx:
                for direction in range(2):
                    ni, nj = i + dx[direction], j + dy[direction]
                    resist = ModInt(0)

                    while (
                        0 <= ni < h
                        and 0 <= nj < w
                        and (ni, nj) not in node_idx
                        and s[ni][nj] not in {" ", "."}
                    ):
                        if s[ni][nj] in {"v", "^"}:
                            resist += ModInt(1)
                            while (
                                0 <= ni < h and 0 <= nj < w and s[ni][nj] in {"v", "^"}
                            ):
                                ni += dx[direction]
                                nj += dy[direction]
                            continue
                        ni += dx[direction]
                        nj += dy[direction]

                    if (ni, nj) in node_idx:
                        graph[node_idx[(i, j)]].append(Edge(node_idx[(ni, nj)], resist))

    # print(len(graph), file=sys.stderr)
    # for i in range(len(graph)):
    #     for e in graph[i]:
    #         print(i, e.to, e.resist.val(), file=sys.stderr)

    return reduce_zero_edge(graph, start_idx, goal_idx)


def create_admittance_matrix(graph, n):
    """
    グラフからアドミタンス行列 Y を作成する。
    """
    Y = [dict() for _ in range(n)]
    for i in range(n):
        # 対角成分は初期的に0
        Y[i][i] = ModInt(0)
    for i in range(n):
        for edge in graph[i]:
            j = edge.to
            r = edge.resist
            if r.val() > 0:
                g = ModInt(1) / r  # アドミタンス = 1 / 抵抗
                # 非対角成分
                Y[i][j] = Y[i].get(j, ModInt(0)) - g
                Y[j][i] = Y[j].get(i, ModInt(0)) - g
                # 対角成分
                Y[i][i] = Y[i].get(i, ModInt(0)) + g
                Y[j][j] = Y[j].get(j, ModInt(0)) + g
    return Y


def solve_sparse(Y, b):
    """
    疎行列表現の Y と右辺ベクトル b に対して、Gaussian消去法を行う。
    """
    n = len(Y)
    for i in range(n):
        # ピボット要素が 0 でないことを確認
        if i not in Y[i] or Y[i][i].val() == 0:
            raise Exception("Zero pivot encountered!")
        inv_pivot = ModInt(1) / Y[i][i]
        # 行 i を正規化
        for j in list(Y[i].keys()):
            Y[i][j] = Y[i][j] * inv_pivot
            if Y[i][j].val() == 0:
                del Y[i][j]
        b[i] = b[i] * inv_pivot

        # 他の行 k に対して消去
        for k in range(n):
            if k == i:
                continue
            if i in Y[k]:
                factor = Y[k][i]
                for j, pivot_val in Y[i].items():
                    Y[k][j] = Y[k].get(j, ModInt(0)) - factor * pivot_val
                    if Y[k][j].val() == 0:
                        del Y[k][j]
                # 消去後、列 i は0になるはず
                if i in Y[k]:
                    del Y[k][i]
                b[k] = b[k] - factor * b[i]
    return b


def compute_equivalent_resistance(Y, start, goal):
    """
    goal に対応する行・列を削除して縮約行列を作成し、
    疎行列用のGaussian消去法で連立一次方程式 Y * V = b を解く。
    """
    n = len(Y)
    # goalに対応する行・列を削除した際のインデックスの対応付け
    mapping = {}
    idx = 0
    for i in range(n):
        if i == goal:
            continue
        mapping[i] = idx
        idx += 1
    m = n - 1  # 縮約後のサイズ

    # 縮約行列 Y_reduced を疎行列形式で作成
    Y_reduced = [dict() for _ in range(m)]
    for i in range(n):
        if i == goal:
            continue
        new_i = mapping[i]
        for j, val in Y[i].items():
            if j == goal:
                continue
            new_j = mapping[j]
            Y_reduced[new_i][new_j] = Y_reduced[new_i].get(new_j, ModInt(0)) + val

    # 入力電流ベクトル b（startに1, それ以外は0、goalは削除済み）
    b = [ModInt(0) for _ in range(m)]
    b[mapping[start]] = ModInt(1)

    V_reduced = solve_sparse(Y_reduced, b)
    # goalの電位は0に固定しているので、startの電位が合成抵抗となる
    return V_reduced[mapping[start]]


def main():
    h = int(input())
    s = [input().rstrip() for _ in range(h)]

    max_len = max(len(line) for line in s)
    s = [line.ljust(max_len, " ") for line in s]

    graph, start_idx, goal_idx = make_graph(s)
    # print(len(graph), file=sys.stderr)
    # for i in range(len(graph)):
    #     for e in graph[i]:
    #         print(i, e.to, e.resist.val(), file=sys.stderr)

    # print(start_idx, goal_idx, file=sys.stderr)

    # アドミタンス行列を構築
    Y = create_admittance_matrix(graph, len(graph))

    # 合成抵抗を求める
    R_eq = compute_equivalent_resistance(Y, start_idx, goal_idx)

    # 結果を出力
    print(R_eq.val())


if __name__ == "__main__":
    q = int(input())
    for _ in range(q):
        main()
