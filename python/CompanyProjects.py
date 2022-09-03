from collections import defaultdict


def BuildDependency(A, B):
    global dependency
    for leader, dependent in zip(A, B):
        dependency[dependent].append(leader)


def CheckDependency(project1, project2):
    global dependency
    dependentList = dependency.get(project1)
    return dependentList is not None and project2 in dependentList and len(dependentList) == 1


def CheckIfProjectsCanCompleted(firstProject, secondProject):
    return (CheckIfNonDependentProjects(firstProject, secondProject)
            or CheckDependency(firstProject, secondProject)
            or CheckDependency(secondProject, firstProject))


def CheckIfNonDependentProjects(firstProject, secondProject):
    global dependency
    return dependency.get(firstProject) is None and dependency.get(secondProject) is None


dependency = defaultdict(list)


def GetMaxProfitForEligibleProjects():
    maxProfit = 0
    for firstProject in range(len(V) - 1):
        for secondProject in range(firstProject + 1, len(V)):
            if CheckIfProjectsCanCompleted(firstProject, secondProject):
                maxProfit = max(V[firstProject], V[secondProject], V[firstProject] + V[secondProject])
    return maxProfit


if __name__ == "__main__":
    # V = [-3, 5, 7, 2, 3]
    # A = [3, 1]
    # B = [2, 4]
    # V = [1, 1, 5]
    # A = [0, 1]
    # B = [2, 2]
    V = [5, 6, 6, 7, -10]
    A = [0, 0, 0, 1, 2, 3]
    B = [1, 2, 3, 3, 1, 2]
    BuildDependency(A, B)
    maxProfit = GetMaxProfitForEligibleProjects()
    print(maxProfit)
