#include <bits/stdc++.h>

using namespace std;

using ll = long long;

struct IoSetup {
    IoSetup() {
        cin.tie(nullptr);
        ios::sync_with_stdio(false);
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
    // y 座標について座圧する
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
    vector<map<ll, ll>> to(block_cnt); // to[i][j] := i 番目のブロック内で j 番目の縦線の先頭がどこに行くか
    vector<map<ll, set<ll>>> lines(block_cnt); // lines[i][j] := i 番目のブロック内で j 番目の縦線から出ている横線の y 座標の集合
    // x 番目の縦線の座標 y の位置からブロックの先頭まで逆順に辿ったときの縦線の番号を返す
    auto traverse_rev = [&](ll x, ll y){
        ll b = y / block_size; // block id
        ll nx = x, ny = y % block_size;
        while(ny >= 0){
            // 次に移動する縦線が nx - 1 か nx + 1 かを判定する
            // 現在の高さ ny より上にある左側の横線と右側の横線のうち、最も近いものを探す
            ll l = -1, r = -1; //
            if(lines[b].contains(nx - 1)){
                auto itrl = lines[b][nx - 1].upper_bound(ny);
                if(itrl != lines[b][nx - 1].begin()) l = *prev(itrl);
            }
            if(lines[b].contains(nx)){
                auto itr = lines[b][nx].upper_bound(ny);
                if(itr != lines[b][nx].begin()) r = *prev(itr);
            }
            // 近い方に移動する
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
        // t = 1, 2 のクエリでは to[block_id] と line[block_id][x] を適切に変更する必要がある
        // (x, y), (x + 1, y) から逆順にブロックの先頭まで辿ったときの縦線の番号を求める(それぞれ parl, parr とする)
        // 横線を追加 / 削除したときは to[block_id][parl] と to[block_id][parr] を swap すればよい
        ll block_id = y / block_size;
        ll parl = traverse_rev(x, y);
        ll parr = traverse_rev(x + 1, y);
        if(!to[block_id].contains(parl)) to[block_id][parl] = parl;
        if(!to[block_id].contains(parr)) to[block_id][parr] = parr;
        swap(to[block_id][parl], to[block_id][parr]);
        lines[block_id][x].emplace(y % block_size);
    };
    auto query2 = [&](ll x, ll y){
        ll block_id = y / block_size;
        ll parl = traverse_rev(x, y);
        ll parr = traverse_rev(x + 1, y);
        if(!to[block_id].contains(parl)) to[block_id][parl] = parl;
        if(!to[block_id].contains(parr)) to[block_id][parr] = parr;
        swap(to[block_id][parl], to[block_id][parr]);
        lines[block_id][x].erase(y % block_size);
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
        if(q.t == 1){
            query1(q.x, q.y);
        }else if(q.t == 2){
            query2(q.x, q.y);
        }else{
            cout << query3(q.s) << '\n';
        }
    }
}