# あみだくじ
## 問題

あみだくじとは、運試しや抽選に使われる、日本でも古くから親しまれているくじ引きの一種です。

左から縦線 $1$、縦線 $2$、$\dots$、縦線 $N$ と番号がついた $N$ 本の縦線からなるあみだくじがあります。縦線は全て $M + 1\ [\mathrm{cm}]$ であり、横線の端点となれるのは上から $1, 2, \dots, M\ [\mathrm{cm}]$ の位置のみです。

<!-- ![あみだくじ(1)](https://hackmd.io/_uploads/rJeFfkG5ke.svg) -->
![あみだくじ.drawio](https://hackmd.io/_uploads/BJT_Fp2qkg.svg)

次の $Q$ 個のクエリを処理してください。
- `1 x y`
    - 縦線 $x$ と 縦線 $(x + 1)$ の間に上から $y\ [\mathrm{cm}]$ の位置に横線を平行に書き加える。このクエリが与えられるとき、縦線 $(x-1)$ と縦線 $x$ の間、縦線 $x$ と縦線 $(x + 1)$ の間、縦線 $(x+1)$ と縦線 $(x + 2)$ の間に上から $y\ [\mathrm{cm}]$ の位置に横線がないことが保証される。
- `2 x y`
    - 縦線 $x$ から縦線 $(x + 1)$ の間の上から $y\ [\mathrm{cm}]$ の位置に引かれている平行な横線を削除する。このクエリが与えられるとき、縦線 $x$ と縦線 $x + 1$ の間に上から $y\ [\mathrm{cm}]$ の位置に横線があることが保証される。
- `3 s`
    - $s$ 番目の縦線の上端から、横線があれば必ずそれを通るというルールで下へたどったときに、最終的にたどり着く縦棒の番号を出力する。

## 制約

<!-- 平方分割 -->
- ${@constraints.MIN_N} \le N \le {@constraints.MAX_N}$
- ${@constraints.MIN_M} \le M \le {@constraints.MAX_M}$
- ${@constraints.MIN_Q} \le Q \le {@constraints.MAX_Q}$
- $1 \leq x \leq N - 1$
- $1 \leq y \leq M$
- $1 \leq s \leq N$
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
$query_1$
$query_2$
$\vdots$
$query_Q$

</div>

ただし、$query_i$は $i$ 個目のクエリを表し、以下のいずれかの形式です。
```
1 x y
```
```
2 x y
```
```
3 s
```

# 出力
問題文の指示に従ってクエリへの答えを改行区切りで標準出力に出力してください。
