#include <iostream>
#include <sstream>
#include <stack>
#include <vector>
#include <cmath>
#include <map>
#include <stdio.h>

using namespace std;

int checkPr(string x) {
    if ((x == "-") || (x == "+"))
        return 1;
    else if ((x == "*") || (x == "/"))
        return 2;
    else if (x == "#")
        return 0;
    else if (x == "(")
        return 0;
    else if (x == ")")
        return 0;
    else
        return 3;
}

string readStr() {

    string val;

    getline(cin, val);
    return val;
}

void delPr(string &res, stack <string> &stackNum, int pr) {

    string handStr = stackNum.top();
    int handPr;
    handPr = checkPr(handStr);
    while (pr <= handPr) { 
        stackNum.pop();
        res += handStr + " ";
        handStr = stackNum.top();  
        handPr = checkPr(handStr);  
    }
}

int main() {

    setlocale(LC_ALL, "Russian");
    string res = " ";
    string exp;
    stack <string> stackNum;
    
    cout << "Введите инфиксное выражение " << endl; 
    auto v = readStr();
    auto s = istringstream(v);
    float num = 0;

    stackNum.push("#");
    while (getline(s, exp, ' ')) {
        if (sscanf_s(exp.data(), "%f", &num) >= 1) {
            string strPar = to_string((int)(num));
            delPr(res, stackNum, 3);
            stackNum.push(strPar);
        }
        else if (exp == "("){
            stackNum.push(exp);
        }
        else if (exp == ")") {
            while (stackNum.top() != "(") {
                res += stackNum.top() + " ";
                stackNum.pop();
            }
            stackNum.pop();
        }
        else {
            int pr = checkPr(exp);
            delPr(res, stackNum, pr);
            stackNum.push(exp);
        }
    }
    while (stackNum.top() != "#") {
        res += stackNum.top() + " ";
        stackNum.pop();
    }
    cout << endl << "Обратная польская запись: " << res << endl;
    return 0;
}