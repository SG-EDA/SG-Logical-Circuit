#include <iostream>
#include "node.h"

list<node*> nodeManager::allNode;
vector<line*> nodeManager::allInput;
vector<line*> nodeManager::allOutput;

int main()
{
    line A=line("A");
    line B=line("B");
    line C=line("C");
    line D=line("D");

    nodeManager::addInputLine(&A);
    nodeManager::addInputLine(&B);
    nodeManager::addInputLine(&C);
    nodeManager::addInputLine(&D);

    node nn1(new notGate());
    nn1.addInputLine(&A);
    node nn2(new notGate());
    nn2.addInputLine(&B);
    node nn3(new notGate());
    nn3.addInputLine(&C);
    node nn4(new notGate());
    nn4.addInputLine(&D);

    line NA=line(&nn1);
    line NB=line(&nn2);
    line NC=line(&nn3);
    line ND=line(&nn4);

    node n1(new andGate());
    n1.addInputLine(&NB);
    n1.addInputLine(&NC);
    line NBNC=line(&n1);
    node n2(new andGate());
    n2.addInputLine(&NBNC);
    n2.addInputLine(&ND);
    line NBNCND=line(&n2);

    node n3(new andGate());
    n3.addInputLine(&B);
    n3.addInputLine(&D);
    line BD=line(&n3);

    node n4(new orGate());
    n4.addInputLine(&NBNCND);
    n4.addInputLine(&BD);
    line NBNCND_BD=line(&n4);

    node n5(new andGate());
    n5.addInputLine(&NA);
    n5.addInputLine(&NBNCND_BD);
    line i1=line(&n5);

    node n6(new andGate());
    n6.addInputLine(&A);
    n6.addInputLine(&NB);
    line i2=line(&n6);

    node n7(new andGate());
    n7.addInputLine(&C);
    n7.addInputLine(&D);
    line i3=line(&n7);

    node n8(new orGate());
    n8.addInputLine(&i1);
    n8.addInputLine(&i2);
    line r1=line(&n8);

    node n9(new orGate());
    n9.addInputLine(&r1);
    n9.addInputLine(&i3);
    line r2=line(&n9);

    nodeManager::addOutputNode(&r2);
    nodeManager::trueTable();
    r2.stru();
    nodeManager::gateNum();
}
