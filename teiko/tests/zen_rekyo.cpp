# include <iostream>
# include <string>
# include <set>
# include <algorithm>
# include <stack>
# include <vector>
# include <cassert>

using namespace std;


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

int main() {
   int n;
   std::cin >> n;

   // 最初の括弧の種類
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

   for (string s : st) {
      std::cout << s << std::endl;
   }
   std::cout << st.size() << std::endl;
}