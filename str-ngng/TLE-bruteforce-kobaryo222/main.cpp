#include <iostream>
#include <string>
#include <cassert>

using namespace std;

int main()
{
    int N, Q;
    cin >> N >> Q;
    string S;
    cin >> S;
    // O(QN^4)
    long long QN4 = 1LL * Q * N * N * N * N;
    if (QN4 > 100000000) {
        assert(false);
    }
    for (int i = 0; i < Q; i++) {
        int l, r;
        cin >> l >> r;
        l--;
        long long int ans = 0;
        for (int a = l; a < r; a++) {
            for (int b = a + 1; b < r; b++) {
                for (int c = b + 1; c < r; c++) {
                    for (int d = c + 1; d < r; d++) {
                        if (S[a] == S[c] && S[b] == S[d] && S[a] != S[b])
                            ans++;
                    }
                }
            }
        }
        cout << ans << endl;
    }
}