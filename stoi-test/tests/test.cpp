#include "../dialSolver/dialSolver.h"
#include <iostream>
using std::cout;

void printValues(int expected, int actual) {
    cout << "EXPECTED: " << expected << " ACTUAL: " << actual << '\n';
}

void testRotateLeft() {
    cout << __func__ << ": ";
    DialSolver* dial = new DialSolver(2);
    dial->rotateLeft(3);
    printValues(1, dial->readCount());
}

void testRotateRight() {
    cout << __func__ << ": ";
    DialSolver* dial = new DialSolver(98);
    dial->rotateRight(5);
    printValues(1, dial->readCount());
}

void testHitZeroRight() {
    cout << __func__ << ": ";
    DialSolver* dial = new DialSolver(98);
    dial->rotateRight(2);
    printValues(1, dial->readCount());
}

void testHitZeroLeft() {
    cout << __func__ << ": ";
    DialSolver* dial = new DialSolver(2);
    dial->rotateLeft(2);
    printValues(1, dial->readCount());
}

void testLoopLeftTwice() {
    cout << __func__ << ": ";
    DialSolver* dial = new DialSolver(1);
    dial->rotateLeft(200);
    printValues(2, dial->readCount());
}

void testLoopRightTwice() {
    cout << __func__ << ": ";
    DialSolver* dial = new DialSolver(98);
    dial->rotateRight(200);
    printValues(2, dial->readCount());
}

void testLoopAndZeroRight() {
    cout << __func__ << ": ";
    DialSolver* dial = new DialSolver(98);
    dial->rotateRight(202);
    printValues(3, dial->readCount());
}

void testLoopAndZeroLeft() {
    cout << __func__ << ": ";
    DialSolver* dial = new DialSolver(2);
    dial->rotateLeft(202);
    printValues(3, dial->readCount());
}

void testLoopOnZeroLeft() {
    cout << __func__ << ": ";
    DialSolver* dial = new DialSolver(0);
    dial->rotateLeft(300);
    printValues(3, dial->readCount());
}

void testLoopOnZeroRight() {
    cout << __func__ << ": ";
    DialSolver* dial = new DialSolver(0);
    dial->rotateRight(300);
    printValues(3, dial->readCount());
}

void testTenThousandLoop() {
    cout << __func__ << ": ";
    DialSolver* dial = new DialSolver(50);
    dial->rotateRight(1000);
    cout << "count: ";
    printValues(10, dial->readCount());
    cout << "dial: ";
    printValues(50, dial->readDial());
}

void testDoNothing1() {
    cout << __func__ << ": ";
    DialSolver* dial = new DialSolver(0);
    dial->rotateRight(5);
    printValues(0, dial->readCount());
}

void testDoNothing2() {
    cout << __func__ << ": ";
    DialSolver* dial = new DialSolver(0);
    dial->rotateLeft(5);
    printValues(0, dial->readCount());
}

void testDoNothing3() {
    cout << __func__ << ": ";
    DialSolver* dial = new DialSolver(50);
    dial->rotateRight(40);
    printValues(0, dial->readCount());
}

void testDoNothing4() {
    cout << __func__ << ": ";
    DialSolver* dial = new DialSolver(80);
    dial->rotateLeft(30);
    printValues(0, dial->readCount());
}

int main() {
    std::cout << "RUNNING TESTS: \n";
    testRotateLeft();
    testRotateRight();
    testHitZeroRight();
    testHitZeroLeft();
    testLoopLeftTwice();
    testLoopRightTwice();
    testLoopAndZeroRight();
    testLoopAndZeroLeft();
    testLoopOnZeroLeft();
    testLoopOnZeroRight();
    testTenThousandLoop();
    testDoNothing1();
    testDoNothing2();
    testDoNothing3();
    testDoNothing4();
}