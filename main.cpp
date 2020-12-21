#include <iostream>
#include "script.h"

int main()
{
    script s;
    while(1)
    {
        string input;
        printf(">>");
        getline(cin,input);
        try
        {
            s.eval(input);
        }
        catch(string e)
        {
            cout<<e<<endl;
        }
    }
}
