#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum class tokenType {
    _number,
    _constant,
    _variable,
    _function,
    _comma,
    _operator,
    _leftParenthesis,
    _rightParenthesis,
    _delimiter,
    _undefType

};

class token {
public:
    token(std::string nm):name(nm){;}
    virtual tokenType getType() const  = 0;
    const std::string getName() const {return name;}
private:
    std::string name;
};

const token* getToken(const char* cstr,size_t& ich ,size_t len, std::ostream& logStream);

#include <queue>
#include <stack>
#include <vector>

typedef std::queue<const token*> tQueue;
typedef std::stack<const token*> tStack;
typedef std::vector<const token*> tVector;
typedef std::stack<double> dStack;

#endif
