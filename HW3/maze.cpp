#include <iostream>
using namespace std;

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

int main()
{
    char maze[10][10] = {
        { 'X','X','X','X','X','X','X','X','X','X' },
        { 'X','.','X','.','.','.','X','.','.','X' },
        { 'X','.','X','.','X','X','X','X','.','X' },
        { 'X','.','X','.','.','X','.','X','.','X' },
        { 'X','.','X','X','.','X','.','.','.','X' },
        { 'X','.','.','.','.','.','.','X','X','X' },
        { 'X','.','X','X','X','X','.','X','.','X' },
        { 'X','.','.','.','.','X','X','X','.','X' },
        { 'X','.','X','.','.','X','.','.','.','X' },
        { 'X','X','X','X','X','X','X','X','X','X' }
    };

    if (pathExists(maze, 5, 6, 8, 1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
    return 0;
}

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {

    if (sr == er && sc == ec) {
        //Since they are at the same coordinate, that means a solution
        return true;
    }

    //Maze [which row] [which colum];
    maze[sr][sc] = '-';

    if (sc > 0 && maze[sr][sc - 1] == '.') {
        //This means the LEFT of this maze is a path
        maze[sr][sc - 1] = '-';
        if (pathExists(maze, sr, sc - 1, er, ec)) {
            //If we already found a path there's no need to continue
            return true;
        }
    }
    if (sr > 0 && maze[sr - 1][sc] == '.') {
        //This means the UP of this maze is a path
        maze[sr - 1][sc] = '-';
        if (pathExists(maze, sr - 1, sc, er, ec)) {
            //If we already found a path there's no need to continue
            return true;
        }
    }
    if (sc < 9 && maze[sr][sc + 1] == '.') {
        //This means the RIGHT of this maze is a path
        maze[sr][sc + 1] = '-';
        if (pathExists(maze, sr, sc + 1, er, ec)) {
            //If we already found a path there's no need to continue
            return true;
        }
    }
    if (sr < 9 && maze[sr + 1][sc] == '.') {
        //This means the DOWN of this maze is a path
        maze[sr + 1][sc] = '-';
        if (pathExists(maze, sr + 1, sc, er, ec)) {
            //If we already found a path there's no need to continue
            return true;
        }
    }
    //Since this is reached that means there's no path, so false
    return false;
}