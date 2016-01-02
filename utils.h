#ifndef UTILS_H
#define UTILS_H



inline bool isDigit (const char ch) {
    return ch >= '0' && ch <= '9';
}

inline bool isLetter (const char ch) {
    return ch >= 'A' && ch <='Z' || ch >= 'a' && ch <= 'z';
}

inline bool isOperator (const char ch){
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

inline bool isDelimiter(const char ch){
    return ch == ' ';
}

inline bool isParenthesis(const char ch){
    return ch == '(' || ch == ')';
}

inline bool isLeftParenthesis(const char ch){
    return ch == '(';
}

inline bool isRightParenthesis(const char ch){
    return ch == ')';
}

inline bool isComma(const char ch){
    return ch == ',';
}

inline bool isDemical(const char ch){
    return ch == '.';
}



#endif