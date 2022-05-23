#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "globals.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>

using namespace std;

class Ship
{
public:
    Ship(std::string setName, int setSize, char setType) :name(setName), size(setSize), type(setType)
    {
        id = -1;
        valid = (size >= 0);
    }
    string Name()   const { return name; }
    int Size()      const { return size; }
    void SetID(int setID) { id = setID; }
    int ID()        const { return id; }
    char getType()  const { return type; }
    bool isValid()  const { return valid; }


    int IDFromType(char searchType) const {
        if (id == searchType)
            return id;
        else
            return -1;
    }
private:
    string name;
    int id;
    int size;
    char type;
    bool valid;
};

class GameImpl
{
public:
    GameImpl(int nRows, int nCols);
    int rows() const;
    int cols() const;
    bool isValid(Point p) const;
    Point randomPoint() const;
    bool addShip(int length, char symbol, string name);
    int nShips() const;
    int shipLength(int shipId) const;
    char shipSymbol(int shipId) const;
    string shipName(int shipId) const;
    Player* play(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause);
private:

    std::vector <Ship> ships;

    int m_rows;
    int m_cols;
};




void waitForEnter()
{
    cout << "Press enter to continue: ";
    cin.ignore(10000, '\n');
}

GameImpl::GameImpl(int nRows, int nCols)
{
    if (nRows > MAXROWS) {
        nRows = MAXROWS;
    }
    if (nCols > MAXCOLS) {
        nCols = MAXCOLS;
    }
    m_rows = nRows;
    m_cols = nCols;
}

int GameImpl::rows() const
{
    return m_rows;  
}

int GameImpl::cols() const
{
    return m_cols;  
}

bool GameImpl::isValid(Point p) const
{
    return p.r >= 0 && p.r < rows() && p.c >= 0 && p.c < cols();
}

Point GameImpl::randomPoint() const
{
    return Point(randInt(rows()), randInt(cols()));
}

bool GameImpl::addShip(int length, char symbol, string name)
{
    Ship ship = Ship(name, length, symbol);
    if (ship.isValid()) {
        ship.SetID(ships.size());
        ships.push_back(ship);
        return true;
    }
    return false;
}

int GameImpl::nShips() const
{
    return ships.size();
}

int GameImpl::shipLength(int shipId) const
{
    if (shipId < ships.size() && shipId >= 0) {
        return ships[shipId].Size();
    }
    return -1;
}

char GameImpl::shipSymbol(int shipId) const
{
    if (shipId < ships.size() && shipId >= 0) {
        return ships[shipId].getType();
    }
    return '?';  
}

string GameImpl::shipName(int shipId) const
{
    if (shipId < ships.size() && shipId >= 0) {
        return ships[shipId].Name();
    }
    return "";  
}

Player* GameImpl::play(Player* p1, Player* p2, Board& b1, Board& b2, bool shouldPause)
{

    Player* winner = p1;
    if (!(p1->placeShips(b1)) || !(p2->placeShips(b2)))
    {
        return nullptr;
    }
    bool validShot = false;
    bool hitShip = false;
    bool destroyedShip = false;
    int shipID = -1;

    int Player1Ships = p1->game().nShips();
    int Player2Ships = p2->game().nShips();

    while (!b1.allShipsDestroyed() && !b2.allShipsDestroyed()) {//now its same as update in unity
        cout << p1->name() << "'s turn. "<<endl;
        b2.display(p1->isHuman());
        cout<<"Board for " << p2->name() << "" << endl; 

        Point P1Attack = p1->recommendAttack();

        if (b2.attack(P1Attack, hitShip, destroyedShip, shipID))
        {
            if (!hitShip)
            {
                cout << p1->name() << " attacked " << "(" << P1Attack.r << "," << P1Attack.c << ")" << " and missed, resulting in: " << endl;
            }
            else
            {
                if (destroyedShip)
                {
                    if (shipID < 0) {
                        int i = 0;
                    }
                    cout << p1->name() << " attacked " << "(" << P1Attack.r << "," << P1Attack.c << ")" << " and destroyed the " << p2->game().shipName(shipID) << ", resulting in: " << endl;
                    
                    Player2Ships--;

                    if (Player2Ships == 0)
                    {
                        b2.display(p1->isHuman());

                        break;
                    }
                }
                else
                {
                    cout << p1->name() << " attacked " << "(" << P1Attack.r << "," << P1Attack.c << ")" << " and hit something, resulting in: " << endl;
                }
            }
            p1->recordAttackResult(P1Attack, validShot, hitShip, destroyedShip, shipID);
            p2->recordAttackByOpponent(P1Attack);


        }
        else {
            cout << p1->name() << " wasted a shot at " << "(" << P1Attack.r << "," << P1Attack.c << ")" << endl;
        }


        b2.display(p1->isHuman());

        if (shouldPause) {
            if (p1->isHuman()) {
                waitForEnter();
                cin.ignore(10000, '\n');
            }
            else {
                waitForEnter();
            }
        }

        cout << endl;
        cout << p2->name() << "'s turn. "<<endl;
        b1.display(p2->isHuman());
        cout << "Board for " << p1->name() << ": " << endl;

        validShot = false;
        hitShip = false;
        destroyedShip = false;

        Point P2Attack = p2->recommendAttack();
        if (b1.attack(P2Attack, hitShip, destroyedShip, shipID))
        {
            if (!hitShip)
            {
                cout << p2->name() << " attacked " << "(" << P2Attack.r << "," << P2Attack.c << ")" << " and missed, resulting in: " << endl;
            }
            else
            {
                if (destroyedShip)
                {
                    if (shipID < 0) {
                        int i = 0;
                    }
                    cout << p2->name() << " attacked " << "(" << P2Attack.r << "," << P2Attack.c << ")" << " and destroyed the " << p1->game().shipName(shipID) << ", resulting in: " << endl;
                    Player1Ships--;

                    if (Player1Ships == 0)
                    {
                        b1.display(p2->isHuman());
                        break;
                    }
                }
                else
                {
                    cout << p2->name() << " attacked " << "(" << P2Attack.r << "," << P2Attack.c << ")" << " and hit something, resulting in: " << endl;
                }
            }
            p2->recordAttackResult(P2Attack, validShot, hitShip, destroyedShip, shipID);
            p1->recordAttackByOpponent(P2Attack);


        }
        else
        {
            cout << p2->name() << " wasted a shot at " << "(" << P2Attack.r << "," << P2Attack.c << ")" << endl;
        }
        b1.display(p2->isHuman());

        if (shouldPause) {
            if (p2->isHuman()) {
                waitForEnter();
                cin.ignore(10000, '\n');
            }
            else {
                waitForEnter();
            }
        }
    }

    //Winning
    //both are human, but p1 is the winner
    Player* loser = winner;
    cout << endl;
    cout << "Results are OUT!" << endl;
    if (Player2Ships == 0 && Player1Ships > 0) {
        winner = p1;
        loser = p2;
        cout << "Winner's Board" << endl;
        if (loser->isHuman()) {
            b1.display(false);
        }
    }
    else if (Player1Ships == 0 && Player2Ships > 0) {
        winner = p2;
        loser = p1;
        cout << "Winner's Board" << endl;
        if (loser->isHuman()) {
            b2.display(false);
        }
    }
    cout << winner->name() << " wins!" << endl;
    ships.clear();
    return winner;
}

//******************** Game functions *******************************

// These functions for the most part simply delegate to GameImpl's functions.
// You probably don't want to change any of the code from this point down.

Game::Game(int nRows, int nCols)
{
    if (nRows < 1 || nRows > MAXROWS)
    {
        cout << "Number of rows must be >= 1 and <= " << MAXROWS << endl;
        exit(1);
    }
    if (nCols < 1 || nCols > MAXCOLS)
    {
        cout << "Number of columns must be >= 1 and <= " << MAXCOLS << endl;
        exit(1);
    }
    m_impl = new GameImpl(nRows, nCols);
}

Game::~Game()
{
    delete m_impl;
}

int Game::rows() const
{
    return m_impl->rows();
}

int Game::cols() const
{
    return m_impl->cols();
}

bool Game::isValid(Point p) const
{
    return m_impl->isValid(p);
}

Point Game::randomPoint() const
{
    return m_impl->randomPoint();
}

bool Game::addShip(int length, char symbol, string name)
{
    if (length < 1)
    {
        cout << "Bad ship length " << length << "; it must be >= 1" << endl;
        return false;
    }
    if (length > rows() && length > cols())
    {
        cout << "Bad ship length " << length << "; it won't fit on the board"
            << endl;
        return false;
    }
    if (!isascii(symbol) || !isprint(symbol))
    {
        cout << "Unprintable character with decimal value " << symbol
            << " must not be used as a ship symbol" << endl;
        return false;
    }
    if (symbol == 'X' || symbol == '.' || symbol == 'o')
    {
        cout << "Character " << symbol << " must not be used as a ship symbol"
            << endl;
        return false;
    }
    int totalOfLengths = 0;
    for (int s = 0; s < nShips(); s++)
    {
        totalOfLengths += shipLength(s);
        if (shipSymbol(s) == symbol)
        {
            cout << "Ship symbol " << symbol
                << " must not be used for more than one ship" << endl;
            return false;
        }
    }
    if (totalOfLengths + length > rows() * cols())
    {
        cout << "Board is too small to fit all ships" << endl;
        return false;
    }
    return m_impl->addShip(length, symbol, name);
}

int Game::nShips() const
{
    return m_impl->nShips();
}

int Game::shipLength(int shipId) const
{
    assert(shipId >= 0 && shipId < nShips());
    return m_impl->shipLength(shipId);
}

char Game::shipSymbol(int shipId) const
{
    assert(shipId >= 0 && shipId < nShips());
    return m_impl->shipSymbol(shipId);
}

string Game::shipName(int shipId) const
{
    assert(shipId >= 0 && shipId < nShips());
    return m_impl->shipName(shipId);
}

Player* Game::play(Player* p1, Player* p2, bool shouldPause)
{
    if (p1 == nullptr || p2 == nullptr || nShips() == 0)
        return nullptr;
    Board b1(*this);
    Board b2(*this);
    return m_impl->play(p1, p2, b1, b2, shouldPause);
}

