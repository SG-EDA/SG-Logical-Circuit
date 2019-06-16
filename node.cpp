#include "node.h"

list<node*> nodeManager::allNode;
vector<line*> nodeManager::allInput;
vector<line*> nodeManager::allOutput;
list<line*> nodeManager::allLine;
vector<node*> nodeManager::allTri;

line::line(string name, node *n, uint sub) : name(name), n(n), sub(sub)
{
    nodeManager::addLine(this);
}

void line::delayedConstruction(node *n, uint sub)
{
    this->n=n;
    this->sub=sub;
}

bool line::getIsEvaling()
{
    if(isConst)
        return false;
    else
        return this->n->isEvaling;
}

bool line::get()
{
    if(isConst)
        return constVal;
    else
        return n->eval()[sub];
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
    if(g->getIsTri())
        nodeManager::addTri(this);
}
