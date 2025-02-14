#include <bits/stdc++.h>
#include "testlib.h"
#include "constraints.h"

int main(int argc, char *argv[]) {
	registerValidation(argc, argv);

	/**
	 * Input
	 * K A_1 A_2 A_3 A_4
	 * J_1 J_2 J_3
	 */

	int K;
	long long A1, A2, A3, A4;
	int J1, J2, J3;

	K = inf.readInt(K_MIN, K_MAX, "K");
	inf.readSpace();

	A1 = inf.readLong(A_MIN, A_MAX, "A_1");
	inf.readSpace();
	A2 = inf.readLong(A_MIN, A_MAX, "A_2");
	inf.readSpace();
	A3 = inf.readLong(A_MIN, A_MAX, "A_3");
	inf.readSpace();
	A4 = inf.readLong(A_MIN, A_MAX, "A_4");
	inf.readEoln();

	J1 = inf.readInt(J_MIN, J_MAX, "J_1");
	inf.readSpace();
	J2 = inf.readInt(J_MIN, J_MAX, "J_2");
	inf.readSpace();
	J3 = inf.readInt(J_MIN, J_MAX, "J_3");
	inf.readEoln();

	inf.readEof();

	assert(K != J1 && K != J2 && K != J3);

	return 0;
}

#ifdef input_style
K A1 A2 A3 A4
J1 J2 J3
#endif