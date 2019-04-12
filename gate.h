#pragma once
#include <vector>
using namespace std;

typedef vector<bool> blist;

class gate
{
protected:
    unsigned int inputNum;
    unsigned int outputNum=1;
public:
    virtual blist realCalu(blist par)=0;
    gate(unsigned int inputNum, unsigned int outputNum=1) : inputNum(inputNum), outputNum(outputNum) {}
    unsigned int getInputNum() { return inputNum; }
    unsigned int getOutputNum() { return outputNum; }

    blist calu(blist par)
    {
        if(this->inputNum!=par.size())
            throw string("The number of parameters does not match");
        else
            return realCalu(par);
    }
};

class andGate : public gate
{
public:
    andGate() : gate(2) {}

    virtual blist realCalu(blist par)
    {
        blist result;
        result.push_back(par[0]&&par[1]);
        return result;
    }
};

class orGate : public gate
{
public:
    orGate() : gate(2) {}

    virtual blist realCalu(blist par)
    {
        blist result;
        result.push_back(par[0]||par[1]);
        return result;
    }
};

class notGate : public gate
{
public:
    notGate() : gate(1) {}

    virtual blist realCalu(blist par)
    {
        par[0]=!par[0];
        return par;
    }
};

class NAGate : public gate
{
public:
    NAGate() : gate(2) {}

    virtual blist realCalu(blist par)
    {
        andGate g1;
        notGate g2;
        par=g1.calu(par);
        return g2.calu(par);
    }
};

class NOGate : public gate
{
public:
    NOGate() : gate(2) {}

    virtual blist realCalu(blist par)
    {
        orGate g1;
        notGate g2;
        par=g1.calu(par);
        return g2.calu(par);
    }
};

class NOAGate : public gate
{
public:
    NOAGate() : gate(4) {}

    virtual blist realCalu(blist par)
    {
        andGate a1;
        andGate a2;
        orGate g1;
        notGate g2;

        blist par1;
        par1.push_back(par[0]);
        par1.push_back(par[1]);
        blist par2;
        par2.push_back(par[2]);
        par2.push_back(par[3]);

        //长度都为1
        par1=a1.calu(par1);
        par2=a2.calu(par2);

        blist r;
        r.push_back(par1[0]);
        r.push_back(par2[0]);

        r=g1.calu(r);
        return g2.calu(r);
    }
};

class XorGate : public gate
{
public:
    XorGate() : gate(2) {}

    virtual blist realCalu(blist par)
    {
        blist result;
        if(par[0]==par[1])
            result.push_back(1);
        else
            result.push_back(0);
        return result;
    }
};

class RSTri : public gate
{
private:
    blist sta;

public:
    RSTri() : gate(2,2)
    {
        sta.push_back(0);
        sta.push_back(1);
    }
    void setQ(bool q)
    {
        sta[Q]=q;
        sta[Q2]=!q;
    }
    bool getQ() { return sta[Q]; }

    const unsigned int R=0;
    const unsigned int S=1;

    const unsigned int Q=0;
    const unsigned int Q2=1;

    virtual blist realCalu(blist par) //第一个是r第二个是s。返回值也是对应，第一个Q2第二个Q
    {

        if(par[R]==0&&par[S]==0) {} //结果不确定
        else if(par[R]==0&&par[S]==1)
        {
            setQ(0);
        }
        else if(par[R]==1&&par[S]==0)
        {
            setQ(1);
        }
        return sta;
    }
};

class RSCTri : public gate
{
private:
    RSTri rstg;

public:
    RSCTri() : gate(3,2) {}
    void setQ(bool q) { rstg.setQ(q); }
    bool getQ() { return rstg.getQ(); }

    const unsigned int R=0;
    const unsigned int S=1;
    const unsigned int CP=2;

    virtual blist realCalu(blist par)
    {
        blist r;
        if(par[CP]==1)
        {
            //按书上电路，连的是与非门，所以这里取非
            r.push_back(!par[R]);
            r.push_back(!par[S]);
        }
        else
        {
            r.push_back(0);
            r.push_back(0);
        }
        return rstg.calu(r);
    }
};

class DTri : public gate
{
private:
    blist sta;

public:
    DTri() : gate(2)
    {
        sta.push_back(0);
    }

    const unsigned int D=0;
    const unsigned int CP=1;

    virtual blist realCalu(blist par)
    {
        if(par[CP]==1)
            sta[D]=par[D];
        return sta;
    }
};

class JKTri : public gate
{
private:
    blist sta;

public:
    JKTri() : gate(3,2)
    {
        sta.push_back(0);
        sta.push_back(1);
    }
    void setQ(bool q)
    {
        sta[Q]=q;
        sta[Q2]=!q;
    }
    bool getQ() { return sta[Q]; }

    const unsigned int J=0;
    const unsigned int K=1;
    const unsigned int CP=2;

    const unsigned int Q=0;
    const unsigned int Q2=1;

    virtual blist realCalu(blist par)
    {
        if(par[CP]==1)
        {
            if(par[J]==0&&par[K]==1)
            {
                setQ(0);
            }
            else if(par[J]==1&&par[K]==0)
            {
                setQ(1);
            }
            else if(par[J]==1&&par[K]==1)
            {
                setQ(!par[Q]);
            }
        }
        return sta;
    }
};
