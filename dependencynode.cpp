#include "dependencynode.h"


using namespace DependencyAnalyzer;

DependencyNode::DependencyNode(const std::string &name, const std::string &path, bool exists, DependencyNode *parent)
{
    m_Parent = parent;
    m_Parent->addChild(this);
    m_Name = name;
    m_Path = path;
    m_Exists = exists;
}

const std::vector<DependencyNode *> & DependencyNode::children() const
{
    return m_Children;
}

const std::string & DependencyNode::name() const
{
    return m_Name;
}

const std::string & DependencyNode::path() const
{
    return m_Path;
}

bool DependencyNode::exists() const
{
    return m_Exists;
}

void DependencyNode::addChild(DependencyNode *child)
{
    m_Children.push_back(child);
}

