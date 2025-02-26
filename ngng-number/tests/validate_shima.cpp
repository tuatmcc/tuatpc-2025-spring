#include "constraints.h"
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    registerValidation(argc, argv);
    string num = inf.readToken(format("[0-9]{%d, %d}", MIN_length_of_N, MAX_length_of_N + 1));
    ensure(num[0] != '0');
    if (num.size() == MAX_length_of_N + 1) {
        ensure(num[0] == '1');
        for (int i = 1; i < num.size(); i++) {
            ensure(num[i] == '0');
        }
    }
    inf.readEoln();
    inf.readEof();
}