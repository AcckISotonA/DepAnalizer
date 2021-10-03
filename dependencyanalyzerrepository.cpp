#include "dependencyanalyzerrepository.h"
#include <filesystem>
#include <set>
#include "containerhelper.h"
#include <iostream>


using namespace DependencyAnalyzer;
using namespace std::filesystem;

DependencyAnalyzerRepository * DependencyAnalyzerRepository::m_Instance = nullptr;
DependencyAnalyzerRepository::RepositoryDestroyer DependencyAnalyzerRepository::m_RepositoryDestroyer;
vector<AbstractDependencyNodeFactory *> DependencyAnalyzerRepository::m_Factories {};
vector<string> DependencyAnalyzerRepository::m_IncludePaths {};

void DependencyAnalyzerRepository::addFactory(AbstractDependencyNodeFactory *factory)
{
    m_Factories.push_back(factory);
}

const vector<AbstractDependencyNodeFactory *> & DependencyAnalyzerRepository::factories()
{
    return m_Factories;
}

AbstractDependencyNodeFactory * DependencyAnalyzerRepository::findFactory(const string &extension)
{
    for (auto *analyzer : m_Factories)
    {
        if (contains(analyzer->extensions(), extension))
        {
            return analyzer;
        }
    }

    return nullptr;
}

void DependencyAnalyzerRepository::addIncludePath(const string &path)
{
    m_IncludePaths.push_back(path);
}

const vector<string> DependencyAnalyzerRepository::includePaths()
{
    return m_IncludePaths;
}

vector<DependencyNode *> DependencyAnalyzerRepository::dependencies(const string &path)
{
    vector<DependencyNode *> result {};

    for (const auto & entry : directory_iterator(path))
    {
        auto * factory = findFactory(entry.path().extension().string());
        if (factory)
        {
            DependencyNode *node = factory->createNode(entry.path().string());
            if (node)
            {
                result.push_back(node);
            }
        }
    }

    return result;
}

DependencyAnalyzerRepository::DependencyAnalyzerRepository()
{
}
    
DependencyAnalyzerRepository::~DependencyAnalyzerRepository()
{
}

DependencyAnalyzerRepository * DependencyAnalyzerRepository::instance()
{
    if (!m_Instance)
    {
        m_Instance = new DependencyAnalyzerRepository();
        m_RepositoryDestroyer.initialize(m_Instance);
    }

    return m_Instance;
}

DependencyAnalyzerRepository::RepositoryDestroyer::~RepositoryDestroyer()
{
    delete m_Instance;
}

void DependencyAnalyzerRepository::RepositoryDestroyer::initialize(DependencyAnalyzerRepository *repositoryInstance)
{
    m_Instance = repositoryInstance;
}
