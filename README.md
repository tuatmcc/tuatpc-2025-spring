# TUATPC2025 Spring

## チュートリアル

- リポジトリを運用する人向け => [docs/admin.md](./docs/admin.md)
- Docker の使い方 => [docs/docker.md](./docs/docker.md)
- Rimeの使い方 => [docs/rime.md](./docs/rime.md)
- Git/GitHubの使い方 => [docs/git.md](./docs/git.md)

## 対応していること
- Rime の自動実行
- 問題文に関する校閲・HTMLのLint
   - 一部対応しています
   - 「問題」「制約」「入力」「出力」「入力例1」「出力例1」の流れで書かれているか
   - タイトルのみで `<h2>` を使っているか
   - `<code></code>` や `\(\)` の前後で空白を入れているか
- 入力のファイルが `*.in` であることの確認
   - `/\d+[-_].*\.in/` しか許さないようにしました
      - つまり、`00-example.in` とか `01_sample-00.in` みたいにしないと怒られます
   - 変なことされない限りはチェックできるはず…

## 対応していないこと

- C/C++/Ruby/Python以外の言語でのジャッジ
   - 希望があれば追加できます（多分）
- Python3.6系サポート（なんかエラー言われたので3.8にしました）
- GitHub Actions をたっっっくさん実行する
   - Private リポジトリにするので、あまりに酷使すると使えなくなります
   - https://docs.github.com/ja/billing/managing-billing-for-github-actions/about-billing-for-github-actions
   - 一回のテストで5分消費するとしても400回は耐えるので、よほどのことが無い限り大丈夫だとは思います
   - 万が一超えた場合も勝手には課金されないらしいです

## 参考情報
- [AOJの実行環境 _ Aizu Online Judge](https://onlinejudge.u-aizu.ac.jp/system_info)

## Docker 環境の導入

### Docker のインストール

```
curl -fsSL https://get.docker.com -o get-docker.sh
sudo sh get-docker.sh
```