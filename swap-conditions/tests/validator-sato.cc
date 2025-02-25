#include <bits/stdc++.h>
#include "testlib.h"
#include "constraints.h"

int main(int argc, char *argv[]) {
	registerValidation(argc, argv);

	/**
	 * Input
	 *
	 * T
	 * case_1
	 * ...
	 * case_T
	 */
	
	/**
	 * Testcase
	 *
	 * X Y R
	 * A_1 A_2 A_3 A_4
	 */

	int T;
	inf.readInt(T_MIN, T_MAX, "T");
	inf.readEoln();

	while (T--) {
		int X, Y, R;
		long long A_1, A_2, A_3, A_4;

		X = inf.readInt(X_MIN, X_MAX, "X");
		inf.readSpace();
		Y = inf.readInt(Y_MIN, Y_MAX, "Y");
		inf.readSpace();
		R = inf.readInt(R_MIN, R_MAX, "R");
		inf.readEoln();

		A_1 = inf.readInt(A_MIN, A_MAX, "A_1");
		inf.readSpace();
		A_2 = inf.readInt(A_MIN, A_MAX, "A_2");
		inf.readSpace();
		A_3 = inf.readInt(A_MIN, A_MAX, "A_3");
		inf.readSpace();
		A_4 = inf.readInt(A_MIN, A_MAX, "A_4");
		inf.readEoln();

		assert(X != Y);
	}
	inf.readEof();

	return 0;
}

#ifdef input_style
T
X Y R
A_1 A_2 A_3 A_4
#endif