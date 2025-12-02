#pragma once

class DialSolver {
    int count;
    int dial;
    void incrementCount() { 
        count++; }
    int remainderAndCount(int n, int GF);
    public:
    DialSolver(int x) {
        count = 0;
        dial = x;
    }
    int readCount() { return count; }
    int readDial() { return dial; }
    void rotateLeft(int n);
    void rotateRight(int n);
}typedef DialSolver;