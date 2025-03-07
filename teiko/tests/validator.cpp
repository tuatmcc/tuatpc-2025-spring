# include "testlib.h"
# include <bits/stdc++.h>
# include <atcoder/modint>
using namespace std;
using namespace std::literals::string_literals;
using Fp = atcoder::modint998244353;

const int Q_MIN = 1;
const int Q_MAX = (long long)(1e5);
const int MAX_HW = 1500000;
const int MAX_REG = 30;

int main(int argc, char* argv[]){
   registerValidation(argc, argv);
   int Q = inf.readInt();
   inf.readEoln();

   int sum = 0;

   while (Q--) {
      const int N = inf.readInt();
      inf.readEoln();
      std::vector<std::string> s = inf.readLines(N);
      for (auto& si : s) {
         sum += si.size();
         //  inf.ensure(N * (int)si.size() <= MAX_HW);
      }
   
      class Parser {
       public:
           //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
           //  2.1. コンストラクタ
           //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
           Parser(const std::vector<std::string>& _s)
               : s(_s),
               height(s.size()),
               width(s[0].size())
           {}
   
           //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
           //  2.2. パースをする
           //  
           // <回路> にあたる部分です。
           //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
           Fp parse() {
               int i = start_point();
               int j = "o---"s.size();
               Fp R = series(i, j).first;
               return R;
           }
   
           //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
           //  2.3. <直列抵抗>
           //
           //  直列抵抗の合成抵抗と右端を返します。
           //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
           std::pair<Fp, int> series(int i, int j) {
               Fp R = 0;
               std::tie(R, j) = parallel(i, j);
               while (s[i][j] == '+' || s[i][j] == '^') {
                   if (s[i][j] == '+' && s[i][j + 1] == ' ') {
                       break;
                   }
                   if (s[i][j] == '+' && (s[i - 1][j] == '|' || s[i + 1][j] == '|')) {
                       break;
                   }
                   Fp R2 = 0;
                   std::tie(R2, j) = parallel(i, j);
                   R += R2;
               }
               return {R, j};
           }
   
           //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
           //  2.3. <並列抵抗>
           //
           //  並列抵抗の合成抵抗と右端を返します。
           //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
           std::pair<Fp, int> parallel(int i, int j) {
               if (s[i][j] == '+') {
                   int top = i;
                   while (s[top - 1][j] != ' ') {
                       top--;
                   }
   
                   Fp G = 0;
                   int next_j = 0;
                   for (int row = top; s[row][j] != ' '; row++) {
                       if (s[row][j] == '+') {
                           Fp R;
                           int b;
                           int nj = skip_wire(row, j + 1);
                           std::tie(R, b) = series(row, nj);
                           next_j = std::max<int>(next_j, b);
                           G += Fp(1) / R;
                       }
                   }
   
                   Fp R = Fp(1) / G;
                   next_j = skip_wire(i, next_j);
                   return { R, next_j };
               }
               else {
                   Fp R = Fp(1);
                   int next_j = skip_wire(i, j + "^v^v^v"s.size()) + 1;
                   return { R, next_j };
               }
           }
   
           //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
           //  2.3. <始点>
           //
           //  `o` の行数を返します。
           //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
           int start_point() {
               for (int i = 0; i < height; i++) {
                   if (s[i][0] == 'o') {
                       return i;
                   }
               }
               assert(false);
           }
   
           //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
           //  2.4. 導線
           //
           //  導線をスキップしたときの j の位置を返します
           //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
           int skip_wire(int r, int c) {
               while (s[r][c] == '-') {
                   c++;
               }
               return c;
           }
   
       private:
           std::vector<std::string> s;
           int height, width;
       } parser(s);
   
       int cnt = 0;
       for (auto line : s) {
           for (auto c : line) {
               std::set<int> chs = {'|', '-', 'o', ' ', '^', 'v', '+'};
               inf.ensure(chs.count(c) == 1);
           }
           for (int i = 0; i < line.size(); i++) {
               auto sub = line.substr(i, "^v^v^v"s.size());
               if (sub == "^v^v^v") {
                   cnt++;
               }
           }
       }
       inf.ensure(cnt <= MAX_REG);
   
       for (int i = 0; i < s.size() - 1; i++) {
           for (int j = 0; j < s[i].size(); j++) {
               if (s[i][j] == '+') {
                   inf.ensure(s[i + 1][j] == ' ');
               }
           }
       }
   }

   inf.readEof();

   inf.ensure(sum <= MAX_HW);

   return 0;
}