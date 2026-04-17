#ifndef DIGITNODE_H
#define DIGITNODE_H

class DigitNode {
public:
    DigitNode(char v, DigitNode* next);
    ~DigitNode() = default;

    char      value;
    DigitNode* next;
    long long  intValue;
};

#endif // DIGITNODE_H
