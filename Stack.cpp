#include "Stack.h"
#include <iostream>

using namespace std;

Stack::Stack() : top(nullptr), printDepth(-1) {}

Stack::~Stack() { 
}

DigitList* Stack::instrAmpersand(DigitList* list) {
    if (list == nullptr) return list;
    if (list->next != nullptr) {
        printDepth++;
        instrAmpersand(list->next);
    } else {
        printDepth++;
    }
    cout << printDepth-- << ": ";
    if (list->head != nullptr) list->printAll(list->head);
    cout << endl;
    return list;
}

DigitList* Stack::instrPush() {
    top = new DigitList(nullptr, top);
    return top;
}

DigitList* Stack::instrPop() {
    if (top == nullptr) return nullptr;
    DigitList* tmp = top;
    top = top->next;
    tmp->clear(tmp->head);
    tmp->head = nullptr;
    delete tmp;
    return top;
}

DigitList* Stack::instrDuplicate() {
    if (top != nullptr) {
        DigitList* copy = new DigitList(nullptr, top);
        copy->copyFrom(top->head);
        top = copy;
    }
    return top;
}

DigitList* Stack::instrSwap() {
    if (top != nullptr && top->next != nullptr) {
        DigitNode* a = top->head;
        top->head = top->next->head;
        top->next->head = a;
    }
    return top;
}

DigitList* Stack::instrAt() {
    if (top == nullptr) return top;
    long long pos = top->toInt(top->head);
    top->clear(top->head);
    top->head = nullptr;
    DigitList* tmp = top->next;
    delete top;
    top = tmp;
    DigitList* target = nthList(top, pos, 0);
    DigitList* copy = new DigitList(nullptr, top);
    copy->copyFrom(target->head);
    top = copy;
    return top;
}

DigitList* Stack::instrReadChar() {
    char c;
    cin >> c;
    top->prepend(c);
    return top;
}

DigitList* Stack::instrPrintChar() {
    if (top != nullptr && top->head != nullptr) {
        cout << top->head->value;
        instrPop();
    }
    return top;
}

DigitList* Stack::instrNegate() {
    if (top == nullptr) return top;
    if (top->head == nullptr) {
        top->prepend('-');
        return top;
    }
    DigitNode* beforeMinus = findBeforeMinus(top->head);
    if (beforeMinus->next == nullptr) {
        beforeMinus->next = new DigitNode('-', nullptr);
    } else {
        delete beforeMinus->next;
        beforeMinus->next = nullptr;
    }
    if (top->head->value == '-') top->head = nullptr;
    return top;
}

int Stack::instrAbs(DigitNode*& node) {
    if (node == nullptr) return 0;
    DigitNode* beforeMinus = findBeforeMinus(node);
    if (beforeMinus->next != nullptr) {
        delete beforeMinus->next;
        beforeMinus->next = nullptr;
        return -1;
    }
    if (node->value == '-') {
        node = nullptr;
        return 0;
    }
    return 0;
}

DigitList* Stack::instrIntToChar() {
    if (top != nullptr && top->head != nullptr) {
        char c = (char)top->toInt(top->head);
        clearTop();
        top->prepend(c);
    }
    return top;
}

DigitList* Stack::instrCharToInt() {
    if (top != nullptr && top->head != nullptr) {
        int code = (int)top->head->value;
        instrPop();
        instrPush();
        top->prependInt(code);
    }
    return top;
}

DigitList* Stack::instrSplit() {
    if (top != nullptr && top->head != nullptr) {
        char c = top->head->value;
        DigitNode* old = top->head;
        top->head = top->head->next;
        delete old;
        instrPush();
        top->prepend(c);
    }
    return top;
}

DigitList* Stack::instrAppend() {
    if (top == nullptr || top->next == nullptr) return top;
    if (top->head != nullptr) {
        DigitNode* a = top->head;
        top = top->next;
        top->lastNode(top->head)->next = a;
    }
    return top;
}

int Stack::instrLessThan() {
    if (top == nullptr || top->next == nullptr) return 0;

    int aSign = instrAbs(top->head);
    int aLen  = top->trimLeadingZeros(top->head);
    int bSign = instrAbs(top->next->head);
    int bLen  = top->trimLeadingZeros(top->next->head);

    int cmp = 2;
    if (aLen == bLen)
        cmp = top->compareMagnitude(top->head, top->next->head);

    if (aLen == bLen && aLen == 0) return 0;
    if (aLen == bLen && cmp == 1) return 1;
    if (bSign < aSign && top->head->value != '0') return 1;
    if (bSign > aSign && top->head->value != '0') return -1;
    if (aLen == bLen && aSign == bSign && aSign == -1 && cmp == -1) return 1;
    if (aLen == bLen && cmp == 1) return 0;
    if (aLen == bLen && cmp == -1) return (aSign > bSign) ? 1 : -1;
    if (aSign == bSign && aSign == -1) return (aLen < bLen) ? 1 : -1;
    return (aLen < bLen) ? -1 : 1;
}

DigitList* Stack::instrEqual() {
    if (top == nullptr || top->next == nullptr) return top;

    int aSign = instrAbs(top->head);
    int aLen  = 0;
    top->stripZeros(top->head, &aLen);
    int bSign = instrAbs(top->next->head);
    int bLen  = 0;
    top->next->stripZeros(top->next->head, &bLen);

    int cmp = 2;
    if (aLen == bLen)
        cmp = top->compareMagnitude(top->head, top->next->head);

    instrPop();
    instrPop();
    instrPush();

    bool equal = (aSign == bSign && cmp == 0) ||
                 (aLen == bLen && aLen == 0 && cmp == 0);
    top->prepend(equal ? '1' : '0');
    return top;
}

DigitList* Stack::instrNot() {
    if (top == nullptr) return top;
    if (top->head == nullptr) {
        top->prepend('1');
        return top;
    }
    if (top->head->value == '0' && top->head->next == nullptr) {
        clearTop();
        top->prepend('1');
        return top;
    }
    clearTop();
    top->prepend('0');
    return top;
}

DigitList* Stack::instrTilde(int instrIndex) {
    instrPush();
    if (instrIndex == 0) top->prepend('0');
    else top->prependInt(instrIndex);
    return top;
}

int Stack::instrJump() {
    if (top == nullptr) return 0;
    long long target = top->toInt(top->head);
    instrPop();
    if (top == nullptr) return 0;
    if (top->head == nullptr) { instrPop(); return 0; }
    if (top->head->value == '0' && top->head->next == nullptr) {
        instrPop();
        return 0;
    }
    instrPop();
    return (int)target;
}

DigitList* Stack::instrAdd() {
    if (top == nullptr || top->next == nullptr) return top;
    if (top->head == nullptr || top->next->head == nullptr) return top;

    int aSign = instrAbs(top->head);
    int bSign = instrAbs(top->next->head);
    DigitList* listA = top;
    DigitList* listB = top->next;
    listA->trimLeadingZeros(listA->head);
    listB->trimLeadingZeros(listB->head);
    int cmp = instrLessThan();

    top = top->next->next;
    instrPush();

    if (aSign == bSign && aSign == -1) {
        top->addition(listA->head, listB->head, 0);
        applyNegativeSign();
    } else if (aSign == bSign) {
        top->addition(listA->head, listB->head, 0);
        top->head = top->reverseList(top->head);
        top->trimLeadingZeros(top->head);
    } else if (aSign == 0 && bSign == -1) {
        if (cmp == -1) {
            top->subtraction(listB->head, listA->head, 0);
            applyNegativeSign();
        } else {
            top->subtraction(listA->head, listB->head, 0);
            top->head = top->reverseList(top->head);
            top->trimLeadingZeros(top->head);
        }
    } else { 
        if (cmp == 1) {
            top->subtraction(listA->head, listB->head, 0);
            applyNegativeSign();
        } else {
            top->subtraction(listB->head, listA->head, 0);
            top->head = top->reverseList(top->head);
            top->trimLeadingZeros(top->head);
        }
    }
    return top;
}

DigitList* Stack::nthList(DigitList* list, long long n, long long i) {
    if (list == nullptr || i == n) return list;
    return nthList(list->next, n, i + 1);
}

DigitNode* Stack::findBeforeMinus(DigitNode* node) {
    if (node->next == nullptr || node->next->value == '-') return node;
    return findBeforeMinus(node->next);
}

void Stack::clearTop() {
    top->clear(top->head);
    top->head = nullptr;
}

void Stack::applyNegativeSign() {
    top->head = top->reverseList(top->head);
    top->trimLeadingZeros(top->head);
    top->head = top->reverseList(top->head);
    top->prepend('-');
    top->head = top->reverseList(top->head);
}
