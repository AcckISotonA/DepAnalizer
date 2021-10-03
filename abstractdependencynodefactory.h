#pragma once
#include <vector>
#include <string>
#include "dependencynode.h"


using namespace std;

namespace DependencyAnalyzer
{
    class AbstractDependencyNodeFactory
    {
    public:
        virtual DependencyNode * createNode(string filePath, DependencyNode *parent = nullptr) = 0;
        virtual vector<string> extensions() const = 0;

        AbstractDependencyNodeFactory & operator=(const AbstractDependencyNodeFactory&) = delete;
    };
}