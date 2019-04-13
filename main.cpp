#include <iostream>
#include "script.h"

int main()
{
    while(1)
    {
        string input;
        printf(">>");
        getline(cin,input);
        script::eval(input);
    }
}
