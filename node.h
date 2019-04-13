#pragma once
#include "gate.h"
#include "help.h"
#include <map>

class node;
class nodeManager;

class line
{
private:
    node *n;
    uint sub;
    bool isConst=false;
    string name;
public:
    bool constVal;

    line(node *n,uint sub=0) : n(n), sub(sub) {}
    line(string name,bool constVal=0) : name(name), isConst(true), constVal(constVal) {}
    bool get();
    string getName() { return this->name; }
    //~line() { delete this->n; } //node只被管理器析构，node析构同时析构自己的line
    void stru(uint tabNum=0);
};


class node
{
private:
    vector<line*> inputLine; //与g的input个数相等。每个连接需指明插槽位
    blist getInputPar()
    {
        blist par;
        for(line* i : inputLine)
            par.push_back(i->get());
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

    void stru(uint tabNum=0)
    {
        cout<<g->getName()<<"-";
        for(uint i=0;i<inputLine.size();i++)
        {
            inputLine[i]->stru(tabNum+1);
            if(i!=inputLine.size()-1)
            {
                cout<<endl;
                help::tab(tabNum+1);
            }
        }
        if(tabNum==0)
            cout<<endl;
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

    static void trueTable(uint sub = 0)
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
        for(line* i : allInput)
            cout<<"["<<i->getName()<<"]"<<i->get()<<" ";
        cout<<" -> ";
        for(uint i=0;i<allOutput.size();i++)
            cout<<"["<<i<<"]"<<allOutput[i]->get()<<" ";
        cout<<endl;
    }

    static void reset()
    {
        for(node* i : allNode)
            i->isEval=false;
    }
};

