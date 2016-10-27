#include <iostream>
#include <fstream>
#include "equationParser.h"

using namespace std;

int main()
{

    string logFile = "/home/dmitry/work/equationParser/log.txt";
    string eqFile = "/home/dmitry/work/equationParser/input.txt";
    ifstream in (eqFile);
    if (in.is_open())
    {
        string str;
        getline(in,str);
        equationParser& parser = equationParser::instance(logFile);
        string res = parser.parse(str);
        cout<<"result = "<<res<<endl;
    }

    return 0;
}
