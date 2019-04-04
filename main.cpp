#include <iostream>
#include "gate.h"

int main()
{
    for(int q=0;q<=1;q++)
    for(int r=0;r<=1;r++)
    for(int s=0;s<=1;s++)
    {
        RSTri rstg;
        rstg.setQ(q);

        blist par;
        par.push_back(r);
        par.push_back(s);

        par=rstg.calu(par);
        cout<<"q"<<q<<" r"<<r<<" s"<<s<<" result"<<par[0]<<endl;
    }

    cout<<"next"<<endl;

    for(int cp=0;cp<=1;cp++)
    for(int q=0;q<=1;q++)
    for(int r=0;r<=1;r++)
    for(int s=0;s<=1;s++)
    {
        RSCTri rstg;
        rstg.setQ(q);

        blist par;
        par.push_back(r);
        par.push_back(s);
        par.push_back(cp);

        par=rstg.calu(par);
        cout<<"cp"<<cp<<" q"<<q<<" r"<<r<<" s"<<s<<" result"<<par[0]<<endl;
    }
}
