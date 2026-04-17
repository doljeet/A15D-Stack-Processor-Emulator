#ifndef STACK_H
#define STACK_H

#include "DigitList.h"

class Stack {
public:
    Stack();
    ~Stack();

    DigitList* instrAmpersand(DigitList* list);
    DigitList* instrPush();
    DigitList* instrPop();
    DigitList* instrDuplicate();
    DigitList* instrSwap();
    DigitList* instrAt();
    DigitList* instrReadChar();
    DigitList* instrPrintChar();
    DigitList* instrNegate();
    int instrAbs(DigitNode*& node);
    DigitList* instrIntToChar();
    DigitList* instrCharToInt();
    DigitList* instrSplit();
    DigitList* instrAppend();
    int instrLessThan();
    DigitList* instrEqual();
    DigitList* instrNot();
    DigitList* instrTilde(int instrIndex);
    int instrJump();
    DigitList* instrAdd();

    DigitList* top;

private:
    int printDepth;

    DigitList* nthList(DigitList* list, long long n, long long i);
    DigitNode* findBeforeMinus(DigitNode* node);
    void clearTop();
    void applyNegativeSign();
};

#endif // STACK_H
