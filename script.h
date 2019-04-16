#pragma once
#include "node.h"

class script
{
private:
    static void runFile(vector<string> com);
    static void equExp(string sen);
    static void colonExp(string sen);

public:
    static map<string,line*> lineMap; //没有所有权
    static void clear();
    static void eval(string sen);
    static void evalAll(string code)
    {
        auto com=help::split(code,"\n");
        for(auto i : com)
            eval(i);
    }
};
