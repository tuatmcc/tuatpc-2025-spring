#include<bits/stdc++.h>
using namespace std;

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

int main(){
    int N;
    cin >> N;
    vector<char> X(N);
    for(int i = 0; i < N; i++)cin >> X[i];
    map<int, vector<pair<int, int>>> m;//mapにする必要なんてない
    for(int i = 0; i < N; i++){
        int M;
        cin >> M;
        vector<int> V(M), W(M);
        int v;
        for(int j = 0; j < M; j++){
            cin >> v;
            V[j] = v - 1;
        }
        for(int j = 0; j < M; j++)cin >> W[j];
        //i -> V[j]
        for(int j = 0; j < M; j++){
            m[V[j]].push_back({i, W[j]});//逆に入れる重みとともに
        }
    }
    int L;
    cin >> L;
    string S;
    cin >> S;

    if(S.size() == 1){
        bool flag = false;
        for(int i = 0; i < N; i++){
            if(X[i] == S[0]){
                cout << "1 1\n";
            }else{
                cout << "0 1\n";
            }
        }
        return 0;
    }
    vector<vector<long long>> ans(S.size() - 1, vector<long long>(N, 0));
    for(int i = 0; i < S.size() - 1; i++){
        for(int j = 0; j < N; j++){
            if(X[j] != S[S.size() - 1 - i])continue;
            for(int k = 0; k < m[j].size(); k++){
                if(X[m[j][k].first] == S[S.size() - 2 - i]){
                    if(i == 0){
                        ans[i][m[j][k].first] += (long long)m[j][k].second;
                    }else{
                        ans[i][m[j][k].first] += ans[i - 1][j] * (long long)m[j][k].second;
                    }
                }
            }
        }
    }
    /*約分*/

    for(int i = 0; i < N; i++){
        long long a = ans[S.size() - 2][i];
        long long b = pow(100, S.size() - 1);
        if(a == 0){
            cout << "0 1\n";
        }else if(a == b){
            cout << "1 1\n";
        }else{
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
    return 0;
}