#ifndef FUNCTION_H
#define FUNCTION_H

#include <cmath>
#include <iostream>
#include <stack>
#include "utils.h"
#include "token.h"
#include "number.h"
#include "exceptions.h"

using std::endl;

class baseFunction:public token{
public:
    baseFunction(std::string nm):token(nm){;}
    virtual tokenType getType() const{return tokenType::_function; }
    virtual void apply(dStack& rStack, std::ostream& logStream) const  = 0;
};

class comma:public token{
public:
    comma():token(","){;}
    virtual tokenType  getType() const {return tokenType::_comma; }
};

class sinus:public baseFunction {
public:
    sinus():baseFunction("sin"){;}
    virtual void apply(dStack& rStack, std::ostream& logStream) const {
        if (rStack.size() < 1) throw(bad_argument + getName());
        const double a = rStack.top();
        rStack.pop();
        logStream<<"sinus\n";
        logStream<<"sin("<<a<<") = ";
        double res = sin(a);
        logStream<<res<<endl;
        rStack.push(res);
    }
};

class cosinus:public baseFunction {
public:
    cosinus():baseFunction("cos"){;}
    virtual void apply(dStack& rStack, std::ostream& logStream) const {
        if (rStack.size() < 1) throw(bad_argument + getName());
        const double a = rStack.top();
        rStack.pop();
        logStream<<"cos("<<a<<") = ";
        const double res = cos(a);
        logStream<<a<<endl;
        rStack.push( res);
    }
};

class tangens:public baseFunction {
public:
    tangens():baseFunction("tan"){;}
    virtual void apply(dStack& rStack, std::ostream& logStream) const {
            if (rStack.size() < 1) throw (bad_argument + getName());
            const double a = rStack.top();
            rStack.pop();
            logStream << "tan(" << a << ") = ";
            const double res = tan(a);
            logStream << a << endl;
            rStack.push(res);
    }

};

class exponent:public baseFunction {
public:
    exponent():baseFunction("exp"){;}
    virtual void apply(dStack& rStack, std::ostream& logStream) const {
            if (rStack.size() < 1) throw (bad_argument + getName());
            const double a = rStack.top();
            rStack.pop();
            logStream << "exp(" << a << ") = ";
            const double res = exp(a);
            logStream << a << endl;
            rStack.push(res);
    }

};

class absolut:public baseFunction {
public:
    absolut():baseFunction("abs"){;}
    virtual void apply(dStack& rStack, std::ostream& logStream) const {
        if (rStack.size() < 1) throw(bad_argument + getName());
        const double a = rStack.top();
        rStack.pop();
        logStream<<"abs("<<a<<") = ";
        double res = fabs(a);
        logStream<<a<<endl;
        rStack.push( res);
    }
};

const static comma Comma;
const static sinus Sin;
const static cosinus Cos;
const static tangens Tan;
const static exponent Exp;
const static absolut Abs;


const token* readFunctionOrConstant(const char* cstr,size_t& ich ,size_t len, std::ostream& logStream);


const token* readComma(const char* cstr,size_t& ich ,size_t len, std::ostream& logStream);


#endif
