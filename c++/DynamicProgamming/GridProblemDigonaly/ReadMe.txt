Print all shortest routes in a rectangular grid
Given an M × N rectangular grid, print all routes in the grid that start at the first cell (0, 0) and ends at the last cell (M-1, N-1). We can move down or right or diagonally (down-right), but not up or left.

For example,

Input:

{ 1, 2, 3 }
{ 4, 5, 6 }
{ 7, 8, 9 }

Output:

[ 1, 4, 7, 8, 9 ]
[ 1, 4, 5, 8, 9 ]
[ 1, 4, 5, 6, 9 ]
[ 1, 4, 5, 9 ]
[ 1, 4, 8, 9 ]
[ 1, 2, 5, 8, 9 ]
[ 1, 2, 5, 6, 9 ]
[ 1, 2, 5, 9 ]
[ 1, 2, 3, 6, 9 ]
[ 1, 2, 6, 9 ]
[ 1, 5, 8, 9 ]
[ 1, 5, 6, 9 ]
[ 1, 5, 9 ]
