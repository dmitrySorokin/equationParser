#ifndef EQUATIONPARSER_H
#define EQUATIONPARSER_H

#include <fstream>
#include <iostream>
#include "number.h"
#include "token.h"
#include "operator.h"
#include "delimiter.h"
#include "function.h"
#include <queue>
#include <stack>
#include <string>
#include <vector>

class equationParser {
public:
    static equationParser& instance(std::string file) {
        static equationParser parser(file);
        return parser;
    }
    std::string parse(std::string str);
    ~equationParser(){
        clean();
    }

private:
    tQueue Queue;
    tVector Vector;
    std::ofstream logStream;
    std::vector<const token*> specialTokens;
    equationParser(std::string file):logStream(file) {
        std::cout<<"construct parser \n";
        specialTokens.push_back(new operatorPlus);
        specialTokens.push_back(new operatorMinus);
        specialTokens.push_back(new operatorMultiply);
        specialTokens.push_back(new operatorDivide);
        specialTokens.push_back(new operatorPower);

        specialTokens.push_back(new sinus);
        specialTokens.push_back(new cosinus);
        specialTokens.push_back(new tangens);

        specialTokens.push_back(new number(M_PI));
        specialTokens.push_back(new number(M_E));

        specialTokens.push_back(new delimiter);
        specialTokens.push_back(new comma);

        specialTokens.push_back(new undefined);
    }
    void clean(){

    }
    const double Calculate();
};

#endif
