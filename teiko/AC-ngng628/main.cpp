# include <iostream>
# include <string>
# include <vector>
# include <algorithm>
# include <tuple>
# include <atcoder/modint>
using namespace std::literals::string_literals;
using Fp = atcoder::modint998244353;

int main() {
    //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
    //  1. 入力
    //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
    int h, w{};
    std::cin >> h;
    std::cin.ignore();
    std::vector<std::string> s(h + 2);
    for (int i = 1; i <= h; i++) {
        std::getline(std::cin, s[i]);
        w = std::max<int>(w, s[i].size());
    }

    for (auto& si : s) {
        while (si.size() < w) {
            si.push_back(' ');
        }
    }

    //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
    //  2. 構文解析
    //━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
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
                next_j = skip_wire(i, next_j + 1);
                return { R, next_j };
            }
            else {
                Fp R = Fp(1);
                int next_j = skip_wire(i, j + "^v^v^v"s.size());
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

    std::cout << parser.parse().val() << std::endl;
}