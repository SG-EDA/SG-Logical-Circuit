#pragma once
#include "gate.h"
#include "help.h"
#include <map>

class node;
class nodeManager;

class line
{
private:
    string name;
    node *n;
    uint sub;
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
        if(isEval==false)
        {
            this->result=g->calu(getInputPar());
            this->isEval=true;
        }
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
    static vector<node*> allTri;
    static void recuTriTrue(uint sub = 0)
    {
        tri* t=(tri*)(allTri[sub]->g);
        t->setQ(0);

        if(sub==allTri.size()-1)
            run(true);
        else
            recuTriTrue(sub+1);

        t->setQ(1);

        if(sub==allTri.size()-1)
            run(true);
        else
            recuTriTrue(sub+1);
    }

    static void resetChunk()
    {
        for(node* i : allNode)
            i->isEval=false;
    }

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
        allTri.clear();
    }

    static void addNode(node* n) { allNode.push_back(n); }
    static void addLine(line* n) { allLine.push_back(n); }
    static void addInputLine(line* n) { allInput.push_back(n); }
    static void addOutputLine(line* n) { allOutput.push_back(n); }
    static void addTri(node* n) { allTri.push_back(n); }

    static void gateNum()
    {
        cout<<"Gate:"<<allNode.size()<<endl;
        map<string,int> num;
        for(node* i : allNode)
            num[i->g->getName()]+=1;
        for(auto i : num)
            cout<<i.first<<":"<<i.second<<endl;
    }

    static void trueTable(uint sub = 0, bool staRecu=false)
    {
        auto conti=[&]()
        {
            if(sub==allInput.size()-1)
            {
                if(staRecu)
                    recuTriTrue();
                else
                    run();
            }
            else
                trueTable(sub+1,staRecu);
        };

        allInput[sub]->constVal=0;
        conti();
        allInput[sub]->constVal=1;
        conti();
    }

    static void run(bool outputSta=false)
    {
        resetChunk();
        for(line* i : allInput)
            cout<<"["<<i->getName()<<"]"<<i->get()<<" ";

        if(outputSta)
        {
            cout<<" || ";
            for(uint i=0;i<allTri.size();i++)
            {
                tri* t=(tri*)(allTri[i]->g);
                cout<<"["<<i<<"]"<<t->getQ()<<" ";
            }
        }

        cout<<" -> ";
        for(uint i=0;i<allOutput.size();i++)
            cout<<"["<<i<<"]"<<allOutput[i]->get()<<" ";

        cout<<endl;
    }

    static void resetTri()
    {
        for(node* i : allTri)
        {
            tri* t=(tri*)(i->g);
            t->setQ(0);
        }
    }

    static void stru()
    {
        for(line* i : allOutput)
            i->stru();
    }

    static void middleVar()
    {
        for(line* i : allLine)
            cout<<"["<<i->getName()<<"]"<<i->get()<<"/t";
        cout<<endl;
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

