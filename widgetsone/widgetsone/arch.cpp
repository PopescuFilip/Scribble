#include "arch.h"

Arch::Arch():
    m_firstNode(nullptr),
    m_secondNode(nullptr)
{}

Arch::Arch(Node *firstNode, Node *secondNode)
{
    m_firstNode = firstNode;
    m_secondNode = secondNode;
}

Arch::Arch(const Arch & other)
{
    m_firstNode = other.m_firstNode;
    m_secondNode = other.m_secondNode;
}

Node *Arch::getFirstNode() const
{
    return m_firstNode;
}

Node *Arch::getSecondNode() const
{
    return m_secondNode;
}

bool Arch::operator ==(const Arch &arch) const
{
    return this->m_firstNode == arch.m_firstNode and this->m_secondNode == arch.m_secondNode;
}
