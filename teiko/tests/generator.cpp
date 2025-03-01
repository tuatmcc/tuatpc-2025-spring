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
const int R_NUM_MAX = 10000;

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

   string generate_bracket_sequence(int N, int bracket_count = -1, int depth = 0) {
      if (N == 1) return "R";

      if (bracket_count == -1) {
         bracket_count = rnd.next(1, max(1, N / 3));  // Adjusted bracket count range
      }

      string result;
      vector<int> partitions;
      int remaining = N;

      while (remaining > 0) {
         if (remaining <= 2) {
            partitions.push_back(remaining);
            break;
         }
         int part = rnd.next(2, min(remaining, max(2, N / bracket_count)));
         if (part > remaining) part = remaining;
         partitions.push_back(part);
         remaining -= part;
      }

      result += open_bracket();
      for (int i = 0; i < (int)partitions.size(); i++) {
         char ob = open_bracket();
         result += ob;

         int nest_probability = max(10, 50 - depth * 5);  // Decreasing probability as depth increases
         if (partitions[i] > 2 && rnd.next(1, 100) <= nest_probability) {
            result += generate_bracket_sequence(partitions[i], -1, depth + 1);
         } else {
            result += string(partitions[i], 'R');
         }

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

      for (int i = 0; i < ret.size(); i++) {
         while (ret[i].back() == ' ') {
            ret[i].pop_back();
         }
      }
   }

   void clean_source() {
      while (source.size() > 3) {
         std::vector<int> v(source.size(), -1);
         std::stack<int> stk;
         for (int i = 0; i < source.size(); i++) {
            if (source[i] == '(' || source[i] == '[') {
               stk.emplace(i);
            }
            else if (source[i] == ')' || source[i] == ']') {
               assert(not stk.empty());
               int left = stk.top();
               stk.pop();
               assert(flip(source[left]) == source[i]);
               v[left] = i;
            }
         }

         bool ok = true;
         for (int i = 0; i < source.size() - 2; i++) {
            auto s = source.substr(i, 3);
            assert(s.size() == 3);
            if (s == "(R)" || s == "[R]") {
               source[i] = ' ';
               source[i + 2] = ' ';
               ok = false;
            }
            if (s == "(R)" || s == "[R]") {
               source[i] = ' ';
               source[i + 2] = ' ';
               ok = false;
            }
            if ((source[i] == '(' || source[i] == '[') && (source[i + 1] == '(') || source[i] == '[') {
               int r1 = v[i];
               int r2 = v[i + 1];
               if (std::abs(r2 - r1) == 1) {
                  source[i] = ' ';
                  source[i + 1] = ' ';
                  source[r1] = ' ';
                  source[r2] = ' ';
                  ok = false;
               }
            }
         }

         if (ok) {
            break;
         }

         source.erase(std::remove(source.begin(), source.end(), ' '), source.end());
      }
   }

   int cur = 0;

   std::vector<std::string> generate2D(bool should_kasamashi = false) {
      // int H = require_size(0, source.size() - 1).height * 2;
      // int W = require_size(0, source.size() - 1).width * 2;
      clean_source();
      int H = 1;
      int W = 1;
      ret.assign(H, std::string(W, '*'));

      kaiseki(0, 4);

      totonoe();

      if (should_kasamashi) {
         kasamashi();
      }

      return ret;
   }

   void kasamashi() {
      for (int i = 0; i < ret.size(); i++) {
         for (int j = 0; j + 18 < ret[i].size(); j++) {
            auto sub = ret[i].substr(j, "^v^v^v^v--------------"s.size());
            if (sub == "^v^v^v^v--------------") {
               ret[i][j + 11] = '^';
               ret[i][j + 12] = 'v';
               ret[i][j + 13] = '^';
               ret[i][j + 14] = 'v';
               ret[i][j + 15] = '^';
               ret[i][j + 16] = 'v';
               ret[i][j + 17] = '^';
               ret[i][j + 18] = 'v';
            }
         }
      }
   }

   // 回路 ::= 直列 | 並列 | 抵抗
   // 直列 ::= ( 回路 回路 … 回路 )
   // 並列 ::= [ 回路 回路 … 回路 ]
   void kaiseki(int i, int j) {
      cur = 0;
      j = asgn(ret, 0, 0, "o---");
      auto [di, dj] = kairo(i, j);
      asgn(ret, i, j + dj, "---o");
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

   {
      ofstream of(::format("00_sample_01.in").c_str());
      of << "1" << std::endl;
      of << "o---^v^v^v---^v^v^v---o" << std::endl;
      of.close();
   }
   {
      ofstream of(::format("00_sample_02.in").c_str());
      of << "3" << std::endl;
      of << "o---+---^v^v^v---+---o" << std::endl;
      of << "    |            |" << std::endl;
      of << "    +---^v^v^v---+" << std::endl;
      of.close();
   }
   {
      ofstream of(::format("00_sample_03.in").c_str());
      of << "9" << std::endl;
      of << "o---+---^v^v^v-----------+---^v^v^v---o" << std::endl;
      of << "    |                    |" << std::endl;
      of << "    +---+---^v^v^v---+---+" << std::endl;
      of << "    |   |            |   |" << std::endl;
      of << "    |   +---^v^v^v---+   |" << std::endl;
      of << "    |                    |" << std::endl;
      of << "    +---^v^v^v-----------+" << std::endl;
      of << "    |                    |" << std::endl;
      of << "    +---^v^v^v-----------+" << std::endl;
      of.close();
   }
   {
      ofstream of(::format("00_sample_04.in").c_str());
      of << "21" << std::endl;
      of << "o---+---^v^v^v---------------------------------------------------------------------------+---o" << std::endl;
      of << "    |                                                                                    |" << std::endl;
      of << "    +---+---^v^v^v-------------------------------------------------------------------+---+" << std::endl;
      of << "        |                                                                            |" << std::endl;
      of << "        +---+---^v^v^v-----------------------------------------------------------+---+" << std::endl;
      of << "            |                                                                    |" << std::endl;
      of << "            +---+---^v^v^v---------------------------------------------------+---+" << std::endl;
      of << "                |                                                            |" << std::endl;
      of << "                +---+---^v^v^v-------------------------------------------+---+" << std::endl;
      of << "                    |                                                    |" << std::endl;
      of << "                    +---+---^v^v^v-----------------------------------+---+" << std::endl;
      of << "                        |                                            |" << std::endl;
      of << "                        +---+---^v^v^v---------------------------+---+" << std::endl;
      of << "                            |                                    |" << std::endl;
      of << "                            +---+---^v^v^v-------------------+---+" << std::endl;
      of << "                                |                            |" << std::endl;
      of << "                                +---+---^v^v^v-----------+---+" << std::endl;
      of << "                                    |                    |" << std::endl;
      of << "                                    +---+---^v^v^v---+---+" << std::endl;
      of << "                                        |            |" << std::endl;
      of << "                                        +---^v^v^v---+" << std::endl;
      of.close();
   }


   // 完全ランダム
   for (int t = 1; t <= 20; t++) {
      ofstream of(::format("01_random_%02d.in", t).c_str());

      Generator gen;
      gen.gen_source(1000);
      auto s = gen.generate2D(true);
      chmax<int>(max_hw, s.size() * s[0].size());
      of << s.size() << std::endl;
      for (auto si : s) {
         of << si << std::endl;
      }

      of.close();
   }

   // 1. 直列だけ
   for (int t = 1; int num : {1, 2, 5000}) {
      ofstream of(::format("02_series_%02d.in", t).c_str());

      Generator gen;
      gen.source = "(" + std::string(num, 'R') + ")";
      auto s = gen.generate2D();
      chmax<int>(max_hw, s.size() * s[0].size());
      of << s.size() << std::endl;
      for (auto si : s) {
         of << si << std::endl;
      }

      of.close();
      t++;
   }

   // 2. 並列だけ
   for (int t = 1; int num : {2, 5, 5000}) {
      ofstream of(::format("03_para_%02d.in", t).c_str());

      Generator gen;
      gen.source = "[" + std::string(num, 'R') + "]";
      auto s = gen.generate2D();
      chmax<int>(max_hw, s.size() * s[0].size());
      of << s.size() << std::endl;
      for (auto si : s) {
         of << si << std::endl;
      }

      of.close();
      t++;
   }

   // 1, 2, ..., k のやつ
   for (int t = 1; int num : {2, 11, 20, 30}) {
      ofstream of(::format("04_sum_%02d.in", t).c_str());

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
      of << s.size() << std::endl;
      for (auto si : s) {
         of << si << std::endl;
      }

      of.close();
      t++;
   }

   // 1, 2, ..., k のやつ（逆順）
   for (int t = 1; int num : {2, 11, 30}) {
      ofstream of(::format("05_revsum_%02d.in", t).c_str());

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
      of << s.size() << std::endl;
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
      "[[(RR)R](RR)]",
      "[(RRR)[RR]]",
      "[R(R[R(RR)])]",
      "[R[R[R[R[R[RR]]]]]]"
   }) {
      ofstream of(::format("07_handmaid_%02d.in", t).c_str());

      Generator gen;
      gen.source = hack;
      auto s = gen.generate2D();
      chmax<int>(max_hw, s.size() * s[0].size());
      of << s.size() << std::endl;
      for (auto si : s) {
         of << si << std::endl;
      }

      of.close();
      t++;
   }

   // 1, 2, ..., k のやつ
   for (int t = 1; int num : {2, 11, 30}) {
      ofstream of(::format("08_sumpara_%02d.in", t).c_str());

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
      of << s.size() << std::endl;
      for (auto si : s) {
         of << si << std::endl;
      }

      of.close();
      t++;
   }

   // 1, 2, ..., k のやつ（逆順）
   for (int t = 1; int num : {2, 11, 30}) {
      ofstream of(::format("09_revsumpara_%02d.in", t).c_str());

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
      of << s.size() << std::endl;
      for (auto si : s) {
         of << si << std::endl;
      }

      of.close();
      t++;
   }

   // 入れ子
   for (int t = 1; int num : {10, 300, 299}) {
      ofstream of(::format("10_ireko_%02d.in", t).c_str());

      Generator gen;
      gen.source = "";
      for (int i = 1; i <= num; i++) {
         gen.source.append("[R");
      }
      gen.source.append("R");
      gen.source += std::string(num, ']');

      auto s = gen.generate2D(true);
      chmax<int>(max_hw, s.size() * s[0].size());
      of << s.size() << std::endl;
      for (auto si : s) {
         of << si << std::endl;
      }

      of.close();
      t++;
   }

   // toufu hack
   {
      ofstream of(::format("11_toufu_01.in").c_str());

      Generator gen;
      std::string unit = "[RR]";

      gen.source = "(";
      for (int i = 0; i < R_NUM_MAX; i++) {
         gen.source.append(unit);
      }
      gen.source += ")";


      auto s = gen.generate2D(true);
      chmax<int>(max_hw, s.size() * s[0].size());
      of << s.size() << std::endl;
      for (auto si : s) {
         of << si << std::endl;
      }

      of.close();
   }
   // toufu hack
   {
      // [R, (R, [R, (R, [R, R)])])]
      for (int par = 0; par <= 1; par++) {
         ofstream of(::format("11_toufu_%02d.in", 2 + par).c_str());

         Generator gen;
         gen.source = "";
         std::stack<char> stk;
         char br = '[';
         for (int i = 0; i < 400 - par; i++) {
            gen.source.push_back(br);
            gen.source.push_back('R');
            stk.push(br);
            br = (br == '[') ? '(' : '[';
         }
         gen.source.push_back('R');
         while (not stk.empty()) {
            gen.source.push_back(stk.top() == '[' ? ']' : ')');
            stk.pop();
         }


         auto s = gen.generate2D(true);
         chmax<int>(max_hw, s.size() * s[0].size());
         of << s.size() << std::endl;
         for (auto si : s) {
            of << si << std::endl;
         }

         of.close();

      }
   }
   // toufu hack
   {
      ofstream of(::format("11_toufu_04.in").c_str());

      Generator gen;
      gen.source = "[";
      const int mx = std::sqrt((long)1.5e6);
      auto unit = "(" + std::string(mx / "^v^v^v^v---"s.size() - 20, 'R') + ")";
      char br = '[';
      for (int i = 0; i < mx / 2 - 2; i++) {
         gen.source.append(unit);
      }
      gen.source.push_back(']');

      auto s = gen.generate2D(true);
      chmax<int>(max_hw, s.size() * s[0].size());
      of << s.size() << std::endl;
      for (auto si : s) {
         of << si << std::endl;
      }

      of.close();
   }

   std::cout << max_hw << std::endl;

   return 0;
}
