#include "DigitNode.h"

DigitNode::DigitNode(char v, DigitNode* next) : value(v), next(next) {
    intValue = (value >= '0' && value <= '9') ? (v - '0') : 0;
}
