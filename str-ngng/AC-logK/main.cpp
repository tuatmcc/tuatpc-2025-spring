#include <bits/stdc++.h>
using namespace std;

class MoAlgorithm{
    public:
    using F = function<void(int)>;

    MoAlgorithm(int N, F add_l, F add_r, F del_l, F del_r, F solve) :
        add_left_(add_l),
        add_right_(add_r),
        del_left_(del_l),
        del_right_(del_r),
        solve_(solve){
        n = 1;
        while(n < N) n <<= 1;
    }
    
    MoAlgorithm(int N, F add, F del, F solve) :
        add_left_(add),
        add_right_(add),
        del_left_(del),
        del_right_(del),
        solve_(solve){
        n = 1;
        while(n < N) n <<= 1;
    }

    void Insert(int left, int right){
        query_.emplace_back(left, right);
    }

    void Execute(){
        int Q = int(query_.size());
        vector<int> index(Q);
        iota(index.begin(), index.end(), 0);
        vector<int64_t> ord(Q);
        for(int i = 0; i < Q; ++i) ord[i] = HilbertOrder(query_[i]);
        sort(index.begin(), index.end(), [&](int i, int j){
            return ord[i] < ord[j];
        });
        int cl = 0, cr = 0;
        for(int i : index){
            const auto& [l, r] = query_[i];
            while(cl > l) add_left_(--cl);
            while(cr < r) add_right_(cr++);
            while(cl < l) del_left_(cl++);
            while(cr > r) del_right_(--cr);
            solve_(i);
        }
    }

    private:
    int n;
    vector<pair<int, int>> query_;
    F add_left_, add_right_, del_left_, del_right_, solve_;

    int64_t HilbertOrder(const pair<int, int> &q){
        auto [x, y] = q;
        int64_t ret = 0;
        for(int64_t s = n >> 1, rx, ry; s; s >>= 1){
            rx = (x & s) > 0, ry = (y & s) > 0;
            ret += s * s * ((rx * 3) ^ ry);
            if(ry) continue;
            if(rx) x = n - 1 - x, y = n - 1 - y;
            swap(x, y);
        }
        return ret;
    }
};

int main(){
    int N, Q; cin >> N >> Q;
    string S; cin >> S;

    const int C = 26;
    using ll = long long;
    using Vec = array<ll, C>;
    using Mat = array<array<ll, C>, C>;
    Vec c1;
    Mat c2, c3;
    fill(c1.begin(), c1.end(), 0);
    for(int i = 0; i < C; ++i){
        fill(c2[i].begin(), c2[i].end(), 0);
        fill(c3[i].begin(), c3[i].end(), 0);
    }
    ll cur = 0;
    vector<ll> ans(Q);
    MoAlgorithm mo(
        N,
        [&](int i){
            int s = S[i] - 'a';
            for(int c = 0; c < C; ++c){
                if(c == s) continue;
                cur += c3[c][s];
            }
            for(int c = 0; c < C; ++c){
                if(c == s) continue;
                c3[s][c] += c2[c][s];
            }
            for(int c = 0; c < C; ++c){
                if(c == s) continue;
                c2[s][c] += c1[c];
            }
            ++c1[s];
        },
        [&](int i){
            int s = S[i] - 'a';
            for(int c = 0; c < C; ++c){
                if(c == s) continue;
                cur += c3[c][s];
            }
            for(int c = 0; c < C; ++c){
                if(c == s) continue;
                c3[s][c] += c2[s][c];
            }
            for(int c = 0; c < C; ++c){
                if(c == s) continue;
                c2[c][s] += c1[c];
            }
            ++c1[s];
        },
        [&](int i){
            int s = S[i] - 'a';
            for(int c = 0; c < C; ++c){
                if(c == s) continue;
                cur -= c3[c][s];
            }
            for(int c = 0; c < C; ++c){
                if(c == s) continue;
                c3[s][c] -= c2[c][s];
            }
            for(int c = 0; c < C; ++c){
                if(c == s) continue;
                c2[s][c] -= c1[c];
            }
            --c1[s];
        },
        [&](int i){
            int s = S[i] - 'a';
            for(int c = 0; c < C; ++c){
                if(c == s) continue;
                cur -= c3[c][s];
            }
            for(int c = 0; c < C; ++c){
                if(c == s) continue;
                c3[s][c] -= c2[s][c];
            }
            for(int c = 0; c < C; ++c){
                if(c == s) continue;
                c2[c][s] -= c1[c];
            }
            --c1[s];
        },
        [&](int i){
            ans[i] = cur;
        }
    );
    for(int i = 0; i < Q; ++i){
        int l, r; cin >> l >> r;
        mo.Insert(l - 1, r);
    }
    mo.Execute();

    for(const auto &val : ans){
        cout << val << '\n';
    }
}