#pragma once
#include "abstractdependencynodefactory.h"
#include "dependencynode.h"
#include <string>


using namespace std;

namespace DependencyAnalyzer
{
    class DependencyAnalyzerRepository
    {
    public:
        static void addFactory(AbstractDependencyNodeFactory *factory);
        static const vector<AbstractDependencyNodeFactory *> & factories();
        static AbstractDependencyNodeFactory * findFactory(const string &extension);
        static void addIncludePath(const string &path);
        static const vector<string> includePaths();
        static vector<DependencyNode *> dependencies(const string &path);


    private:
        class RepositoryDestroyer
        {
        private:
            DependencyAnalyzerRepository *m_Instance;
        public:
            ~RepositoryDestroyer();
            void initialize(DependencyAnalyzerRepository *repositoryInstance);
        };
        friend class RepositoryDestroyer;


        // Methods and functions
        DependencyAnalyzerRepository();
        ~DependencyAnalyzerRepository();
        static DependencyAnalyzerRepository * instance();


        // Variables
        static DependencyAnalyzerRepository *m_Instance;
        static RepositoryDestroyer m_RepositoryDestroyer;
        static vector<AbstractDependencyNodeFactory *> m_Factories;
        static vector<string> m_IncludePaths;
    };
}