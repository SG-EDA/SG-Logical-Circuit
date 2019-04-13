#pragma once
#include "gate.h"
#include <map>

class node;
class nodeManager;

class line
{
private:
    node *n;
    unsigned int sub;
    bool isConst=false;
public:
    bool constVal;

    line(node *n,unsigned int sub=0) : n(n), sub(sub) {}
    line(bool constVal=0) : isConst(true), constVal(constVal) {}
    bool get();
    //~line() { delete this->n; } //node只被管理器析构，node析构同时析构自己的line
};


class node
{
private:
    vector<line*> inputLine; //与g的input个数相等。每个连接需指明插槽位
    blist getInputPar()
    {
        blist par;
        for(line* l : inputLine)
            par.push_back(l->get());
        return par;
    }

public:
    bool isEval=false;
    blist result;
    gate *g;

    node(gate* g);
    ~node();
    void addInputLine(line* l) { inputLine.push_back(l); }

    blist eval()
    {
        this->result=g->calu(getInputPar());
        this->isEval=true;
        return this->result;
    }
};


class nodeManager
{
private:
    static list<node*> allNode;
    static vector<line*> allInput;
    static vector<line*> allOutput;

public:
    static void deleteAllNode()
    {
        for(line* i : allOutput)
            delete i;
        for(node* i : allNode)
            delete i;
    }

    static void addNode(node* n) { allNode.push_back(n); }
    static void addInputLine(line* n) { allInput.push_back(n); }
    static void addOutputNode(line* n) { allOutput.push_back(n); }

    static void gateNum()
    {
        cout<<"Gate:"<<allNode.size()<<endl;
        map<string,int> num;
        for(node* i : allNode)
            num[i->g->getName()]+=1;
        for(auto i : num)
            cout<<i.first<<":"<<i.second<<endl;
    }

    static void trueTable(unsigned int sub = 0)
    {
        allInput[sub]->constVal=false;

        if(sub==allInput.size()-1)
            output();
        else
            trueTable(sub+1);

        allInput[sub]->constVal=true;

        if(sub==allInput.size()-1)
            output();
        else
            trueTable(sub+1);
    }

    static void output()
    {
        reset();
        for(unsigned int i=0;i<allInput.size();i++)
            cout<<"["<<i<<"]"<<allInput[i]->get()<<" ";
        cout<<" -> ";
        for(unsigned int i=0;i<allOutput.size();i++)
            cout<<"["<<i<<"]"<<allOutput[i]->get()<<" ";
        cout<<endl;
    }

    static void reset()
    {
        for(node* i : allNode)
            i->isEval=false;
    }
};

