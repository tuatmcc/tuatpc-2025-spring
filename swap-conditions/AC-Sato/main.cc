#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#define min(a, b) (a) < (b) ? (a) : (b)
#define min3(a, b, c) min(min((a), (b)), (c))
#define min4(a, b, c, d) min(min((a), (b)), min((c), (d)))

using pil = pair<int, ll>;
using vpil = vector<pil>;

bool comp(pil &a, pil &b) {
	if (a.second == b.second) return a.first < b.first;
	return a.second > b.second;
}

int main() {
	int K;
	ll A[4], J[3];
	cin >> K; --K;
	cin >> A[0] >> A[1] >> A[2] >> A[3];
	cin >> J[0] >> J[1] >> J[2];
	--J[0]; --J[1]; --J[2];

	vpil idx_score = {{K, A[K]}, {J[0], A[J[0]]}, {J[1], A[J[1]]}, {J[2], A[J[2]]}};
	// 降順ソート
	sort(idx_score.begin(), idx_score.end(), comp);

	for (int r = 0; r < 4; ++r) {
		const char end = '\n';
		if (A[K] > idx_score[r].second) {
			cout << "-1" << end;
			continue;
		}

		// そのままでいいなら探索しない
		if (idx_score[r].first == K && idx_score[r].second == A[K]) {
			cout << "0" << end;
			continue;
		}

		// 二分探索するらしい
		ll low = -1, high = 2 * idx_score[0].second + 1;
		bool flag = true;
		int new_rank;
		vpil new_is;
		while (high - low > 1) {
			ll mid = low + (high - low) / 2;
			ll new_score = A[K] + 4 * mid;
			new_is = {{K, A[K] + 4 * mid}, {J[0], A[J[0]] - mid}, {J[1], A[J[1]] - mid}, {J[2], A[J[2]] - 2 * mid}};
			sort(new_is.begin(), new_is.end(), comp);
			for (int i = 0; i < 4; ++i) if(new_is[i].first == K) new_rank = i;
			if (new_rank <= r) {
				high = mid;
			} else if (new_rank > r) {
				low = mid;
			}
			if (high <= 1 && new_rank != r) {
				cout << "-1" << end;
				flag = false;
			}
		}
		if (flag) {
			vpil h, l;
			bool ch, cl;
			if (high < low) {
				ll tmp = high;
				high = low;
				low = tmp;
			}
			h = {{K, A[K] + 4 * high}, {J[0], A[J[0]] - high}, {J[1], A[J[1]] - high}, {J[2], A[J[2]] - 2 * high}};
			l = {{K, A[K] + 4 * low}, {J[0], A[J[0]] - low}, {J[1], A[J[1]] - low}, {J[2], A[J[2]] - 2 * low}};
			sort(h.begin(), h.end(), comp);
			sort(l.begin(), l.end(), comp);
			ch = h[r].first == K;
			cl = l[r].first == K;
			if (cl)
				cout << low << end;
			else if (ch)
				cout << high << end;
			else
				cout << "-1" << end;
		}
		// if (flag)
			// cout << high << end;
	}

	return 0;
}
