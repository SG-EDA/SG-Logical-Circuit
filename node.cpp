#include "node.h"

list<node*> nodeManager::allNode;
vector<line*> nodeManager::allInput;
vector<line*> nodeManager::allOutput;
list<line*> nodeManager::allLine;

line::line(string name, node *n, uint sub) : name(name), n(n), sub(sub)
{
    nodeManager::addLine(this);
}

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

node::node(gate* g, bool count) : g(g)
{
    if(count)
        nodeManager::addNode(this);
}
