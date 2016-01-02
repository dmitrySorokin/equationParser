#include <iostream>
#include <fstream>
#include "equationParser.h"

using namespace std;

template <typename T>
void func(T t)
{
    cout<<t<<endl;
}

template <typename  T, typename... Args>
void func(T t, Args...args)
{
    cout<<t<<endl;
    func(args...);
};

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



    cout << "Hello, World!" << endl;
    return 0;
}