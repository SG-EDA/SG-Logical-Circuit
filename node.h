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
    string name;
    bool isConst=false;
public:
    bool constVal;

    line(string name, node *n,uint sub=0);
    line(string name,bool constVal=0) : name(name), isConst(true), constVal(constVal) {}
    bool get();
    string getName() { return this->name; }
    void stru(uint tabNum=0);
};


class node
{
private:
    blist getInputPar()
    {
        blist par;
        for(line* i : inputLine)
            par.push_back(i->get());
        return par;
    }

public:
    vector<line*> inputLine; //与g的input个数相等。每个连接需指明插槽位
    bool isEval=false;
    blist result;
    gate *g;

    node(gate* g,bool count=true);
    ~node() { delete g; }
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
    static list<line*> allLine;
    static vector<line*> allInput;
    static vector<line*> allOutput;

public:
    static void deleteAll()
    {
        for(line* i : allLine)
            delete i;
        for(node* i : allNode)
            delete i;
        allNode.clear();
        allLine.clear();
        allInput.clear();
        allOutput.clear();
    }

    static void addNode(node* n) { allNode.push_back(n); }
    static void addLine(line* n) { allLine.push_back(n); }
    static void addInputLine(line* n) { allInput.push_back(n); }
    static void addOutputLine(line* n) { allOutput.push_back(n); }

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
            run();
        else
            trueTable(sub+1);

        allInput[sub]->constVal=true;

        if(sub==allInput.size()-1)
            run();
        else
            trueTable(sub+1);
    }

    static void run()
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

    static void stru()
    {
        for(line* i : allOutput)
            i->stru();
    }

    static void middleVar()
    {
        for(line* i : allLine)
            cout<<"["<<i->getName()<<"]"<<i->get()<<endl;
    }

    static void multiplexing()
    {
        uint lineNum=0;
        map<string,int>result;
        for(node* i : allNode)
        {
            for(line* j : i->inputLine)
                result[j->getName()]++;
        }
        for(auto i : result)
        {
            cout<<"["<<i.first<<"]"<<i.second<<"\t"; 
            lineNum+=i.second;
        }
        cout<<endl<<"lineNum:"<<lineNum<<endl;
    }
};

