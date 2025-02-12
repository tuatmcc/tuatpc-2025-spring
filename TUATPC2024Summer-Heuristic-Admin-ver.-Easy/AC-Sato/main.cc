#include <bits/stdc++.h>

using namespace std;

#define max(a, b) (a) > (b) ? (a) : (b)
#define chmax(a, b) (a) = (max(a, b))

int main() {
	int n;
	long long all_users_rating_max = 0, max_sum = 0;

	cin >> n;

	vector<pair<long long, long long>> ah(n);

	for (int i = 0; i < n; ++i) {
		long long this_user_max;
		cin >> ah[i].first >> ah[i].second;

		this_user_max = max(ah[i].first, ah[i].second);
		chmax(all_users_rating_max, this_user_max);
		max_sum += this_user_max;
	}

	if (n == 1 || n == 2 || all_users_rating_max < 1600 || max_sum < 4200)
		cout << "Yes\n";
	else
		cout << "No\n";

	return 0;
}