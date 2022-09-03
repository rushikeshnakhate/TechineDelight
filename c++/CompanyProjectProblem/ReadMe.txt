Question: A Company Is Planning N Projects, Numbered From 0 To N-1. Completing The K-Th Project Will Bring Value V[K] To The Company. For Some Projects There May Be Additional Requirements - The L-Th Requirement States That Before Starting Project B[L], Project A[L] Should Be Completed. There Are M Such Requirements. The Company Has Enough Resources For At Most Two
This problem has been solved!
You’ll get a detailed solution from a subject matter expert that helps you learn core concepts.

See answer
A company is planning N projects, numbered from 0 to N-1. Completing the K-th project will bring value V[K] to the company. For some projects there may be additional requirements - the L-th requirement states that before starting project B[L], project A[L] should be completed. There are M such requirements.

The company has enough resources for at most two projects to be completed. If two projects are chosen, they will be completed one by one (in sequential order) and the total value they bring to the company is the sum of their individual values. What is the highest value that a valid choice of projects can bring to the company?

Write a function:

class Solution { public int solution(int[] V, int[] A, int[] B); }

that, given array V of N integers and two arrays A and B of M integers each, returns the maximum value that the company may gain by completing at most two possible projects.

Examples:

1. Given V = [-3, 5, 7, 2, 3], A = [3, 1] and B = [2, 4], the function should return 9.
 This can be achieved by completing project 3 (with value 2) first and then project 2 (with value 7).

2. Given V = [1, 1, 5], A = [0, 1] and B = [2, 2], the function should return 2.

3. Given V = [5, 6, 6, 7, -10] and A = [0, 0, 0, 1, 2, 3] and B = [1, 2, 3, 3, 1, 2], the function should return 5.
The project that are possible to be completed are 0 and 4. As project 4 would bring negative value to the company, it is optimal to do only project 0. The structure of dependencies of projects 1, 2 and 3 form a cycle, so none of them can be completed in a valid choice of projects.

Write an efficient algorithm for the following assumptions:

- N is an integer within the range [1..100,000];
- M is an integer within the range [0..100,000];
- each element of array V is an integer within the range [-1,000,000,000..1,000,000,000];
- each element of arrays A and B is an integer within the range [0..N-1];
- a project may not require itself to be completed (A[K] != B[K]);
- projects’ requirements do not repeat.