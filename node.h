#pragma once
#include "gate.h"

class node
{
    public:
    vector<node*> allpar; //每个node的求值结果是blist，里面可能有一个或多个变量
    gate *g;
    unsigned int sub=-1;

    ~node()
    {
        delete g;
        for(unsigned int i=0;i<allpar.size();i++)
            delete allpar[i];
    }

    blist calu()
    {

    }
}
