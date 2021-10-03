#pragma once
#include "abstractdependencynodefactory.h"


namespace DependencyAnalyzer
{
    class CppDependencyFactory : public AbstractDependencyNodeFactory
    {
    public:
        CppDependencyFactory();
        ~CppDependencyFactory();

        virtual DependencyNode * createNode(string filePath, DependencyNode *parent = nullptr);
        virtual vector<string> extensions() const;

    private:
        static string replace(string text, const char * str1, const char * str2);
    };
}