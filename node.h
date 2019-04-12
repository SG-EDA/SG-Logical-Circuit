#pragma once
#include "gate.h"

class node
{
    public:
    vector<node*> outputNode; //与g的output个数相等。每个连接需指明插槽位
    gate *g;

    ~node()
    {
        delete g;
        for(unsigned int i=0;i<allpar.size();i++)
            delete allpar[i];
    }

    blist calu(blist input)
    {
        blist result=g->calu(input);
    }
}
