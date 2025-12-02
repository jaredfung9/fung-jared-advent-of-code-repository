#include "dialSolver.h"
#include <iostream>

int modulo(int n, int GF) {
    if (n < 0) {
        return GF + (n % GF); // remainder is negative
    }
    return n % GF;
}

int DialSolver::remainderAndCount(int n, int GF) {
    count += n / GF;
    return modulo(n, GF);
}

void DialSolver::rotateLeft(int n) {
    int remainder = remainderAndCount(n, 100);
    int prev = dial;
    dial = modulo(dial - remainder, 100);

    if (prev == 0) {
        return;
    }
    if ((dial == 0) || (prev < dial)) {
        incrementCount();
    }
}

void DialSolver::rotateRight(int n) {
    int remainder = remainderAndCount(n, 100);
    int prev = dial;
    dial = modulo(dial + remainder, 100);
    if (prev == 0) {
        return;
    }
    
    if ((dial == 0) || (prev > dial)) {
        incrementCount();
    }
}