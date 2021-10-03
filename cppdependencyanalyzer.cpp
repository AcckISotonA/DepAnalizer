#include "cppdependencyanalyzer.h"
#include <fstream>
#include <iostream>
#include <regex>


using namespace DependencyAnalyzer;

CppDependencyFactory::CppDependencyFactory()
{
}

CppDependencyFactory::~CppDependencyFactory()
{
}

DependencyNode * CppDependencyFactory::createNode(string filePath, DependencyNode *parent)
{
    DependencyNode *result = nullptr;

    ifstream file(filePath);
    string line = "";
    string sourceCode = "";
    bool multilineComment = false;
    while (file >> line)
    {
        regex regexp("^(#include \".*\")|^(#include <.*>)");
        smatch matches;
        regex_search(line, matches, regexp);
        for (auto match : matches)
        {
            string matchStr = match.str();
            matchStr = matchStr.replace(matchStr.begin(), matchStr.end(), "#include ", "");
            matchStr = matchStr.replace(matchStr.begin(), matchStr.end(), "\"", "");
            matchStr = matchStr.replace(matchStr.begin(), matchStr.end(), "\"", "");
            matchStr = matchStr.replace(matchStr.begin(), matchStr.end(), "\"", "");
        }
        // Search single line comment
        size_t start = line.find("", 0);
        if (start != string::npos)
        {
            // Remove single line comment
            line.erase(start);
        }

        // Search multiline comment
        size_t start = line.find("/*", 0);
        if (start != string::npos)
        {
            // Remove single line comment
            line.erase(start);
        }

        size_t end = 0;
        
    }
    if (file.is_open())
    {
        file.close();
    }

    return result;
}

vector<string> CppDependencyFactory::extensions() const
{
    return vector<string> {".h", ".cpp", ".hpp"};
}

string CppDependencyFactory::replace(string text, const char * str1, const char * str2)
{
    return text.replace(text.begin(), text.end(), str1, str2);
}