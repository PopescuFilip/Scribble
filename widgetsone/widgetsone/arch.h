#pragma once
#include "Node.h"

class Arch
{
private:
    Node* m_firstNode;
    Node* m_secondNode;

public:
    Arch();
    Arch(Node* firstNode, Node* secondNode);
    Arch(const Arch& a);
    Node* getFirstNode()const;
    Node* getSecondNode()const;
    bool operator ==(const Arch& other)const;
};


