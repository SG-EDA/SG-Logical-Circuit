#include "node.h"

bool line::get()
{
    if(isConst)
        return constVal;
    else
    {
        if(!n->isEval)
            n->eval();
        return n->result[sub];
    }
}

void line::stru(uint tabNum)
{
    if(isConst)
    {
        cout<<getName();
        return;
    }
    else
        n->stru(tabNum);
}

node::node(gate* g) : g(g)
{
    nodeManager::addNode(this);
}

node::~node()
{
    delete g;
    for(unsigned int i=0;i<inputLine.size();i++)
        delete inputLine[i];
}
