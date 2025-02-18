#include <bits/stdc++.h>

using namespace std;

using ll = long long;

template <class T> bool chmin(T &a, const T &b) { return a > b ? a = b, true : false; }
template <class T> bool chmax(T &a, const T &b) { return a < b ? a = b, true : false; }

struct IoSetup {
    IoSetup() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
        cout << fixed << setprecision(10);
        cerr << fixed << setprecision(10);
    }
} iosetup;

struct Query{
    ll t, x, y, s;
    Query(ll t, ll s) : t(t), x(-1), y(-1), s(s) {}
    Query(ll t, ll x, ll y) : t(t), x(x), y(y), s(-1) {}
};

int main(){
    ll N, M, Q;
    cin >> N >> M >> Q;
    vector<Query> queries;
    for(int i = 0; i < Q; i++){
        ll t;
        cin >> t;
        if(t == 1 || t == 2){
            ll x, y;
            cin >> x >> y;
            queries.emplace_back(t, x, y);
        }else{
            ll s;
            cin >> s;
            queries.emplace_back(t, s);
        }
    }
    vector<ll> ys;
    for(auto q : queries){
        if(q.t != 3){
            ys.push_back(q.y);
        }
    }
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    unordered_map<ll, ll> zipy;
    for (int i = 0; i < ys.size(); i++) {
        zipy[ys[i]] = i + 1;
    }
    for(auto &q : queries){
        if(q.t != 3){
            q.y = zipy[q.y];
        }
    }
    M = ys.size();
    ll block_size = sqrt(M) + 1;
    ll block_cnt = (M + block_size - 1) / block_size + 1;
    vector<map<ll, ll>> to(block_cnt);
    vector<map<ll, set<ll>>> lines(block_cnt);
    // auto traverse = [&](ll x, ll y){
    //     ll b = y / block_size;
    //     ll nx = x, ny = y % block_size;
    //     while(ny < block_size){
    //         ll lidx, ridx;
    //         {
    //             ll ng = -1, ok = lines[b][nx - 1].size();
    //             while(abs(ok - ng) > 1){
    //                 ll mid = abs(ok + ng) / 2;
    //                 if(lines[b][nx - 1][mid] >= ny) ok = mid;
    //                 else ng = mid;
    //             }
    //             lidx = ok;
    //         }
    //         {
    //             ll ok = -1, ng = lines[b][nx].size();
    //             while(abs(ok - ng) > 1){
    //                 ll mid = abs(ok + ng) / 2;
    //                 if(lines[b][nx][mid] >= ny) ok = mid;
    //                 else ng = mid;
    //             }
    //             ridx = ok;
    //         }
    //         ll l = block_size, r = block_size;
    //         if(lidx != lines[b][nx - 1].size()) l = lines[b][nx - 1][lidx];
    //         if(ridx != lines[b][nx].size()) r = lines[b][nx][ridx];
    //         if(l <= r){
    //             if(l == block_size) break;
    //             ny = l;
    //             nx--;
    //         }else{
    //             ny = r;
    //             nx++;
    //         }
    //         ny++;
    //     }
    //     return nx;
    // };
    auto traverse_rev = [&](ll x, ll y){
        ll b = y / block_size;
        ll nx = x, ny = y % block_size;
        while(ny >= 0){
            ll l = -1, r = -1;
            // assert(b < block_cnt);
            if(lines[b].contains(nx - 1)){
                auto itrl = lines[b][nx - 1].upper_bound(ny);
                if(itrl != lines[b][nx - 1].begin()) l = *prev(itrl);
            }
            if(lines[b].contains(nx)){
                auto itr = lines[b][nx].upper_bound(ny);
                if(itr != lines[b][nx].begin()) r = *prev(itr);
            }
            if(l >= r){
                if(l == -1) break;
                ny = l;
                nx--;
            }else{
                ny = r;
                nx++;
            }
            ny--;
        }
        return nx;
    };
    auto query1 = [&](ll x, ll y){
        ll block_id = y / block_size;
        ll parl = traverse_rev(x, y);
        ll parr = traverse_rev(x + 1, y);
        // cout << parl << ' ' << parr << '\n';
        if(!to[block_id].contains(parl)) to[block_id][parl] = parl;
        if(!to[block_id].contains(parr)) to[block_id][parr] = parr;
        swap(to[block_id][parl], to[block_id][parr]);
        lines[block_id][x].emplace(y % block_size);
        // assert(traverse_rev(x, y) == parr);
        // assert(traverse_rev(x + 1, y) == parl);
    };
    auto query2 = [&](ll x, ll y){
        ll block_id = y / block_size;
        ll parl = traverse_rev(x, y);
        ll parr = traverse_rev(x + 1, y);
        // cout << parl << ' ' << parr << '\n';
        if(!to[block_id].contains(parl)) to[block_id][parl] = parl;
        if(!to[block_id].contains(parr)) to[block_id][parr] = parr;
        swap(to[block_id][parl], to[block_id][parr]);
        lines[block_id][x].erase(y % block_size);
        // assert(traverse_rev(x, y) == parr);
        // assert(traverse_rev(x + 1, y) == parl);
    };
    auto query3 = [&](ll s){
        ll cur = s;
        for(int i = 0; i < block_cnt; i++){
            if(to[i].contains(cur)){
                cur = to[i][cur];
            }
        }
        return cur;
    };
    for(auto q : queries){
        // cout << "query: " << q.t << ' ' << q.x << ' ' << q.y << ' ' << q.s << '\n';
        if(q.t == 1){
            query1(q.x, q.y);
        }else if(q.t == 2){
            query2(q.x, q.y);
        }else{
            cout << query3(q.s) << '\n';
        }
        // for(int i = 1; i <= N; i++){
        //     cout << i << ' ';
        // }
        // cout << '\n';
        // for(int i = 1; i <= N; i++){
        //     cout << query3(i) << ' ';
        // }
        // cout << '\n';
    }
}