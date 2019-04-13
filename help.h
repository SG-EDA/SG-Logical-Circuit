#include <iostream>
using namespace std;

class help
{
public:
    static void tab(unsigned int num=0)
    {
        for(unsigned int i=0;i<num;i++)
            cout<<"   ";
    }
};
