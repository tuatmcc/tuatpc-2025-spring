# include "testlib.h"
# include <bits/stdc++.h>
# include <cassert>
using namespace std;

const int Q_MIN = 1;
const int Q_MAX = (long long)(1e5);
const int MAX_HW = 1500000;
const int MAX_REG = 30;

bool is_ok_brackets(const std::string& s) {
   std::stack<char> stk;
   for (auto si : s) {
      if (si == '(' || si == '[') {
         stk.push(si);
      }
      else if (si == ')' || si == ']') {
         if (stk.empty()) return false;
         char top = stk.top();
         stk.pop();
         if (top == '(' && si == ']') return false;
         if (top == '[' && si == ')') return false;
      }
   }
   return stk.empty();
}


void clean_source(std::string& source) {
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

      for (int i = 0; i < source.size() - 1; i++) {
         auto s = source.substr(i, 2);
         if (s == "()" || s == "[]") {
            source[i] = ' ';
            source[i + 1] = ' ';
            ok = false;
         }
      }

      if (ok) {
         break;
      }

      source.erase(std::remove(source.begin(), source.end(), ' '), source.end());
   }
}




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
const int R_NUM_MAX = 30;

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


   cout << "DEBUG 00_sample_01" << std::endl;
   {
      ofstream of(::format("00_sample_01.in").c_str());
      of << "1" << std::endl;
      of << "o---^v^v^v---^v^v^v---o" << std::endl;
      of.close();

      of << 3 << std::endl;

      of << "3" << std::endl;
      of << "o---+---^v^v^v---+---o" << std::endl;
      of << "    |            |" << std::endl;
      of << "    +---^v^v^v---+" << std::endl;
      of.close();

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
   cout << "DEBUG 01_random_" << std::endl;
   for (int t = 1; t <= 5; t++) {
      ofstream of(::format("01_random_%02d.in", t).c_str());

      std::vector<std::vector<std::string>> cases;
      int hw = MAX_HW;
      while (true) {
         Generator gen;
         gen.gen_source(30);
         auto s = gen.generate2D(true);
         int hw_cnt = 0;
         for (auto line : s) hw_cnt += line.size();

         if (hw - hw_cnt >= 0 && cases.size() + 1 <= Q_MAX) {
            cases.push_back(s);
         }
         else {
            break;
         }
         hw -= hw_cnt;
      }

      int q = cases.size();
      std::cout << q << std::endl;
      for (auto s : cases) {
         of << s.size() << std::endl;
         for (auto si : s) {
            of << si << std::endl;
         }
      }

      of.close();
   }

   cout << "DEBUG 02_series_01" << std::endl;
   // 1. 直列だけ
   {
      ofstream of(::format("02_series_01.in").c_str());

      std::vector<std::vector<std::string>> cases;
      int hw = MAX_HW;
      for (int num = 1; num <= MAX_REG; num++) {
         Generator gen;
         gen.source = "(" + std::string(num, 'R') + ")";
         auto s = gen.generate2D();

         cases.push_back(s);
      }

      int q = cases.size();
      std::cout << q << std::endl;
      for (auto s : cases) {
         of << s.size() << std::endl;
         for (auto si : s) {
            of << si << std::endl;
         }
      }

      of.close();
   }

   cout << "DEBUG 03_para" << std::endl;
   // 2. 並列だけ
   {
      ofstream of(::format("03_para_01.in").c_str());

      std::vector<std::vector<std::string>> cases;
      int hw = MAX_HW;
      for (int num = 1; num <= MAX_REG; num++) {
         Generator gen;
         gen.source = "[" + std::string(num, 'R') + "]";
         auto s = gen.generate2D();

         cases.push_back(s);
      }

      int q = cases.size();
      std::cout << q << std::endl;
      for (auto s : cases) {
         of << s.size() << std::endl;
         for (auto si : s) {
            of << si << std::endl;
         }
      }

      of.close();
   }

   cout << "DEBUG 04 sum" << std::endl;
   {
      ofstream of(::format("04_sum_01.in").c_str());

      std::vector<std::vector<std::string>> cases;
      int hw = MAX_HW;
      for (int num = 1; ; num++) {
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

         int hw_cnt = 0;
         for (auto line : s) hw_cnt += line.size();

         if (hw - hw_cnt >= 0 && cases.size() + 1 <= Q_MAX) {
            cases.push_back(s);
         }
         else {
            break;
         }
         hw -= hw_cnt;
      }

      int q = cases.size();
      std::cout << q << std::endl;
      for (auto s : cases) {
         of << s.size() << std::endl;
         for (auto si : s) {
            of << si << std::endl;
         }
      }

      of.close();
   }

   cout << "DEBUG 05 revsum" << std::endl;
   {
      ofstream of(::format("05_revsum_01.in").c_str());

      std::vector<std::vector<std::string>> cases;
      int hw = MAX_HW;
      for (int num = 1; ; num++) {
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
   
         int hw_cnt = 0;
         for (auto line : s) hw_cnt += line.size();

         if (hw - hw_cnt >= 0 && cases.size() + 1 <= Q_MAX) {
            cases.push_back(s);
         }
         else {
            break;
         }
         hw -= hw_cnt;
      }

      int q = cases.size();
      std::cout << q << std::endl;
      for (auto s : cases) {
         of << s.size() << std::endl;
         for (auto si : s) {
            of << si << std::endl;
         }
      }

      of.close();
   }


   // 適当手打ち
   cout << "DEBUG 07 07_handmade_01" << std::endl;
   {
      ofstream of(::format("07_handmade_01.in").c_str());
      std::vector<std::string> hacks = {
         "(R(RRRRR)(RR[RR](RRRR[RR]RR)([RRR(RRRR)R(RR)R][([RRRRR][RR][RR][RR])[RR]R](RRRRRRRRR))))",
         "([RRRRRRRRRRRRRR]RR[RRRRRRRRRRRRR]R(RRRRR)R(RRR)(RRR)[RRR]RR(RRRR)R)",
         "(([RRR]R[RR])[RRRRRRRRRRRRR]R([RRR][RRRR][RRRRRR]RRR)((RRRR)[RR](RR[RR]R)RR)[RRR])",
         "([(R(RR[RR(RR[RR([RRR(RRR)RRRR(RR)]RRR(RRRRRRRR[RRR]R)RRRR)RR]R)RR]R)R)RR]RRR)",
         "[[(RR)R](RR)]",
         "[(RRR)[RR]]",
         "[R(R[R(RR)])]",
         "[R[R[R[R[R[RR]]]]]]"
      };
      std::cout << hacks.size() << std::endl;
      for (int t = 1; std::string hack : hacks) {
         Generator gen;
         gen.source = hack;
         auto s = gen.generate2D();
         chmax<int>(max_hw, s.size() * s[0].size());
         of << s.size() << std::endl;
         for (auto si : s) {
            of << si << std::endl;
         }
      }

      of.close();
   }


   // 1, 2, ..., k のやつ
   cout << "DEBUG 08" << std::endl;
   {
      ofstream of(::format("08_sumpara_01.in").c_str());

      std::vector<std::vector<std::string>> cases;
      int hw = MAX_HW;
      for (int num = 1; ; num++) {
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
   
         int hw_cnt = 0;
         for (auto line : s) hw_cnt += line.size();

         if (hw - hw_cnt >= 0 && cases.size() + 1 <= Q_MAX) {
            cases.push_back(s);
         }
         else {
            break;
         }
         hw -= hw_cnt;
      }

      int q = cases.size();
      std::cout << q << std::endl;
      for (auto s : cases) {
         of << s.size() << std::endl;
         for (auto si : s) {
            of << si << std::endl;
         }
      }

      of.close();
   }

   cout << "DEBUG 09" << std::endl;
   // 逆順
   {
      ofstream of(::format("09_revsumpara_01.in").c_str());

      std::vector<std::vector<std::string>> cases;
      int hw = MAX_HW;
      for (int num = 1; ; num++) {
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
      
         int hw_cnt = 0;
         for (auto line : s) hw_cnt += line.size();

         if (hw - hw_cnt >= 0 && cases.size() + 1 <= Q_MAX) {
            cases.push_back(s);
         }
         else {
            break;
         }
         hw -= hw_cnt;
      }

      int q = cases.size();
      std::cout << q << std::endl;
      for (auto s : cases) {
         of << s.size() << std::endl;
         for (auto si : s) {
            of << si << std::endl;
         }
      }

      of.close();
   }

   cout << "DEBUG 10" << std::endl;
   // いれこ
   {
      ofstream of(::format("10_ireko_01.in").c_str());

      std::vector<std::vector<std::string>> cases;
      int hw = MAX_HW;
      for (int num = 1; ; num++) {
         Generator gen;
         gen.source = "";
         for (int i = 1; i <= num; i++) {
            gen.source.append("[R");
         }
         gen.source.append("R");
         gen.source += std::string(num, ']');
   
         auto s = gen.generate2D(true);
         
         int hw_cnt = 0;
         for (auto line : s) hw_cnt += line.size();

         if (hw - hw_cnt >= 0 && cases.size() + 1 <= Q_MAX) {
            cases.push_back(s);
         }
         else {
            break;
         }
         hw -= hw_cnt;
      }

      int q = cases.size();
      std::cout << q << std::endl;
      for (auto s : cases) {
         of << s.size() << std::endl;
         for (auto si : s) {
            of << si << std::endl;
         }
      }

      of.close();
   }

   cout << "DEBUG 11" << std::endl;
   {
      ofstream of(::format("11_toufu_01.in").c_str());

      std::vector<std::vector<std::string>> cases;
      int hw = MAX_HW;
      for (int num = 1; ; num++) {
         Generator gen;
         std::string unit = "[RR]";
   
         gen.source = "(";
         for (int i = 0; i < R_NUM_MAX; i++) {
            gen.source.append(unit);
         }
         gen.source += ")";
   
         auto s = gen.generate2D(true);
            
         int hw_cnt = 0;
         for (auto line : s) hw_cnt += line.size();

         if (hw - hw_cnt >= 0 && cases.size() + 1 <= Q_MAX) {
            cases.push_back(s);
         }
         else {
            break;
         }
         hw -= hw_cnt;
      }

      int q = cases.size();
      std::cout << q << std::endl;
      for (auto s : cases) {
         of << s.size() << std::endl;
         for (auto si : s) {
            of << si << std::endl;
         }
      }

      of.close();
   }

   cout << "DEBUG 11_toufu_02" << std::endl;
   {
      ofstream of(::format("11_toufu_02.in").c_str());

      std::vector<std::vector<std::string>> cases;
      int hw = MAX_HW;
      for (int num = 1; ; num++) {
         if (R_NUM_MAX - num <= 0) break;
         Generator gen;
         gen.source = "";
         std::stack<char> stk;
         char br = '[';
         for (int i = 0; i < R_NUM_MAX - num; i++) {
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
            
         int hw_cnt = 0;
         for (auto line : s) hw_cnt += line.size();

         if (hw - hw_cnt >= 0 && cases.size() + 1 <= Q_MAX) {
            cases.push_back(s);
         }
         else {
            break;
         }
         hw -= hw_cnt;
      }

      int q = cases.size();
      std::cout << q << std::endl;
      for (auto s : cases) {
         of << s.size() << std::endl;
         for (auto si : s) {
            of << si << std::endl;
         }
      }

      of.close();
   }


   // toufu hack
   std::cout << "DBUG 11_toufu_03" << std::endl;
   {
      ofstream of(::format("11_toufu_03.in").c_str());

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
      int q = 1;
      of << 1 << std::endl;
      chmax<int>(max_hw, s.size() * s[0].size());
      of << s.size() << std::endl;
      for (auto si : s) {
         of << si << std::endl;
      }

      of.close();
   }

   // 全列挙
   std::cout << "DBUG all" << std::endl;
      for (int n = 3; n <= 7; n++) {
         ofstream of(::format("12_all_0%d.in", n).c_str());

         set<string> st;
         st.insert("(" + std::string(n, 'R') + ")");
         st.insert("[" + std::string(n, 'R') + "]");
         for (char br : {'(', '['}) {
            // 以降の括弧の数
            for (int i = 1; i <= n - 2; i++) {
               // '(' の数
               for (int op = 0; op <= i; op++) {
                  // '[' の数
                  int cl = i - op;
                  if (cl < 0) continue;
                  if (cl == 0 && br == '(') continue;
      
                  auto rec = [&st, br, i](auto&& self, int op, int cl, int r, std::string s) -> void {
                     if (op == 0 && cl == 0 && r == 0) {
                        auto t = s;
                        if (i == 1 && ((s.back() == '(' || s.back() == '[') && (s.back() == ')' || s.back() == ']'))) return;
                        if (is_ok_brackets(t)) {
                           t = std::string(1, br) + t + std::string(1, br == '(' ? ')' : ']');
                           clean_source(t);
                           if (t.front() != '(' && t.front() != '[') {
                              t = std::string(1, br) + t + std::string(1, br == '(' ? ')' : ']');
                           }
                           if (std::count(t.begin(), t.end(), '[') >= 1) {
                              st.insert(t);
                           }
                        }
                        return;
                     }
                     if (r == 0) {
                        return;
                     }
                     if (op > 0) {
                        for (int j = 1; j <= r; j++) {
                           auto rs = std::string(j, 'R');
                           auto t = s;
                           t.append("(" + rs + ")");
                           self(self, op - 1, cl, r - j, t);
                        }
                     }
                     if (cl > 0) {
                        for (int j = 1; j <= r; j++) {
                           auto rs = std::string(j, 'R');
                           auto t = s;
                           t.append("[" + rs + "]");
                           self(self, op, cl - 1, r - j, t);
                        }
                     }
                     if (s.back() != 'R') {
                        for (int j = 1; j <= r; j++) {
                           auto rs = std::string(j, 'R');
                           auto t = s;
                           t.append(rs);
                           self(self, op, cl, r - j, t);
                        }
                     }
                  };
      
                  rec(rec, op, cl, n, "");
               }
            }
         }
      
         of << st.size() << std::endl;
         for (string sub : st) {
            Generator gen;
            gen.source = sub;
            auto s = gen.generate2D(false);
            of << s.size() << std::endl;
            for (auto si : s) {
               of << si << std::endl;
            }
         }
         of.close();
      }



   return 0;
}
