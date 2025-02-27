# ngng 文字列

## 問題文

英小文字からなる長さ $N$ の文字列 $S$ が与えられます。$S$ の $i$ 文字目を $S_i$ とします。

$Q$ 個のクエリが与えられるので、処理してください。

$i$ 番目のクエリでは整数 $L_i, R_i$ が与えられるので、以下の問題を解いてください。

- 次の条件をすべて満たす整数の組 $(a, b, c, d)$ の個数を求めてください。
    - $L_i \le a < b < c < d \le R_i$
    - $S_a = S_c$
    - $S_b = S_d$
    - $S_a \ne S_b$

## 制約

- ${@constraints.MIN_N} \le N \le {@constraints.MAX_N}$
- ${@constraints.MIN_Q} \le Q \le {@constraints.MAX_Q}$
- $S$ は英小文字のみからなる長さ $N$ の文字列
- $1 \le L_i \le  R_i \le N$
- $N, Q, L_i, R_i$ は整数

### 部分点

この問題に部分点は存在しません。

## 入力

入力は以下の形式で標準入力から与えられます。

<div style="background: #f5f5f5; border: 1px #ccc solid; 2px 3px 0 #ddd; font-size: 100%; padding: 16px 0 0 15px; color: #333; border-radius: 3px">
    
$N\ \ Q$
$S$
$L_1\ \ R_1$
$L_2\ \ R_2$
$\ \vdots$
$L_Q\ \ R_Q$

</div>


## 出力

標準出力に $Q$ 行出力してください。$i$ 行目には、$i$ 番目のクエリの答えを出力してください。

{@samples.all}