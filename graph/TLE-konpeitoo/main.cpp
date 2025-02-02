#include<bits/stdc++.h>
using namespace std;
vector<vector<pair<int, int>>> g;
string S;
vector<char> X;

long long gcd(long long a, long long b){
    while(true){
        if(a % b == 0)break;
        else{
            long long tmp;
            tmp = b;
            b = a % b;
            a = tmp;
        }
    }
    return b;
}

long long _dfs(int now, int length){
    if(length + 1 == S.size())return 1;
    long long tmp = 0;
    for(auto x : g[now]){
        if(X[x.first] != S[length + 1])continue;
        tmp += ((long long)x.second) * _dfs(x.first, length + 1);
    }
    return tmp;
}

long long dfs(int start){
    return _dfs(start, 0);
}

int main(){
    int N;
    cin >> N;
    g = vector<vector<pair<int, int>>>(N, vector<pair<int, int>>());
    X = vector<char>(N);
    for(int i = 0; i < N; i++)cin >> X[i];
    for(int i = 0; i < N; i++){
        int M;
        cin >> M;
        vector<int> V(M), W(M);
        for(int j = 0; j < M; j++)cin >> V[j];
        for(int j = 0; j < M; j++)cin >> W[j];
        for(int j = 0; j < M; j++)g[i].push_back({V[j] - 1, W[j]});
    }
    cin >> S;
    vector<long long> ans(N, 0);
    for(int i = 0; i < N; i++){
        if(X[i] != S[0])continue;
        ans[i] = dfs(i);
    }
    for(int i = 0; i < N; i++){
        if(ans[i] == 0){
            cout << "0 1\n";
        }
        else{
            long long a = ans[i];
            long long b = pow(100, S.size() - 1);
            if(a == b){
                cout << "1 1\n";
            }
            else{
                /*ユークリッドの互除法*/
                long long e = -1;
                while(e != 1){
                    e = gcd(a, b);
                    a /= e;
                    b /= e;
                }
                cout << a << " " << b << "\n";
            }
        }
    }
    return 0;
}