#include "Stack.h"
#include <iostream>
#include <string>

using namespace std;

string readProgram() {
    string line;
    getline(cin, line);
    return line;
}

int main() {
    Stack* stack = new Stack();
    stack->instrPush(); // ensure there's always a top list to write into

    string program = readProgram();
    int len = (int)program.size();

    for (int t = 0; t < len; t++) {
        char ins = program[t];

        if      (ins == '&') { stack->instrAmpersand(stack->top); }
        else if (ins == '\'') { stack->instrPush(); }
        else if (ins == ',') { stack->instrPop(); }
        else if (ins == ':') { stack->instrDuplicate(); }
        else if (ins == ';') { stack->instrSwap(); }
        else if (ins == '@') { stack->instrAt(); }
        else if (ins == '.') { stack->instrReadChar(); }
        else if (ins == '>') { stack->instrPrintChar(); }
        else if (ins == '-') { stack->instrNegate(); }
        else if (ins == '^') { stack->instrAbs(stack->top->head); }
        else if (ins == '[') { stack->instrCharToInt(); }
        else if (ins == ']') { stack->instrIntToChar(); }
        else if (ins == '$') { stack->instrSplit(); }
        else if (ins == '#') { stack->instrAppend(); }
        else if (ins == '<') {
            int r = stack->instrLessThan();
            stack->instrPop();
            stack->instrPop();
            stack->instrPush();
            stack->top->prepend(r == 1 ? '1' : '0');
        }
        else if (ins == '=') { stack->instrEqual(); }
        else if (ins == '!') { stack->instrNot(); }
        else if (ins == '~') { stack->instrTilde(t); }
        else if (ins == '?') {
            int jump = stack->instrJump();
            if (jump != 0) t = jump - 1;
        }
        else if (ins == '+') { stack->instrAdd(); }
        else {
            if (stack->top != nullptr) stack->top->prepend(ins);
        }
    }

    delete stack;
    return 0;
}
