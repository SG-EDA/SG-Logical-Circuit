#include "script.h"

map<string,line*> script::lineMap;

void script::run(vector<string> com)
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


void script::equState(string sen)
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
    else if(com2[0]=="Xor")
        g=new XorGate();
    else if(com2[0]=="RS")
        g=new RSTri();
    else if(com2[0]=="RSC")
        g=new RSCTri();
    else if(com2[0]=="D")
        g=new DTri();
    else if(com2[0]=="JK")
        g=new JKTri();
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
           line* newLine=new line(n,i);
           lineMap[com3[i]]=newLine;
        }
    }
}


void script::eval(string sen)
{
    if(sen=="")
        return;
    if(sen.find(":")!=-1)
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
            run(com);
        }
        else
            throw string("Unexpected line markup");
    }
    else if(sen.find("=")!=-1)
    {
        equState(sen);
    }
    else
    {
        if(sen=="trueTable")
            nodeManager::trueTable();
        else if(sen=="gateNum")
            nodeManager::gateNum();
        else if(sen=="run")
            nodeManager::output();
        else if(sen=="stru")
            nodeManager::stru();
        else if(sen=="clear")
            nodeManager::deleteAll();
        else
            throw string("Unknow command");
    }
}
