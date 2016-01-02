#include "function.h"
#include "number.h"
#include "operator.h"
#include "parenthesis.h"
#include "token.h"
#include "delimiter.h"

#include <iostream>
#include <algorithm>

using namespace std;

const token* readFunctionOrConstant(const char* cstr,size_t& ich ,size_t len, std::ostream& logStream) {
    logStream<<"readFunctionOrConstant: ";
    const token* tkn = nullptr;
    std::string name;
    char ch = cstr[ich];

    while ((isLetter(ch) || isDigit(ch)) && (ich < len)){
        name += ch;
        ++ich;
        ch = cstr[ich];
    }

    if (ch == '('){//this is function
        if (name == "sin")      tkn = &Sin;
        else if (name == "cos") tkn = &Cos;
        else if (name == "tan") tkn = &Tan;
        else if (name == "exp") tkn = &Exp;
        else if (name == "abs") tkn = &Abs;
    }
    else if (isOperator(ch) || isComma(ch) || isRightParenthesis(ch)){//this is constant
        if (name == "pi")     tkn = &pi;
        else if (name == "e") tkn = &e;
        else tkn = new variable(name);
    }
    else {
        throw("readFunctionOrConstant: " + name);
    }

    logStream<<"readFunctionOrConstant: "<<tkn->getName()<<endl;
    return tkn;
}

const token* readComma(const char* cstr, size_t& ich ,size_t len, std::ostream& logStream) {
    const token* tkn = nullptr;
    if (cstr[ich] == ',')
        tkn = &Comma;
    ++ich;
    return tkn;
}

const token* readNumber(const char* cstr, size_t& ich ,size_t len, std::ostream& logStream) {
    double res = 0;
    int dem = 1;
    char ch = cstr[ich];
    while(isDigit(ch) && (ich < len)) {
        res = res * 10 + cstr[ich] - '0';
        ++ich;
        ch = cstr[ich];
        if (isDemical(ch)){
            ++ich;
            ch = cstr[ich];
            dem *= 10;
        }
    }
    res /= dem;
    logStream<<"readNumber: "<<res<<endl;
    return new constant(res);
}

const token* readOperator(const char* cstr, size_t& ich ,size_t len, std::ostream& logStream) {
    const token *o1 = nullptr;
    char ch = cstr[ich];

    if (ch == '+') {
        o1 = &Plus;
    }
    else if (ch == '-') {
        int i = 1;
        while((ich-i >= 0) && isDelimiter(cstr[ich - i]))
            i++;
        if(((ich-i) == -1) || (cstr[ich-i] == '('))
            o1 = &UnaryMinus;
        else
            o1 = &Minus;
    }
    else if (ch == '*') {
        o1 = &Multiply;
    }
    else if (ch == '/') {
        o1 = &Divide;
    }
    else if (ch == '^') {
        o1 = &Power;
    }

    ++ich;
    logStream<<"readOperator: "<<o1->getName()<<endl;
    return o1;
}

const token* readParenthesis(const char* cstr, size_t& ich ,size_t len, std::ostream& logStream) {
    const token* tkn = nullptr;
    char ch = cstr[ich];

    if (ch == '(')      tkn = &lParenthesis;
    else if (ch == ')') tkn = &rParenthesis;

    logStream<<"readParenthesis: "<<tkn->getName()<<endl;
    ++ich;
    return tkn;

}

const token* readDelimiter(const char* cstr, size_t& ich ,size_t len, std::ostream& logStream) {
    logStream<<"skip delimiter = "<<"\""<<cstr[ich]<<"\""<<", code = "<<int(cstr[ich])<<endl;
    ++ich;
    return &Delimiter;
}
const token* readUndefined(const char* cstr, size_t& ich ,size_t len, std::ostream& logStream) {
    logStream<<"unknown symbol = "<<"\""<<cstr[ich]<<"\""<<", code = "<<int(cstr[ich])<<endl;
    ++ich;
    return &Undefined;
}

const token* getToken(const char* cstr, size_t& ich ,size_t len, std::ostream& logStream) {
    //logStream << "getToken: ich =  " << ich << endl;
    char ch = cstr[ich];
    const token* tkn = nullptr;

    if (isDigit(ch))             tkn = readNumber(cstr,ich ,len, logStream);
    else if (isOperator(ch))     tkn = readOperator(cstr,ich,len, logStream);
    else if (isLetter(ch))       tkn = readFunctionOrConstant(cstr,ich,len, logStream);
    else if (isParenthesis(ch))  tkn = readParenthesis(cstr,ich,len, logStream);
    else if (isComma(ch))        tkn = readComma(cstr,ich,len, logStream);
    else if (isDelimiter(ch))    tkn = readDelimiter(cstr,ich,len, logStream);
    else                         tkn = readUndefined(cstr,ich,len, logStream);

    return tkn;
}