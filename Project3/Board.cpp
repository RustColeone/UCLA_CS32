#include "Board.h"
#include "Game.h"
#include "globals.h"
#include <iostream>

using namespace std;

class BoardImpl
{
public:
    BoardImpl(const Game& g);
    void clear();
    void block();
    void unblock();
    bool placeShip(Point topOrLeft, int shipId, Direction dir);
    bool unplaceShip(Point topOrLeft, int shipId, Direction dir);
    void display(bool shotsOnly) const;
    bool attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId);
    bool allShipsDestroyed() const;

private:
    // TODO:  Decide what private members you need.  Here's one that's likely
    //        to be useful:
    const Game& m_game;
    vector<vector<char>> board;

    vector<int> shipsInGame;
    vector<int> shipsRemoved;

    int cols;
    int rows;
};

BoardImpl::BoardImpl(const Game& g)
    : m_game(g)
{
    cols = g.cols();
    rows = g.rows();
    for (int i = 0; i < rows; i++) {
        vector<char> temp;
        for (int j = 0; j < cols; j++) {
            temp.push_back('.');
        }
        board.push_back(temp);
    }
}

void BoardImpl::clear()
{
    for (int r = 0; r < cols; r++)
        for (int c = 0; c < rows; c++)
            board[r][c] = '.';//set it back to 0 or means unblock the cell.

    shipsInGame.clear();
    shipsRemoved.clear();
}

void BoardImpl::block()
{
    for (int r = 0; r < m_game.rows(); r++)
        for (int c = 0; c < m_game.cols(); c++)
            if (randInt(2) == 0)//50 percent chance
                board[r][c] = '#';
}

void BoardImpl::unblock()
{
    for (int r = 0; r < m_game.rows(); r++)
        for (int c = 0; c < m_game.cols(); c++)
            if (board[r][c] == '#')
                board[r][c] = '.';
}

bool BoardImpl::placeShip(Point topOrLeft, int shipId, Direction dir)
{
    //When out of range, return
    if (topOrLeft.r >= rows || topOrLeft.c >= cols || topOrLeft.c < 0 || topOrLeft.r < 0)
        return false;

    //when ship id is out of range
    if (shipId >= m_game.nShips())
        return false;

    //When ship is horizontal, check size of row (number of coloum)
    if (dir == HORIZONTAL)
    {
        if (m_game.shipLength(shipId) + topOrLeft.c > cols)
            return false;
        int r = topOrLeft.r;
        for (int c = topOrLeft.c; c < m_game.shipLength(shipId) + topOrLeft.c; c++)
            if (board[r][c] != '.') //not enough space
                return false;

        for (int i = 0; i < m_game.nShips(); i++)
            if (shipId == i)//if valid ship
            {
                for (int j = 0; j < shipsInGame.size(); j++)//find all ships
                    if (shipsInGame[j] == shipId)//if ship exists
                        return false;//can't place repeated ship
                shipsInGame.push_back(i);
            }

        for (int c = topOrLeft.c; c < m_game.shipLength(shipId) + topOrLeft.c; c++)
            board[r][c] = m_game.shipSymbol(shipId);//place ship

    }
    else if (dir == VERTICAL)//same as horizontal
    {
        if (m_game.shipLength(shipId) + topOrLeft.r > rows)
            return false; // out of range exception

        int c = topOrLeft.c;
        for (int r = topOrLeft.r; r < m_game.shipLength(shipId) + topOrLeft.r; r++)
            if (board[r][c] != '.') 
                return false;

        for (int i = 0; i < m_game.nShips(); i++)
            if (shipId == i)
            {
                for (int j = 0; j < shipsInGame.size(); j++)
                    if (shipsInGame[j] == shipId)
                        return false;
                shipsInGame.push_back(i);
            }

        for (int r = topOrLeft.r; r < m_game.shipLength(shipId) + topOrLeft.r; r++)
            board[r][c] = m_game.shipSymbol(shipId);
    }

    return true; 
    //at this point if you haven't return by an exception already
    //it must means that placement is successful
}

bool BoardImpl::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    if (topOrLeft.r >= rows || topOrLeft.c >= cols || topOrLeft.c < 0 || topOrLeft.r < 0)
        return false;

    for (int i = 0; i < shipsInGame.size(); i++)
        if (shipsInGame[i] == shipId)
            return false;//there's no such ship

    char shipSymbol = m_game.shipSymbol(shipId);

    if (dir == HORIZONTAL)
    {
        if (m_game.shipLength(shipId) + topOrLeft.c > cols)
            return false;//out of range exception
        int r = topOrLeft.r;
        for (int c = topOrLeft.c; c < m_game.shipLength(shipId) + topOrLeft.c; c++) 
            if (board[r][c] != shipSymbol)
                return false;
        for (int c = topOrLeft.c; c < m_game.shipLength(shipId) + topOrLeft.c; c++) 
            board[r][c] = '.';//can remove
        display(false);
        shipsInGame.pop_back();
    }
    else if(dir == VERTICAL)  
    {
        if (m_game.shipLength(shipId) + topOrLeft.r > rows)
            return false;

        int c = topOrLeft.c;
        for (int r = topOrLeft.r; r < m_game.shipLength(shipId) + topOrLeft.r; r++)
            if (board[r][c] != shipSymbol)
                return false;
        for (int r = topOrLeft.r; r < m_game.shipLength(shipId) + topOrLeft.r; r++)
            board[r][c] = '.';
        display(false);
        shipsInGame.pop_back();
    }
    return true;
}

void BoardImpl::display(bool shotsOnly) const
{
    cout << "  ";
    for (int i = 0; i < cols; i++) {
        cout << i;
    }
    cout << endl;

    for (int r = 0; r < rows; r++) //1 space with number of rows
    {
        cout << r << " ";
        for (int c = 0; c < cols; c++) //should be 2 spaces due to number of cols
        {
            if (shotsOnly) {
                if (board[r][c] == 'X' || board[r][c] == 'o') {
                    cout << board[r][c];
                }
                else {
                    cout << ".";
                }
            }
            else {
                cout << board[r][c];
            }
        }
        cout << endl;
    }
}

bool BoardImpl::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    if (p.r < 0 || p.r > rows || p.c < 0 || p.c > cols)
        return false;//where are you point at?

    if (board[p.r][p.c] == 'X')
        return false;//Already hit this

    if (board[p.r][p.c] == '.')
    {
        board[p.r][p.c] = 'o';
        shotHit = false; //hit and missed
        return true;
    }
    else if (board[p.r][p.c] != 'o' || board[p.r][p.c] != 'X' || board[p.r][p.c] != '#') {
        char temp = board[p.r][p.c];
        for (int i = 0; i < shipsInGame.size(); i++) {
            if (m_game.shipSymbol(shipsInGame[i]) == temp) {
                shotHit = true;
                shipId = shipsInGame[i];
            }
        }
        board[p.r][p.c] = 'X';
        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                if (temp == board[r][c])
                {
                    //loop through the entire board to see if any of the ship that's left inside
                    shipDestroyed = false;
                    return true;
                }
        shipDestroyed = true;
        for (int i = 0; i < shipsInGame.size(); i++) {
            if (m_game.shipSymbol(shipsInGame[i]) == temp) {
                shipId = shipsInGame[i];
                shipsRemoved.push_back(shipId);
            }
        }
    }
    return true;
}

bool BoardImpl::allShipsDestroyed() const
{
    if (shipsInGame.size() == shipsRemoved.size()) {
        return true;
    }
    return false;
}

//******************** Board functions ********************************

// These functions simply delegate to BoardImpl's functions.
// You probably don't want to change any of this code.

Board::Board(const Game& g)
{
    m_impl = new BoardImpl(g);
}

Board::~Board()
{
    delete m_impl;
}

void Board::clear()
{
    m_impl->clear();
}

void Board::block()
{
    return m_impl->block();
}

void Board::unblock()
{
    return m_impl->unblock();
}

bool Board::placeShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->placeShip(topOrLeft, shipId, dir);
}

bool Board::unplaceShip(Point topOrLeft, int shipId, Direction dir)
{
    return m_impl->unplaceShip(topOrLeft, shipId, dir);
}

void Board::display(bool shotsOnly) const
{
    m_impl->display(shotsOnly);
}

bool Board::attack(Point p, bool& shotHit, bool& shipDestroyed, int& shipId)
{
    return m_impl->attack(p, shotHit, shipDestroyed, shipId);
}

bool Board::allShipsDestroyed() const
{
    return m_impl->allShipsDestroyed();
}
