#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

int evaluate(string infix, string& postfix, bool& result);
// Evaluates a boolean expression
//   If infix is a syntactically valid infix boolean expression,
//   then set postfix to the postfix form of that expression, set
//   result to the value of the expression, and return zero.  If
//   infix is not a syntactically valid expression, return 1; in
//   that case, postfix may or may not be changed, but result must
//   be unchanged.

int importance(char c) {
    switch (c) {
    case '!':
        return 3;
    case '&':
        return 2;
    case '|':
        return 1;
    default:
        return 4;
    }
}

bool validInfix(string infixExpression) {

    stack<char> pstack;
    stack<char> ostack;

    stack<char> infix;
    string infixStr;

    char lastChar = '/';
    for (char& c : infixExpression) {
        switch (c) {
        case ' ':
            break;
        case '(':
            if (isalpha(lastChar) || lastChar == ')')
                return false;
            infixStr += c;
            lastChar = c;
            break;
        case ')':
            if (!isalpha(lastChar) && lastChar != ')')
                return false;
            infixStr += c;
            lastChar = c;
            break;
        case '|':
        case '&':
            if (!isalpha(lastChar) && lastChar != ')')
                return false;
            infixStr += c;
            lastChar = c;
            break;
        case '!':
            if (isalpha(lastChar) || lastChar == ')')
                return false;
            infixStr += c;
            lastChar = c;
            break;
        default:
            if (!isalpha(c) || isalpha(lastChar) || lastChar == ')')
                return false;
            infixStr += c;
            lastChar = c;
            break;
        }
    }



    int leftBracketCount = 0;
    int rightBracketCount = 0;

    int operatorCount = 0;
    int operendCount = 0;
    for (char& c : infixStr) {
        if (c == '&' || c == '|') {
            operatorCount++;
        }
        if (c == 'T' || c == 'F') {
            operendCount++;
        }
        if (c == '(') {
            leftBracketCount++;
        }
        if (c == ')') {
            rightBracketCount++;
        }
    }
    if (operendCount - operatorCount != 1 || leftBracketCount - rightBracketCount) {
        return false;
    }

    return infixStr != "/";
}

int evaluate(string infix, string& postfix, bool& result)
{
    postfix = "";
    stack<char> temp;
    char lastChar = '/';
    temp.push(lastChar);

    if (!validInfix(infix)) {
        return 1;
    }

    for (char& c : infix) {
        switch (c) {
        case ' ':
            break;
        case 'T':
        case 'F':
            postfix += c;
            break;
        case '(':
            temp.push('(');
            break;
        case ')':
            while (temp.top() != '/' && temp.top() != '(') {
                postfix += temp.top();
                temp.pop();
            }
            temp.pop();
            break;
        case '&':
        case '|':
        case '!':
            while (temp.top() != '/' && temp.top() != '(' && importance(c) <= importance(temp.top())) {
                postfix += temp.top();
                temp.pop();
            }
            temp.push(c);
            break;
        default:
            break;
            //return 1;
        }
        lastChar = c;
    }
    while (temp.top() != '/') {
        postfix += temp.top();        //store and pop until stack is not empty.
        temp.pop();
    }

    stack<int> eval;

    for (char& c : postfix) {
        if (c == 'T') {
            eval.push(1);
        }
        else if (c == 'F') {
            eval.push(0);
        }
        else {
            if (eval.size() == 1) {
                if (c == '!') {
                    int val = eval.top();
                    eval.pop();
                    eval.push(-val + 1);
                }
                break;
            }
            int val2 = eval.top();
            eval.pop();
            int val1 = eval.top();
            eval.pop();
            switch (c) {
                case '|':
                    eval.push(val1 + val2);
                    break;
                case '&':
                    eval.push(val1 * val2);
                    break;
                default:
                    eval.push(val1);
                    eval.push(-val2 + 1);
            }
        }
    }
    result = eval.top();
    return 0;


}

int main()
{
    string pf;
    bool answer;

    assert(evaluate("T", pf, answer) == 0 && answer);
    assert(evaluate("(F)", pf, answer) == 0 && !answer);
    assert(evaluate("T&(F)", pf, answer) == 0 && !answer);
    assert(evaluate("T & !F", pf, answer) == 0 && answer);
    assert(evaluate("!(F|T)", pf, answer) == 0 && !answer);
    assert(evaluate("!F|T", pf, answer) == 0 && answer);
    assert(evaluate("T|F&F", pf, answer) == 0 && answer);
    assert(evaluate("T&!(F|T&T|F)|!!!(F&T&F)", pf, answer) == 0 && answer);


    assert(evaluate("T| F", pf, answer) == 0 && pf == "TF|" && answer);
    assert(evaluate("T|", pf, answer) == 1);
    assert(evaluate("F F", pf, answer) == 1);
    assert(evaluate("TF", pf, answer) == 1);
    assert(evaluate("()", pf, answer) == 1);
    assert(evaluate("()T", pf, answer) == 1);
    assert(evaluate("T(F|T)", pf, answer) == 1);
    assert(evaluate("T(&T)", pf, answer) == 1);
    assert(evaluate("(T&(F|F)", pf, answer) == 1);
    assert(evaluate("T+F", pf, answer) == 1);
    assert(evaluate("", pf, answer) == 1);
    assert(evaluate("F  |  !F & (T&F) ", pf, answer) == 0
        && pf == "FF!TF&&|" && !answer);
    assert(evaluate(" F  ", pf, answer) == 0 && pf == "F" && !answer);
    assert(evaluate("((T))", pf, answer) == 0 && pf == "T" && answer);
    cout << "Passed all tests" << endl;
}