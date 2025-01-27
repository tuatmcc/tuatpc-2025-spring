# statements-manager の使い方

## はじめに

Rime の使い方については理解しているものとします。

## 概要

競プロの作問で起こる典型ミスとして

- 問題文に記載されている制約と Generator / Validator の制約が異なっていて、実際に用いられる入力で制約違反が起こってしまう
- 問題文と Generator で用いられているサンプル入出力が異なる

というものがあります。

これらのミスを防ぐために statements-manager を使います。このツールは競プロの問題文の管理の補助を行ってくれるツールで、問題ごとに `problem.toml` という設定ファイルを作り、`ss-manager run` を実行することで

- 設定ファイルに記載されている制約から `constraints.hpp` を自動生成する
- Markdown で記述された問題文を HTML や PDF にコンパイルする
- 設定ファイルに記載されている制約を問題文の指定した箇所に展開する
- 入出力例を問題文の指定した箇所に展開する

といったことを行ってくれます。

## 追加でやること

- `{問題ディレクトリ}/problem.toml`
- `{問題ディレクトリ}/problem.toml`


## インストール

```
pip install statements-manager
```

作問用 Docker イメージにはすでにインストールされているので、特に作業を行う必要はありません。

## ディレクトリ構成

Rime 単体でのディレクトリ構成は以下のようなものでした。

```
TUATPC
├── PROJECT
├── A/
│   ├── PROBLEM
│   ├── tests/
│   │   ├── TESTSET
│   │   ├── generator.cpp
│   │   └── validator-kobaryo222.cpp
│   ├── AC-kobaryo222/
│   ├── WA-kobaryo222/
│   │    ...
├── B/
│   ├── PROBLEM
│   ├── AC-kobaryo222/
│   │    ...
```

statements-manager を使うためには以下のようにします。

```
TUATPC
├── ++ problemset.toml (ss-manager の問題セット全体についての設定のファイル)
├── PROJECT
├── A/
│   ├── ++ problem.toml (ss-manager の A 問題についての設定のファイル)
│   ├── PROBLEM
│   ├── tests/
│   │   ├── ++ 00_sample_01.in (入力例 1)
│   │   ├── ++ 00_sample_01.out (出力例 1)
│   │   ├── ++ 00_sample_02.in (入力例 2)
│   │   ├── ...
│   │   ├── ++ constraints.hpp (制約が含まれたヘッダーファイル・ss-manager で自動生成される)
│   │   ├── TESTSET
│   │   ├── generator.cpp
│   │   └── validator-kobaryo222.cpp
│   ├── ++ statement/ (問題文用のディレクトリ)
│   │   ├── ++ statement.md (問題文)
│   │   └── ++ figure1.png (問題文中の図等・あれば)
│   ├── AC-kobaryo222/
│   ├── WA-kobaryo222/
│   │    ...
├── B/
│   ├── ++ problem.toml (ss-manager の B 問題についての設定のファイル)
│   ├── PROBLEM
│   ├── tests/
│   ├── ++ statement/
│   ├── AC-kobaryo222/
│   │    ...
```

## 