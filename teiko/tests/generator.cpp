# include "testlib.h"
# include <bits/stdc++.h>
# include <cassert>
using namespace std;

template <class T>
bool chmax(T& a, const T& b) {
   if (a < b) {
      a = b;
      return true;
   }
   return false;
}

template <class T>
bool chmin(T& a, const T& b) {
   if (a > b) {
      a = b;
      return true;
   }
   return false;
}

const int R_NUM_MIN = 1;
const int R_NUM_MAX = 100;

// 1.
// これを生成する。
// [R, (R, R), (R, [R, R, R])]
//
// 2.
// 

struct Size {
   Size() = default;
   Size(int h, int w) : height(h), width(w) {}
   int height;
   int width;
};

// (R, R) が直列
// [R, R] が並列
class Generator {
public:
   char open_bracket() {
      if (rnd.next(0, 1)) {
         return '[';
      }
      else {
         return '(';
      }
   }

   char close_bracket(char c) {
      return (c == '(') ? ')' : ']';
   }

   string generate_bracket_sequence(int N, int bracket_count = -1) {
      if (N == 1) return "R";

      if (bracket_count == -1) {
         bracket_count = rnd.next(1, N / 2);
         // bracket_count = 1 + rand() % (N / 2);  // Random bracket count between 1 and N/2
      }

      string result;
      vector<int> partitions;
      int remaining = N;

      while (remaining > 0) {
         if (remaining <= 2) {
            partitions.push_back(remaining);
            break;
         }
         int part = rnd.next(2, min(remaining, max(2, N / bracket_count)) + 1);
         // int part = 2 + rand() % min(remaining, max(2, N / bracket_count));
         if (part > remaining) part = remaining;
         partitions.push_back(part);
         remaining -= part;
      }

      result += open_bracket();
      for (int i = 0; i < (int)partitions.size(); i++) {
         char ob = open_bracket();
         result += ob;
         result += string(partitions[i], 'R');
         result += close_bracket(ob);
      }
      result += close_bracket(result[0]);

      return result;
   }

   void gen_source(int N, int bracket_count = -1) {
      source = generate_bracket_sequence(N, bracket_count);
   }

   void totonoe() {
      for (auto& si : ret) {
         for (auto& c : si) {
            if (c == '*') {
               c = ' ';
            }
         }
      }

      while (true) {
         bool ok = true;
         for (char c : ret.back()) {
            ok &= c == ' ';
         }
         if (ok) {
            ret.pop_back();
         }
         else {
            break;
         }
      }
      while (true) {
         bool ok = true;
         for (auto line : ret) {
            ok &= line.back() == ' ';
         }
         if (ok) {
            for (auto& line : ret) {
               line.pop_back();
            }
         }
         else {
            break;
         }
      }
   }

   int cur = 0;

   std::vector<std::string> generate2D() {
      // int H = require_size(0, source.size() - 1).height * 2;
      // int W = require_size(0, source.size() - 1).width * 2;
      int H = 1;
      int W = 1;
      ret.assign(H, std::string(W, '*'));

      kaiseki(0, 4);

      totonoe();

      return ret;
   }

   // 回路 ::= 直列 | 並列 | 抵抗
   // 直列 ::= ( 回路 回路 … 回路 )
   // 並列 ::= [ 回路 回路 … 回路 ]
   void kaiseki(int i, int j) {
      cur = 0;
      j = asgn(ret, 0, 0, "o---");
      auto [di, dj] = kairo(i, j);
      asgn(ret, i, j + dj, "---o")  ;
   }

   std::pair<int, int> kairo(int i, int j) {
      // 直列
      if (source[cur] == '(') {
         int h = 0, w = 0;
         skip("(");

         int di, dj;
         std::tie(di, dj) = kairo(i, j);
         chmax(h, di);
         w += dj;

         while (source[cur] != ')') {
            j += dj;

            j = asgn(ret, i, j, "---");
            w += 3;

            std::tie(di, dj) = kairo(i, j);
            chmax(h, di);
            w += dj;
         }

         skip(")");
         return {h, w};
      }
      else if (source[cur] == '[') {
         skip("[");
         int h = 0, w = 0;

         std::vector<int> is;
         std::pair<int, int> origin = { i, j };

         asgn(ret, i, j, "+---");
         int di, dj;
         std::tie(di, dj) = kairo(i, j + "+---"s.size());
         is.push_back(i);
         h += di;
         chmax(w, dj);
         while (source[cur] != ']') {
            for (int iter = 0; iter < di; iter++) {
               asgn(ret, ++i, j, "|");
            }

            h++;
            asgn(ret, ++i, j, "+---");
            is.push_back(i);

            std::tie(di, dj) = kairo(i, j + "+---"s.size());

            h += di;
            chmax(w, dj);
         }

         w += "+---"s.size();

         // 後ろの横棒をいい感じに
         for (int line : is) {
            asgn(ret, line, j + w, "---+");
            int jj = j + w - 1;
            while (ret[line][jj] == '*') {
               asgn(ret, line, jj, "-");
               jj--;
            }
         }
         for (int line = is.front(); line < is.back(); line++) {
            if (ret[line][j + w + "---"s.size()] != '+') {
               asgn(ret, line, j + w + "---"s.size(), "|");
            }
         }

         w += "---+"s.size();

         skip("]");
         return {h, w};
      }
      else {
         skip("R");
         asgn(ret, i, j, "^v^v^v");
         return {1, "^v^v^v"s.size()};
      }
   }

   void skip(const std::string& s) {
      for (char c : s) {
         assert(source[cur] == c);
         cur++;
      }
   }

   int asgn(std::vector<std::string>& str, int line, int start, const std::string& t) {
      for (int i = 0; i < t.size(); i++) {
         if (line >= str.size()) {
            const int w = str.front().size();
            while (line >= str.size()) {
               str.push_back(std::string(w, '*'));
            }
         }
         for (int k = 0; k < str.size(); k++) {
            while (i + start >= str[k].size()) {
               str[k].push_back('*');
            }
         }
         str[line][i + start] = t[i];
      }
      return start + t.size();
   }

   std::string source;
private:
   std::map<std::pair<int, int>, Size> cache;
   std::vector<std::string> ret;

   bool is_bracket(char c) {
      return c == '(' || c == ')' || c == '[' || c == ']';
   }

   char flip(char c) {
      switch (c) {
      case '(':
         return ')';
      case ')':
         return '(';
      case '[':
         return ']';
      case ']':
         return '[';
      default:
         return '?';
      }
   }
};

int main(int argc, char* argv[]){
   registerGen(argc, argv, 1);

   int max_hw = 0;


   // 完全ランダム
   for (int t = 1; t <= 20; t++) {
      ofstream of(format("06_random_%02d.in", t).c_str());

      Generator gen;
      gen.gen_source(1000);
      auto s = gen.generate2D();
      chmax<int>(max_hw, s.size() * s[0].size());
      of << s.size() << ' ' << s[0].size() << std::endl;
      for (auto si : s) {
         of << si << std::endl;
      }

      of.close();
   }

   // 1. 直列だけ
   for (int t = 1; int num : {1, 2, 5, 20, 100, 5000}) {
      ofstream of(format("02_series_%02d.in", t).c_str());

      Generator gen;
      gen.source = "(" + std::string(num, 'R') + ")";
      auto s = gen.generate2D();
      chmax<int>(max_hw, s.size() * s[0].size());
      of << s.size() << ' ' << s[0].size() << std::endl;
      for (auto si : s) {
         of << si << std::endl;
      }

      of.close();
      t++;
   }

   // 2. 並列だけ
   for (int t = 1; int num : {2, 5, 20, 100, 5000}) {
      ofstream of(format("03_para_%02d.in", t).c_str());

      Generator gen;
      gen.source = "[" + std::string(num, 'R') + "]";
      auto s = gen.generate2D();
      chmax<int>(max_hw, s.size() * s[0].size());
      of << s.size() << ' ' << s[0].size() << std::endl;
      for (auto si : s) {
         of << si << std::endl;
      }

      of.close();
      t++;
   }

   // 1, 2, ..., k のやつ
   for (int t = 1; int num : {2, 10, 11, 12, 20, 30}) {
      ofstream of(format("04_sum_%02d.in", t).c_str());

      Generator gen;
      gen.source = "(R";
      for (int i = 2; i <= num; i++) {
         gen.source.push_back('[');
         for (int iter = 0; iter < i; iter++) {
            gen.source.push_back('R');
         }
         gen.source.push_back(']');
      }
      gen.source += ")";

      auto s = gen.generate2D();
      chmax<int>(max_hw, s.size() * s[0].size());
      of << s.size() << ' ' << s[0].size() << std::endl;
      for (auto si : s) {
         of << si << std::endl;
      }

      of.close();
      t++;
   }

   // 1, 2, ..., k のやつ（逆順）
   for (int t = 1; int num : {2, 10, 11, 12, 20, 30}) {
      ofstream of(format("05_revsum_%02d.in", t).c_str());

      Generator gen;
      gen.source = "(";
      for (int i = num; i >= 1; i--) {
         gen.source.push_back('[');
         for (int iter = 0; iter < i; iter++) {
            gen.source.push_back('R');
         }
         gen.source.push_back(']');
      }
      gen.source += ")";

      auto s = gen.generate2D();
      chmax<int>(max_hw, s.size() * s[0].size());
      of << s.size() << ' ' << s[0].size() << std::endl;
      for (auto si : s) {
         of << si << std::endl;
      }

      of.close();
      t++;
   }

   // 適当手打ち
   for (int t = 1; std::string hack : {
      "(R(RRRRR)(RR[RR](RRRR[RR]RR)([RRR(RRRR)R(RR)R][([RRRRR][RR][RR][RR])[RR]R](RRRRRRRRR))))",
      "([RRRRRRRRRRRRRR]RR[RRRRRRRRRRRRR]R(RRRRR)R(RRR)(RRR)[RRR]RR(RRRR)R)",
      "(([RRR]R[RR])[RRRRRRRRRRRRR]R([RRR][RRRR][RRRRRR]RRR)((RRRR)[RR](RR[RR]R)RR)[RRR])",
      "([(R(RR[RR(RR[RR([RRR(RRR)RRRR(RR)]RRR(RRRRRRRR[RRR]R)RRRR)RR]R)RR]R)R)RR]RRR)",
      "[R[R[R[R[R[RR]]]]]]"
   }) {
      ofstream of(format("07_handmaid_%02d.in", t).c_str());

      Generator gen;
      gen.source = hack;
      auto s = gen.generate2D();
      chmax<int>(max_hw, s.size() * s[0].size());
      of << s.size() << ' ' << s[0].size() << std::endl;
      for (auto si : s) {
         of << si << std::endl;
      }

      of.close();
      t++;
   }

   // 1, 2, ..., k のやつ
   for (int t = 1; int num : {2, 10, 11, 12, 20, 30}) {
      ofstream of(format("08_sumpara_%02d.in", t).c_str());

      Generator gen;
      gen.source = "[R";
      for (int i = 2; i <= num; i++) {
         gen.source.push_back('(');
         for (int iter = 0; iter < i; iter++) {
            gen.source.push_back('R');
         }
         gen.source.push_back(')');
      }
      gen.source += "]";

      auto s = gen.generate2D();
      chmax<int>(max_hw, s.size() * s[0].size());
      of << s.size() << ' ' << s[0].size() << std::endl;
      for (auto si : s) {
         of << si << std::endl;
      }

      of.close();
      t++;
   }

   // 1, 2, ..., k のやつ（逆順）
   for (int t = 1; int num : {2, 10, 11, 12, 20, 30}) {
      ofstream of(format("09_revsumpara_%02d.in", t).c_str());

      Generator gen;
      gen.source = "[";
      for (int i = num; i >= 1; i--) {
         gen.source.push_back('(');
         for (int iter = 0; iter < i; iter++) {
            gen.source.push_back('R');
         }
         gen.source.push_back(')');
      }
      gen.source += "]";

      auto s = gen.generate2D();
      chmax<int>(max_hw, s.size() * s[0].size());
      of << s.size() << ' ' << s[0].size() << std::endl;
      for (auto si : s) {
         of << si << std::endl;
      }

      of.close();
      t++;
   }

   // 入れ子
   for (int t = 1; int num : {10, 300, 299}) {
      ofstream of(format("10_ireko_%02d.in", t).c_str());

      Generator gen;
      gen.source = "";
      for (int i = 1; i <= num; i++) {
         gen.source.append("[R");
      }
      gen.source += std::string(num, ']');

      auto s = gen.generate2D();
      chmax<int>(max_hw, s.size() * s[0].size());
      of << s.size() << ' ' << s[0].size() << std::endl;
      for (auto si : s) {
         of << si << std::endl;
      }

      of.close();
      t++;
   }

   std::cout << max_hw << std::endl;

   return 0;
}