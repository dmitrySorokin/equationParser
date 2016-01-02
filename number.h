#ifndef NUMBER_H
#define NUMBER_H

#include "token.h"
#include <cmath>
#include <string>

class number:public token{
public:
    number(double val):token(std::to_string(val)),value(val){;}
    virtual tokenType getType() const{return tokenType::_number; }
    inline const double getValue()const {return value;}
private:
    double value;
};


class constant:public token {
public:
    constant(double val):token(std::to_string(val)),value(val){;}
    virtual tokenType getType() const{return tokenType::_constant; }
    inline const double getValue()const {return value;}
private:
    double value;
};

class variable:public token{
public:
    variable(std::string name):token(name){;}
    virtual tokenType getType() const{return tokenType::_variable; }
    inline const double getValue()const {return value;}
    inline void setValue(double val) const{value = val;}
private:
    mutable double value;
};

const token* readNumber(const char* cstr,size_t& ich ,size_t len, std::ostream& logStream);




static const constant pi(M_PI);
static const constant e(M_E);
#endif
