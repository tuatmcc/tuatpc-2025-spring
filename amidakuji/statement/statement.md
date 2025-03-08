# あみだくえりー

## 問題文

あみだくじとは、運試しや抽選に使われる、日本でも古くから親しまれているくじ引きの一種です。

左から縦線 $1$、縦線 $2$、$\dots$、縦線 $N$ と番号がついた $N$ 本の縦線からなるあみだくじがあります。縦線は全て $M + 1\ [\mathrm{cm}]$ であり、横線の端点となれるのは上端から $1, 2, \dots, M\ [\mathrm{cm}]$ の位置のみです。

<!-- ![あみだくじ(1)](https://hackmd.io/_uploads/rJeFfkG5ke.svg) -->
![あみだくじ.drawio](https://hackmd.io/_uploads/S1uIw-CqJl.svg)

クエリが $Q$ 個与えられるので順に処理してください。クエリは次の $3$ 種類あり、以下のいずれかの形式で与えられます。
- `1 x y` : 縦線 $x$ と縦線 $(x + 1)$ の間の上端から $y\ [\mathrm{cm}]$ の位置に横線を平行に引く。
    - このクエリが与えられる直前において、縦線 $x$ と 縦線 $(x + 1)$ の間の上端から $y\ [\mathrm{cm}]$ の位置に接している他の横線が存在しないことが保証される。
- `2 x y` : 縦線 $x$ と縦線 $(x + 1)$ の間の上端から $y\ [\mathrm{cm}]$ の位置に引かれている平行な横線を削除する。
    - このクエリが与えられる直前において、縦線 $x$ と 縦線 $(x + 1)$ の間の上端から $y\ [\mathrm{cm}]$ の位置に横線が存在することが保証される。
- `3 s` : 縦線 $s$ の上端から、横線があれば必ずそれを通るというルールで下へたどったときに、最終的にたどり着く縦線の番号を出力する。

## 制約

<!-- 平方分割 -->
- ${@constraints.MIN_N} \le N \le {@constraints.MAX_N}$
- ${@constraints.MIN_M} \le M \le {@constraints.MAX_M}$
- ${@constraints.MIN_Q} \le Q \le {@constraints.MAX_Q}$
- $1 \leq x \leq N - 1$
- $1 \leq y \leq M$
- $1 \leq s \leq N$
- $1$ つ目の形式のクエリについて、縦線 $x$ と 縦線 $(x + 1)$ の間の上端から $y\ [\mathrm{cm}]$ の位置に接している他の横線が存在しない
- $2$ つ目の形式のクエリについて、縦線 $x$ と 縦線 $(x + 1)$ の間の上端から $y\ [\mathrm{cm}]$ の位置に横線が存在する
- 入力はすべて整数

### 部分点
<!-- セグ木 -->
以下の制約を追加したデータセットに正解した場合は $1$ 点が与えられる。
- ${@constraints.SUBTASK_MIN_N} \le N \le {@constraints.SUBTASK_MAX_N}$
- ${@constraints.SUBTASK_MIN_M} \le M \le {@constraints.SUBTASK_MAX_M}$


## 入力

入力は以下の形式で標準入力から与えられます。

<div class="code-math">

$N$ $M$
$Q$
$\mathrm{query}_1$
$\mathrm{query}_2$
$\vdots$
$\mathrm{query}_Q$

</div>

ただし、$\mathrm{query}_i$は $i$ 個目のクエリを表し、以下のいずれかの形式です。
```txt
1 x y
```
```txt
2 x y
```
```txt
3 s
```

## 出力
$3$ つ目の形式のクエリの個数を  $k$ として、標準出力に $k$  行出力してください。  $i$ 行目には  $i$  個目の $3$ つ目の形式のクエリに対する答えを出力してください。

{@samples.all}
