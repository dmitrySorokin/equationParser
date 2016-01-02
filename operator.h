#ifndef OPERATOR_H
#define OPERATOR_H

#include "number.h"
#include "token.h"
#include "exceptions.h"
#include <string>
#include <iostream>
#include <stack>
#include <cmath>

using std::endl;

enum class priority
{
    first,
    second,
    third
};

enum class associativity
{
    left,
    right
};

class baseOperator:public token {
public:
    baseOperator(std::string nm,priority pr,associativity ass):
            token(nm),
            prior(pr),
            assoc(ass)
            {;}
    virtual tokenType getType() const{return tokenType::_operator;}
    const priority getPriority() const {return prior;}
    const associativity getAssociativity() const {return assoc;}
    virtual void apply(std::stack<double>& rStack, std::ostream& logStream) const  = 0;

private:
    priority prior;
    associativity assoc;

};




class operatorUnaryMinus:public baseOperator{
public:
    operatorUnaryMinus():baseOperator(" -u ",priority::first,associativity::left){;}
    virtual void apply(std::stack<double>& rStack, std::ostream& logStream) const {
        if (rStack.size() < 1)
            throw(bad_stack + getName());

        const double a = rStack.top();
        rStack.pop();
        logStream<<"a = "<<a;
        double res = -a;
        logStream<<", -a = "<<res<<endl;
        rStack.push(res);

    }
};

class operatorPlus:public baseOperator{
public:
    operatorPlus():baseOperator(" + ",priority::first,associativity::left){;}
    virtual void apply(std::stack<double>& rStack, std::ostream& logStream) const {
        if (rStack.size() < 2)
            throw(bad_stack + getName());

        const double b = rStack.top();
        rStack.pop();
        const double a = rStack.top();
        rStack.pop();
        logStream<<"a = "<<a<<", b = "<<b;
        double res = a + b;
        logStream<<", a + b = "<<res<<endl;
        rStack.push(res);

    }
};

class operatorMinus:public baseOperator{
public:
    operatorMinus():baseOperator(" - ",priority::first,associativity::left){;}
    virtual void apply(std::stack<double>& rStack, std::ostream& logStream) const {
        if (rStack.size() < 2)
            throw(bad_stack + getName());

        const double b = rStack.top();
        rStack.pop();
        const double a = rStack.top();
        rStack.pop();
        logStream<<"a = "<<a<<", b = "<<b;
        double res = a - b;
        logStream<<", a - b = "<<res<<endl;
        rStack.push(res);
    }
};

class operatorMultiply:public baseOperator{
public:
    operatorMultiply():baseOperator(" * ",priority::second,associativity::left){;}
    virtual void apply(std::stack<double>& rStack, std::ostream& logStream) const {
        if (rStack.size() < 2)
            throw(bad_stack + getName());

        const double b = rStack.top();
        rStack.pop();
        const double a = rStack.top();
        rStack.pop();
        logStream<<"a = "<<a<<", b = "<<b;
        double res = a * b;
        logStream<<", a * b = "<<res<<endl;
        rStack.push(res);

    }
};

class operatorDivide:public baseOperator{
public:
    operatorDivide():baseOperator(" / ",priority::second,associativity::left){;}
    virtual void apply(std::stack<double>& rStack, std::ostream& logStream) const {
        if (rStack.size() < 2)
            throw(bad_stack + getName());

        const double b = rStack.top();
        rStack.pop();
        const double a = rStack.top();
        rStack.pop();
        if (b == 0) {
            throw (bad_operator + getName());
        }
        else {
            logStream << "a = " << a << ", b = " << b;
            double res = a / b;
            logStream << ", a / b = " << res << endl;
            rStack.push(res);
        }
        logStream<<"operator / end\n";
    }
};

class operatorPower:public baseOperator{
public:
    operatorPower():baseOperator(" ^ ",priority::third,associativity::right){;}
    virtual void apply(std::stack<double>& rStack, std::ostream& logStream) const {
        if (rStack.size() < 2)
            throw(bad_stack + getName());

        const double b = rStack.top();
        rStack.pop();
        const double a = rStack.top();
        rStack.pop();
        if (a < 0) {
            logStream<<"cat\n";
            throw (bad_operator + getName());
        }


        logStream << "a = " << a << ", b = " << b;
        double res = pow(a, b);
        logStream << ", a ^ b = " << res << endl;
        rStack.push(res);

        }

};

const static operatorPlus Plus;
const static operatorMinus Minus;
const static operatorMultiply Multiply;
const static operatorDivide Divide;
const static operatorPower Power;
const static operatorUnaryMinus UnaryMinus;

const token* readOperator(const char* cstr, size_t& ich ,size_t len, std::ostream& logStream);

#endif
