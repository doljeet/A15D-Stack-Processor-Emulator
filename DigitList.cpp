#include "DigitList.h"
#include <iostream>

using namespace std;

DigitList::DigitList(DigitNode* head, DigitList* next) : head(head), next(next) {}

DigitList::~DigitList() { 
    /* nodes freed explicitly via clear() */ 
}

DigitNode* DigitList::prepend(char digit) {
    head = new DigitNode(digit, head);
    return head;
}

int DigitList::prependInt(int value) {
    if (value != 0) {
        prependInt(value / 10);
        prepend((value % 10) + '0');
    }
    return value;
}

void DigitList::copyFrom(DigitNode* node) {
    if (node == nullptr) return;
    if (node->next != nullptr) copyFrom(node->next);
    prepend(node->value);
}

void DigitList::clear(DigitNode* node) {
    if (node == nullptr) return;
    clear(node->next);
    delete node;
}

long long DigitList::toInt(DigitNode* node) {
    long long idx = 0, val = 0;
    computeValue(node, &idx, &val);
    return val + node->intValue;
}

DigitNode* DigitList::lastNode(DigitNode* node) {
    if (node->next != nullptr) return lastNode(node->next);
    return node;
}

DigitNode* DigitList::printAll(DigitNode* node) {
    if (node == nullptr) return node;
    cout << node->value;
    if (node->next != nullptr) printAll(node->next);
    return node;
}

int DigitList::trimLeadingZeros(DigitNode*& node) {
    int len = 0;
    if (node == nullptr) return 0;
    if (node->value == '0') {
        stripZeros(node, &len);
        if (node == nullptr) {
            node = new DigitNode('0', nullptr);
            len++;
        }
    } else {
        stripZeros(node, &len);
    }
    return len;
}

int DigitList::compareMagnitude(DigitNode* a, DigitNode* b) {
    if (a == nullptr || b == nullptr) return 0;
    int result = compareMagnitude(a->next, b->next);
    if (result != 0) return result;
    int da = a->value - '0';
    int db = b->value - '0';
    if (da == db) return 0;
    return (da > db) ? 1 : -1;
}

int DigitList::addition(DigitNode* a, DigitNode* b, int carry) {
    int av = (a != nullptr) ? a->intValue : 0;
    int bv = (b != nullptr) ? b->intValue : 0;
    int sum = av + bv + carry;
    prepend((sum % 10) + '0');
    carry = (sum > 9) ? 1 : 0;

    DigitNode* an = (a != nullptr) ? a->next : nullptr;
    DigitNode* bn = (b != nullptr) ? b->next : nullptr;
    if (an != nullptr || bn != nullptr) return addition(an, bn, carry);
    if (carry > 0) prependInt(carry);
    return 0;
}

int DigitList::subtraction(DigitNode* a, DigitNode* b, int borrow) {
    int av = (a != nullptr) ? a->intValue : 0;
    int bv = (b != nullptr) ? b->intValue : 0;
    int diff = av + borrow - bv;
    if (diff < 0) {
        prepend((diff + 10) + '0');
        borrow = -1;
    } else {
        prepend(diff + '0');
        borrow = 0;
    }
    DigitNode* an = (a != nullptr) ? a->next : nullptr;
    DigitNode* bn = (b != nullptr) ? b->next : nullptr;
    if (an != nullptr || bn != nullptr) return subtraction(an, bn, borrow);
    if (borrow < 0) prependInt(borrow);
    return 0;
}

DigitNode* DigitList::reverseList(DigitNode* node) {
    if (node == nullptr || node->next == nullptr) return node;
    DigitNode* rev = reverseList(node->next);
    node->next->next = node;
    node->next = nullptr;
    return rev;
}

long long DigitList::computeValue(DigitNode* node, long long* idx, long long* val) {
    if (node->next != nullptr) {
        (*idx)++;
        long long digit = computeValue(node->next, idx, val);
        long long place = 1;
        for (long long i = 0; i < *idx; i++) place *= 10;
        *val += digit * place;
        (*idx)--;
        return node->intValue;
    }
    return node->intValue;
}

int DigitList::stripZeros(DigitNode*& node, int* len) {
    if (node == nullptr) return 1;
    if (stripZeros(node->next, len) && node->value == '0') {
        delete node;
        node = nullptr;
        return 1;
    }
    (*len)++;
    return 0;
}
