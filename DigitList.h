#ifndef DIGITLIST_H
#define DIGITLIST_H

#include "DigitNode.h"

class DigitList {
public:
    DigitList(DigitNode* head, DigitList* next);
    ~DigitList();

    DigitNode* prepend(char digit);
    int prependInt(int value);
    void copyFrom(DigitNode* node);
    void clear(DigitNode* node);
    long long toInt(DigitNode* node);
    DigitNode* lastNode(DigitNode* node);
    DigitNode* printAll(DigitNode* node);
    int trimLeadingZeros(DigitNode*& node);

    int compareMagnitude(DigitNode* a, DigitNode* b);
    int addition(DigitNode* a, DigitNode* b, int carry);
    int subtraction(DigitNode* a, DigitNode* b, int borrow);
    DigitNode* reverseList(DigitNode* node);

    long long computeValue(DigitNode* node, long long* idx, long long* val);
    int stripZeros(DigitNode*& node, int* len);

    DigitNode* head;
    DigitList* next;
};

#endif // DIGITLIST_H
