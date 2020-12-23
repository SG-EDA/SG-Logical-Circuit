#pragma once
#include "node.h"
#include "lefParser.h"
#include "lefParser.h"
#include <map>
using namespace std;

class element
{
private:
    node* elementNode;
    LEF::cell elementCell;
public:
    element(node* elementNode,LEF::cell elementCell)
    {
        this->elementNode=elementNode,this->elementCell=elementCell;
    }
    node* getnode()
    {
        return this->elementNode;
    }
    LEF::cell getCell()
    {
        return this->elementCell;
    }
};

class layout
{
private:
    nodeManager* manager;
    lefParser lp;
    int width;
    int heigh;

public:
    float getInterfaceManhattanDistance(pinRect a,pinRect b)//计算接口间曼哈顿距离
    {
        float x1,y1,x2,y2;
        tie(x1,y1)=a.getMidPos();
        tie(x2,y2)=b.getMidPos();
        return abs(x1-x2)+abs(y1-y2);//C++11支持abs运算浮点数  如有问题应换fabs
    }
    //按照建议间距摆放矩形***未实现
    layout(nodeManager* manager, lefParser lp, int width, int heigh) :
        manager(manager), lp(lp), width(width), heigh(heigh)//未完成
    {
        float Recomspacing=1.0;//目前假设的建议间距  后续调用lp中的建议间距进行替换
        float focus[]={float(width)/2,float(heigh)/2};//第一个元件应放在版图中心点
        map<node*,int> allNode=manager->getNodeMultiplexing();//获取每个node被使用的次数并储存
        int temp=0;
        node* tempnode=NULL;
        for(auto i : allNode)//寻找被使用最多次数的node
        {
            if(i.second>temp)
            {
                temp=i.second;
                tempnode=i.first;
            }
        }
        string type=tempnode->g->getName();
        LEF::cell obj=lp.getCell(type);
        obj.setToLayout(focus[0],focus[1]);
        //进行布局
    }
};
