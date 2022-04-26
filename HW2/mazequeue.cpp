
#include <iostream>
#include <queue>

using namespace std;

bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise


class Coord
{
public:
    Coord(int rr, int cc) : m_row(rr), m_col(cc) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
private:
    int m_row;
    int m_col;
};



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
}



bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {

    queue<Coord> coordQueue;
    Coord startCoord(sr, sc);
    coordQueue.push(startCoord);
    Coord endCoord = Coord(er, ec);

    
    //Maze [which row] [which colum];
    maze[sr][sc] = '-';

    while (!coordQueue.empty()) {

        Coord current = coordQueue.front();
        int r = current.r(), c = current.c();
        char currentMaze = maze[r][c];

        //For testing only
        /*
        cout << "r = " << r;
        cout << ", c = " << current.c();
        cout<< " current maze" << maze[r][c] << endl;
        */
        /*
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                if(i == r && j == c)
                    cout<<"o";
                else if(i == er && j == ec)
                    cout<<"!";
                else
                    cout<<maze[i][j];
                cout<<" ";
            }
            cout<<endl;
        }
        */

        coordQueue.pop();

        if (r == er && c == ec) {
            //Since they are at the same coordinate, that means a solution
            return true;
        }
        if (c > 0 && maze[r][c - 1] == '.') {
            //This means the LEFT of this maze is a path
            maze[r][c - 1] = '-';
            coordQueue.push(Coord(r, c - 1));
        }
        if (r > 0 && maze[r - 1][c] == '.') {
            //This means the UP of this maze is a path
            maze[r - 1][c] = '-';
            coordQueue.push(Coord(r - 1, c));
        }
        if (c < 9 && maze[r][c + 1] == '.') {
            //This means the RIGHT of this maze is a path
            maze[r][c + 1] = '-';
            coordQueue.push(Coord(r, c + 1));
        }
        if (r < 9 && maze[r + 1][c] == '.') {
            //This means the DOWN of this maze is a path
            maze[r + 1][c] = '-';
            coordQueue.push(Coord(r + 1, c));
        }
    }

    return false;
}
/*
Push the starting coordinate(sr, sc) onto the coordinate stackand
update maze[sr][sc] to indicate that the algorithm has encountered
it(i.e., set maze[sr][sc] to have a value other than '.').
While the stack is not empty,
{ Pop the top coordinate off the stack.This gives you the current
        (r,c) location that your algorithm is exploring.
    If the current(r,c) coordinate is equal to the ending coordinate,
        then we've solved the maze so return true!
    Check each place you can move from the current cell as follows :
        If you can move WEST and haven't encountered that cell yet,
            then push the coordinate(r,c - 1) onto the stack and update
            maze[r][c - 1] to indicate the algorithm has encountered it.
        If you can move NORTH and haven't encountered that cell yet,
            then push the coordinate(r - 1,c) onto the stack and update
            maze[r - 1][c] to indicate the algorithm has encountered it.
        If you can move EAST and haven't encountered that cell yet,
            then push the coordinate(r,c + 1) onto the stack and update
            maze[r][c + 1] to indicate the algorithm has encountered it.
        If you can move SOUTH and haven't encountered that cell yet,
            then push the coordinate(r + 1,c) onto the stack and update
            maze[r + 1][c] to indicate the algorithm has encountered it.
}
There was no solution, so return false*/