#include <iostream>
#include "script.h"

int main()
{
    while(1)
    {
        string input;
        printf(">>");
        getline(cin,input);
        try
        {
            script::eval(input);
        }
        catch(string e)
        {
            cout<<e<<endl;
        }
    }
}
