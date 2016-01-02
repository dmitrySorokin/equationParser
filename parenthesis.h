#ifndef PARENTHESIS_H
#define PARENTHESIS_H

#include "token.h"

class leftParenthesis:public token
{
public:
    leftParenthesis():token("("){;}
    virtual tokenType getType() const
    {
        return tokenType::_leftParenthesis;
    }
};

class rightParenthesis:public token
{
public:
    rightParenthesis():token(")"){;}
    virtual tokenType getType() const
    {
        return tokenType::_rightParenthesis;
    }
};

const static leftParenthesis lParenthesis;
const static rightParenthesis rParenthesis;


const token* readParenthesis(const char* cstr, size_t& ich ,size_t len, std::ostream& logStream);

#endif
