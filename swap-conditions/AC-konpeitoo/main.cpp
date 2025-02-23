#include<bits/stdc++.h>
using namespace std;

int main(){
    int T;
    cin >> T;
    for(int t = 0; t < T; t++){
        int X;
        cin >> X;
        X--;
        int Y;
        cin >> Y;
        Y--;
        int R;
        cin >> R;
        vector<long long> A(4);
        for(int i = 0; i < 4; i++)cin >> A[i];
    
        //今のrankを求める。
        int up = 0, down = 0;
        for(int i = 0; i < 4; i++){
            if(i == X)continue;
            if(A[X] < A[i])up++;
            else if(A[i] < A[X])down++;
            else if(i < X)up++;
            else down++;
        }
        int iniRank = up + 1;
    
        //solve
        long long ans = -1;
        if(R < iniRank){
            vector<long long> a(4);
            long long __min = 0, __max = 2000000000000000000, mid;
            while(__min <= __max){
                mid = (__min + __max) / 2;
                for(int i = 0; i < 4; i++)a[i] = A[i];
                for(int i = 0; i < 4; i++){
                    if(i == X)a[i] += 4 * mid;
                    else if(i == Y)a[i] -= 2 * mid;
                    else a[i] -= mid;
                }
                //rank
                up = 0;
                for(int i = 0; i < 4; i++){
                    if(i == X)continue;
                    if(a[X] < a[i])up++;
                    else if(a[i] < a[X]);
                    else if(i < X)up++;
                    else;
                }
                up++;
                if(up == R){
                    ans = mid;
                    __max = mid - 1;
                }else if(up < R){
                    __max = mid - 1;
                }else{
                    __min = mid + 1;
                }
            }
        }else if(R == iniRank)ans = 0;
        cout << ans << endl;
    }
    return 0;
}