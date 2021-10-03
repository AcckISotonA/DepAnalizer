#pragma once

#include <vector>
#include <string>


namespace DependencyAnalyzer
{
    class DependencyNode
    {
    public:
        DependencyNode(const std::string &name, const std::string &path, bool exists, DependencyNode *parent = nullptr);
        virtual const std::vector<DependencyNode *> & children() const;

        const std::string & name() const;
        const std::string & path() const;
        bool exists() const;


    protected:
        void addChild(DependencyNode *child);


    private:
        DependencyNode *m_Parent;
        std::vector<DependencyNode *> m_Children;
        std::string m_Name;
        std::string m_Path;
        bool m_Exists;
    };
}