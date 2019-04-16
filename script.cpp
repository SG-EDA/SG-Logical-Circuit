#include "script.h"

map<string,line*> script::lineMap;

void script::clear()
{
    nodeManager::deleteAll();
    lineMap.clear();
    line* trueLine=new line("1",(bool)1);
    lineMap["1"]=trueLine;
    line* falseLine=new line("0",(bool)0);
    lineMap["0"]=falseLine;
}

void script::runFile(vector<string> com)
{
    nodeManager::deleteAll();
    string path;
    if(com.size()==3)
       path=com[1]+":"+com[2];
    else
        path=com[1];

    string code=help::readTxt(path);
    cout<<code<<endl;
    cout<<"----- load:"<<path<<" -----"<<endl<<endl;
    script::evalAll(code);
    cout<<endl<<"-----end-----"<<endl;
}


void script::equExp(string sen)
{
    vector<string> com=help::split(sen,"=");
    vector<string> com2=help::split(com[1]," ");

    //先根据com2创建门电路
    gate *g;
    if(com2[0]=="and")
        g=new andGate();
    else if(com2[0]=="or")
        g=new orGate();
    else if(com2[0]=="not")
        g=new notGate();
    else if(com2[0]=="NA")
        g=new NAGate();
    else if(com2[0]=="NO")
        g=new NOGate();
    else if(com2[0]=="NOA")
        g=new NOAGate();
    else if(com2[0]=="xor")
        g=new xorGate();
    else if(com2[0]=="RS")
        g=new RSTri();
    else if(com2[0]=="RSC")
        g=new RSCTri();
    else if(com2[0]=="D")
        g=new DTri();
    else if(com2[0]=="JK")
        g=new JKTri();
    else if(com2[0]=="T")
        g=new TTri();
    else
        throw string("Unknown gate type");

    node *n=new node(g);
    for(uint i=1;i<com2.size();i++)
    {
        n->addInputLine(lineMap[com2[i]]);
    }

    //创建导线
    vector<string> com3=help::split(com[0],",");
    for(uint i=0;i<com3.size();i++)
    {
        if(com3[i]=="_")
            continue;
        else
        {
           line* newLine=new line(com3[i],n,i);
           lineMap[com3[i]]=newLine;
        }
    }
}

void script::colonExp(string sen)
{
    vector<string> com=help::split(sen,":");

    if(com[0]=="input")
    {
        line* newline=new line(com[1]);
        lineMap[com[1]]=newline;
        nodeManager::addInputLine(newline);
    }
    else if(com[0]=="output")
        nodeManager::addOutputLine(lineMap[com[1]]);
    else if(com[0]=="set")
    {
        vector<string> com2=help::split(com[1]," ");
        lineMap[com2[0]]->constVal=help::toint(com2[1]);
    }
    else if(com[0]=="load")
    {
        runFile(com);
    }
    else
        throw string("Unexpected line markup");
}

void script::commandExp(string sen)
{
    if(sen=="trueTable")
        nodeManager::trueTable();
    else if(sen=="statTable")
        nodeManager::trueTable(0,true);
    else if(sen=="gateNum")
        nodeManager::gateNum();
    else if(sen=="run")
        nodeManager::run();
    else if(sen=="stru")
        nodeManager::stru();
    else if(sen=="clear")
        script::clear();
    else if(sen=="middleVar")
        nodeManager::middleVar();
    else if(sen=="multiplexing")
        nodeManager::multiplexing();
    else if(sen=="resetTri")
        nodeManager::resetTri();
    else
        throw string("Unknow command");
}

void script::eval(string sen)
{
    if(sen=="")
        return;
    else if(sen.find(":")!=-1)
        colonExp(sen);
    else if(sen.find("=")!=-1)
        equExp(sen);
    else
        commandExp(sen);
}
