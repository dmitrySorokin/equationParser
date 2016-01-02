#include <algorithm>
#include "equationParser.h"
#include "operator.h"
#include "function.h"
#include "exceptions.h"

using namespace std;

string equationParser::parse(string str)
{
    cout<<"equationParer: parse \n";
    logStream << "expression = " << str << endl;
    const char *data = str.data();
    size_t len = str.length();
    size_t ich = 0;
    tStack Stack;

    try {
        while (ich < len) {
            const token *tkn = getToken(data,ich ,len, logStream);
            //logStream<<"parse: got token: "<<tkn->getName()<<endl;

            if (tkn->getType() == tokenType::_constant) {
                //logStream<<"parse: number\n";
                Queue.push(tkn);
            }
            else if (tkn->getType() == tokenType::_variable){
                Queue.push(tkn);
                Vector.push_back(tkn);
            }
            else if (tkn->getType() == tokenType::_function) {
                //logStream<<"parse: function\n";
                Stack.push(tkn);
            }
            else if (tkn->getType() == tokenType::_comma) {
                //logStream<<"parse comma\n";
                while (!Stack.empty() && (Stack.top()->getType() != tokenType::_leftParenthesis)) {
                    logStream<<"push operator "<<tkn->getName()<<endl;
                    Queue.push(tkn);
                    Stack.pop();
                }
                if (Stack.top()->getType() != tokenType::_leftParenthesis){
                    throw(bad_comma + Stack.top()->getName());
                }
            }
            else if (tkn->getType() == tokenType::_operator) {
                //logStream<<"parse operator\n";
                const baseOperator *o1 = static_cast<const baseOperator *>(tkn);
                while (!Stack.empty() && (Stack.top()->getType() == tokenType::_operator)) {
                    const baseOperator *o2 = static_cast<const baseOperator *>(Stack.top());
                    if (o1->getAssociativity() == associativity::left && o1->getPriority() <= o2->getPriority() ||
                        o1->getAssociativity() == associativity::right && o1->getPriority() < o2->getPriority()) {
                        logStream << "push operator " << o2->getName() << endl;
                        Queue.push(o2);
                        Stack.pop();
                    }
                    else
                    {
                        break;
                    }
                }
                Stack.push(o1);
            }
            else if (tkn->getType() == tokenType::_leftParenthesis) {
                //logStream<<"parse left parenthesis\n";
                Stack.push(tkn);
            }
            else if (tkn->getType() == tokenType::_rightParenthesis) {
                //logStream<<"parse right parenthesis\n";

                while (!Stack.empty() && Stack.top()->getType() != tokenType::_leftParenthesis) {
                    const baseOperator *op = static_cast<const baseOperator *>(Stack.top());
                    logStream << "push operator " << op->getName() << endl;
                    Queue.push(op);
                    Stack.pop();
                }
                if (Stack.empty()){
                    throw(bad_parentheses);
                }
                Stack.pop();
                if (!Stack.empty() && Stack.top()->getType() == tokenType::_function) {
                    const baseFunction *func = static_cast<const baseFunction *>(Stack.top());
                    Queue.push(func);
                    Stack.pop();
                }
            }
            else if (tkn->getType() == tokenType::_delimiter) {
                continue;
            }
            else {
                logStream<<"parse: unknown token: "<<tkn->getName()<<endl;
                throw(tkn->getName());
            }
        }

        while (!Stack.empty()) {
            const token* top = Stack.top();
            if (top->getType() != tokenType::_operator) {
                throw(bad_parentheses);
            }
            const baseOperator* op = static_cast<const baseOperator*>(top);
            Stack.pop();
            logStream<<"push operator "<<op->getName()<<endl;
            Queue.push(op);
        }

        double res =  Calculate();
        return to_string(res);
    }
    catch(string str) {
        logStream<<"catch exception: "<<str<<endl;
        clean();
        return str;
    }
}


const double equationParser::Calculate() {
    logStream<<"Calculate: queue size is "<<Queue.size()<<endl;
    dStack rStack;
    for_each(Vector.begin(),Vector.end(),[](const token* tkn){
        auto var = static_cast<const variable*>(tkn);
        cout<<"enter value for variable: "<<var->getName()<<endl;
        double val;
        cin >> val;
        var->setValue(val);
    });
    while (!Queue.empty()) {
        const token *tkn = Queue.front();
        while(!Queue.empty() ) {
            tkn = Queue.front();
            if (tkn->getType() == tokenType::_constant || tkn->getType() == tokenType::_variable) {
                rStack.push(static_cast<const number*>(tkn)->getValue());
                cout<<tkn->getName()<<endl;
            }
            else if((tkn->getType() == tokenType::_operator) || (tkn->getType() == tokenType::_function)) {
                cout<<tkn->getName()<<endl;
                break;
            }

            Queue.pop();
        }

        if(Queue.empty()) break;
        if (tkn->getType() == tokenType::_function) {
            const baseFunction *func = static_cast<const baseFunction *>(tkn);
            Queue.pop();
            func->apply(rStack,logStream);

        }
        else if (tkn->getType() == tokenType::_operator) {
            const baseOperator *op = static_cast<const baseOperator*>(tkn);
            Queue.pop();
            op->apply(rStack, logStream);
        }
    }
    return rStack.top();
}