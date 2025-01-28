#include<bits/stdc++.h>
using namespace std;

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
    string S;
    cin >> S;

    if(S.size() == 1){
        bool flag = false;
        for(int i = 0; i < N; i++){
            if(X[i] == S[0]){
                if(flag == false){
                    cout << "1" << endl;
                    flag = true;
                }else cout << " ";
                cout << i + 1;
            }
        }
        if(flag == false){//存在しない場合
            cout << "0" << endl;
            for(int i = 0; i < N; i++){
                if(i != 0)cout << " ";
                cout << i + 1;
            }
        }
        cout << endl;
        return 0;
    }
    vector<vector<long double>> ans(S.size() - 1, vector<long double>(N, 0));
    for(int i = 0; i < S.size() - 1; i++){
        for(int j = 0; j < N; j++){
            if(X[j] != S[S.size() - 1 - i])continue;
            for(int k = 0; k < m[j].size(); k++){
                if(X[m[j][k].first] == S[S.size() - 2 - i]){
                    if(i == 0){
                        ans[i][m[j][k].first] += (long double)m[j][k].second / (long double)100;
                    }else{
                        ans[i][m[j][k].first] += ans[i - 1][j] * (long double)m[j][k].second / (long double)100;
                    }
                }else{
                    //cout << X[m[j][k].first] << " " << "S -> " << S[2 - i] << endl;
                }
            }
        }
    }
    cout << fixed << setprecision(20) << *max_element(ans[S.size() - 2].begin(), ans[S.size() - 2].end()) << endl;//fixedとかいる？
    long double _m = *max_element(ans[S.size() - 2].begin(), ans[S.size() - 2].end());
    bool flag = false;
    for(int i = 0; i < N; i++){
        if(abs(_m - ans[S.size() - 2][i]) < 0.0000000000000001){// && X[i] == S[0]){
            if(flag == false)flag = true;
            else cout << " ";
            cout << i + 1;
        }
    }
    //デバック用出力
    for(int i = 0; i < N; i++){
        if(i != 0)cout << " ";
        cout << ans[S.size() - 2][i];
    }
    cout << endl;
    /*if(flag == false){
        for(int i = 0; i < N; i++){
            if(i != 0)cout << " ";
            cout << i + 1;
        }
    }*/
    cout << endl;
    return 0;
}