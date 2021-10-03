#include <iostream>
#include <vector>
#include <string>
#include "dependencyanalyzerrepository.h"
#include "cppdependencyanalyzer.h"

using namespace std;
using namespace DependencyAnalyzer;

int main(int argc, char *argv[])
{
    DependencyAnalyzerRepository::addFactory(new CppDependencyFactory());

    string path = "";

    bool setIncludeValue = false;
    string args = "";
    for (int argi = 1; argi < argc; argi++)
    {
        string arg = argv[argi];
        args += arg;
        if (arg[0] == '-')
        {
            if (setIncludeValue)
            {
                throw std::logic_error("Invalid argument: " + args);
            }
            setIncludeValue = true;
        }
        else
        {
            if (setIncludeValue)
            {
                DependencyAnalyzerRepository::addIncludePath(arg);
            }
            else
            {
                path = arg;
            }
        }
    }

    if (path.size() == 0)
    {
        throw std::logic_error("Invalid source files directory");
    }

    auto res = DependencyAnalyzerRepository::dependencies(path);
    while (res.size() > 0)
    {
        auto node = res[res.size() - 1];
        res.erase(res.end());
        cout << node->name();
        delete node;
    }
    return 0;
}