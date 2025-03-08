#include <bits/stdc++.h>
using namespace std;

using ll = long long;

template<typename T>
class RollbackUnionFind{
    public:
    using F = function<T(T, T)>;

    RollbackUnionFind(size_t n, F merge) : par_(n, -1), data_(n, T{}), f(merge), record_(0){}

    RollbackUnionFind(size_t n, vector<T> &data, F merge) : par_(n, -1), data_(data), f(merge), record_(0){}

    int Find(const int k) const {
        if(par_[k] < 0) return k;
        return Find(par_[k]);
    }

    bool Same(const int x, const int y) const {
        return Find(x) == Find(y);
    }

    bool Unite(int x, int y){
        x = Find(x), y = Find(y);
        history_.push({x, par_[x], data_[x]});
        history_.push({y, par_[y], data_[y]});
        if(x == y) return false;
        if(par_[x] > par_[y]) swap(x, y);
        data_[x] = f(data_[x], data_[y]);
        par_[x] += par_[y];
        par_[y] = x;
        return true;
    }
    
    int Size(const int k) const {
        return -par_[Find(k)];
    }

    T Get(const int k) const {
        return data_[Find(k)];
    }
    
    vector<vector<int>> Group() const {
        vector<vector<int>> ret(par_.size());
        for(int i = 0; i < par_.size(); ++i){
            ret[Find(i)].emplace_back(i);
        }
        ret.erase(remove_if(begin(ret), end(ret), [&](vector<int> &v){
            return v.empty();
        }), end(ret));
        return ret;
    }

    void Record(){
        record_ = history_.size();
    }

    void Undo(){
        auto [y, py, dy] = history_.top();
        history_.pop();
        par_[y] = py;
        data_[y] = dy;
        auto [x, px, dx] = history_.top();
        history_.pop();
        par_[x] = px;
        data_[x] = dx;
    }

    void Rollback(){
        int state = record_;
        while(state < (int)history_.size()) Undo();
    }
    
    private:
    vector<int> par_;
    stack<tuple<int, int, T>> history_;
    int record_;
    
    vector<T> data_;
    F f;
};

int main(){
    ll N, M; cin >> N >> M;
    ll Q; cin >> Q;
    vector<tuple<int, ll, ll>> query;
    vector<ll> V;
    auto conv = [&](ll x, ll y) -> ll {
        return y * N + x;
    };
    for(int i = 0; i < Q; ++i){
        int t; ll x, y{}; cin >> t;
        if(t != 3){
            cin >> x >> y, --x;
            V.emplace_back(conv(x, 0)); V.emplace_back(conv(x + 1, 0));
            V.emplace_back(conv(x, y)); V.emplace_back(conv(x + 1, y));
            V.emplace_back(conv(x, y + 1)); V.emplace_back(conv(x + 1, y + 1));
            V.emplace_back(conv(x, M + 1)); V.emplace_back(conv(x + 1, M + 1));
        }
        else{
            cin >> x, --x;
            V.emplace_back(conv(x, 0)); V.emplace_back(conv(x, M + 1));
        }
        // cerr << t << ' ' << x << ' ' << y << endl;
        query.emplace_back(t, x, y);
    }
    sort(V.begin(), V.end());
    V.erase(unique(V.begin(), V.end()), V.end());
    map<ll, vector<ll>> Lines;
    for(auto v : V){
        Lines[v % N].emplace_back(v);
    }
    map<pair<ll, ll>, vector<int>> EdgeTime;
    for(const auto &[_, vs] : Lines){
        for(int i = 1; i < vs.size(); ++i){
            EdgeTime[{vs[i - 1], vs[i]}].emplace_back(0);
        }
    }
    for(int i = 0; i < Q; ++i){
        const auto &[t, x, y] = query[i];
        if(t != 3){
            EdgeTime[{conv(x, y), conv(x, y + 1)}].emplace_back(i);
            EdgeTime[{conv(x + 1, y), conv(x + 1, y + 1)}].emplace_back(i);
            EdgeTime[{conv(x, y), conv(x + 1, y + 1)}].emplace_back(i);
            EdgeTime[{conv(x + 1, y), conv(x, y + 1)}].emplace_back(i);
        }
    }
    for(const auto &[_, vs] : Lines){
        for(int i = 1; i < vs.size(); ++i){
            EdgeTime[{vs[i - 1], vs[i]}].emplace_back(Q + 1);
        }
    }
    int q = 1;
    while(q < Q) q <<= 1;
    vector<vector<pair<ll, ll>>> tree(q * 2);
    auto add = [&](auto self, int tl, int tr, int el, int er, pair<ll, ll> e, int k) -> void {
        if(er <= tl || tr <= el) return;
        if(el <= tl && tr <= er){
            tree[k].emplace_back(e);
            return;
        }
        int tm = (tl + tr) >> 1;
        self(self, tl, tm, el, er, e, k * 2 + 0);
        self(self, tm, tr, el, er, e, k * 2 + 1);
    };
    for(auto &[e, t] : EdgeTime){
        if(t.size() % 2) t.emplace_back(Q + 1);
        // cerr << "{" << e.first << ", " << e.second << "} : ";
        // for(auto tt : t) cerr << tt << ' ';
        // cerr << endl;
        for(int i = 1; i < t.size(); i += 2){
            if(t[i - 1] != t[i]) add(add, 0, q, t[i - 1], t[i], e, 1);
        }
    }
    auto find = [&](ll val) -> int {
        return distance(V.begin(), lower_bound(V.begin(), V.end(), val));
    };
    // for(auto v : V) cerr << v << ' ';
    // cerr << endl;
    RollbackUnionFind<ll> uf(V.size(), V, [](ll l, ll r){return max(l, r);});
    vector<ll> ans(Q, -1);
    auto dfs = [&](auto self, int k) -> void {
        int cnt = tree[k].size();
        // cerr << "k = " << k << endl;
        for(const auto &[u, v] : tree[k]){
            // cerr << "add : " << u << ", " << v << endl;
            uf.Unite(find(u), find(v));
        }
        // cerr << endl;
        if(k >= q){
            int i = k - q;
            // cerr << k << ' ' << q << ' ' << i << endl;
            if(i < Q){
                const auto &[t, x, y] = query[i];
                if(t == 3){
                    // auto C = uf.Group();
                    // cerr << endl << "UF" << endl;
                    // for(auto &vs : C){
                    //     for(auto &v : vs) cerr << V[v] << ' ';
                    //     cerr << endl;
                    // }
                    // cerr << endl;
                    ans[i] = uf.Get(find(conv(x, 0)));
                    // cerr << i << ' ' << x << ' ' << ans[i] << endl;
                }
            }
        }
        else{
            self(self, k * 2 + 0);
            self(self, k * 2 + 1);
        }
        // cerr << "k = " << k << endl;
        for(const auto &[u, v] : tree[k]){
            // cerr << "del : " << u << ", " << v << endl;
            uf.Undo();
        }
        // cerr << endl;
    };
    dfs(dfs, 1);
    for(auto v : ans){
        if(v != -1) cout << v - N * (M + 1) + 1 << endl;
    }
}