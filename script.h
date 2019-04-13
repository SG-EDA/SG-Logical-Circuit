#pragma once
#include "node.h"

class script
{
private:
    static void run(vector<string> com);
    static void equState(string sen);
public:
    static map<string,line*> lineMap; //没有所有权
    static void eval(string sen);
    static void evalAll(string code)
    {
        auto com=help::split(code,"\n");
        for(auto i : com)
            eval(i);
    }
};
