#pragma once
#include "gate.h"

class line
{
private:
    node *n;
    unsigned int sub;
public:
    line(node *n,unsigned int sub) : n(n), sub(sub) {}
    bool get()
    {
        if(!n->isEval)
            n->eval();
        return n->result[sub];
    }
};

class node
{
private:
    blist getInputPar()
    {
        blist par;
        for(line* l : inputNode)
            par.push_back(l->get());
        return par;
    }

public:
    bool isEval=false;
    vector<line*> inputNode; //与g的input个数相等。每个连接需指明插槽位
    blist result;
    gate *g;

    node(gate* g) : g(g) {}

    ~node()
    {
        delete g;
        for(unsigned int i=0;i<inputNode.size();i++)
            delete inputNode[i];
    }

    blist eval()
    {
        this->result=g->calu(getInputPar());
        this->isEval=true;
    }
}
