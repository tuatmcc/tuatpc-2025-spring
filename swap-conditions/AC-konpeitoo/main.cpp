#include<bits/stdc++.h>
using namespace std;

int main(){
    int K;
    cin >> K;
    K--;
    vector<long long> A(4);
    for(int i = 0; i < 4; i++)cin >> A[i];
    vector<int> J(3);
    for(int i = 0; i < 3; i++){
        cin >> J[i];
        J[i]--;
    }
    //long long _min = 0, _max = 0;
    //_max = min(A[J[0]], min(A[J[1]], A[J[2]] / 2));

    //今のrankを求める。
    int up = 0, down = 0;
    for(int i = 0; i < 4; i++){
        if(i == K)continue;
        if(A[K] < A[i])up++;
        else if(A[i] < A[K])down++;
        else if(i < K)up++;
        else down++;
    }
    int iniRank = up + 1;

    //solve
    vector<long long> a(4);
    for(int i = 1; i < iniRank; i++){
        //long long __min = _min, __max = _max, mid, ans = -1;
        long long __min = 0, __max = 2000000000000000000, mid, ans = -1;
        while(__min <= __max){
            mid = (__min + __max) / 2;
            for(int j = 0; j < 4; j++)a[j] = A[j];
            //K
            a[K] += 4 * mid;
            a[J[0]] -= mid;
            a[J[1]] -= mid;
            a[J[2]] -= 2 * mid;
            //rank
            up = 0;
            for(int j = 0; j < 4; j++){
                if(j == K)continue;
                if(a[K] < a[j])up++;
                else if(a[j] < a[K]);
                else if(j < K)up++;
                else;
            }
            up++;

            if(up == i){
                ans = mid;
                __max = mid - 1;
            }else if(up < i){
                __max = mid - 1;
            }else{
                __min = mid + 1;
            }
            
        }
        cout << ans << endl;
    }
    //inirank
    cout << "0" << endl;
    for(int i = iniRank + 1; i <= 4; i++)cout << "-1" << endl;
    return 0;
}