#include<algorithm>
#include <vector>
#include <iostream>
#include<map>

template<typename T1, typename T2>
T1 &operator<<(T1 &t1, T2 &t2) {
    for (auto x: t2) {
        t1 << x << " \n";
    }
    t1 << std::endl;
    return t1;
}

class Dependency {
    static std::multimap<int, int> dependency;
public:
    static void Build(int V[], int A[], int B[], int numberOfProjects, int numberOfAdditionalRequirements) {
        int *A_start = A;
        int *A_end = A + numberOfAdditionalRequirements;
        int *B_start = B;

        std::transform(A_start, A_end, B_start, std::inserter(dependency, dependency.end()),
                       [](int leadingProject, int dependentProject) {
                           return std::pair<int, int>(dependentProject, leadingProject);
                       });
    }

    static void PrintDependency() {
        for (auto x: dependency) {
            std::cout << x.first << " ->" << x.second << std::endl;
        }
    }

    static bool HasAnyDependency(int project) {
        return dependency.find(project) != dependency.end();
    }

    static int GetDependentProject(int project) {
        if (HasAnyDependency(project))
            return dependency.find(project)->second;
    }

    static int CountOfDependency(int project) {
        if (HasAnyDependency(project))
            return dependency.count(project);
    }
};

std::multimap<int, int> Dependency::dependency;

class Solution {
    static std::map<std::pair<int, int>, int> projectsWithIndexAndProfit;
public:
    static int solution(int V[], int A[], int B[], int numberOfProjects, int numberOfAdditionalRequirements) {
        for (int i = 0; i < numberOfProjects; ++i) {
            for (int j = i + 1; j < numberOfProjects; ++j) {
                int profit = V[i] + V[j];
                auto x = std::make_pair(i, j);
                projectsWithIndexAndProfit[x] = profit;
            }
        }

        Dependency::Build(V, A, B, numberOfProjects, numberOfAdditionalRequirements);
        Dependency::PrintDependency();

        int maxProfit = 0;
        for (auto x: projectsWithIndexAndProfit) {
            int firstProject = x.first.first;
            int secondProject = x.first.second;
            int currentProfit = x.second;
            if (!Dependency::HasAnyDependency(firstProject) && !Dependency::HasAnyDependency(secondProject)) {

                maxProfit = std::max(maxProfit, x.second);
                int maxValueFromIndivualProjects = std::max(V[firstProject], V[secondProject]);
                maxProfit = std::max(maxProfit, maxValueFromIndivualProjects);

            }
            maxProfit = Process(V, maxProfit, currentProfit, secondProject, firstProject);
            maxProfit = Process(V, maxProfit, currentProfit, firstProject, secondProject);
        }
        return 0;
    }

    static int Process(const int *V, int maxProfit, int currentProfit, int firstProject, int secondProject) {
        if (Dependency::GetDependentProject(firstProject) == secondProject
            && !Dependency::HasAnyDependency(secondProject)
            && Dependency::CountOfDependency(firstProject) == 1) {

            maxProfit = std::max(maxProfit, currentProfit);
            int maxValueFromIndivualProjects = std::max(V[firstProject], V[secondProject]);
            maxProfit = std::max(maxProfit, maxValueFromIndivualProjects);
        }
        return maxProfit;
    }

};

int main() {
//    int V[] = {-3, 5, 7, 2, 3};
//    int A[] = {3, 1};
//    int B[] = {2, 4};
//    int V[] = {1, 1, 5};
//    int A[] = {0, 1};
//    int B[] = {2, 2};

    int V[] = {5, 6, 6, 7, -10};
    int A[] = {0, 0, 0, 1, 2, 3};
    int B[] = {1, 2, 3, 3, 1, 2};

    int numberOfProjects = sizeof(V) / sizeof V[0];
    int numberOfAdditionalRequirements = sizeof(A) / sizeof(A[0]);
    Solution::solution(V, A, B, numberOfProjects, numberOfAdditionalRequirements);

    return 0;
}