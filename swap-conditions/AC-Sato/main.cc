#include <bits/stdc++.h>

using namespace std;
using ll = long long;

using pil = pair<int, ll>;
using vpil = vector<pil>;

bool comp(pil &a, pil &b) {
	if (a.second == b.second) return a.first < b.first;
	return a.second > b.second;
}

int main() {
	int T; cin >> T;

	while (T--) {
		int X, Y, Z[2], R; cin >> X >> Y >> R; --X; --Y; --R;
		ll A[4]; cin >> A[0] >> A[1] >> A[2] >> A[3];
		for (int i = 0, k = 0; i < 4; ++i) {
			if (i == X || i == Y) continue;
			Z[k] = i;
			++k;
		}
		vpil idx_score = {{X, A[X]}, {Y, A[Y]}, {Z[0], A[Z[0]]}, {Z[1], A[Z[1]]}};
		sort(idx_score.begin(), idx_score.end(), comp);

		// 元からR位なら0
		if (idx_score[R].first == X) {
			cout << "0\n";
			continue;
		}

		// 元から目標スコアを超えてたら-1
		if (A[X] > idx_score[R].second) {
			cout << "-1\n";
			continue;
		}

		// 二分探索
		ll low = -1, high = 1e18+1;
		bool flag = true;
		int new_rank;
		vpil new_is;
		while (high - low > 1) {
			ll mid = low + (high - low) / 2;
			new_is = {{X, A[X] + 4 * mid}, {Y, A[Y] - 2 * mid}, {Z[0], A[Z[0]] - mid}, {Z[1], A[Z[1]] - mid}};
			sort(new_is.begin(), new_is.end(), comp);
			for (int i = 0; i < 4; ++i) if(new_is[i].first == X) new_rank = i;
			if (new_rank <= R) {
				high = mid;
			} else if (new_rank > R) {
				low = mid;
			}
			if (high <= 1 && new_rank != R) {
				cout << "-1\n";
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
			h = {{X, A[X] + 4 * high}, {Y, A[Y] - 2 * high}, {Z[0], A[Z[0]] - high}, {Z[1], A[Z[1]] - high}};
			l = {{X, A[X] + 4 * low}, {Y, A[Y] - 2 * low}, {Z[0], A[Z[0]] - low}, {Z[1], A[Z[1]] - low}};
			sort(h.begin(), h.end(), comp);
			sort(l.begin(), l.end(), comp);
			ch = h[R].first == X;
			cl = l[R].first == X;
			if (cl)
				cout << low << '\n';
			else if (ch)
				cout << high << '\n';
			else
				cout << "-1\n";
		}
	}

	return 0;
}
