#pragma once
#include "node.h"
#include "lefParser.h"

class layout
{
private:
    nodeManager* manager;
    lefParser lp;
    int width;
    int heigh;

public:
    layout(nodeManager* manager, lefParser lp, int width, int heigh) :
        manager(manager), lp(lp), width(width), heigh(heigh)
    {
        //进行布局
    }
};
