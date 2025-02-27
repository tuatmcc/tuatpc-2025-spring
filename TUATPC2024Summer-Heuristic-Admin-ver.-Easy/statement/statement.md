# TUATPC2024Summer (Heuristic) (Admin ver.) (Easy)

## 問題文

長さ $N$ の整数列 $A = (A_1, A_2, \dots, A_N), B = (B_1, B_2, \dots, B_N)$ が与えられます。

以下の $3$ つの条件のうち少なくとも $1$ つを満たすか判定してください。

- $N \leq 2$
- $\underset{1 \leq i \leq N}{\max}\left( \max(A_i, B_i) \right) < 1600$
- $\displaystyle\sum_{i=1}^{N} \max(A_i, B_i)  < 4200$


## 制約

- ${@constraints.MIN_N} \leq N \leq {@constraints.MAX_N}$
- ${@constraints.MIN_A} \leq A_i, B_i \leq {@constraints.MAX_A}$
- 入力は全て整数

### 部分点

この問題に部分点はありません。

## 入力

入力は以下の形式で標準入力から与えられます。

<div style="background: #f5f5f5; border: 1px #ccc solid; 2px 3px 0 #ddd; font-size: 100%; padding: 16px 0 0 15px; color: #333; border-radius: 3px">
    
$N$
$A_1\ \ B_1$
$A_2\ \ B_2$
$\ \vdots$
$A_N\ \ B_N$
    
</div>

## 出力

$3$ つの条件のうち少なくとも $1$ つ満たすものがある場合は `Yes` を、ない場合は `No` を標準出力に出力してください。

{@samples.all}