# include "testlib.h"
# include <bits/stdc++.h>
# include <cassert>
using namespace std;

const int R_NUM_MIN = 1;
const int R_NUM_MIN = 100;

//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  1. 直列だけ
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
vector<string> series(int num) {
   std::vector<string> ret;
   std::string s;
   s.append("o---");
   for (int i = 0; i < num; i++) {
      s.append("^v^v^v---");
   }
   s.append("o");
   ret.push_back(s);
   return ret;
}


//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
//  2. 並列だけ
//━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
vector<string> series(int num) {
   std::vector<string> ret;
   std::string s;
   s.append("o---");
   for (int i = 0; i < num; i++) {
      s.append("^v^v^v---");
   }
   s.append("o");
   ret.push_back(s);
   return ret;
}

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
   std::vector<std::string> generate2D() {
      int H = require_size(0, source.size() - 1).height * 2;
      int W = require_size(0, source.size() - 1).width * 2;
      ret.assign(H, std::string(W, '*'));

      ret[0][0] = 'o';
      ret[0][1] = '-';
      ret[0][2] = '-';
      ret[0][3] = '-';

      rec(0, 0, 4);
   }

   void rec(int left, int i, int j) {
      if (source[left] == '(') {
         
      }
      else if (source[left] == '[') {
         j = asgn(ret[i], j, "+---");
         rec(left + 1, i, j);
      }
      else {
         assert(source[left] == 'R');
         asgn(ret[i], j, "^v^v^v");
      }
   }

   int asgn(std::string& str, int start, const std::string& t) {
      for (int i = 0; i < t.size(); i++) {
         str[i + start] = t[i];
      }
      return start + t.size();
   }

   Size require_size(int l, int r) {
      assert(source[l] == '(' || source[l] == '[');
      assert(source[r] == ')' || source[r] == ']');
      if (cache.count({l, r})) {
         return cache[{l, r}];
      }

      Size sz(0, 0);
      if (source[l] == '(') {
         for (int i = l + 1; i < r; i++) {
            if (source[i] == 'R') {
               sz.height = std::max(sz.height, 1);
               sz.width += "---^v^v^v---"s.size();
            }
            else if (is_bracket(source[i])) {
               int left = i;
               int right = i;
               while (source[right] != flip(source[l])) {
                  right++;
               }
               auto [h, w] = require_size(l, r);

               sz.height = std::max(sz.height, h);
               sz.width += w + "---"s.size();
            }
         }
      }
      else {
         for (int i = l + 1; i < r; i++) {
            if (source[i] == 'R') {
               sz.height += 1 + 1;
               sz.width = std::max<int>(sz.width, "---^v^v^v---"s.sz());
            }
            else if (is_bracket(source[i])) {
               int left = i;
               int right = i;
               while (source[right] != flip(source[l])) {
                  right++;
               }
               auto [h, w] = require_size(l, r);

               sz.height = h + 1;
               sz.width = std::max(sz.width, w);
            }
         }
      }

      return sz;
   }

private:
   std::string source;
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

   // 1. 直列だけ
   for (int t = 1; t <= 20; t++) {
      ofstream of(format("02_series_%02d.in", t + 1).c_str());

      auto s = series(std::sqrt(5 * t) * (double)10);
      for (auto si : s) {
         of << si << std::endl;
      }

      of.close();
   }

   // 2. 並列だけ

   return 0;
}